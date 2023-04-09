#pragma once

#include "CObj.h"

#include "CAnimator.h"
#include "CAnimationClip.h"

#include <string>

class CVehicle
	: public CObj
{
	std::string m_strName;

	CAnimator           m_animator;
	//CAnimationClip      m_animClip;
	CAnimationClip* m_ridingAnimDir[4];

	Dir m_eMoveDir = Dir::Down;

	u_int m_rideHeight;
	bool m_bAvailable = false;
	float m_speed = 0.0f;

public:
	CVehicle(const D2D1_RECT_F& _rect, std::string _strVehicleName);
	~CVehicle();

	void SetAvailable(bool _bAvailable) { m_bAvailable = _bAvailable; }

	bool GetAvailable() const { return m_bAvailable; }
	u_int GetRideHeight() const { return m_rideHeight; }
	std::string GetName() const { return m_strName; }
	float GetSpeed() const { return m_speed; }

	void Update(D2D1_RECT_F& _rect);
	void Render(ID2D1RenderTarget* _pRenderTarget);

	void SetDir(Dir _dir) { m_eMoveDir = _dir; }
};