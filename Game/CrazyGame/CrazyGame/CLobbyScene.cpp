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
	CBitmap* bitmap = CResourceManager::GetInst()->Load(L"login.png");

	// UI Layer �����
	CLayer *layer = CreateLayer("MapChoiceButton", INT_MAX);

	// ��׶���
	CUIPanel* background = new CUIPanel();
	background->SetBitmap(bitmap);
	background->SetRect({ 0, 0, 1920.f, 1080.f });
	layer->AddObj(background); 

	// �������� ��ư
	bitmap = CResourceManager::GetInst()->Load(L"map_select_village.png");
	u_int width = bitmap->GetBitmap()->GetPixelSize().width;
	u_int height = bitmap->GetBitmap()->GetPixelSize().height;
	CUIButton* btn = new CUIButton("village.map");
	btn->SetBitmap(bitmap);
	btn->SetRect({ 510.f, 800.f, 510.f + width, 800.f + height });
	layer->AddObj(btn);
	tMapData mapData = CResourceManager::GetInst()->LoadMapData(L"village.map");
	m_mapData.insert(std::make_pair("village.map", mapData));
	btn->SetCallback<CLobbyScene>(this, &CLobbyScene::OnMapButtonClicked);

	// ������ ��ư
	bitmap = CResourceManager::GetInst()->Load(L"map_select_pirate.png");
	width = bitmap->GetBitmap()->GetPixelSize().width;
	height = bitmap->GetBitmap()->GetPixelSize().height;
	btn = new CUIButton("pirate.map");
	btn->SetBitmap(bitmap);
	btn->SetRect({ 810.f, 800.f, 810.f + width, 800.f + height });
	layer->AddObj(btn);
	mapData = CResourceManager::GetInst()->LoadMapData(L"pirate.map");
	m_mapData.insert(std::make_pair("pirate.map", mapData));
	btn->SetCallback<CLobbyScene>(this, &CLobbyScene::OnMapButtonClicked);

	// �׽�Ʈ�� ��ư
	bitmap = CResourceManager::GetInst()->Load(L"map_select_test.png");
	width = bitmap->GetBitmap()->GetPixelSize().width;
	height = bitmap->GetBitmap()->GetPixelSize().height;
	btn = new CUIButton("test.map");
	btn->SetBitmap(bitmap);
	btn->SetRect({ 1110.f, 800.f, 1110.f + width, 800.f + height });
	layer->AddObj(btn);
	mapData = CResourceManager::GetInst()->LoadMapData(L"test.map");
	m_mapData.insert(std::make_pair("test.map", mapData));
	btn->SetCallback<CLobbyScene>(this, &CLobbyScene::OnMapButtonClicked);

	CResourceManager::GetInst()->LoadFiles(L"resource/sprite/");
}

CLobbyScene::~CLobbyScene()
{
	
}

void CLobbyScene::OnMapButtonClicked(const std::string _strName)
{
	tMapData data = FindMapData(_strName);

	CInGameScene* scene = CSceneManager::GetInst()->CreateScene<CInGameScene>();
	CSceneManager::GetInst()->SetNextScene(scene);
	scene->SetMapData(data);
	scene->Init();
}

tMapData& CLobbyScene::FindMapData(const std::string& _strName)
{
	std::unordered_map<std::string, tMapData>::iterator iter = m_mapData.find(_strName);
	if (iter == m_mapData.end())
	{
		MessageBox(NULL, L"m_mapData�� �ش� Ű ���� �����Ͱ� �����ϴ�.", L"����", MB_OK);
		CApp::GetInst()->ExitGame();
	}
	return iter->second;
}
