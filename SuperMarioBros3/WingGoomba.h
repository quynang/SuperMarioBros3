#pragma once

#include "Enemy.h"

#define WING_GOOMBA_WALKING_SPEED 0.08f;
#define WING_GOOMBA_GRAVITY	0.07f;
#define	DEBOUNCING_SPEED_Y	-0.2f
#define WING_GOOMBA_HAS_WING_ANI_WALKING_INDEX	0
#define WING_GOOMBA_HAS_WING_ANI_JUMPING_INDEX	1

#define WING_GOOMBA_LOST_WING_ANI_WALKING_INDEX	2
#define WING_GOOMBA_ANI_DEAD_INDEX	3

#define WING_GOOMBA_WALKING_BBOX_WIDTH 20
#define WING_GOOMBA_WALKING_BBOX_HEIGHT 19
#define WING_GOOMBA_JUMPING_BBOX_HEIGHT	19
#define WING_GOOMBA_JUMPING_BBOX_WIDTH	20

#define WING_GOOMBA_LOST_WING_BBOX_WIDTH 16
#define WING_GOOMBA_LOST_WING_BBOX_HEIGHT 16

#define WING_GOOMBA_DEAD_BBOX_HEIGHT	9

#define TYPE_HAS_WING	1
#define TYPE_LOST_WING	2

#define WING_GOOMBA_STATE_WALKING 100
#define WING_GOOMBA_STATE_JUMPING 200
#define WING_GOOMBA_STATE_BOUNCING 400
#define WING_GOOMBA_STATE_DEAD 300

#define STEP_JUMPING_1	1000
#define STEP_JUMPING_2	2000
#define STEP_JUMPING_3	3000
#define STEP_JUMPING_NONE	4000

#define MAX_DEBOUNCING_TIME	100
#define MAX_JUMPING_TIME	200
#define MAX_CHARGE_X	20

class WingGoomba : public Enemy
{

public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt);
	virtual void Render();
	float charge_x = 0;
	float charge_time_jump = 0;
	float counter_time_dead_ani = 0;
	int type;
	int state;
	int step;
	void setStep(int step);
	WingGoomba();
	void handleIsTrampled();
	void JumpToNextStep() { step = step + 1000; }
	void setType(int type) { this->type = type; }
	int GetState() { return this->state; }
	virtual void SetState(int state);
};