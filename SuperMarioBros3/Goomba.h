#pragma once
#include "Enemy.h"

#define	GOOMBA_ANI_SET_ID	3
#define GOOMBA_WALKING_SPEED 0.1f;
#define GOOMBA_GRAVITY			0.001f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 9

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200

#define GOOMBA_ANI_WALKING 0
#define GOOMBA_ANI_DIE 1
#define TIME_STATE_DIE 100.0f

class CGoomba : public Enemy
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	
	virtual void Render();
	int state;
	bool start_action = false;
	float counter_time = 0;
public:
	void Update(DWORD dt);
	CGoomba();
	void handleJumpingOn();
	int GetState() { return this->state; }
	virtual void SetState(int state);
	void handleIsAttacked();
};