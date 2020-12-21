#pragma once
#include "MovableObject.h"
#define ITEM_RED_MUSHROOM	1
#define	ITEM_SUPER_LEAF	2
#define ITEM_COIN_50	3
#define ITEM_GREEN_MUSHROOM	4
class Item : public MovableObject {
public:
	int type;
	virtual void handleIsCollected();
};