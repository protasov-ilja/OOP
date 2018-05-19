#include "stdafx.h"
#include "CMyString.h"
#include <algorithm>
#include <cassert>
#include <iostream>

CMyString::CMyString(const char* pString)
	: CMyString(pString, strlen(pString))
{
}

CMyString::CMyString(const char* pString, size_t length)
{
	if (length != 0)
	{
		m_pChars = std::make_unique<char[]>(length + 1);
		memcpy(m_pChars.get(), pString, length + 1);
		m_pChars[length] = '\0';
		m_length = length;
	}
}

CMyString::CMyString(const std::string& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

CMyString::CMyString(const CMyString& other)
{
	if (other.m_length != 0)
	{
		m_pChars = std::make_unique<char[]>(other.m_length + 1);
		memcpy(m_pChars.get(), other.m_pChars.get(), other.m_length + 1);
		m_length = other.m_length;
	}
}

CMyString::CMyString(std::unique_ptr<char[]>& pChars, size_t length)
	: m_pChars(std::move(pChars))
	, m_length(length)
{
}

CMyString::CMyString(CMyString&& other)
	: m_pChars(std::move(other.m_pChars))
	, m_length(other.m_length)
{
	other.m_length = 0;
}

CMyString& CMyString::operator=(CMyString&& other)
{
	if (this != &other)
	{
		std::swap(m_pChars, other.m_pChars);
		std::swap(m_length, other.m_length);
		other.Clear();
	}

	return *this;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	static const char zeroLengthString[] = "";

	return m_pChars ? m_pChars.get() : zeroLengthString;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length)
	{
		return CMyString();
	}

	return ((SIZE_MAX - length < start) || (start + length > m_length)) ? CMyString(&m_pChars[start], m_length - start) : CMyString(&m_pChars[start], length);
}

void CMyString::Clear()
{
	m_length = 0;
	m_pChars.reset();
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (std::addressof(other) != this)
	{
		CMyString tmpCopy(other);
		std::swap(m_pChars, tmpCopy.m_pChars);
		std::swap(m_length, tmpCopy.m_length);
	}

	return *this;
}
const CMyString operator+(const CMyString& string1, const CMyString& string2)
{
	if ((string1.m_length != 0) && (string2.m_length != 0))
	{
		if (SIZE_MAX - string1.m_length < (string2.m_length + 1))
		{
			throw std::out_of_range("sum of lengths is out of range");
		}

		std::unique_ptr<char[]> tmpCopy = std::make_unique<char[]>(string1.m_length + string2.m_length + 1);
		memcpy(tmpCopy.get(), string1.m_pChars.get(), string1.m_length);
		memcpy(tmpCopy.get() + string1.m_length, string2.m_pChars.get(), string2.m_length + 1);
		tmpCopy[string1.m_length + string2.m_length] = '\0';

		return CMyString(tmpCopy, string1.m_length + string2.m_length);
	}
	else if ((string1.m_length == 0) && (string2.m_length == 0))
	{
		return CMyString();
	}
	else if (string1.m_length == 0)
	{
		return string2;
	}
	else
	{
		return string1;
	}
}

CMyString const CMyString::operator+=(const CMyString& string)
{
	return *this = *this + string;
}

bool CMyString::operator==(const CMyString& string) const
{
	if (m_length != string.m_length)
	{
		return false;
	}

	return memcmp(m_pChars.get(), string.m_pChars.get(), m_length) == 0;
}

bool CMyString::operator!=(const CMyString& string) const
{
	return !(*this == string);
}

char const& CMyString::operator[](size_t index) const
{
	if (index >= m_length)
	{
		throw std::out_of_range("index is out of range");
	}

	return m_pChars[index];
}

char& CMyString::operator[](size_t index)
{
	if (index >= m_length)
	{
		throw std::out_of_range("index is out of range");
	}

	return m_pChars[index];
}

bool CMyString::operator<(const CMyString& string) const
{
	return m_length == string.m_length ? memcmp(m_pChars.get(), string.m_pChars.get(), m_length) < 0 : m_length < string.m_length;
}

bool CMyString::operator>=(const CMyString& string) const
{
	return !(*this < string);
}

bool CMyString::operator>(const CMyString& string) const
{
	return m_length == string.m_length ? memcmp(m_pChars.get(), string.m_pChars.get(), m_length) > 0 : m_length > string.m_length;
}

bool CMyString::operator<=(const CMyString& string) const
{
	return !(*this > string);
}

std::istream& operator>>(std::istream& stream, CMyString& string)
{
	std::string inputString;
	stream >> inputString;
	string = inputString;

	return stream;
}

std::ostream& operator<<(std::ostream& stream, const CMyString& string)
{
	for (size_t i = 0; i < string.GetLength(); ++i)
	{
		stream << string[i];
	}

	return stream;
}
