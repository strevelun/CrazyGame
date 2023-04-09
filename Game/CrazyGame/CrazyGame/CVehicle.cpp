#include "CVehicle.h"
#include "CResourceManager.h"
#include "CBitmap.h"

CVehicle::CVehicle(const D2D1_RECT_F& _rect, std::string _strVehicleName) : CObj(_rect)
{
	// 여기서 모든 애니 로딩
	if (_strVehicleName.compare("UFO") == 0)
	{
		CAnimationClip* animClip = CResourceManager::GetInst()->GetAnimationClip("UFO_Back");
		animClip->SetFrametimeLimit(0.1f);
		m_animator.AddClip("UFO_Back", animClip);
		animClip = CResourceManager::GetInst()->GetAnimationClip("UFO_Front");
		animClip->SetFrametimeLimit(0.1f);
		m_animator.AddClip("UFO_Front", animClip);
		animClip = CResourceManager::GetInst()->GetAnimationClip("UFO_Left");
		animClip->SetFrametimeLimit(0.1f);
		m_animator.AddClip("UFO_Left", animClip);
		animClip = CResourceManager::GetInst()->GetAnimationClip("UFO_Right");
		animClip->SetFrametimeLimit(0.1f);
		m_animator.AddClip("UFO_Right", animClip);
		m_animator.SetClip("UFO_Front");

		m_strName = "UFO";
		m_rideHeight = 60.0f;
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
		m_animator.SetClip("UFO_Back");
		break;
	case Dir::Down:
		m_animator.SetClip("UFO_Front");
		break;
	case Dir::Left:
		m_animator.SetClip("UFO_Left");
		break;
	case Dir::Right:
		m_animator.SetClip("UFO_Right");
		break;
	}

	m_animator.Update();
}

void CVehicle::Render(ID2D1RenderTarget* _pRenderTarget)
{
	// Animator에 Render함수를 둔다.

	tAnimationFrame* frame = m_animator.GetCurClip()->GetCurFrame();

	_pRenderTarget->DrawBitmap(CResourceManager::GetInst()->GetIdxBitmap(frame->bitmapIdx)->GetBitmap(),
		m_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		frame->rect);
}