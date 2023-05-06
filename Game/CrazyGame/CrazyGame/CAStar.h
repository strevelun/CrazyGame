#pragma once

#include <vector>

typedef struct _node
{
	bool operator<(const _node& other) { return f_score < other.f_score; }

	float f_score;
	float g_score;
	float h_score;
	_node* parentNode;
} Node;

class CBoard;

class CAStar
{
	std::vector<std::vector<int>> m_board;

public:
	CAStar();
	~CAStar();

	void Init(CBoard* _board);
};