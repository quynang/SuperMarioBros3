#pragma once

#include "Sprites.h"
#include "Animations.h"
#include <iostream>
class Effect {
protected:
	float x, y;
	LPANIMATION_SET animation_set;
	
public:
	bool is_finished = false;
	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; };
	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};