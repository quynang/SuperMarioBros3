#pragma once
#include "GameObject.h"
#include "MarioState.h"
class MarioState;
   
#define MARIO_WALKING_SPEED		0.3f 
//0.1f
#define MARIO_JUMP_SPEED_Y		0.5f
#define FLYING_SPEED_X	0.2f
#define MARIO_FLYING_SPEED_Y		0.18f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.01f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_DIE				400


#define MARIO_ANI_DIE				8

#define	MARIO_TYPE_SMALL	1
#define	MARIO_TYPE_BIG		2
#define MARIO_TYPE_RACCOON	3

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 5000
#define TIME_ANI_SMACKING_TAIL	25

#define IDLE 1001
#define FALLING 1002
#define WALKING 1003
#define JUMPING	1004
#define FLYING	1005
#define FALLING_WHILE_FLYING	1006
#define KICK	1007
#define HOLDING	1008
#define TAIL_SMACKING_1	1009
#define TAIL_SMACKING_2	1010
#define TAIL_SMACKING_3 1011

class CMario : public CGameObject
{
	int type;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;
	int power = 0;
	int can_pick_item = 0;

	MarioState * marioState;
	friend class WalkingState;
	friend class IdleState;
	friend class JumpingState;
	friend class FallingState;
	friend class FlyingState;
	friend class FallingWhileFlyingState;
	friend class KickState;
	friend class HoldingState;
	friend class TailSmacking_1_State;
	friend class TailSmacking_2_State;
	friend class TailSmacking_3_State;
	CGameObject* item_picked = NULL;

public:

	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void handleOnKeyUp(int keyCode);
	void handleOnKeyDown(int keyCode);
	void handleKeyState(BYTE* states);
	void SetAni(int ani);
	void ChangeState(MarioState* marioState) { marioState = marioState; }
	void SetState(int state);
	void SetType(int t) { type = t; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void SetPosForItemPicked();

	void Reset();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};