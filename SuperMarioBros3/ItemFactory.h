#pragma once
#include <iostream>
#include "Item.h"

#define MUSHROOM	1
#define	SUPER_LEAF	2
class ItemFactory {
	static ItemFactory* _instance;
public:
	Item* create(int item_type, float x, float y);
	static ItemFactory* GetInstance();
};