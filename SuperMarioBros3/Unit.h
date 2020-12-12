#pragma once
#include "GameObject.h"
#include "Grid.h"
struct Cell;

struct Unit;
typedef Unit * LPUNIT;

//Unit is a element of Cell in Grid. We need this object to implement my idea for Grid.
//Maybe we should give a better name for this ??

struct Unit {
	LPGAMEOBJECT object;
	Cell* ownerCell = NULL;

	//Define prev_ and next_ for implementation of Doubly Linked List. Let's see it on Grid.h 
	Unit* prev_ = NULL;
	Unit* next_ = NULL;
};

