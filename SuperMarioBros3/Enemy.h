#pragma once
#include "MovableObject.h"

class Enemy : public MovableObject {
public:
	bool can_be_trumped = true;
	virtual void handleIsTrampled() = 0;
};
