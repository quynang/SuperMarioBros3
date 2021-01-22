#pragma once
#include "Enemy.h"

#define	FLY_PARATROPA_ANI_SET_ID	28 

#define FLY_PARATROPA_ANI_INDEX_LEFT	0
#define FLY_PARATROPA_ANI_INDEX_RIGHT	1

#define FLY_PARATROPA_SPEED_y	0.1f

#define FLY_PARATROPA_STATE_FLYING	100
#define FLY_PARATROPA_STATE_FALLING	200

#define FLY_PARATROPA_BBOX_WIDTH	16
#define FLY_PARATROPA_BBOX_HEIGHT	27

#define MAX_Y 70

class FlyParatroopa : public Enemy
{
	float counter_y = 0;
public:
	FlyParatroopa();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt);
	virtual void Render();
	int type;
	int state;
	void handleJumpingOn();
	void handleIsKicked(int nx);
	void setType(int type) { this->type = type; }
	int GetState() { return this->state; }
	virtual void SetState(int state);
	void handleIsAttacked();
};