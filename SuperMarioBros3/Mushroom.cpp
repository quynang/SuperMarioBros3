#include "Mushroom.h"
#include "Utils.h"
Mushroom::Mushroom(float x, float y)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	SetAnimationSet(animation_sets->Get(ITEMS_ANI_SET));
	this->x = x;
	this->y = y;
	this->state = MUSHROOM_STATE_SPROUT;
	this->vy = MUSHROOM_SPROUT_SPEED_Y;
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
	MovableObject::Update(dt);

	if (charge_y >= 16) this->state = MUSHROOM_STATE_MOVING;

	if (this->state == MUSHROOM_STATE_SPROUT) {
		charge_y += abs(dy);
	}

	if (this->state == MUSHROOM_STATE_MOVING) {
		vy += MUSHROOM_GRAVITY;
	}

	x += dx;
	y += dy;
	/*vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(&m_coObjects, coEvents);
	
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

			if (dynamic_cast<CBigBox*>(e->obj))
			{
				x += dx;
				vx = - e->nx * GOOMBA_WALKING_SPEED;
			}

			else if (dynamic_cast<CGround*>(e->obj)) {
			
				vx = e->nx * GOOMBA_WALKING_SPEED;
				x += dx;
			}
	
		}
	}*/

	m_coObjects.clear();
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
}
