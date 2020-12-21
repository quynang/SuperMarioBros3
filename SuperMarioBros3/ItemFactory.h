#pragma once
#include <iostream>
#include "Item.h"
class ItemFactory {
	static ItemFactory* _instance;
public:
	Item* create(int item_type, float x, float y);
	static ItemFactory* GetInstance();
};