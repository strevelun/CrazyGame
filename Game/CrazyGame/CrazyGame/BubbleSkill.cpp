#include "BubbleSkill.h"

BubbleSkill::BubbleSkill(eDir _eDir)
{
	m_dirX = 0; m_dirY = 0;
	m_eMovingDir = _eDir;

	switch (_eDir)
	{
	case eDir::Left:
		m_dirX = -1;
		break;
	case eDir::Right:
		m_dirX = 1;
		break;
	case eDir::Up:
		m_dirY = -1;
		break;
	case eDir::Down:
		m_dirY = 1;
		break;
	}
}

BubbleSkill::~BubbleSkill()
{
}

void BubbleSkill::Update()
{
}
