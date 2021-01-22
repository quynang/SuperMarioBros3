#include "FlyParatroopa.h"
#include "BigBox.h"
#include "Ground.h"
#include "FloatingBrick.h"
#include "Utils.h"
#include "PlayScence.h"
#include "EffectFactory.h"

FlyParatroopa::FlyParatroopa()
{
	this->nx = -1;
	SetState(FLY_PARATROPA_STATE_FLYING);
	SetAnimationSetById(FLY_PARATROPA_ANI_SET_ID);
}

void FlyParatroopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + FLY_PARATROPA_BBOX_WIDTH;
	bottom = top + FLY_PARATROPA_BBOX_HEIGHT;

}

void FlyParatroopa::Update(DWORD dt)
{
	Enemy::Update(dt);
	x += 0;
	y += dy;
	if (this->state == FLY_PARATROPA_STATE_FLYING)
	{
		counter_y += abs(dy);
		if (counter_y >= MAX_Y)
		{
			counter_y = 0;
			this->vy = -this->vy;
		}
	}
	coObjects.clear();
}


void FlyParatroopa::Render()
{
	
	int ani_index = -1;
	if (nx > 0)
		ani_index = FLY_PARATROPA_ANI_INDEX_RIGHT;
	else
		ani_index = FLY_PARATROPA_ANI_INDEX_LEFT;

	animation_set->at(ani_index)->Render(x, y);

	//RenderBoundingBox();
}

void FlyParatroopa::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case FLY_PARATROPA_STATE_FALLING:
		vy = -FLY_PARATROPA_SPEED_y;
		break;
	case FLY_PARATROPA_STATE_FLYING:
		vy = FLY_PARATROPA_SPEED_y;
		break;

	default:
		break;
	}

}

void FlyParatroopa::handleJumpingOn() {
	SetState(FLY_PARATROPA_STATE_FALLING);
}

void FlyParatroopa::handleIsAttacked() {
}


void FlyParatroopa::handleIsKicked(int nx) {

}