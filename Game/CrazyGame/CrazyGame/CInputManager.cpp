#include "CInputManager.h"
#include "CMouse.h"
#include "CObj.h"
#include "CTimer.h"

CInputManager* CInputManager::m_inst = nullptr;

CInputManager::CInputManager()
{
	//m_pMouse = CObj::CreateObj<CMouse>();
	m_pMouse = new CMouse();

}

CInputManager::~CInputManager()
{
}
/*
void CInputManager::SpaceBar()
{
	m_startTime = CTimer::GetInst()->GetDeltaTime();
}

void CInputManager::DoubleSpaceBar()
{
}
*/

void CInputManager::Input()
{
	m_pMouse->Input();
	m_pMouse->Update();


}
