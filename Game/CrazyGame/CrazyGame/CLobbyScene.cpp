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
	tMapData data = FindMapData(_strName);

	CInGameScene* scene = dynamic_cast<CInGameScene*>(CSceneManager::GetInst()->GetScene("InGameScene"));
	CSceneManager::GetInst()->ChangeScene("InGameScene");
	scene->SetMapData(data);
}

tMapData& CLobbyScene::FindMapData(const std::string& _strName)
{
	std::unordered_map<std::string, tMapData>::iterator iter = m_mapData.find(_strName);
	if (iter == m_mapData.end())
	{
		MessageBox(NULL, L"m_mapData에 해당 키 값의 데이터가 없습니다.", L"오류", MB_OK);
		CApp::GetInst()->ExitGame();
	}
	return iter->second;
}

void CLobbyScene::Init()
{
	CBitmap* bitmap = CResourceManager::GetInst()->Load(L"login.png");

	// UI Layer 만들기
	CLayer* layer = CreateLayer("MapChoiceButton", INT_MAX);

	// 백그라운드
	CUIPanel* background = new CUIPanel({ 0, 0, 1920.f, 1080.f });
	background->SetBitmap(bitmap);
	layer->AddObj(background);

	// 빌리지맵 버튼
	bitmap = CResourceManager::GetInst()->Load(L"map_select_village.png");
	u_int width = bitmap->GetBitmap()->GetPixelSize().width;
	u_int height = bitmap->GetBitmap()->GetPixelSize().height;
	CUIButton* btn = new CUIButton({ 510.f, 800.f, 510.f + width, 800.f + height }, "village.map");
	btn->SetBitmap(bitmap);
	layer->AddObj(btn);
	tMapData mapData = CResourceManager::GetInst()->LoadMapData(L"village.map");
	m_mapData.insert(std::make_pair("village.map", mapData));
	btn->SetCallback<CLobbyScene>(this, &CLobbyScene::OnMapButtonClicked);

	// 해적맵 버튼
	bitmap = CResourceManager::GetInst()->Load(L"map_select_pirate.png");
	width = bitmap->GetBitmap()->GetPixelSize().width;
	height = bitmap->GetBitmap()->GetPixelSize().height;
	btn = new CUIButton({ 810.f, 800.f, 810.f + width, 800.f + height }, "pirate.map");
	btn->SetBitmap(bitmap);
	layer->AddObj(btn);
	mapData = CResourceManager::GetInst()->LoadMapData(L"pirate.map");
	m_mapData.insert(std::make_pair("pirate.map", mapData));
	btn->SetCallback<CLobbyScene>(this, &CLobbyScene::OnMapButtonClicked);

	// 테스트맵 버튼
	bitmap = CResourceManager::GetInst()->Load(L"map_select_test.png");
	width = bitmap->GetBitmap()->GetPixelSize().width;
	height = bitmap->GetBitmap()->GetPixelSize().height;
	btn = new CUIButton({ 1110.f, 800.f, 1110.f + width, 800.f + height }, "test.map");
	btn->SetBitmap(bitmap);
	layer->AddObj(btn);
	mapData = CResourceManager::GetInst()->LoadMapData(L"test.map");
	m_mapData.insert(std::make_pair("test.map", mapData));
	btn->SetCallback<CLobbyScene>(this, &CLobbyScene::OnMapButtonClicked);
}
