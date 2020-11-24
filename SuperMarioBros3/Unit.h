#pragma once
#include "GameObject.h"
#include "Grid.h"
struct Cell;

struct Unit;
typedef Unit * LPUNIT;

struct Unit {

	LPGAMEOBJECT object;
	Cell* ownerCell;
	int cellVectorIndex = -1;
};

