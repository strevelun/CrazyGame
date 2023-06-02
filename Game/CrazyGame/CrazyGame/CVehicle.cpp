#include "CVehicle.h"
#include "CResourceManager.h"
#include "CBitmap.h"

CVehicle::CVehicle(const D2D1_RECT_F& _rect, std::wstring _strVehicleName) : CMoveObj(_rect)
{
	// 여기서 모든 애니 로딩
	if (_strVehicleName.compare(L"UFO") == 0)
	{
		CAnimationClip* animClip = CResourceManager::GetInst()->GetAnimationClip(L"UFO_Back");
		animClip->SetFrametimeLimit(0.1f);
		m_anim.AddClip(L"UFO_Back", animClip);
		animClip = CResourceManager::GetInst()->GetAnimationClip(L"UFO_Front");
		animClip->SetFrametimeLimit(0.1f);
		m_anim.AddClip(L"UFO_Front", animClip);
		animClip = CResourceManager::GetInst()->GetAnimationClip(L"UFO_Left");
		animClip->SetFrametimeLimit(0.1f);
		m_anim.AddClip(L"UFO_Left", animClip);
		animClip = CResourceManager::GetInst()->GetAnimationClip(L"UFO_Right");
		animClip->SetFrametimeLimit(0.1f);
		m_anim.AddClip(L"UFO_Right", animClip);
		m_anim.SetClip(L"UFO_Front");
		m_size.height = animClip->GetFirstFrame()->size.height;
		m_size.width = animClip->GetFirstFrame()->size.width;
		m_strName = L"UFO";
		m_rideHeight = 40.0f;
		m_speed = 350.0f;
	}
}

CVehicle::~CVehicle()
{

}

void CVehicle::Update(D2D1_RECT_F& _rect)
{
	m_rect = _rect;

	switch (m_eMoveDir)
	{
	case eDir::Up:
		m_anim.SetClip(L"UFO_Back");
		break;
	case eDir::Down:
		m_anim.SetClip(L"UFO_Front");
		break;
	case eDir::Left:
		m_anim.SetClip(L"UFO_Left");
		break;
	case eDir::Right:
		m_anim.SetClip(L"UFO_Right");
		break;
	}

	m_anim.Update();
}

void CVehicle::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{
	m_anim.Render(_pRenderTarget, m_rect);
}