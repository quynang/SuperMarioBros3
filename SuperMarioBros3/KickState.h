#pragma once
#include "MarioState.h"
#include "Utils.h"
class CMario;

#define MARIO_ANI_SMALL_KICK_RIGHT		39
#define MARIO_ANI_SMALL_KICK_LEFT			40
#define MARIO_ANI_BIG_KICK_RIGHT		41
#define MARIO_ANI_BIG_KICK_LEFT			42
#define RACCOON_MARIO_ANI_KICK_RIGHT	43
#define RACCOON_MARIO_ANI_KICK_LEFT	44
#define FIRE_MARIO_ANI_KICK_RIGHT	75
#define FIRE_MARIO_ANI_KICK_LEFT	76

#define KICK_ACTION_TIME 0.07f

class KickState : public MarioState {

public:

	KickState() { current_state = KICK; };

	float counter_time = 0;

	void handleOnKeyUp(CMario& mario, int keyCode);

	void handleOnKeyDown(CMario& mario, int keyCode);

	void handleKeyState(CMario& mario, BYTE* states);

	void update(CMario& mario, DWORD dt);

	int getAni(CMario& mario);

};

