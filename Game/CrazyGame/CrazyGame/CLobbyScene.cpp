#include "CLobbyScene.h"
#include "CLayer.h"
#include "CResourceManager.h"
#include "CUIButton.h"
#include "CBitmap.h"
#include "CUIPanel.h"

CLobbyScene::CLobbyScene()
{
	CBitmap* bitmap = CResourceManager::GetInst()->Load(L"login.png");

	// UI Layer �����
	CLayer *layer = CreateLayer("MapChoiceButton", INT_MAX);

	// ��׶���
	CUIPanel* background = new CUIPanel();
	background->SetBitmap(bitmap);
	background->SetPos({ 0, 0, 1920.f, 1080.f });
	layer->AddObj(background); 

	// �������� ��ư
	bitmap = CResourceManager::GetInst()->Load(L"map_select_village.png");
	u_int width = bitmap->GetBitmap()->GetPixelSize().width;
	u_int height = bitmap->GetBitmap()->GetPixelSize().height;
	CUIButton* btn = new CUIButton();
	btn->SetBitmap(bitmap);
	btn->SetPos({ 510.f, 800.f, 510.f + width, 800.f + height });
	layer->AddObj(btn);

	// ������ ��ư
	bitmap = CResourceManager::GetInst()->Load(L"map_select_pirate.png");
	width = bitmap->GetBitmap()->GetPixelSize().width;
	height = bitmap->GetBitmap()->GetPixelSize().height;
	btn = new CUIButton();
	btn->SetBitmap(bitmap);
	btn->SetPos({ 810.f, 800.f, 810.f + width, 800.f + height });
	layer->AddObj(btn);

	// �׽�Ʈ�� ��ư
	bitmap = CResourceManager::GetInst()->Load(L"map_select_test.png");
	width = bitmap->GetBitmap()->GetPixelSize().width;
	height = bitmap->GetBitmap()->GetPixelSize().height;
	btn = new CUIButton();
	btn->SetBitmap(bitmap);
	btn->SetPos({ 1110.f, 800.f, 1110.f + width, 800.f + height });
	layer->AddObj(btn);
}

CLobbyScene::~CLobbyScene()
{
}
