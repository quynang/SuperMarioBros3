#pragma once
#include "MovableObject.h"
#define ITEM_RED_MUSHROOM	1
#define	ITEM_SUPER_LEAF	2
#define ITEM_COIN_50	3
#define ITEM_GREEN_MUSHROOM	4
class Item : public MovableObject {
	bool is_collected = false;
public:
	Item() { this->ignore_check_collision = true; }
	int type;
	bool isCollected() { return is_collected; }
	virtual void handleIsCollected();
};