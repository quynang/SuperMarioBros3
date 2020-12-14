#include "BreakableBrick.h"
#include "Utils.h"
#include "ItemFactory.h"

void BreakableBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BREAKABLE_BRICK_BBOX_WIDTH;
	bottom = y + BREAKABLE_BRICK_BBOX_HEIGHT;
}

void BreakableBrick::Update(DWORD dt)
{

	m_coObjects.clear();
}


void BreakableBrick::Render()
{
	
	animation_set->at(0)->Render(x,y);
	//RenderBoundingBox();	
}

void BreakableBrick::SetState(int state)
{
	this->state = state;
	
}

void BreakableBrick::ProduceItem() {
}
