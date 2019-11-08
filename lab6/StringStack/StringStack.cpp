#include "stdafx.h"
#include "StringStack.h"
#include <string>
#include <memory>

CStringStack::CStringStack()
{
}

CStringStack::CStringStack(const CStringStack& other)
{
	if (other.m_length != 0)
	{
		m_top = std::make_unique<Node>(other.m_size);
		memcpy(m_pChars.get(), other.m_pChars.get(), other.m_length + 1);
		m_length = other.m_length;
	}


	const auto size = arr.GetSize();
	if (size != 0)
	{
		m_top = RawAlloc(size);
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

CStringStack::CStringStack(CStringStack&& other)
	: m_top(std::move(other.m_top.get()))
	, m_size(other.m_size)
{
	other.m_top = nullptr;
	other.m_size = 0;
}


CStringStack::~CStringStack()
{
}

bool CStringStack::IsEmpty() const
{
	return m_top == nullptr;
}


size_t CStringStack::GetSize() const
{
	return m_size;
}

void CStringStack::Push(const std::string& str)
{
	auto newNode = std::make_unique<Node>(str, m_top, nullptr);
	Node *newLastNode = newNode.get();
	if (m_top)
	{
		m_lastNode->next = std::move(newNode);
	}
	else // empty list
	{
		m_top = std::move(newNode);
	}

	m_lastNode = newLastNode;
	++m_size;
}