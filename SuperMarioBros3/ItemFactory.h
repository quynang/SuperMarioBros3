#pragma once
#include <iostream>
#include "Item.h"
#define MUSHROOM	1
#define	SUPER_LEAF	2
#define COIN_50	3
#define GREEN_MUSHROOM	4
class ItemFactory {
	static ItemFactory* _instance;
public:
	Item* create(int item_type, float x, float y);
	static ItemFactory* GetInstance();
};