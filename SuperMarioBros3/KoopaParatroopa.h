#pragma once

#include "Enemy.h"

#define PARATROPA_ANI_INDEX_WALKING_LEFT	0
#define PARATROPA_ANI_INDEX_WALKING_RIGHT	1
#define PARATROPA_ANI_INDEX_HIDING_IN_SHELL	2
#define PARATROPA_ANI_INDEX_SLIDING	3
#define PARATROPA_LOST_WING_ANI_INDEX_WALKING_LEFT	4
#define PARATROPA_LOST_WING_ANI_INDEX_WALKING_RIGHT	5

#define PARATROPA_WALKING_SPEED	0.1f
#define PARATROPA_GRAVITY	0.1f
#define PARATROPA_JUMPING_SPEED	-0.15f
#define PARATROPA_SLIDING_SPEED	0.2f

#define	PARATROPA_TYPE_HAS_WING	1
#define PARATROPA_TYPE_LOST_WING	2

#define PARATROPA_STATE_WALKING	100
#define PARATROPA_STATE_JUMPING	200
#define PARATROPA_STATE_FALLING	300
#define PARATROPA_STATE_HIDING_IN_SHELL	400
#define PARATROPA_STATE_SLIDING	500


#define PARATROPA_BBOX_WIDTH	16
#define PARATROPA_BBOX_HEIGHT	27

#define PARATROPA_SHELL_BBOX_WIDTH	16
#define PARATROPA_SHELL_BBOX_HEIGHT	16

#define MAX_JUMPING_TIME	250
class KoopaParatroopa : public Enemy
{
	float jumping_time = 0;
	bool first_update_flag = true;
public:
	KoopaParatroopa();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt);
	virtual void Render();
	int type;
	int state;
	void handleJumpingOn();
	void setType(int type) { this->type = type; }
	int GetState() { return this->state; }
	virtual void SetState(int state);
};