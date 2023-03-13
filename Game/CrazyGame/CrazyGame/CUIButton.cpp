#include "CUIButton.h"
#include "CInputManager.h"
#include "CMouse.h"

// GetMouse�ؼ� ���콺 �����´��� ���콺 ���� ���¸� ������ ���� Click ���¶��...
// SceneManager���� CreateScene
// �� ��ȯ�Ҷ� ���� ������ �Ҵ�� ��� �ڿ� ���� 

CUIButton::CUIButton(std::string _strName)
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
