#pragma once
#include "MovableObject.h"
#include "MarioState.h"
class MarioState;

#define MARIO_ANI_SET_ID 1
#define MARIO_WALKING_SPEED		0.3f 
//0.1f
#define MARIO_JUMP_SPEED_Y		0.4f
#define FLYING_SPEED_X	0.2f
#define MARIO_FLYING_SPEED_Y		0.18f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.008f
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
#define MARIO_TYPE_FIRE	4

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define TAIL_BBOX_WIDTH	8
#define TAIL_BBOX_HEIGHT	6
#define DISTANCE_FROM_FOOT_TO_TAIL	2

#define DISTANCE_FROM_HEAD_TO_HAND	14

#define MARIO_UNTOUCHABLE_TIME 1000
#define TIME_ANI_SMACKING_TAIL	25

#define TIME_ANI_THROW	25

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
#define THROW_1	1012
#define THROW_2	1013
#define BOUNCING	1014
#define DIE	1015
#define STAND_ON_MOVING_BAR	1016

#define MAX_POWER	7
#define TIME_POWER_STEP	70

class CMario : public MovableObject
{
	int type;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;
	
	bool is_running = false;
	int can_pick_item = 0;
	bool is_holding = false;
	bool is_visible = true;
	float running_time;

	MarioState * state = NULL;
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
	friend class Throw_1_State;
	friend class Throw_2_State;
	friend class StandOnMovingBarState;
	CGameObject* item_holding = NULL;
	void processCollision();
	void proccessOverlapping();
public:
	int power = 0;
	bool mission_passed = false;
	CMario();
	virtual void Update(DWORD dt);
	virtual void Render();
	void handleOnKeyUp(int keyCode);
	void handleOnKeyDown(int keyCode);
	void handleKeyState(BYTE* states);
	void SetType(int t) { type = t; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void SetPosForItemPicked();
	void handleTailAttacking();
	RECT getTailRect();
	void getPositionOfHandWhenThrowing(float& x, float& y);
	void SetState(int state);
	void handleCollectItem(int item_type);
	void Reset();
	void setIsVisible(bool value) { this->is_visible = value; }
	int getCurrentType() { return type; }
	void isHurted();
	void updatePower(DWORD dt);
	int getCurrentState();
	bool flag = false;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};