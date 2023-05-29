#pragma once
#include "Setting.h"

class CMoveObj;

class Skill
{
protected:
	CMoveObj* m_pOwner = nullptr;
	bool m_skillEnd = false;

public:
	Skill();
	virtual ~Skill();
	virtual void Update();

	bool IsSkillEnd() const { return m_skillEnd; }
};

