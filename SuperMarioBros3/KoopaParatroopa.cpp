#include "KoopaParatroopa.h"
#include "BigBox.h"
#include "Ground.h"
#include "FloatingBrick.h"
#include "Utils.h"
#include "PlayScence.h"
#include "EffectFactory.h"

KoopaParatroopa::KoopaParatroopa()
{
	this->nx = -1;
	this->vx = this->nx*PARATROPA_WALKING_SPEED;
	this->type = PARATROPA_TYPE_HAS_WING;
	this->SetState(PARATROPA_STATE_FALLING);
	
}

void KoopaParatroopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (this->state == PARATROPA_STATE_HIDING_IN_SHELL || this->state == PARATROPA_STATE_SLIDING ) {
		right = left + PARATROPA_SHELL_BBOX_WIDTH;
		bottom = top + PARATROPA_SHELL_BBOX_HEIGHT;
	}
	else {
		right = left + PARATROPA_BBOX_WIDTH;
		bottom = top + PARATROPA_BBOX_HEIGHT;
	}
}

void KoopaParatroopa::Update(DWORD dt)
{
	
	Enemy::Update(dt);
	if(state != PARATROPA_STATE_JUMPING) vy += PARATROPA_GRAVITY;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	
	coEvents.clear();

	CalcPotentialCollisions(&coStaticObjects, coEvents);
	
	if (coEvents.size()==0)
	{
		x += dx;
		y += dy;
	
	}

	else
	{
		
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->ny < 0) {
				this->vx = this->nx * PARATROPA_WALKING_SPEED;
				if(this->type != PARATROPA_TYPE_LOST_WING ) SetState(PARATROPA_STATE_JUMPING);
			}
				
			else if (e->ny > 0)
				SetState(PARATROPA_STATE_FALLING);
			else if (e->nx != 0) {
				this->nx = e->nx;
				this->vx = this->nx * PARATROPA_WALKING_SPEED;
			}
				
		
		}

	}

	if (this->state == PARATROPA_STATE_JUMPING) jumping_time += dt;
	if (jumping_time >= MAX_JUMPING_TIME) {
		jumping_time = 0;
		SetState(PARATROPA_STATE_FALLING);
	}
		
	coStaticObjects.clear();


}


void KoopaParatroopa::Render()
{
	
	int ani_index = -1;
	switch (this->state)
	{
	case PARATROPA_STATE_WALKING:
		if (type == PARATROPA_TYPE_HAS_WING)
			ani_index = this->nx > 0 ? PARATROPA_ANI_INDEX_WALKING_RIGHT : PARATROPA_ANI_INDEX_WALKING_LEFT;
		else
			ani_index = this->nx > 0 ? PARATROPA_LOST_WING_ANI_INDEX_WALKING_RIGHT : PARATROPA_LOST_WING_ANI_INDEX_WALKING_LEFT;
		break;
	case PARATROPA_STATE_FALLING:
		if (type == PARATROPA_TYPE_HAS_WING)
			ani_index = this->nx > 0 ? PARATROPA_ANI_INDEX_WALKING_RIGHT : PARATROPA_ANI_INDEX_WALKING_LEFT;
		else
			ani_index = this->nx > 0 ? PARATROPA_LOST_WING_ANI_INDEX_WALKING_RIGHT : PARATROPA_LOST_WING_ANI_INDEX_WALKING_LEFT;
		break;

	case PARATROPA_STATE_JUMPING:
		if (type == PARATROPA_TYPE_HAS_WING)
			ani_index = this->nx > 0 ? PARATROPA_ANI_INDEX_WALKING_RIGHT : PARATROPA_ANI_INDEX_WALKING_LEFT;
		else
			ani_index = this->nx > 0 ? PARATROPA_LOST_WING_ANI_INDEX_WALKING_RIGHT : PARATROPA_LOST_WING_ANI_INDEX_WALKING_LEFT;
		break;
	case PARATROPA_STATE_HIDING_IN_SHELL:
		ani_index = PARATROPA_ANI_INDEX_HIDING_IN_SHELL;
		break;
	case PARATROPA_STATE_SLIDING:
		ani_index = PARATROPA_ANI_INDEX_SLIDING;
		break;
	}

	animation_set->at(ani_index)->Render(x, y);

	//RenderBoundingBox();
}

void KoopaParatroopa::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case PARATROPA_STATE_WALKING:
		vy = this->nx * PARATROPA_WALKING_SPEED;
		break;
	case PARATROPA_STATE_FALLING:
		vy = PARATROPA_GRAVITY;
		jumping_time = 0;
		break;

	case PARATROPA_STATE_JUMPING:
		vy = PARATROPA_JUMPING_SPEED;
		break;
	case PARATROPA_STATE_HIDING_IN_SHELL:
		vx = 0;
		break;
	case PARATROPA_STATE_SLIDING:
		vx = PARATROPA_SLIDING_SPEED;
		break;
	default:
		break;
	}

}

void KoopaParatroopa::handleIsTrampled() {
	
}