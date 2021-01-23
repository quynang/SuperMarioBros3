#include "BreakableBrick.h"
#include "Utils.h"
#include "ItemFactory.h"
#include "EffectFactory.h"

void BreakableBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!this->visible) return;
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
	if(this->visible)
		animation_set->at(0)->Render(x,y);
	//RenderBoundingBox();	
}

void BreakableBrick::SetState(int state)
{
	this->state = state;
}

void BreakableBrick::ProduceItem() {
	ItemFactory::GetInstance()->create(ITEM_COIN_50, this->x, this->y);
	this->visible = false;
}

void BreakableBrick::handleWasAttacked() {
	if (!is_dead)
	EffectFactory::GetInstance()->create(BROKEN, this->x + BREAKABLE_BRICK_BBOX_WIDTH/2, this->y - BREAKABLE_BRICK_BBOX_HEIGHT/2);
	this->is_dead = true;	
}

void BreakableBrick::handleWasHitByHeadOfMario() {
	if (!is_dead)
	EffectFactory::GetInstance()->create(BROKEN, this->x + BREAKABLE_BRICK_BBOX_WIDTH/2, this->y - BREAKABLE_BRICK_BBOX_HEIGHT/2);
	this->is_dead = true;	
}


