#pragma once
#include "MarioState.h"

#define JUMP_HEIGHT_NORMAL 40
#define JUMP_HEIGHT_MAX	65

class JumpingState : public MarioState {
	float jump_height;
public:

	JumpingState() : chargeY_(0) { current_state = JUMPING; setJumpHeight(JUMP_HEIGHT_NORMAL); };

	virtual void setJumpHeight(float height);

	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mari, DWORD dt);

	int getAni(CMario& mario);

private:
	float chargeY_;
};