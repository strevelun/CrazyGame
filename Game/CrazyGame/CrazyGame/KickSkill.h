#pragma once
#include "BubbleSkill.h"
class KickSkill :
    public BubbleSkill
{
private:

public:
    KickSkill(CBubble* _pOwner, eDir _eDir);
    ~KickSkill();
    void Update() override;
};

