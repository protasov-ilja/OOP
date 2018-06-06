#include "stdafx.h"
#include "StringStack.h"
#include <string>
#include <memory>

CStringStack::CStringStack()
{
}


CStringStack::~CStringStack()
{
}

bool CStringStack::IsEmpty() const
{
	return m_top;
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