#include "ItemFactory.h"
#include "SuperLeaf.h"
#include "Mushroom.h"
#include "GreenMushroom.h"
#include "PlayScence.h"
#include "coin50.h"
#include "Utils.h"

ItemFactory *ItemFactory::_instance = NULL;

ItemFactory *ItemFactory::GetInstance()
{
	if (_instance == NULL) _instance = new ItemFactory();
	return _instance;
}

Item* ItemFactory::create(int item_type, float x, float y) {

	switch (item_type)
	{
	case ITEM_RED_MUSHROOM:
		{
			Item* mushroom = new Mushroom(x, y);
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObjectIntoBeginning(mushroom);
			return mushroom;
			break;
		}
	case ITEM_SUPER_LEAF:
		{
			Item* super_leaf = new SuperLeaf(x, y);
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(super_leaf);
			return super_leaf;
			break;
		}
	case ITEM_COIN_50:
		{
			Item* coin_50  = new Coin50(x, y);
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(coin_50);
			return coin_50;
			break;
		}
	case ITEM_GREEN_MUSHROOM:
		{
			Item* green_mushroom = new GreenMushroom(x, y);
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObjectIntoBeginning(green_mushroom);
			return green_mushroom;
			break;
		}
	default:
		DebugOut(L"Can't find item type: %d !\n", item_type);
		break;
	}
}