#include "CGameObj.h"

CGameObj::CGameObj(const D2D1_RECT_F& _rect) : CObj(_rect)
{
}

CGameObj::~CGameObj()
{
}

void CGameObj::Update()
{
	m_anim.Update();
}
