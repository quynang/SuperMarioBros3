#pragma once
#include "FloatingBrick.h"
#define	FLOATING_BRICK_2_ANI_SET_ID	22
class FloatingBrick_2 : public CFloatingBrick
{
public:
	FloatingBrick_2() { this->SetAnimationSetById(FLOATING_BRICK_2_ANI_SET_ID); }
};