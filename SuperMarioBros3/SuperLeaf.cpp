#include "SuperLeaf.h"
#include "EffectFactory.h"
#include "Utils.h"

SuperLeaf::SuperLeaf(float x, float y)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	SetAnimationSet(animation_sets->Get(SUPER_LEAF_ANI_SET_ID));
	this->x = x;
	this->y = y;
	this->nx = 1;
	SetState(SUPER_LEAF_STATE_BOUNCING);
}

void SuperLeaf::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + SUPER_LEAF_BBOX_WIDTH;
	bottom = y + SUPER_LEAF_BBOX_HEIGHT;
}

void SuperLeaf::Update(DWORD dt)
{
	if (charge_y >= MAX_CHARGE_Y) SetState(SUPER_LEAF_STATE_FALLING);

	if (this->state == SUPER_LEAF_STATE_BOUNCING) {
		vy = SUPER_LEAF_SPEED_BOUNCING_Y;
		MovableObject::Update(dt);
		y += dy;
		charge_y += abs(dy);
	}

	else if(this->state == SUPER_LEAF_STATE_FALLING){
		vx = nx * SUPER_LEAF_SPEED_X;
		MovableObject::Update(dt);
		x += dx;
		y += dy;

		charge_x += abs(dx);

		if (charge_x >= MAX_CHARGE_X)
		{
			charge_x = 0;
			this->nx = -nx;
		}
	}
}

void SuperLeaf::Render()
{
	int ani = -1;

	if (nx > 0)
		ani = SUPER_LEAF_ANI_RIGHT_INDEX;
	else
		ani = SUPER_LEAF_ANI_LEFT_INDEX;
	
	animation_set->at(ani)->Render(x,y);

	//RenderBoundingBox();
}

void SuperLeaf::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case SUPER_LEAF_STATE_BOUNCING:
		vy = SUPER_LEAF_SPEED_BOUNCING_Y;
		vx = 0;
		break;
	case SUPER_LEAF_STATE_FALLING:
		vy = SUPER_LEAF_SPEED_Y;
	}
	
}

void SuperLeaf::handleIsCollected()
{
	if (!is_dead)
	{
		EffectFactory::GetInstance()->create(SMOKE, this->x, this->y);
		this->is_dead = true;

	}
}
