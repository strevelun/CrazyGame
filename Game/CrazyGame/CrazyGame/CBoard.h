#pragma once
#include <vector>
#include "Setting.h"
class CBoard
{
    tMapData m_mapData;
    std::vector<std::vector<eInGameObjType>> m_board;

public:
    CBoard();
    ~CBoard();
    void SetMapData(tMapData _mapData) { m_mapData = _mapData; }
    void SetBoard();

    bool IsMovable(int _x, int _y);
    void PutBubble(D2D1_RECT_F _rect);
    void RemoveObj(D2D1_RECT_F _rect);

    tMapData GetMapData() const { return m_mapData; }
    void SetInGameObjType(int _x, int _y, eInGameObjType _type) { m_board[_y][_x] = _type; }
};

