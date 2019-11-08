#pragma once
#include <algorithm>
#include <new>

template <typename T>
class CMyArray
{
public:
	template <typename Type>
	class CMyIterator
	{
		friend CMyArray;

	public:
		using self_type = CMyIterator;
		using value_type = Type;
		using reference = value_type&;
		using pointer = value_type*;
		using iterator_category = std::random_access_iterator_tag;
		using difference_type = ptrdiff_t;

		CMyIterator() = default;

		CMyIterator(const CMyIterator& it)
			: ptr(it.ptr)
		{
		}

		bool operator==(const self_type& right) const
		{
			return m_ptr == right.m_ptr;
		}

		bool operator!=(const self_type& right) const
		{
			return !(*this == right);
		}

		pointer operator->() const
		{
			return &m_ptr;
		}

		reference operator*() const
		{
			return *m_ptr;
		}

		reference operator[](difference_type n) const
		{
			auto tmp = *this;
			tmp += n;
			return *tmp;
		}

		reference operator+=(difference_type n)
		{
			m_ptr += n;
			return *this;
		}

		reference operator-=(difference_type n)
		{
			return *this += -n;
		}

		self_type& operator++()
		{
			++m_ptr;
			return *this;
		}

		const self_type operator++(int)
		{
			auto tmpIt(*this);
			++*this;
			return tmpIt;
		}

		self_type& operator--()
		{
			--m_ptr;
			return *this;
		}

		const self_type operator--(int)
		{
			auto tmpIt(*this);
			--*this;
			return tmpIt;
		}

	private:
		CMyIterator(Type* ptr);
		Type* m_ptr = nullptr;
	};

	typedef CMyIterator<T> myIterator;
	typedef CMyIterator<const T> myConstIterator;
	typedef std::reverse_iterator<myIterator> myReverseIterator;
	typedef std::reverse_iterator<myConstIterator> myReverseConstIterator;

	CMyArray() = default;
	~CMyArray();
	CMyArray(const CMyArray& arr);
	CMyArray& operator=(const CMyArray& arr);
	CMyArray(CMyArray&& arr);
	CMyArray& operator=(CMyArray&& arr);
	void Append(const T& value);
	void Clear();
	void Resize(size_t size);
	T& GetBack();
	const T& GetBack() const;
	size_t GetSize() const;
	size_t GetCapacity() const;
	const T& operator[](size_t index) const;
	T& operator[](size_t index);
	myIterator begin();
	myIterator end();
	myConstIterator begin() const;
	myConstIterator end() const;
	myReverseIterator rbegin();
	myReverseIterator rend();
	myReverseConstIterator rbegin() const;
	myReverseConstIterator rend() const;

private:
	void ResizeCapacity(size_t capacity);
	// удалять элементы
	static void DeleteItems(T* begin, T* end);

	// Копирует элементы из текущего вектора в to, возвращает newEnd
	static void CopyItems(const T* srcBegin, T* srcEnd, T* const dstBegin, T*& dstEnd);
	static void DestroyItems(T* from, T* to);

	// Необработанное распределение
	static T* RawAlloc(size_t n);

	// освобождение памяти
	static void RawDealloc(T* p);

	T* m_begin = nullptr;
	T* m_end = nullptr;
	T* m_endOfCapacity = nullptr;
};

template <typename T>
CMyArray<T>::CMyArray(const CMyArray& arr)
{
	const auto size = arr.GetSize();
	if (size != 0)
	{
		m_begin = RawAlloc(size);
		try
		{
			CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
			m_endOfCapacity = m_end;
		}
		catch (...)
		{
			DeleteItems(m_begin, m_end);
			throw;
		}
	}
}

template <typename T>
CMyArray<T>::CMyArray(CMyArray&& arr)
	: m_begin(arr.m_begin)
	, m_end(arr.m_end)
	, m_endOfCapacity(arr.m_endOfCapacity)
{
	arr.m_begin = nullptr;
	arr.m_end = nullptr;
	arr.m_endOfCapacity = nullptr;
}

template <typename T>
CMyArray<T>::~CMyArray()
{
	DeleteItems(m_begin, m_end);
}

template <typename T>
void CMyArray<T>::Append(const T& value)
{
	if (m_end == m_endOfCapacity) // no free space
	{
		size_t newCapacity = std::max(size_t(1), GetCapacity() * 2);

		auto newBegin = RawAlloc(newCapacity);
		T* newEnd = newBegin;
		try
		{
			CopyItems(m_begin, m_end, newBegin, newEnd);
			// Конструируем копию value по адресу newItemLocation
			new (newEnd) T(value);
			++newEnd;
		}
		catch (...)
		{
			DeleteItems(newBegin, newEnd);
			throw;
		}

		DeleteItems(m_begin, m_end);

		// Переключаемся на использование нового хранилища элементов
		m_begin = newBegin;
		m_end = newEnd;
		m_endOfCapacity = m_begin + newCapacity;
	}
	else // has free space
	{
		new (m_end) T(value);
		++m_end;
	}
}

template <typename T>
void CMyArray<T>::Clear()
{
	if (GetSize() != 0)
	{
		DestroyItems(m_begin, m_end);
		m_end = m_begin;
	}
}

template <typename T>
void CMyArray<T>::Resize(size_t newSize)
{
	if (newSize > GetCapacity()) // когда новая длина больше вместимости
	{
		auto newBegin = RawAlloc(newSize);
		auto newEndOfCapacity = newBegin + newSize;
		T* newEnd = newBegin;
		try
		{
			CopyItems(m_begin, m_end, newBegin, newEnd);
			for (; newEnd < newEndOfCapacity; ++newEnd)
			{
				new (newEnd) T();
			}
		}
		catch (...)
		{
			DeleteItems(newBegin, newEnd);
			throw;
		}

		DeleteItems(m_begin, m_end);
		// Переключаемся на использование нового хранилища элементов
		m_begin = newBegin;
		m_end = newEnd;
		m_endOfCapacity = newEndOfCapacity;
	}
	else if (newSize < GetSize()) // когда новая длина меньше текущей
	{
		auto newEnd = m_begin + newSize;
		DestroyItems(newEnd, m_end);
		m_end = newEnd;
	}
	else if (newSize > GetSize()) // когда новая длина больше текущей, но меньше или = вместимости
	{
		auto prevEnd = m_end;
		m_end = m_begin + size;
		size_t currPos = 0;
		auto rasnica = newSize - GetSize();

		try
		{
			for (size_t i = 0; i < rasnica; ++i)
			{
				new (m_end + i) T();
				++currPos;
			}

			for (; currPos != m_end; ++currPos)
			{
				new (m_end) T();
			}
		}
		catch (...)
		{
			DestroyItems(prevEnd, prevEnd + currPos);
			throw;
		}

		for (size_t i = 0; i < newSize - GetSize(); ++i)
		{
			new (m_end) T();
			//Append(T()); // нельзя делать тк может быть утечка памяти при создании типа T
			++m_end;
		} // constructDefault и передавать до куда получилось сконструировать
	}
}

template <typename T>
void CMyArray<T>::ResizeCapacity(size_t capacity)
{
	if (size > 0)
	{
		T * begin = RawAlloc(size);
		T * current = begin;
		auto countOfItems = GetSize();
		if (countOfItems != 0)
		{
			try {
				CopyItems(m_begin, m_end, current);
				DestroyItems(m_begin, m_end);
				RawDealloc();
			}
			catch (...)
			{
				DestroyItems(begin, current);
				throw;
			}
		}

		m_begin = begin;
		m_endOfCapacity = m_begin + size;
		m_end = current;
	}
	else
	{
		DestroyItems(m_begin, m_end);
		RawDealloc();
		m_begin = nullptr;
		m_end = nullptr;
		m_endOfCapacity = nullptr;
	}

}

template <typename T>
T& CMyArray<T>::GetBack()
{
	assert(GetSize() != 0u);
	return m_end[-1];
}

template <typename T>
const T& CMyArray<T>::GetBack() const
{
	assert(GetSize() != 0u);
	return m_end[-1];
}

template <typename T>
size_t CMyArray<T>::GetSize() const
{
	if (!m_begin)
	{
		return 0;
	}

	return m_end - m_begin;
}

template <typename T>
size_t CMyArray<T>::GetCapacity() const
{
	return m_endOfCapacity - m_begin;
}

template <typename T>
const T& CMyArray<T>::operator[](size_t index) const
{
	if (m_begin + index >= m_end)
	{
		throw std::out_of_range("index is out of range");
	}

	return *(m_begin + index);
}

template <typename T>
T& CMyArray<T>::operator[](size_t index)
{
	if (m_begin + index >= m_end)
	{
		throw std::out_of_range("index is out of range");
	}

	return *(m_begin + index);
}

template <typename T>
CMyArray<T>& CMyArray<T>::operator=(const CMyArray& arr)
{
	if (std::addressof(arr) != this)
	{
		CMyArray tmpCopy(arr);
		std::swap(m_begin, tmpCopy.m_begin);
		std::swap(m_end, tmpCopy.m_end);
		std::swap(m_endOfCapacity, tmpCopy.m_endOfCapacity);
	}

	return *this;
}

template <typename T>
CMyArray<T>& CMyArray<T>::operator=(CMyArray&& arr)
{
	if (this != &arr)
	{
		Clear();
		m_begin = arr.m_begin;
		m_end = arr.m_end;
		m_endOfCapacity = arr.m_endOfCapacity;

		arr.m_begin = nullptr;
		arr.m_end = nullptr;
		arr.m_endOfCapacity = nullptr;
	}

	return *this;
}

template <typename T>
void CMyArray<T>::DeleteItems(T* begin, T* end)
{
	// Разрушаем старые элементы
	DestroyItems(begin, end);
	// Освобождаем область памяти для их хранения
	RawDealloc(begin);
}

template <typename T>
void CMyArray<T>::CopyItems(const T* srcBegin, T* srcEnd, T* const dstBegin, T*& dstEnd)
{
	for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
	{
		// Construct "T" at "dstEnd" as a copy of "*begin"
		new (dstEnd) T(*srcBegin);
	}
}

template <typename T>
void CMyArray<T>::DestroyItems(T* from, T* to)
{
	// to - первый скорнструированный объект

	while (to != from)
	{
		--to;
		// явно вызываем деструктор для шаблонного типа T
		to->~T();
	}
}

template <typename T>
T* CMyArray<T>::RawAlloc(size_t n)
{
	size_t memSize = n * sizeof(T);
	T* ptr = static_cast<T*>(malloc(memSize));
	if (!ptr)
	{
		throw std::bad_alloc();
	}

	return ptr;
}

template <typename T>
void CMyArray<T>::RawDealloc(T* p)
{
	free(p);
}

template <typename T>
typename CMyArray<T>::myIterator CMyArray<T>::begin()
{
	return CMyIterator(m_begin);
}

template <typename T>
typename CMyArray<T>::myIterator CMyArray<T>::end()
{
	return CMyIterator(m_end);
}

template <typename T>
typename CMyArray<T>::myConstIterator CMyArray<T>::begin() const
{
	return myConstIterator(m_begin);
}

template <typename T>
typename CMyArray<T>::myConstIterator CMyArray<T>::end() const
{
	return myConstIterator(m_end);
}

template <typename T>
typename CMyArray<T>::myReverseIterator CMyArray<T>::rbegin()
{
	return myReverseIterator(m_end);
}

template <typename T>
typename CMyArray<T>::myReverseIterator CMyArray<T>::rend()
{
	return myReverseIterator(m_begin);
}

template <typename T>
typename CMyArray<T>::myReverseConstIterator CMyArray<T>::rbegin() const
{
	return myReverseConstIterator(m_end);
}

template <typename T>
typename CMyArray<T>::myReverseConstIterator CMyArray<T>::rend() const
{
	return myReverseConstIterator(m_begin);
}
