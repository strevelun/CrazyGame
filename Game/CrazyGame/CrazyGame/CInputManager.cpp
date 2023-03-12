#include "CInputManager.h"
#include "CMouse.h"
#include "CObj.h"

CInputManager* CInputManager::m_inst = nullptr;

CInputManager::CInputManager()
{
	m_pMouse = CObj::CreateObj<CMouse>();
}

CInputManager::~CInputManager()
{
}

void CInputManager::Input()
{
	m_pMouse->Input();
	m_pMouse->Update();
}
