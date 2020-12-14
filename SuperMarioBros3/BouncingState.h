#pragma once
#include "JumpingState.h"
#define BOUNCE_HEIGHT	30
class BouncingState : public JumpingState
{
public:
	BouncingState() { current_state = BOUNCING; setJumpHeight(BOUNCE_HEIGHT); }
};