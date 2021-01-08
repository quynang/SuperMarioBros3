#include "ButtonP.h"
#include "PlayScence.h"
#include "BreakableBrick.h"
ButtonP::ButtonP(float x, float y) {
	SetAnimationSetById(BUTTON_P_ANI_SET_ID);
	this->x = x;
	this->y = y;
	SetState(BUTTON_P_STATE_MOVE_UP);
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObjectIntoBeginning(this);

}

void ButtonP::Render()
{	
	int ani_index = -1;
	//RenderBoundingBox();
	switch (state)
	{
	case BUTTON_P_STATE_NORMAL:
	case BUTTON_P_STATE_MOVE_UP:
		ani_index = BUTTON_P_MOVE_UP_ANI_INDEX;
		break;
	case BUTTON_P_STATE_PRESSED:
		ani_index = BUTTON_P_PRESSED_ANI_INDEX;
		break;
	}

	animation_set->at(ani_index)->Render(x, y);
}

void ButtonP::Update(DWORD dt) {
	
	if (BUTTON_P_STATE_MOVE_UP)
	{
		MovableObject::Update(dt);
		y += dy;
		charge_y += abs(dy);
		if (charge_y > MAX_Y)
		{
			charge_y = 0;
			SetState(BUTTON_P_STATE_NORMAL);
		}
	}
}


void ButtonP::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case BUTTON_P_STATE_MOVE_UP: 
		vy = BUTTON_P_SPEED_Y;
		break;
	case BUTTON_P_STATE_NORMAL:
		vy = 0;
		break;
	case BUTTON_P_STATE_PRESSED:
		vy = 0;
		this->y += (BUTTON_P_BBOX_HEIGHT - BUTTON_P_PRESSED_BBOX_HEIGHT);
		break;
	}
}

void ButtonP::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BUTTON_P_BBOX_WIDTH;
	if(this->state == BUTTON_P_STATE_PRESSED)
		b = y + BUTTON_P_PRESSED_BBOX_HEIGHT;
	else
		b = y + BUTTON_P_BBOX_HEIGHT;
}

void ButtonP::handlePressed() {
	if (this->state != BUTTON_P_STATE_PRESSED)
	{
		SetState(BUTTON_P_STATE_PRESSED);
		vector<LPGAMEOBJECT> breakable_bricks;
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->findGameObjectsByTag("BREAKABLE_BRICK", breakable_bricks);
		for (size_t i = 0; i < breakable_bricks.size(); i++)
		{
			((BreakableBrick*)breakable_bricks.at(i))->ProduceItem();
		}
	}	
}