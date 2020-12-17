#include "FirePiranhaPlant.h"
#include "Utils.h"
#include "PlayScence.h"
#include "EffectFactory.h"
FirePiranhaPlant::FirePiranhaPlant()
{
	this->nx = 1;
	this->vx = 0;
	this->vy = 0;
	this->state = STATE_HIDDEN;
}

void FirePiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	right = left + BBOX_WIDTH_FIRE_PLANT;
	bottom = top + BBOX_HEIGHT_FIRE_PLANT;
}

void FirePiranhaPlant::Update(DWORD dt)
{

	Enemy::Update(dt);
	y += dy;
	x += 0;
	float player_x, player_y;
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetPosition(player_x, player_y);

	if (abs(this->x - player_x) < 150 && action == false)
	{
		this->x - player_x > 0 ? this->nx = -1 : this->nx = 1;
		action = true;
		SetState(STATE_COME_OUT);
	}
	
	//Looping state.
	if (state == STATE_COME_OUT) {
		charge_y += abs(dy);

		if (charge_y >= 32)
		{	
			SetState(STATE_LOOK);
			charge_y = 0;
		}
	}

	if (state == STATE_LOOK)
	{
		time_look += dt;
		this->startLook();
		if (time_look > 1000) {
			time_look = 0;
			SetState(STATE_FIRE);
		}
		
	}

	if (state == STATE_FIRE)
	{
		time_fire += dt;
		this->startFire();
		if (time_fire > 100) {
			SetState(STATE_HIDDEN);
			time_fire = 0;
		};
	}

	if (state == STATE_HIDDEN)
	{
		charge_y += abs(dy);

		if (charge_y >= 32)
		{	
			charge_y = 0;
			vy = 0;
			action = false;
		}
	}
		
}


void FirePiranhaPlant::Render()
{
	int ani_index = -1;
	switch (state)
	{

	case STATE_COME_OUT:
		this->nx > 0 ? ani_index = INDEX_ANI_RIGHT_COME_OUT : ani_index = INDEX_ANI_LEFT_COME_OUT;
		break;
	case STATE_LOOK:

		if (is_look_up) {
			this->nx > 0 ?  ani_index = INDEX_ANI_RIGHT_LOOK_UP :  ani_index = INDEX_ANI_LEFT_LOOK_UP;
		}
		else {
			this->nx > 0 ?  ani_index = INDEX_ANI_RIGHT_LOOK_DOWN :  ani_index = INDEX_ANI_LEFT_LOOK_DOWN;
		}
		break;

	case STATE_FIRE:

		if (is_fire_up) {
			this->nx > 0 ?  ani_index = INDEX_ANI_RIGHT_FIRE_UP :  ani_index = INDEX_ANI_LEFT_FIRE_UP;
		}
		else {
			this->nx > 0 ?  ani_index = INDEX_ANI_RIGHT_FIRE_DOWN :  ani_index = INDEX_ANI_LEFT_FIRE_DOWN;
		}
		break;

	case STATE_HIDDEN:
		this->nx > 0 ?  (ani_index = INDEX_ANI_RIGHT_COME_OUT) : (ani_index = INDEX_ANI_LEFT_COME_OUT);
		break;
	}
	
	
	animation_set->at(ani_index)->Render(x, y);

	//RenderBoundingBox();
}

void FirePiranhaPlant::SetState(int state)
{
	this->state = state;
	switch (state)
	{
			
	case STATE_COME_OUT:
		this->vy = -SPEED_COME_OUT;
		break;
	case STATE_LOOK:
		vy = 0;
		break;
	case STATE_FIRE:
		vy = 0;
		break;
	case STATE_HIDDEN:
		vy = SPEED_COME_OUT;
		break;
	}
	

}
void FirePiranhaPlant::setStep(int step) { 
	this->step = step;
}

void FirePiranhaPlant::startLook() {
	float player_x, player_y;
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetPosition(player_x, player_y);
	if (player_x > this->x)
		this->nx = 1;
	else
		this->nx = -1;

	if (player_y > this->y)
		this->is_look_up = false;
	else
		this->is_look_up = true;
}

void FirePiranhaPlant::startFire() {
	is_fire_up = is_look_up;
	//TODO: Throw fire ball.
}