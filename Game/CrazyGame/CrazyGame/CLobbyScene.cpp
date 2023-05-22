#include "CLobbyScene.h"
#include "CLayer.h"
#include "CResourceManager.h"
#include "CUIButton.h"
#include "CBitmap.h"
#include "CUIPanel.h"
#include "CSceneManager.h"
#include "CInGameScene.h"
#include "../../D2DCore/CApp.h"

CLobbyScene::CLobbyScene()
{
	

}

CLobbyScene::~CLobbyScene()
{
	
}

void CLobbyScene::OnMapButtonClicked(const std::wstring _strName)
{
	//tMapData data = FindMapData(_strName);

	CInGameScene* scene = dynamic_cast<CInGameScene*>(CSceneManager::GetInst()->GetScene(_strName));
	CSceneManager::GetInst()->ChangeScene(_strName);
	//scene->SetMapData(data);
}



void CLobbyScene::Init()
{
	CBitmap* bitmap = CResourceManager::GetInst()->GetBitmap(L"login.png");

	// UI Layer �����
	CLayer* layer = CreateLayer(L"MapChoiceButton", INT_MAX);

	// ��׶���
	CUIPanel* background = new CUIPanel({ 0, 0, 800.f, 600.f });
	background->SetBitmap(bitmap);
	layer->AddObj(background);

	// �������� ��ư
	bitmap = CResourceManager::GetInst()->GetBitmap(L"map_select_village.png");
	u_int width = bitmap->GetBitmap()->GetPixelSize().width;
	u_int height = bitmap->GetBitmap()->GetPixelSize().height;
	CUIButton* btn = new CUIButton({ 80.f, 450.f, 80.f + width, 450.f + height }, L"village.map");
	btn->SetBitmap(bitmap);
	layer->AddObj(btn);


	btn->SetCallback<CLobbyScene>(this, &CLobbyScene::OnMapButtonClicked);

	float prevEnd = 80 + width;

	// ������ ��ư
	bitmap = CResourceManager::GetInst()->GetBitmap(L"map_select_pirate.png");
	width = bitmap->GetBitmap()->GetPixelSize().width;
	height = bitmap->GetBitmap()->GetPixelSize().height;
	btn = new CUIButton({ prevEnd + 30.f, 450.f, prevEnd + width, 450.f + height }, L"pirate.map");
	btn->SetBitmap(bitmap);
	layer->AddObj(btn);
	btn->SetCallback<CLobbyScene>(this, &CLobbyScene::OnMapButtonClicked);

	prevEnd = prevEnd + width;

	// �׽�Ʈ�� ��ư
	bitmap = CResourceManager::GetInst()->GetBitmap(L"map_select_test.png");
	width = bitmap->GetBitmap()->GetPixelSize().width;
	height = bitmap->GetBitmap()->GetPixelSize().height;
	btn = new CUIButton({ prevEnd + 30.f, 450.f, prevEnd + width, 450.f + height }, L"test.map");
	btn->SetBitmap(bitmap);
	layer->AddObj(btn);
	btn->SetCallback<CLobbyScene>(this, &CLobbyScene::OnMapButtonClicked);
}

void CLobbyScene::Cleanup()
{
	std::list<CLayer*>::iterator iter = m_layerList.begin();
	std::list<CLayer*>::iterator iterEnd = m_layerList.end();

	for (; iter != iterEnd; iter++)
	{
		(*iter)->DeleteAllObj();
		delete* iter;
	}
	m_layerList.clear();
}
