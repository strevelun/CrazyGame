#include "CUIHPBar.h"
#include "CUIPanel.h"
#include "CResourceManager.h"

CUIHPBar::CUIHPBar(const D2D1_RECT_F& _rect, u_int _maxHp) : CUI(_rect)
{
	m_background = new CUIPanel(_rect);
	m_background->SetBitmap(CResourceManager::GetInst()->Load(L"Boss_hp_background.png"));
	m_maxHp = _maxHp;;
}

CUIHPBar::~CUIHPBar()
{
	delete m_background;
}

void CUIHPBar::SetRect(D2D1_RECT_F _rect)
{
	m_rect = _rect;
	m_background->SetRect(_rect);
}

void CUIHPBar::Update()
{
	m_rect.right = m_rect.left + m_hp * (m_rect.right - m_rect.left) / m_maxHp;

	if ((float)m_hp / m_maxHp < 0.33f)
		SetBitmap(CResourceManager::GetInst()->Load(L"Boss_hp_red.png"));
}

void CUIHPBar::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{
	m_background->Render(_pRenderTarget);
	CObj::Render(_pRenderTarget);
}

void CUIHPBar::Die()
{
	m_isAlive = false;
}
