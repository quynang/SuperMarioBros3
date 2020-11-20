#pragma once
#include "MarioState.h"

//TODO: Remove this class and handle it in each state idle, walking, jumping .......

#define MARIO_ANI_SMALL_HOLDING_WALKING_RIGHT		45
#define MARIO_ANI_SMALL_HOLDING_WALKING_LEFT		46
#define MARIO_ANI_BIG_HOLDING_WALKING_RIGHT			47
#define MARIO_ANI_BIG_HOLDING_WALKING_LEFT			48
#define RACCOON_MARIO_ANI_HOLDING_WALKING_RIGHT	49
#define RACCOON_MARIO_ANI_HOLDING_WALKING_LEFT	50

#define MARIO_ANI_IDLE_SMALL_HOLDING_RIGHT		51
#define MARIO_ANI_IDLE_SMALL_HOLDING_LEFT		52
#define MARIO_ANI_IDLE_BIG_HOLDING_RIGHT			53
#define MARIO_ANI_IDLE_BIG_HOLDING_LEFT			54
#define RACCOON_MARIO_ANI_IDLE_HOLDING_RIGHT	55
#define RACCOON_MARIO_ANI_IDLE_HOLDING_LEFT	56

#define FIRE_MARIO_ANI_HOLDING_WALKING_RIGHT	77
#define FIRE_MARIO_ANI_HOLDING_WALKING_LEFT	78
#define FIRE_MARIO_ANI_IDLE_HOLDING_RIGHT	79
#define FIRE_MARIO_ANI_IDLE_HOLDING_LEFT	80



class HoldingState : public MarioState {


public:
	HoldingState() { current_state = HOLDING; };

	virtual void handleOnKeyUp(CMario& mario, int keyCode);

	virtual void handleOnKeyDown(CMario& mario, int keyCode);

	virtual void handleKeyState(CMario& mario, BYTE* states);

	virtual void update(CMario& mario, DWORD dt);

	int getAni(CMario& mario);
};