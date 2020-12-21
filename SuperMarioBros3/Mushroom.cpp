#include "Mushroom.h"
#include "EffectFactory.h"
#include "Utils.h"

Mushroom::Mushroom(float x, float y)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	SetAnimationSet(animation_sets->Get(ITEMS_ANI_SET));
	this->x = x;
	this->y = y;
	this->nx = 1;
	this->state = MUSHROOM_STATE_SPROUT;
	this->vy = MUSHROOM_SPROUT_SPEED_Y;
	this->type = ITEM_RED_MUSHROOM;
}

void Mushroom::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + MUSHROOM_BBOX_WIDTH;
	bottom = y + MUSHROOM_BBOX_HEIGHT;
}

void Mushroom::Update(DWORD dt)
{
	if (this->state == MUSHROOM_STATE_SPROUT) {
		vy = MUSHROOM_SPROUT_SPEED_Y;
		MovableObject::Update(dt);
		y += dy;
		charge_y += abs(dy);
		if (charge_y >= 20) {
			SetState(MUSHROOM_STATE_MOVING);
			charge_y = 0;
		}
	}

	else if (this->state == MUSHROOM_STATE_MOVING) {
		vy += MUSHROOM_GRAVITY;
		MovableObject::Update(dt);
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(&coObjects, coEvents);

		if (coEvents.size() == 0)
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
				if (e->nx != 0)
				{
					this->nx = -this->nx;
					this->vx = this->nx * MUSHROOM_MOVING_SPEED;
				}
			
			}
		}

		coObjects.clear();
	}
}

void Mushroom::Render()
{
	int ani = 0;
	
	animation_set->at(ani)->Render(x,y);

	//RenderBoundingBox();
}

void Mushroom::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case MUSHROOM_STATE_MOVING:
		vx = this->nx* MUSHROOM_MOVING_SPEED;
		vy = 0;
		break;
	case MUSHROOM_STATE_COLLECTED:
		this->is_dead = true;
		break;
	}
}

void Mushroom::handleIsCollected()
{
	if (!is_dead)
	{
		this->is_dead = true;
	}
}
