#pragma once
#include <memory>
#include <string>

class CMyString
{
public:
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
	CMyString const operator+(const CMyString& string) const;
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
	std::unique_ptr<char[]> m_pChars = nullptr;
	size_t m_length = 0;
};

CMyString const operator+(const std::string& string1, const CMyString& string2);
CMyString const operator+(const char* string1, const CMyString& string2);
std::istream& operator>>(std::istream& stream, CMyString& string);
std::ostream& operator<<(std::ostream& stream, const CMyString& string);
