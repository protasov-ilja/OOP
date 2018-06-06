#pragma once

class CStringStack
{
public:
	struct Node
	{
		Node(const std::string& data, std::unique_ptr<Node>&& next)
			: data(data)
			, next(std::move(next))
		{
		}

		std::string data;
		std::unique_ptr<Node> next;
	};

	CStringStack();
	~CStringStack();
	CStringStack(const CStringStack& stack);
	CStringStack(CStringStack&& stack);
	CStringStack& operator=(const CStringStack& other);
	CStringStack& operator=(CStringStack&& other);

	void Push(const std::string& str);
	void Pop();
	std::string GetTop() const;
	void Clear();
	size_t GetSize() const;
	bool IsEmpty() const;

private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_top = nullptr;
};
