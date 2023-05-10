#include "CVehicle.h"
#include "CResourceManager.h"
#include "CBitmap.h"

CVehicle::CVehicle(const D2D1_RECT_F& _rect, std::string _strVehicleName) : CMoveObj(_rect)
{
	// 여기서 모든 애니 로딩
	if (_strVehicleName.compare("UFO") == 0)
	{
		CAnimationClip* animClip = CResourceManager::GetInst()->GetAnimationClip("UFO_Back");
		animClip->SetFrametimeLimit(0.1f);
		m_anim.AddClip("UFO_Back", animClip);
		animClip = CResourceManager::GetInst()->GetAnimationClip("UFO_Front");
		animClip->SetFrametimeLimit(0.1f);
		m_anim.AddClip("UFO_Front", animClip);
		animClip = CResourceManager::GetInst()->GetAnimationClip("UFO_Left");
		animClip->SetFrametimeLimit(0.1f);
		m_anim.AddClip("UFO_Left", animClip);
		animClip = CResourceManager::GetInst()->GetAnimationClip("UFO_Right");
		animClip->SetFrametimeLimit(0.1f);
		m_anim.AddClip("UFO_Right", animClip);
		m_anim.SetClip("UFO_Front");

		m_strName = "UFO";
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
	case Dir::Up:
		m_anim.SetClip("UFO_Back");
		break;
	case Dir::Down:
		m_anim.SetClip("UFO_Front");
		break;
	case Dir::Left:
		m_anim.SetClip("UFO_Left");
		break;
	case Dir::Right:
		m_anim.SetClip("UFO_Right");
		break;
	}

	m_anim.Update();
}

void CVehicle::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{
	m_anim.Render(_pRenderTarget, m_rect);
}