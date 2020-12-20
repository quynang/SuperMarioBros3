#pragma once
#include "Mushroom.h"
#define GREEN_MUSHROOM_ANI_SET_ID	23
class GreenMushroom : public Mushroom
{
public:
	GreenMushroom(float x, float y) : Mushroom(x, y) {
		CAnimationSets* animation_sets = CAnimationSets::GetInstance();
		SetAnimationSet(animation_sets->Get(GREEN_MUSHROOM_ANI_SET_ID));
	};
};
