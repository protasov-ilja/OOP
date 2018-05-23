#pragma once
#include <memory>
#include <string>

class CMyString
{
public:
	friend const CMyString operator+(const CMyString& string1, const CMyString& string2);
	CMyString() = default;
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(const CMyString& other);
	CMyString(CMyString&& other);
	CMyString& operator=(CMyString&& other);
	CMyString(const std::string& stlString);
	~CMyString() = default;
	size_t GetLength() const;
	const char* GetStringData() const;
	CMyString SubString(size_t start, size_t length) const;
	void Clear();
	CMyString& operator=(const CMyString& other);
	CMyString const operator+=(const CMyString& string);
	bool operator==(const CMyString& string) const;
	bool operator!=(const CMyString& string) const;
	char const& operator[](size_t index) const;
	char& operator[](size_t index);
	bool operator<(const CMyString& string) const;
	bool operator>=(const CMyString& string) const;
	bool operator>(const CMyString& string) const;
	bool operator<=(const CMyString& string) const;

private:
	CMyString(std::unique_ptr<char[]>&& pChars, size_t length);
	std::unique_ptr<char[]> m_pChars = nullptr;
	size_t m_length = 0;
};

std::istream& operator>>(std::istream& stream, CMyString& string);
std::ostream& operator<<(std::ostream& stream, const CMyString& string);
