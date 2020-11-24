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
#include "Koopas.h"
#include "KickState.h"
#include "HoldingState.h"
#include "GreenPipe.h"
#include "Textures.h"

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

void CMario::handleOnKeyUp(int keyCode) {
	marioState->handleOnKeyUp(*this, keyCode);
}
void CMario::handleOnKeyDown(int keyCode) {
	marioState->handleOnKeyDown(*this, keyCode);
}
void CMario::handleKeyState(BYTE* states) {
	marioState->handleKeyState(*this, states);
}

void CMario::SetPosForItemPicked() {

	float l_, t_, r_, b_;

	this->GetBoundingBox(l_, t_, r_, b_);

	if (this->nx > 0)
	{
		item_holding->nx = 1;
		item_holding->x = r_ - 2;
		item_holding->y = (b_ - t_) / 2 + t_ - 8;
	}
	else
	{
		item_holding->x = l_ - 16 + 2;
		item_holding->y = (b_ - t_)/2  + t_ - 8;
		item_holding->nx = -1;

	}
}
void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	vy += MARIO_GRAVITY * dt;
	marioState->update(*this, dt);

	if (!can_pick_item && item_holding != NULL)
	{
		//TODO: What if item picked is not Koopas ?
		marioState = new KickState();
		((CKoopas*)item_holding)->TurnOnUpdation();
		((CKoopas*)item_holding)->SetState(KOOPAS_STATE_SLIDING);
		item_holding = NULL;
	}
	
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state!=MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
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
			} else if (dynamic_cast<CKoopas *>(e->obj))

			{
				CKoopas *koopas = dynamic_cast<CKoopas *>(e->obj);

				if (e->ny < 0)
				{
					if (koopas->GetState() != KOOPAS_STATE_HIDE_IN_SHELL)
					{
						vy = -0.5f;//TODO: naming this value
						x -= 6;//Remove this. It's just for testing.
						
						koopas->SetState(KOOPAS_STATE_HIDE_IN_SHELL);
					}
					
					else if (koopas->GetState() == KOOPAS_STATE_HIDE_IN_SHELL)
					{
						koopas->nx = this->nx;
						koopas->SetState(KOOPAS_STATE_SLIDING);

					}
				}
				else if (e->nx != 0)
				{
					if (koopas->GetState() == KOOPAS_STATE_HIDE_IN_SHELL)
					{
						if (!can_pick_item)
						{
							marioState = new KickState();
							koopas->nx = - e->nx;
							koopas->SetState(KOOPAS_STATE_SLIDING);
						}
						else
						{
							marioState = new HoldingState();
							item_holding = koopas;
							((CKoopas*)item_holding)->TurnOffUpdation();
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

				if (e->ny < 0 && (marioState->current_state == FALLING || marioState->current_state == FALLING_WHILE_FLYING))// Bug fix
					marioState = new IdleState();
			}

			else if (dynamic_cast<CBigBox *>(e->obj))  
			{
				if (e->ny < 0 &&  (marioState->current_state == FALLING || marioState->current_state == FALLING_WHILE_FLYING))
				{
					marioState = new IdleState();
				}
				if (e->nx != 0) {
					x += dx;
				}
			}

			else if (dynamic_cast<CFloatingBrick *>(e->obj))
			{
				
				CFloatingBrick *floatingBrick = dynamic_cast<CFloatingBrick *>(e->obj);

				if (e->ny > 0) {

					y += e->t*dy + e->ny*0.4f;
					vy += MARIO_GRAVITY*dt;

					if (marioState->current_state != FALLING)
						marioState = new FallingState();

					if (floatingBrick->flag_ == 0)
						floatingBrick->SetState(DEFLECT_STATE);
					
					
				}
			}

			else if (dynamic_cast<CGreenPipe *>(e->obj))
			{
				if (e->ny < 0 &&  (marioState->current_state == FALLING || marioState->current_state == FALLING_WHILE_FLYING))
				{
					marioState = new IdleState();
					x += dx;
				}
			}
		
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (x < 0) x = 0;
		
	if (item_holding != NULL)
		SetPosForItemPicked();

	if (marioState->current_state == TAIL_SMACKING_2)
		handleTailAttacking(coObjects);
	
}

void CMario::Render()
{
	int alpha = 255;

	if (untouchable) alpha = 128;

	int ani = marioState->getAni(*this);

	RenderBoundingBox();
	animation_set->at(ani)->Render(x, y, alpha);

	/*if (marioState->current_state == TAIL_SMACKING_2) {
		RECT tail_rect = this->getTailRect();
		LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);
		CGame::GetInstance()->Draw(tail_rect.left, tail_rect.top, bbox, 0, 0, TAIL_BBOX_WIDTH, TAIL_BBOX_HEIGHT, 150);
	}*/
	

}

void CMario::SetState(int state)
{
	//TODO: Remove this.
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	//TODO: Fix bounding box for all state of mario.
	left = x;
	top = y; 

	if (type == MARIO_TYPE_SMALL)
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
	else
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
}

RECT CMario::getTailRect() {

	RECT tail_rect;
	float l_, t_, r_, b_;

	this->GetBoundingBox(l_, t_, r_, b_);

	if (this->nx > 0)
	{
		tail_rect.top = b_ - (DISTANCE_FROM_FOOT_TO_TAIL + TAIL_BBOX_HEIGHT);
		tail_rect.left = r_;
		tail_rect.right = r_ + TAIL_BBOX_WIDTH;
		tail_rect.bottom = b_ - DISTANCE_FROM_FOOT_TO_TAIL;
	}
	else
	{
		tail_rect.top = b_ - (DISTANCE_FROM_FOOT_TO_TAIL + TAIL_BBOX_HEIGHT);
		tail_rect.left =  l_ - TAIL_BBOX_WIDTH;
		tail_rect.right = l_;
		tail_rect.bottom = b_ - DISTANCE_FROM_FOOT_TO_TAIL;
	}

	return tail_rect;
}

void CMario::getPositionOfHandWhenThrowing(float& x, float& y) {

	float l_, t_, r_, b_;

	this->GetBoundingBox(l_, t_, r_, b_);

	if (nx > 0) {
		x = r_;
		y = t_ + DISTANCE_FROM_HEAD_TO_HAND;
	}
	else
	{
		x = l_;
		y = t_ + DISTANCE_FROM_HEAD_TO_HAND;
	}
}

void CMario::handleTailAttacking(vector<LPGAMEOBJECT> *coObjects) {

	RECT tail_rect = this->getTailRect();

	for (UINT i = 0; i < coObjects->size(); i++) {
		RECT obj_rect;
		float l, t, r, b;
		coObjects->at(i)->GetBoundingBox(l, t, r, b);
		obj_rect.top = t;
		obj_rect.left = l;
		obj_rect.right = r;
		obj_rect.bottom = b;

		bool isOverlapping = CGame::GetInstance()->isColliding(tail_rect, obj_rect);

		if (isOverlapping && dynamic_cast<CGoomba*>(coObjects->at(i))) {

			CGoomba *goomba = dynamic_cast<CGoomba *>(coObjects->at(i));
		
			if (goomba->GetState()!= GOOMBA_STATE_DIE)
			{
				goomba->SetState(GOOMBA_STATE_DIE);

			}
			
		}
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

