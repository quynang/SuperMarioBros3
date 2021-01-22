#pragma once

#include "Enemy.h"

#define KOOPAS_ANI_SET_ID	5
#define KOOPAS_WALKING_SPEED 0.07f
#define KOOPAS_SLIDING_SPEED 0.4f
#define KOOPAS_GRAVITY	0.015f
#define MAX_TIME_HIDING	2000

#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_SHELL 15

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_HIDE_IN_SHELL	200
#define KOOPAS_STATE_SLIDING 300

#define KOOPAS_ANI_WALKING_RIGHT 0
#define KOOPAS_ANI_WALKING_LEFT 1
#define KOOPAS_ANI_HIDE_IN_SHELL	2
#define KOOPAS_ANI_SLIDING	3

class CKoopas : public Enemy
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt);
	virtual void Render();
	int state;
	float counter_time = 0;
	void proccessOverlapping();

public:
	CKoopas();
	int GetState() { return this->state; }
	virtual void SetState(int state);
	void handleJumpingOn();
	void handleIsKicked(int nx);
	void handleIsAttacked();
};