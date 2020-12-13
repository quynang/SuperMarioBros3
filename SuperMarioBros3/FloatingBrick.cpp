#include "FloatingBrick.h"
#include "Utils.h"
#include "Mushroom.h"
#include "PlayScence.h"
#include "GameEffects.h"
#include "EffectFactory.h"

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

	m_coObjects.clear();
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

	switch (item_type)
	{
	case ITEM_TYPE_RED_MUSHROOM:
		{
			Mushroom* mushroom = new Mushroom(this->x, this->y);
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObjectIntoBeginning(mushroom);
			break;
		}
	case ITEM_TYPE_COIN:
		{
			Effect* effect = EffectFactory::GetInstance()->create(COIN_100);
			effect->SetPosition(this->x, this->y - 16);
			GameEffects::GetInstance()->addEffect(effect);
			break;
		}
	}
}
