#pragma once
#include <vector>
#include "Setting.h"
#include <string>

class CObj;

class CBoard
{
    tMapData m_mapData;
    std::vector<std::vector<eInGameObjType>> m_board;
    std::vector<std::vector<eInGameObjType>> m_moveObjBoard;

public:
    CBoard();
    ~CBoard();
    void SetMapData(tMapData _mapData) { m_mapData = _mapData; }
    void SetBoard();

    bool IsMovable(int _xpos, int _ypos, bool _isGridPos);

    void PutItem(D2D1_RECT_F _rect, std::string _animClipName, CObj* _obj, eInGameObjType _type);
    void RemoveObj(D2D1_RECT_F _rect);

    tMapData GetMapData() const { return m_mapData; }
    void SetInGameObjType(int _x, int _y, eInGameObjType _type) { m_board[_y][_x] = _type; }
    void SetObjTypeInMoveObjBoard(int _x, int _y, eInGameObjType _type) { m_moveObjBoard[_y][_x] = _type; }
    bool PutSplash(D2D1_RECT_F _rect, std::string _animClipName);
};

