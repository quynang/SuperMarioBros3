#pragma once
#include "GameObject.h"
#include "MarioState.h"

class MarioState;
   
#define MARIO_WALKING_SPEED		0.3f 
//0.1f
#define MARIO_JUMP_SPEED_Y		0.5f
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

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 5000

#define IDLE 1001
#define FALLING 1002
#define WALKING 1003
#define JUMPING	1004
class CMario : public CGameObject
{
	int type;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;
	MarioState * marioState;
	friend class WalkingState;
	friend class IdleState;
	friend class JumpingState;
	friend class FallingState;
	int current_state;
	int power = 0;

public:
	int ani = -1;
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

	void Reset();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};