#include "FloatingBrick.h"
#include "Utils.h"
#include "Mushroom.h"
#include "EffectFactory.h"
#include "ButtonP.h"
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

	if (this->state == STATIC_STATE && count_item <= 0) {
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

	switch (this->item_type)
	{
	case BRICK_ITEM_TYPE_COIN_EFFECT:
		EffectFactory::GetInstance()->create(COIN_100, this->x, this->y - 10);
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->UpdateMoney(1);
		break;
	case BRICK_ITEM_TYPE_DYNAMIC:
		{
			switch (current_mario_type)
			{
			case MARIO_TYPE_SMALL:
				ItemFactory::GetInstance()->create(ITEM_RED_MUSHROOM, this->x, this->y);
				break;
			case MARIO_TYPE_BIG:
				ItemFactory::GetInstance()->create(ITEM_SUPER_LEAF, this->x, this->y - 6);
				break;
			case MARIO_TYPE_RACCOON:
				ItemFactory::GetInstance()->create(ITEM_SUPER_LEAF, this->x, this->y - 6);
				break;
			};
		}
		break;
	case BRICK_ITEM_TYPE_GREEN_MUSHROOM:
		ItemFactory::GetInstance()->create(ITEM_GREEN_MUSHROOM, this->x, this->y);
		break;
	case BRICK_ITEM_TYPE_BUTTON_P:
		ButtonP* button_p = new ButtonP(this->x, this->y);
		break;

	}
}

void CFloatingBrick::SetInitInfoFromStringLine(string line)
{
	vector<string> tokens = split(line);
	int init_y = atoi(tokens[3].c_str());
	int item_type = atoi(tokens[4].c_str());
	this->init_y = init_y;
	this->item_type = item_type;
	if(tokens.size() > 5)
		this->count_item = atoi(tokens[5].c_str());
}
void CFloatingBrick::handleWasHitByHeadOfMario()
{
	count_item--;
	if(count_item >= 0)
		SetState(BOUNCING_STATE);

}
void CFloatingBrick::handleWasAttacked()
{
	count_item--;
	if (this->state != STATIC_STATE)
	{
		SetState(STATIC_STATE);
	}
}