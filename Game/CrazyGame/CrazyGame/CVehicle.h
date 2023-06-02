#pragma once

#include "CMoveObj.h"

#include "CAnimator.h"
#include "CAnimationClip.h"

#include <string>

class CVehicle
	: public CMoveObj
{

	std::wstring m_strName;

	CAnimationClip* m_ridingAnimDir[4];

	eDir m_eMoveDir = eDir::Down;

	u_int m_rideHeight = 0;
	float m_speed = 0.0f;

public:
	CVehicle(const D2D1_RECT_F& _rect, std::wstring _strVehicleName);
	~CVehicle();

	u_int GetRideHeight() const { return m_rideHeight; }
	std::wstring GetName() const { return m_strName; }
	float GetSpeed() const { return m_speed; }

	void Update(D2D1_RECT_F& _rect);
	void Render(ID2D1BitmapRenderTarget* _pRenderTarget);

	void SetDir(eDir _dir) { m_eMoveDir = _dir; }
};