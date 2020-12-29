#pragma once
#include "MovableObject.h"

class Enemy : public MovableObject {
protected:
	bool can_be_kicked = false;
	bool can_be_picked_up = false;
	bool can_be_jumped_on = true;
	bool is_updating = true;
public:
	bool canBeJumpedOn() { return this->can_be_jumped_on; }
	bool canBeKicked() { return this->can_be_kicked; }
	bool canBePickedUp() { return this->can_be_picked_up; }
	virtual void handleJumpingOn();
	virtual void handleIsKicked(int nx);
	virtual void handleIsAttacked();
	virtual void Update(DWORD dt);
	virtual void TurnOffUpdation();
	virtual void TurnOnUpdation();
};
