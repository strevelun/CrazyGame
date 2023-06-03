#pragma once
#include <vector>
#include <string>
#include <list>

#include "Setting.h"

class CObj;
class CItem;
class CVehicle;
class CMoveObj;
class CGameObj;

class CBoard
{
    tMapData m_mapData;
    std::vector<std::vector<eInGameObjType>> m_board;
    std::vector<std::vector<CMoveObj*>> m_moveObjBoard;
    std::vector<std::vector<CItem*>> m_itemBoard;

public:
    CBoard();
    ~CBoard();
    void SetMapData(tMapData _mapData) { m_mapData = _mapData; }
    void SetBoard();

    bool IsMovable(int _cellXPos, int _cellYPos, CVehicle* _vehicle = nullptr);
	bool IsGameObjType(int _cellXPos, int _cellYPos, eInGameObjType _type);

    bool PutObj(int _cellXPos, int _cellYPos, CGameObj* _obj, eInGameObjType _type);
    void RemoveObj(D2D1_RECT_F _rect);
    void RemoveObj(int _cellXPos, int _cellYPos, std::wstring _strLayerKey, eInGameObjType _objType);

    tMapData GetMapData() const { return m_mapData; }
    void SetInGameObjType(int _cellXPos, int _cellYPos, eInGameObjType _type) { 
        if (_cellXPos < 0 || _cellXPos > 14 || _cellYPos < 0 || _cellYPos > 12) return;
        m_board[_cellYPos][_cellXPos] = _type; }
    void SetObjTypeInMoveObjBoard(int _cellXPos, int _cellYPos, CMoveObj* _pObj) { m_moveObjBoard[_cellYPos][_cellXPos] = _pObj; }
    bool PutSplash(D2D1_RECT_F _rect, std::wstring _animClipName, CMoveObj* _pOwner);
    bool PutSplash(u_int _cellXPos, u_int _cellYPos, std::wstring _animClipName, CMoveObj* _pOwner);

    CItem* GetItem(D2D1_RECT_F _rect);
    CItem* GetItem(u_int _cellXPos, u_int _cellYPos);
    CMoveObj* GetObjTypeInMoveObjBoard(int _cellXPos, int _cellYPos) {
        if (_cellXPos < 0 || _cellXPos > 14 || _cellYPos < 0 || _cellYPos > 12) return nullptr; 
        return m_moveObjBoard[_cellYPos][_cellXPos]; }

    void PutItem(int _cellXPos, int _cellYPos, CItem* _pItem);
};