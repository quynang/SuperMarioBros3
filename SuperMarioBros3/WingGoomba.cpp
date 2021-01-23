#include "WingGoomba.h"
#include "BigBox.h"
#include "Ground.h"
#include "FloatingBrick.h"
#include "Utils.h"
#include "PlayScence.h"
#include "EffectFactory.h"
WingGoomba::WingGoomba()
{
	this->type = TYPE_HAS_WING;
	this->SetState(WING_GOOMBA_STATE_WALKING);
	setStep(STEP_JUMPING_NONE);
	SetAnimationSetById(WING_GOOMBA_ANI_SET_ID);
	
}

void WingGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	switch (this->type) {

	case TYPE_HAS_WING:
		{	
			right = x + (this->state == WING_GOOMBA_STATE_JUMPING ? WING_GOOMBA_JUMPING_BBOX_WIDTH : WING_GOOMBA_WALKING_BBOX_WIDTH);
			bottom = y + (this->state == WING_GOOMBA_STATE_JUMPING ? WING_GOOMBA_JUMPING_BBOX_HEIGHT : WING_GOOMBA_WALKING_BBOX_HEIGHT);
		}
		break;
	case TYPE_LOST_WING:
		{
			right = x + WING_GOOMBA_LOST_WING_BBOX_WIDTH;
			bottom = y + (this->state == WING_GOOMBA_STATE_DEAD ? WING_GOOMBA_DEAD_BBOX_HEIGHT : WING_GOOMBA_LOST_WING_BBOX_HEIGHT);
		}
		break;
	}

}

void WingGoomba::Update(DWORD dt)
{
	
	Enemy::Update(dt);

	if (this->state == WING_GOOMBA_STATE_WALKING) vy += WING_GOOMBA_GRAVITY;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	
	coEvents.clear();

	CalcPotentialCollisions(&coObjects, coEvents);
	
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
			if (e->ny > 0)
				this->JumpToNextStep();
		
		}

		if(state != WING_GOOMBA_STATE_DEAD) SetState(WING_GOOMBA_STATE_WALKING);
	}

	coObjects.clear();


	//Looping step
	if (type == TYPE_HAS_WING) {
		if (step == STEP_JUMPING_NONE) charge_x += abs(dx);

		if (this->state == WING_GOOMBA_STATE_JUMPING) charge_time_jump += dt;

		if (charge_x >= MAX_CHARGE_X) { setStep(STEP_JUMPING_1); charge_x = 0; };


		switch (step)
		{
		case STEP_JUMPING_1:
			if (this->state == WING_GOOMBA_STATE_WALKING) SetState(WING_GOOMBA_STATE_JUMPING);

			if (charge_time_jump >= MAX_DEBOUNCING_TIME) {
				vy += dt * WING_GOOMBA_GRAVITY;
				setStep(STEP_JUMPING_2);
				charge_time_jump = 0;
			}
			break;

		case STEP_JUMPING_2:
			if (this->state == WING_GOOMBA_STATE_WALKING) SetState(WING_GOOMBA_STATE_JUMPING);

			if (charge_time_jump >= MAX_DEBOUNCING_TIME) {
				vy += dt * WING_GOOMBA_GRAVITY;
				setStep(STEP_JUMPING_3);
				charge_time_jump = 0;
			}
			break;

		case STEP_JUMPING_3:
			if (this->state == WING_GOOMBA_STATE_WALKING) SetState(WING_GOOMBA_STATE_JUMPING);
			if (charge_time_jump >= MAX_JUMPING_TIME) {
				vy += dt * WING_GOOMBA_GRAVITY;
				setStep(STEP_JUMPING_NONE);
				charge_time_jump = 0;
			}
			break;
		}
	}

	if (state == WING_GOOMBA_STATE_DEAD ) {
		counter_time_dead_ani += dt;
		if(counter_time_dead_ani >= 100) this->is_dead = true;
	}

	//Walking follow mario.
	float _x, _y;
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetPosition(_x, _y);

	if (this->x - _x > 0) { this->nx = -1; }

	else if (this->x - _x < 0) { this->nx = 1; }
	
}


void WingGoomba::Render()
{
	int ani_index = -1;
	switch (this->type) {
		case TYPE_HAS_WING:
		{
			if (this->state == WING_GOOMBA_STATE_WALKING) {
				ani_index = WING_GOOMBA_HAS_WING_ANI_WALKING_INDEX;
			}

			else if (this->state == WING_GOOMBA_STATE_JUMPING) {
				ani_index = WING_GOOMBA_HAS_WING_ANI_JUMPING_INDEX;
	
			}
		};
		break;
			
		case TYPE_LOST_WING:
		{

			if (this->state == WING_GOOMBA_STATE_WALKING) {
				ani_index = WING_GOOMBA_LOST_WING_ANI_WALKING_INDEX;
			}

			else if (this->state == WING_GOOMBA_STATE_DEAD) {
				ani_index = WING_GOOMBA_ANI_DEAD_INDEX;
			}

			else if (this->state == WING_GOOMBA_STATE_JUMPING)
				ani_index = WING_GOOMBA_LOST_WING_ANI_WALKING_INDEX;

		}

		break;
	
	}
	
	animation_set->at(ani_index)->Render(x, y);

	//RenderBoundingBox();
}

void WingGoomba::SetState(int state)
{
	this->state = state;
	switch (state)
	{
		case WING_GOOMBA_STATE_WALKING:
			vx = this->nx * WING_GOOMBA_WALKING_SPEED;
			vy += WING_GOOMBA_GRAVITY;
			break;
		case WING_GOOMBA_STATE_JUMPING:
			vy = DEBOUNCING_SPEED_Y;
			break;
		case WING_GOOMBA_STATE_DEAD:
			type = TYPE_LOST_WING;
			vx = 0;
			y += WING_GOOMBA_LOST_WING_BBOX_HEIGHT - WING_GOOMBA_DEAD_BBOX_HEIGHT;
			vy = WING_GOOMBA_GRAVITY;
			break;
	}

}
void WingGoomba::setStep(int step) { 
	this->step = step;
}

void WingGoomba::handleJumpingOn() {
	switch (type) {
		case TYPE_HAS_WING:
			this->type = TYPE_LOST_WING;
			this->SetState(WING_GOOMBA_STATE_WALKING);
			EffectFactory::GetInstance()->create(TEXT_NUMBER, this->x, this->y - WING_GOOMBA_DEAD_BBOX_HEIGHT, 400);
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->UpdateScore(400);
			break;
		case TYPE_LOST_WING:
			if (this->state != WING_GOOMBA_STATE_DEAD) {
				this->SetState(WING_GOOMBA_STATE_DEAD);
				EffectFactory::GetInstance()->create(TEXT_NUMBER, this->x, this->y - WING_GOOMBA_DEAD_BBOX_HEIGHT, 800);
				((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->UpdateScore(800);
			}
			break;
	}
}


void WingGoomba::handleIsAttacked()
{
	if (this->state != WING_GOOMBA_STATE_DEAD)
	{
		SetState(WING_GOOMBA_STATE_DEAD);
		EffectFactory::GetInstance()->create(TEXT_NUMBER, this->x, this->y - 10, 800);
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->UpdateScore(800);
	}
	
}
