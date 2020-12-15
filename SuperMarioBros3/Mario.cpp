#pragma once
#include <algorithm>
#include <assert.h>
#include "Utils.h"
#include "Mario.h"
#include "Game.h"
#include "BigBox.h"
#include "Goomba.h"
#include "Portal.h"
#include "Ground.h"
#include "FloatingBrick.h"
#include "Koopas.h"
#include "GreenPipe.h"
#include "Textures.h"
#include "Coin50.h"
#include "Mushroom.h"
#include "BreakableBrick.h"
#include "EffectFactory.h"
#include "PlayScence.h"

//TODO: How to haven't to include state here.
#include "WalkingState.h"
#include "JumpingState.h"
#include "FallingWhileFlyingState.h"
#include "FlyingState.h"
#include "TailSmacking_1_State.h"
#include "TailSmacking_2_State.h"
#include "TailSmacking_3_State.h"
#include "Throw_1_State.h"
#include "Throw_2_State.h"
#include "KickState.h"
#include "HoldingState.h"
#include "IdleState.h"
#include "FallingState.h"
#include "BouncingState.h"


CMario::CMario(float x, float y) : MovableObject()
{
	type = MARIO_TYPE_SMALL;
	untouchable = 0;
	start_x = x; 
	start_y = y;
	this->x = x; 
	this->y = y;
	state = new FallingState();
}

void CMario::handleOnKeyUp(int keyCode) {
	state->handleOnKeyUp(*this, keyCode);
}
void CMario::handleOnKeyDown(int keyCode) {
	state->handleOnKeyDown(*this, keyCode);
}
void CMario::handleKeyState(BYTE* states) {
	state->handleKeyState(*this, states);
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
void CMario::Update(DWORD dt)
{
	//DebugOut(L"Mario objects to check size: %d\n", m_coObjects.size());
	CGameObject::Update(dt);
	vy += MARIO_GRAVITY * dt;
	state->update(*this, dt);

	if (!can_pick_item && item_holding != NULL)
	{
		//TODO: What if item picked is not Koopas ?
		state = new KickState();
		((CKoopas*)item_holding)->TurnOnUpdation();
		((CKoopas*)item_holding)->SetState(KOOPAS_STATE_SLIDING);
		item_holding = NULL;
	}
	
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(&m_coObjects, coEvents);


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
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
						state = new BouncingState();
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
						state = new BouncingState();
						
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
							state = new KickState();
							koopas->nx = - e->nx;
							koopas->SetState(KOOPAS_STATE_SLIDING);
						}
						else
						{
							state = new HoldingState();
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

				if (e->ny < 0 && (state->current_state == FALLING || state->current_state == FALLING_WHILE_FLYING))// Bug fix
					state = new IdleState();
			}

			else if (dynamic_cast<BreakableBrick *>(e->obj))
			{

				if (e->ny < 0 && (state->current_state == FALLING || state->current_state == FALLING_WHILE_FLYING))// Bug fix
					state = new IdleState();
			}

			else if (dynamic_cast<CBigBox *>(e->obj))  
			{
				if (e->ny < 0 &&  (state->current_state == FALLING || state->current_state == FALLING_WHILE_FLYING))
				{
					state = new IdleState();
				}
				if (e->nx != 0) {
					x += dx;
				}
			}

			else if (dynamic_cast<Mushroom *>(e->obj))  
			{
				Mushroom *mushroom = dynamic_cast<Mushroom *>(e->obj);
				mushroom->is_dead = true;
				SetType(MARIO_TYPE_BIG);
				state = new IdleState();
				EffectFactory::GetInstance()->create(MARIO_TYPE_UP, this->x, this->y, this->nx);
				y = y - (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT);
			}

			else if (dynamic_cast<CFloatingBrick *>(e->obj))
			{
				
				CFloatingBrick *floatingBrick = dynamic_cast<CFloatingBrick *>(e->obj);

				if (e->ny > 0) {

					y += e->t*dy + e->ny*0.4f;
					vy += MARIO_GRAVITY*dt;

					if (state->current_state != FALLING)
						state = new FallingState();

					if (floatingBrick->GetState() != STATIC_STATE) {
						floatingBrick->SetState(BOUNCING_STATE);
					}
					
					
				}
			}

			else if (dynamic_cast<CGreenPipe *>(e->obj))
			{
				if (e->ny < 0 &&  (state->current_state == FALLING || state->current_state == FALLING_WHILE_FLYING))
				{
					state = new IdleState();
					x += dx;
				}
			}

			else if (dynamic_cast<Coin50 *>(e->obj))
			{
				Coin50 *coin_50 = dynamic_cast<Coin50 *>(e->obj);
				coin_50->is_dead = true;
			}
		
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (x < 0) x = 0;
		
	if (item_holding != NULL)
		SetPosForItemPicked();

	if (state->current_state == TAIL_SMACKING_2)
		handleTailAttacking(&m_coObjects);

	m_coObjects.clear();
	
}

void CMario::Render()
{
	int alpha = 255;

	if (untouchable) alpha = 128;

	int ani = state->getAni(*this);

	//RenderBoundingBox();

	if(is_visible) animation_set->at(ani)->Render(x, y, alpha);

	/*if (marioState->current_state == TAIL_SMACKING_2) {
		RECT tail_rect = this->getTailRect();
		LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);
		CGame::GetInstance()->Draw(tail_rect.left, tail_rect.top, bbox, 0, 0, TAIL_BBOX_WIDTH, TAIL_BBOX_HEIGHT, 150);
	}*/
	

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

void CMario::SetState(int state) {
	switch (state)
	{
	case IDLE:
		this->state = new IdleState();
		break;
	case WALKING:
		this->state = new WalkingState();
		break;
	case FALLING:
		this->state = new FallingState();
		break;
	case JUMPING:
		this->state = new JumpingState();
		break;
	case FLYING:
		this->state = new FlyingState();
		break;
	case FALLING_WHILE_FLYING:
		this->state = new FallingState();
		break;
	case KICK:
		this->state = new KickState();
		break;
	case HOLDING:
		this->state = new HoldingState();
		break;
	case TAIL_SMACKING_1:
		this->state = new TailSmacking_1_State();
		break;
	case TAIL_SMACKING_2:
		this->state = new TailSmacking_2_State();
		break;
	case TAIL_SMACKING_3:
		this->state = new TailSmacking_3_State();
		break;
	case THROW_1:
		this->state = new Throw_1_State();
		break;
	case THROW_2:
		this->state = new Throw_2_State();
		break;

	}
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetType(MARIO_TYPE_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

