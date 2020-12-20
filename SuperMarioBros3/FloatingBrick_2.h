#pragma once
#include "FloatingBrick.h"
class FloatingBrick_2 : public CFloatingBrick
{
public:
	FloatingBrick_2();
	FloatingBrick_2(float init_y, int item_type) : CFloatingBrick(init_y, item_type) {}
};