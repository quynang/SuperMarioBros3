#include "BlockRandomItem.h"
#include "PlayScence.h"
#include "EffectFactory.h"
void BlockRandomItem::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

void BlockRandomItem::Update(DWORD dt)
{
	counter_time += dt;
	if (counter_time >= TIME_TO_SWITCH)
	{
		current_item++;
		counter_time = 0;

		if (current_item == 3)
			current_item = 0;
	}
	
}

void BlockRandomItem::Render()
{
	if (is_collected) return;
	int ani = current_item;
	animation_set->at(ani)->Render(x, y);
}

void BlockRandomItem::handleIsCollected() {
	if (!is_collected) {
		is_collected = true;
		CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		mario->SetPosition(x, y + 20);
		mario->nx = 1;
		mario->mission_passed = true;
		EffectFactory::GetInstance()->create(COLLECT_CARD, x, y, current_item);
	}
	
}
