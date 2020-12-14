#include "ItemFactory.h"
#include "SuperLeaf.h"
#include "Mushroom.h"
#include "PlayScence.h"
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
	case MUSHROOM:
		{
			Item* mushroom = new Mushroom(x, y);
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObjectIntoBeginning(mushroom);
			return mushroom;
			break;
		}
	case SUPER_LEAF:
		{
			Item* super_leaf = new SuperLeaf(x, y);
			((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(super_leaf);
			return super_leaf;
			break;
		}
	default:
		DebugOut(L"Can't find item type: %d !\n", item_type);
		break;
	}
}