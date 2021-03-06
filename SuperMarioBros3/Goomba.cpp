#include "Goomba.h"
#include "Utils.h"
#include "EffectFactory.h"
#include "Game.h"
#include "Camera.h"
#include "PlayScence.h"

CGoomba::CGoomba()
{
	this->nx = -1;
	SetState(GOOMBA_STATE_WALKING);
	SetAnimationSetById(GOOMBA_ANI_SET_ID);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else
		bottom = y + GOOMBA_BBOX_HEIGHT;
}

void CGoomba::Update(DWORD dt)
{
	Enemy::Update(dt);
	vy += GOOMBA_GRAVITY * dt;

	if (this->state == GOOMBA_STATE_DIE) counter_time += dt;
	if (counter_time >= TIME_STATE_DIE) this->is_dead = true;

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

			if (e->nx != 0) {
				this->nx = e->nx;
				this->vx = e->nx * GOOMBA_WALKING_SPEED;
			}
		
		}
	}

	coObjects.clear();
}

void CGoomba::Render()
{
	int ani = GOOMBA_ANI_WALKING;
	if (state == GOOMBA_STATE_DIE) {
		ani = GOOMBA_ANI_DIE;
	}

	animation_set->at(ani)->Render(x,y);

	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	this->state = state;
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE;
			vx = 0;
			vy = 0;
			EffectFactory::GetInstance()->create(TEXT_NUMBER, this->x, this->y - GOOMBA_BBOX_HEIGHT_DIE, 100);
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->UpdateScore(100);
			break;
		case GOOMBA_STATE_WALKING:
			vx = this->nx*GOOMBA_WALKING_SPEED;
	}
}

void CGoomba::handleJumpingOn() {

	if (this->state != GOOMBA_STATE_DIE)
	{
		this->SetState(GOOMBA_STATE_DIE);
	}		
}

void CGoomba::handleIsAttacked() {

	if (this->state != GOOMBA_STATE_DIE)
		SetState(GOOMBA_STATE_DIE);
}