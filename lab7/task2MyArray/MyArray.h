#pragma once
#include <algorithm>
#include <new>

template <typename T>
class CMyArray
{
public:
	/*typedef CMyIterator<T> iterator;
	typedef CMyIterator<const T> iterator;*/
	CMyArray() = default;
	//����������� ���������� �������� � ����� �������
	//����������� ��������� ���������� ���������, ������������ � �������
	//����������� ������������� ���������������� ������� � ��������� ������� ��� ������ ��������� �[]�.� ������, ���� ������ �������� ������� �� ������� �������, ������ ������������� ���������� std::out_of_range
	//����������� ��������� ����� ������� ��� ������ ������ Resize().� ������, ���� ����� ����� ������� ������ �������, ����������� � ����� ������� �������� ������ ������������������ ��������� �� ��������� ��� ���� T.
	//����������� ����������� �������(�������� ���� ��� ���������) ��� ������ ������ Clear.
	//����������� ����������� � �������� ������������
	//����������� ����������� � ������������ �������� ������������
	//������ begin() � end(), � ����� rbegin() � rend(), ������������ ��������� ��� �������� ��������� ������� � ������ � �������� �������.
	~CMyArray();
	CMyArray(const CMyArray& arr);
	void Append(const T& value);
	T& GetBack();
	const T& GetBack() const;
	size_t GetSize() const;
	size_t GetCapacity() const;

private:
	static void DeleteItems(T* begin, T* end)
	{
		// ��������� ������ ��������
		DestroyItems(begin, end);
		// ����������� ������� ������ ��� �� ��������
		RawDealloc(begin);
	}

	// �������� �������� �� �������� ������� � to, ���������� newEnd
	static void CopyItems(const T* srcBegin, T* srcEnd, T* const dstBegin, T*& dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			// Construct "T" at "dstEnd" as a copy of "*begin"
			new (dstEnd) T(*srcBegin);
		}
	}

	static void DestroyItems(T* from, T* to)
	{
		// dst - ����� ������, ��� ��������������� �������� ���� ��������� ����������
		// to - ������ ������������������ ������

		while (to != from)
		{
			--to;
			// ���� �������� ���������� ��� ���������� ���� T
			to->~T();
		}
	}

	static T* RawAlloc(size_t n)
	{
		size_t memSize = n * sizeof(T);
		T* p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	static void RawDealloc(T* p)
	{
		free(p);
	}


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
			// ������������ ����� value �� ������ newItemLocation
			new (newEnd) T(value);
			++newEnd;
		}
		catch (...)
		{
			DeleteItems(newBegin, newEnd);
			throw;
		}
		DeleteItems(m_begin, m_end);

		// ������������� �� ������������� ������ ��������� ���������
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
	return m_end - m_begin;
}

template <typename T>
size_t CMyArray<T>::GetCapacity() const
{
	return m_endOfCapacity - m_begin;
}

template <typename T>
CMyArray<T>::~CMyArray()
{
	DeleteItems(m_begin, m_end);
}

