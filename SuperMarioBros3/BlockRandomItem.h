#pragma once
#include "Item.h"
#define BLOCK_RANDOM_ITEM_ANI_SET_ID	25
#define BLOCK_RANDOM_ITEM_BBOX_WIDTH  26
#define BLOCK_RANDOM_ITEM_BBOX_HEIGHT 26

#define ITEM_STAR	0
#define ITEM_MUSHROOM	1
#define ITEM_PLANT	2
#define TIME_TO_SWITCH	50

class BlockRandomItem : public Item
{
	int current_item = 0;
	int counter_time = 0;
	bool is_collected = false;
public:
	BlockRandomItem() { SetAnimationSetById(BLOCK_RANDOM_ITEM_ANI_SET_ID); }
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Update(DWORD dt);
	void handleIsCollected();
};