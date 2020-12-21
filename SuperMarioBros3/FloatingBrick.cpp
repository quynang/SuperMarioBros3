#include "FloatingBrick.h"
#include "Utils.h"
#include "Mushroom.h"
#include "EffectFactory.h"
#include "ItemFactory.h"
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
	//DebugOut(L"Object To Check %d\n", m_coObjects.size());
	CGameObject::Update(dt);
	x += dx;
	y += dy;

	switch (state)
	{
	case BOUNCING_STATE:
		countY_ += dt * vy;
		break;
	case REBOUNDING_STATE:
		countY_ += dt * vy;
		break;
	case STATIC_STATE:
		y = init_y;
		break;
	}

	if (state == BOUNCING_STATE && abs(countY_) >= MAX_HEIGHT)
		SetState(REBOUNDING_STATE);

	else if (state == REBOUNDING_STATE && abs(countY_) >= MAX_HEIGHT)
		SetState(STATIC_STATE);

}


void CFloatingBrick::Render()
{
	
	int ani = BRICK_ANI_QUESTION_MARK;

	if (this->state == STATIC_STATE) {
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
	case BOUNCING_STATE:
		vy = -BOUNCE_SPEED_Y;
		break;
	case REBOUNDING_STATE:
		countY_ = 0;
		vy = BOUNCE_SPEED_Y;
		break;
	case STATIC_STATE:
		vy = 0;
		vx = 0;
		this->ProduceItem();
		
	}
}

void CFloatingBrick::ProduceItem() {
	CMario *mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int current_mario_type = mario->getCurrentType();

	if (item_type == ITEM_TYPE_COIN) {
		EffectFactory::GetInstance()->create(COIN_100, this->x, this->y - 10);

	}
	else if (item_type == GREEN_MUSHROOM) {
		ItemFactory::GetInstance()->create(GREEN_MUSHROOM, this->x, this->y);
	}
	else if (item_type == BUTTON_P) {
		ItemFactory::GetInstance()->create(BUTTON_P, this->x, this->y);
	}
	else {
		switch (current_mario_type)
		{
		case MARIO_TYPE_SMALL:
			ItemFactory::GetInstance()->create(MUSHROOM, this->x, this->y);
			break;
		case MARIO_TYPE_BIG:
			ItemFactory::GetInstance()->create(SUPER_LEAF, this->x, this->y - 6);
			break;
		};
	}
}
