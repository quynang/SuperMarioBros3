#include "BreakableBrick.h"
#include "Utils.h"
#include "ItemFactory.h"
#include "EffectFactory.h"

void BreakableBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BREAKABLE_BRICK_BBOX_WIDTH;
	bottom = y + BREAKABLE_BRICK_BBOX_HEIGHT;
}

void BreakableBrick::Update(DWORD dt)
{

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
	EffectFactory::GetInstance()->create(COIN_50, this->x, this->y);
}

void BreakableBrick::handleIsBroken() {
	if (!is_dead)
	EffectFactory::GetInstance()->create(BROKEN, this->x + 8, this->y - 8);
	this->is_dead = true;	
}