#pragma once
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"
#include "BigBox.h"
#include "Goomba.h"
#include "Portal.h"
#include "IdleState.h"
#include "FallingState.h"
#include "Ground.h"
#include "FloatingBrick.h"

CMario::CMario(float x, float y) : CGameObject()
{
	type = MARIO_TYPE_SMALL;
	untouchable = 0;
	start_x = x; 
	start_y = y; 
	this->x = x; 
	this->y = y;
	marioState = new FallingState();
}

void CMario::SetAni(int ani) {
	this->ani = ani;
}

void CMario::handleOnKeyUp(int keyCode) {
	marioState->handleOnKeyUp(*this, keyCode);
}
void CMario::handleOnKeyDown(int keyCode) {
	marioState->handleOnKeyDown(*this, keyCode);
}
void CMario::handleKeyState(BYTE* states) {
	marioState->handleKeyState(*this, states);
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	vy += MARIO_GRAVITY * dt;
	marioState->update(*this, dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state!=MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
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

		x += min_tx*dx + nx*0.4f;
		y += min_ty*dy + ny*0.4f;

		if (nx!=0) vx = 0;
		if (ny!=0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba *>(e->obj))
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				if (e->ny < 0)
				{
					if (goomba->GetState()!= GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
						marioState = new IdleState();
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable==0)
					{
						if (goomba->GetState()!=GOOMBA_STATE_DIE)
						{
							if (type > MARIO_TYPE_SMALL)
							{
								type = MARIO_TYPE_SMALL;
								StartUntouchable();
							}
							else 
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			}

			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}

		
			else if (dynamic_cast<CGround *>(e->obj))
			{

				if (e->ny < 0 && current_state != JUMPING)// Bug fix
					marioState = new IdleState();
			}

			else if (dynamic_cast<CBigBox *>(e->obj))
			{
				if (e->ny < 0  && current_state != JUMPING)
					marioState = new IdleState();
				else {
					x += dx; 
					
				}
				
			}

			else if (dynamic_cast<CFloatingBrick *>(e->obj))
			{
				
				CFloatingBrick *floatingBrick = dynamic_cast<CFloatingBrick *>(e->obj);

				if (e->ny > 0) {

					y += e->t*dy + e->ny*0.4f;
					vy += MARIO_GRAVITY*dt;

					if (current_state != FALLING)
						marioState = new FallingState();

					if (floatingBrick->flag_ == 0)
						floatingBrick->SetState(DEFLECT_STATE);
					
					
				}
			}
		
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (x < 0) x = 0;

}

void CMario::Render()
{

	int alpha = 255;

	if (untouchable) alpha = 128;

	//RenderBoundingBox();
	animation_set->at(ani)->Render(x, y, alpha);

}

void CMario::SetState(int state)
{
	//TODO: Remove this.
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 

	if (type == MARIO_TYPE_BIG)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetType(MARIO_TYPE_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

