#include "FloatingBrick.h"
#include "Utils.h"
#include "Mushroom.h"
#include "PlayScence.h"
void CFloatingBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BRICK_BOX_WIDTH;
	bottom = y + BRICK_BOX_HEIGHT;
}

void CFloatingBrick::Update(DWORD dt)
{
	CGameObject::Update(dt);
	switch (state)
	{
	case DEFLECT_STATE:
		vy = -DEFLECT_SPEED_Y;
		countY_ += dt * vy;
		break;
	case FALLING_STATE:
		vy = DEFLECT_SPEED_Y;
		countY_ += dt * vy;
		break;
	}

	x += dx;
	y += dy;

	if (state == STATIC_STATE)
		y = init_y;

	m_coObjects.clear();

	
}


void CFloatingBrick::Render()
{
	
	if (state == DEFLECT_STATE && abs(countY_) >= MAX_HEIGHT)
		SetState(FALLING_STATE);

	else if (state == FALLING_STATE && abs(countY_) >= MAX_HEIGHT)
		SetState(STATIC_STATE);

	int ani = BRICK_ANI_QUESTION_MARK;

	if (flag_ == 1) {
		ani = BRICK_ANI_COLLECTED;
	}
	
	animation_set->at(ani)->Render(x,y);
	//RenderBoundingBox();
	
}

void CFloatingBrick::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case DEFLECT_STATE:
		flag_ = 1;
		break;
	case FALLING_STATE:
		countY_ = 0;
		break;
	}
}

void CFloatingBrick::ProduceItem() {
	switch (item_type)
	{
	case ITEM_TYPE_RED_MUSHROOM:
		Mushroom* mushroom = new Mushroom(this->x, this->y);
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(mushroom);
		break;
	}
}
