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

void CLobbyScene::OnMapButtonClicked(const std::string _strName)
{
	//tMapData data = FindMapData(_strName);

	CInGameScene* scene = dynamic_cast<CInGameScene*>(CSceneManager::GetInst()->GetScene(_strName));
	CSceneManager::GetInst()->ChangeScene(_strName);
	//scene->SetMapData(data);
}



void CLobbyScene::Init()
{
	//SetWindowPos(CApp::GetInst()->GetHwnd(), NULL, 0, 0, 1920.0f, 1080.0f, SWP_NOMOVE);

	CBitmap* bitmap = CResourceManager::GetInst()->Load(L"login.png");

	// UI Layer 만들기
	CLayer* layer = CreateLayer("MapChoiceButton", INT_MAX);

	// 백그라운드
	CUIPanel* background = new CUIPanel({ 0, 0, 800.f, 600.f });
	background->SetBitmap(bitmap);
	layer->AddObj(background);

	// 빌리지맵 버튼
	bitmap = CResourceManager::GetInst()->Load(L"map_select_village.png");
	u_int width = bitmap->GetBitmap()->GetPixelSize().width;
	u_int height = bitmap->GetBitmap()->GetPixelSize().height;
	CUIButton* btn = new CUIButton({ 80.f, 450.f, 80.f + width, 450.f + height }, "village.map");
	btn->SetBitmap(bitmap);
	layer->AddObj(btn);


	btn->SetCallback<CLobbyScene>(this, &CLobbyScene::OnMapButtonClicked);

	float prevEnd = 80 + width;

	// 해적맵 버튼
	bitmap = CResourceManager::GetInst()->Load(L"map_select_pirate.png");
	width = bitmap->GetBitmap()->GetPixelSize().width;
	height = bitmap->GetBitmap()->GetPixelSize().height;
	btn = new CUIButton({ prevEnd + 30.f, 450.f, prevEnd + width, 450.f + height }, "pirate.map");
	btn->SetBitmap(bitmap);
	layer->AddObj(btn);
	btn->SetCallback<CLobbyScene>(this, &CLobbyScene::OnMapButtonClicked);

	prevEnd = prevEnd + width;

	// 테스트맵 버튼
	bitmap = CResourceManager::GetInst()->Load(L"map_select_test.png");
	width = bitmap->GetBitmap()->GetPixelSize().width;
	height = bitmap->GetBitmap()->GetPixelSize().height;
	btn = new CUIButton({ prevEnd + 30.f, 450.f, prevEnd + width, 450.f + height }, "test.map");
	btn->SetBitmap(bitmap);
	layer->AddObj(btn);
	btn->SetCallback<CLobbyScene>(this, &CLobbyScene::OnMapButtonClicked);
}
