#pragma once
#include "MovableObject.h"

class Enemy : public MovableObject {
protected:
	bool can_be_kicked = false;
	bool can_be_picked_up = false;
	bool can_be_jumped_on = true;
public:
	virtual void handleJumpingOn();
};
