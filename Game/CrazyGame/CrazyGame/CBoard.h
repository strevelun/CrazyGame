#pragma once
#include <vector>
#include <string>

#include "Setting.h"

class CObj;
class CItem;

class CBoard
{
    tMapData m_mapData;
    std::vector<std::vector<eInGameObjType>> m_board;
    std::vector<std::vector<eInGameObjType>> m_moveObjBoard;
    std::vector<std::vector<CItem*>> m_itemBoard;

public:
    CBoard();
    ~CBoard();
    void SetMapData(tMapData _mapData) { m_mapData = _mapData; }
    void SetBoard();

    bool IsMovable(int _xpos, int _ypos, bool _isGridPos);
	bool IsGameObjType(int x, int y, eInGameObjType _type);

    void PutObj(int _xpos, int _ypos, CObj* _obj, eInGameObjType _type);
    void RemoveObj(D2D1_RECT_F _rect);
	void RemoveObj(int _xpos, int _ypos);

    tMapData GetMapData() const { return m_mapData; }
    void SetInGameObjType(int _x, int _y, eInGameObjType _type) { m_board[_y][_x] = _type; }
    void SetObjTypeInMoveObjBoard(int _x, int _y, eInGameObjType _type) { m_moveObjBoard[_y][_x] = _type; }
    bool PutSplash(D2D1_RECT_F _rect, std::string _animClipName);

    CItem* GetItem(D2D1_RECT_F _rect);
    void PutItem(D2D1_RECT_F _rect, CItem* _pItem);
};