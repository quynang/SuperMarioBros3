#include "PiranhaPlant.h"
#include "PlayScence.h"
#include "Utils.h"

PiranhaPlant::PiranhaPlant()
{
	this->nx = 1;
	SetState(PIRANHA_STATE_HIDDEN);
	this->can_be_jumped_on = false;
}

void PiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	right = left + PIRANHA_BBOX_WIDTH;
	bottom = top + PIRANHA_BBOX_HEIGHT;
}

void PiranhaPlant::Update(DWORD dt)
{
	MovableObject::Update(dt);
	y += dy;
	x += 0;
	float ml, mt, mr, mb;
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetBoundingBox(ml, mt, mr, mb);

	float current_distance_x;
	if (ml - this->x > 0)
	{
		current_distance_x = ml - (this->x + PIRANHA_BBOX_WIDTH);
	}
	else {
		current_distance_x =  this->x - mr;
	}

	if (current_distance_x < MAX_DISTANCE_TO_START && current_distance_x > MIN_DISTANCE_TO_START && start_action == false)
	{
		start_action = true;
		SetState(PIRANHA_STATE_MOVE_UP);
	}

	//Looping state.
	if (this->state == PIRANHA_STATE_MOVE_UP)
	{
		charge_y += abs(dy);
		if(charge_y >= MAX_Y)
		{
			SetState(PIRANHA_STATE_WAITING);
			charge_y = 0;
		}
	}

	if (this->state == PIRANHA_STATE_WAITING)
	{
		counter_time += dt;
		if (counter_time >= MAX_TIME_TO_SWICTH_ACTION)
		{
			SetState(PIRANHA_STATE_MOVE_DOWN);
			counter_time = 0;
		}
	}

	if (this->state == PIRANHA_STATE_MOVE_DOWN)
	{
		charge_y += abs(dy);
		if (charge_y >= MAX_Y)
		{
			SetState(PIRANHA_STATE_HIDDEN);
			charge_y = 0;
		}
	}
	
	if (this->state == PIRANHA_STATE_HIDDEN)
	{
		counter_time += dt;
		if (counter_time >= MAX_TIME_TO_SWICTH_ACTION)
		{

			counter_time = 0;
			start_action = false;
		}
	}
		
}


void PiranhaPlant::Render()
{	
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void PiranhaPlant::SetState(int state)
{
	this->state = state;
	switch (state)
	{

	case PIRANHA_STATE_MOVE_UP:
		this->vy = -PIRANHA_SPEED_Y;
		break;
	case PIRANHA_STATE_MOVE_DOWN:
		this->vy = PIRANHA_SPEED_Y;
		break;
	case PIRANHA_STATE_WAITING:
		vy = 0;
		break;
	case PIRANHA_STATE_HIDDEN:
		vy = 0;
		break;
	}
}

void PiranhaPlant::handleIsAttacked()
{
	if(this->state != PIRANHA_STATE_HIDDEN)
		this->is_dead = true;
}
