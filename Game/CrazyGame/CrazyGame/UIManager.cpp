#include "UIManager.h"
#include "CLayer.h"
#include "CBitmap.h"
#include "CSceneManager.h"
#include "CResourceManager.h"
#include "CUIPanel.h"
#include "CScene.h"

UIManager* UIManager::m_inst = nullptr;

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::ShowAndAddUIPanel(PCWSTR _strFileName)
{
	CLayer* layer = CSceneManager::GetInst()->GetCurScene()->FindLayer(L"MonsterUI");
	CBitmap* loseBitmap = CResourceManager::GetInst()->GetBitmap(_strFileName);
	m_statePanel = new CUIPanel({ 150, 250,150 + 477, 250 + 77 });
	m_statePanel->SetBitmap(loseBitmap);
	layer->AddUIObj(m_statePanel);
}