#include "CUIButton.h"
#include "CInputManager.h"
#include "CMouse.h"

// GetMouse해서 마우스 가져온다음 마우스 현재 상태를 뺴오고 만약 Click 상태라면...
// SceneManager에서 CreateScene
// 씬 전환할때 이전 씬에서 할당된 모든 자원 해제 

CUIButton::CUIButton(const D2D1_RECT_F& _rect, std::string _strName) : CUI(_rect)
{
	m_strName = _strName;
}

CUIButton::~CUIButton()
{
}

void CUIButton::Input()
{
	CMouse* mouse = CInputManager::GetInst()->GetMouse();

	if (mouse->GetMouseState() == eMouseState::Click)
	{
		D2D1_POINT_2F point = mouse->GetMousePoint();
		if (m_rect.left < point.x && point.x < m_rect.right && m_rect.top < point.y && point.y < m_rect.bottom)
		{
			m_BtnCallback(m_strName);
		}
	}
}
