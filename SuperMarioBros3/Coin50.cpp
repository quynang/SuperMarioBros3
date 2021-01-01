#include "Coin50.h"
#include "PlayScence.h"


Coin50::Coin50(float x, float y) {
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	SetAnimationSet(animation_sets->Get(COIN_50_ANI_SET_ID));
	this->x = x;
	this->y = y;
	this->type = ITEM_COIN_50;
}

void Coin50::Render()
{
	//RenderBoundingBox();
	animation_set->at(0)->Render(x, y);
}

void Coin50::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + COIN_50_BOX_WIDTH;
	b = y + COIN_50_BOX_HEIGHT;
}

void Coin50::handleIsCollected() {
	if (!is_dead)
	{
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->UpdateScore(100);
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->UpdateMoney(1);
		this->is_dead = true;
	}
		
}