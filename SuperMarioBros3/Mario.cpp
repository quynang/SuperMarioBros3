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
#include "ButtonP.h"
#include "BreakableBrick.h"
#include "EffectFactory.h"
#include "PlayScence.h"
#include "SuperLeaf.h"
#include "WingGoomba.h"

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
#include "IdleState.h"
#include "FallingState.h"
#include "BouncingState.h"
#include "DieState.h"


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

void CMario::Update(DWORD dt)
{
	state->update(*this, dt);
	CGameObject::Update(dt);
	vy += MARIO_GRAVITY * dt;

	updatePower(dt);

	if (!can_pick_item && item_holding != NULL)
	{
		state = new KickState();
		((Enemy*)item_holding)->TurnOnUpdation();
		((Enemy*)item_holding)->handleIsKicked(this->nx);
		item_holding = NULL;
		is_holding = false;
	}

	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (state->current_state == DIE)
	{
		x += dx;
		y += dy;
	}

	else
	{
		processCollision();
	}
	
	if (x < 0) x = 0;
	if (x > CMap::GetInstance()->getWidth() - MARIO_BIG_BBOX_WIDTH)
	{
		state = new IdleState();
		x = CMap::GetInstance()->getWidth() - MARIO_BIG_BBOX_WIDTH;
	}
		
	if (item_holding != NULL)
		SetPosForItemPicked();

	if (state->current_state == TAIL_SMACKING_2)
		handleTailAttacking();

	coObjects.clear();

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

void CMario::handleTailAttacking() {

	RECT tail_rect = this->getTailRect();

	for (UINT i = 0; i < coObjects.size(); i++) {

		RECT obj_rect;
		float l, t, r, b;
		coObjects.at(i)->GetBoundingBox(l, t, r, b);
		obj_rect.top = t;
		obj_rect.left = l;
		obj_rect.right = r;
		obj_rect.bottom = b;

		bool isOverlapping = CGame::GetInstance()->isColliding(tail_rect, obj_rect);

		if (isOverlapping && dynamic_cast<Enemy*>(coObjects.at(i))) {
			((Enemy*)coObjects.at(i))->handleIsAttacked();
		}

		else if (isOverlapping && dynamic_cast<BreakableBrick*>(coObjects.at(i))) {
			BreakableBrick *breakable_brick = dynamic_cast<BreakableBrick *>(coObjects.at(i));
			breakable_brick->handleIsBroken();
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

void CMario::processCollision() {

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(&coObjects, coEvents);

	float min_tx, min_ty, nx = 0, ny;
	float rdx = 0; 
	float rdy = 0;

	if (coEvents.size()==0)
	{
		x += dx;
		y += dy;
	
		if (state->current_state == WALKING)
			state = new FallingState();
	}
	else 
	{

		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0; 
		float rdy = 0;
		
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx*dx + nx*0.1f;
		y += min_ty*dy + ny*0.1f;

		if (nx!=0) vx = 0;
		if (ny!=0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			//For the case that object can jump on top of mario
			if (e->ny > 0)
				y -= 0.4f;

			if (dynamic_cast<StaticObject*>(e->obj))
			{
				if (e->ny < 0 && (state->current_state == FALLING || state->current_state == FALLING_WHILE_FLYING))// Bug fix
					state = new IdleState();
				else if (e->ny > 0 && state->current_state == JUMPING)
					state = new FallingState();
			}
			else if (dynamic_cast<Item*>(e->obj))
			{
				Item* item = dynamic_cast<Item*>(e->obj);
				item->handleIsCollected();
				this->handleCollectItem(item->type);
			}
			else if (dynamic_cast<Enemy*>(e->obj))
			{
				Enemy* enemy = dynamic_cast<Enemy*>(e->obj);

				if (e->ny < 0)
				{
					if (enemy->canBeJumpedOn())
					{
						enemy->handleJumpingOn();
						state = new BouncingState();
					}
					else
					{
						this->isHurted();
					}
				}

				else if (e->ny > 0)
				{
					this->isHurted();
				}

				else if (e->nx != 0)
				{
					if (enemy->canBePickedUp() && this->can_pick_item)
					{
						this->is_holding = true;
						this->item_holding = enemy;
						((Enemy*)e->obj)->TurnOffUpdation();
					}
					else if (enemy->canBeKicked() && !this->can_pick_item)
					{
						enemy->handleIsKicked(-e->nx);
						state = new KickState();
					}
					else
					{
						this->isHurted();
					}
				}
			}
			else //For other object type.
			{
				if (dynamic_cast<ButtonP*>(e->obj))
				{
					if (e->ny < 0)
					{
						ButtonP* button = dynamic_cast<ButtonP*>(e->obj);
						button->handlePressed();
						state = new IdleState();
					}
				}

				else if (dynamic_cast<CFloatingBrick*>(e->obj))
				{
					CFloatingBrick* floatingBrick = dynamic_cast<CFloatingBrick*>(e->obj);

					if (e->ny > 0) {

						if (state->current_state != FALLING)
							state = new FallingState();

						if (floatingBrick->GetState() != STATIC_STATE)
						{
							floatingBrick->SetState(BOUNCING_STATE);
							((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->UpdateScore(100);
						}
					}
					else if (e->ny < 0 && (state->current_state == FALLING || state->current_state == FALLING_WHILE_FLYING))// Bug fix
					{
						state = new IdleState();
					}
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


void CMario::isHurted() {

	if (untouchable) return;
	
	switch (this->type)
	{
		case MARIO_TYPE_RACCOON:
			SetType(MARIO_TYPE_BIG);
			break;
		case MARIO_TYPE_BIG:
			SetType(MARIO_TYPE_SMALL);
			break;
		case MARIO_TYPE_SMALL:
			state = new DieState();
			return;
	}	
	
	StartUntouchable();

}

void CMario::handleCollectItem(int item_type)
{
	switch (item_type)
	{
	case ITEM_RED_MUSHROOM:
		{
			SetType(MARIO_TYPE_BIG);
			EffectFactory::GetInstance()->create(MARIO_TYPE_UP, this->x, this->y, this->nx);
			this->y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT);
			this->state = new IdleState();
		};
		break;
	case ITEM_SUPER_LEAF:
		SetType(MARIO_TYPE_RACCOON);
		break;
	}
}

void CMario::updatePower(DWORD dt)
{
	if (is_running)
	{
		running_time += dt;		
		if (running_time > TIME_POWER_STEP*MAX_POWER)
			running_time = TIME_POWER_STEP*MAX_POWER;
	}
	else
	{
		running_time -= dt;
		if (running_time < 0)
			running_time = 0;
	}

	power = running_time / TIME_POWER_STEP;
	if (power > MAX_POWER)
	{
		power = MAX_POWER;
	}
}