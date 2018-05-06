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
	if ((pString[0] != '\0') && (length > 0))
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
	if (other.m_length > 0)
	{
		m_pChars = std::make_unique<char[]>(other.m_length + 1);
		memcpy(m_pChars.get(), other.m_pChars.get(), other.m_length + 1);
		m_length = other.m_length;
	}
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

CMyString CMyString::SubString(size_t start, size_t length = SIZE_MAX) const
{
	if ((start > m_length) || (start < 0) || (start + length > m_length))
	{
		throw std::out_of_range("substring is out of range");
	}

	if (start == m_length)
	{
		return "";
	}

	return CMyString(&m_pChars[start], length);
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

CMyString const CMyString::operator+(const CMyString& string) const
{
	std::unique_ptr<char[]> tmpCopy = std::make_unique<char[]>(m_length + string.m_length + 1);
	memcpy(tmpCopy.get(), m_pChars.get(), m_length);
	memcpy(tmpCopy.get() + m_length, string.m_pChars.get(), string.m_length + 1);
	tmpCopy[m_length + string.m_length] = '\0';

	return CMyString(tmpCopy.get(), m_length + string.m_length);
}

CMyString const operator+(const std::string& string1, const CMyString& string2)
{
	return CMyString(string1) + string2;
}

CMyString const operator+(const char* string1, const CMyString& string2)
{
	return CMyString(string1) + string2;
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
	assert(index < m_length);

	return m_pChars[index];
}

char& CMyString::operator[](size_t index)
{
	assert(index < m_length);

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
	stream << string.GetStringData();

	return stream;
}
