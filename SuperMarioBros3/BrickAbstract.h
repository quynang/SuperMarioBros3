#pragma once
#include "MovableObject.h"

class BrickAbstract : public MovableObject
{
public:
	virtual void ProduceItem();
	virtual void handleWasHitByHeadOfMario();
	virtual void handleWasAttacked();
};