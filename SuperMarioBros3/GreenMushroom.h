#pragma once
#include "Mushroom.h"
#define GREEN_MUSHROOM_ANI_SET_ID	23
class GreenMushroom : public Mushroom
{
public:
	GreenMushroom(float x, float y) : Mushroom(x, y) {
		SetAnimationSetById(GREEN_MUSHROOM_ANI_SET_ID);
		this->type = ITEM_GREEN_MUSHROOM;
	};
	
	void handleIsCollected() { this->is_dead = true; };
};
