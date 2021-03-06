#pragma once
#include "Enemy.h"

#define	FIRE_PIRANHA_PLANT_ANI_SET_ID	16
#define INDEX_ANI_LEFT_COME_OUT	0
#define INDEX_ANI_LEFT_LOOK_UP	1
#define INDEX_ANI_LEFT_LOOK_DOWN	2
#define INDEX_ANI_LEFT_FIRE_UP	3
#define INDEX_ANI_LEFT_FIRE_DOWN	4

#define INDEX_ANI_RIGHT_COME_OUT	5
#define INDEX_ANI_RIGHT_LOOK_UP	6
#define INDEX_ANI_RIGHT_LOOK_DOWN	7
#define INDEX_ANI_RIGHT_FIRE_UP	8
#define INDEX_ANI_RIGHT_FIRE_DOWN	9

#define SPEED_COME_OUT	0.15f

#define BBOX_WIDTH_FIRE_PLANT	16
#define BBOX_HEIGHT_FIRE_PLANT	32

#define STATE_HIDDEN	100
#define STATE_COME_OUT	200
#define STATE_LOOK	300
#define STATE_FIRE	400
#define STATE_MOVE_DOWN	500

#define MIN_DISTANCE_TO_START	40
#define MAX_DISTANCE_TO_START	120
#define MAX_CHARGE_Y	32
#define MAX_TIME_LOOK	500
#define MAX_TIME_FIRE	200
#define MAX_TIME_HIDE	600


class FirePiranhaPlant : public Enemy
{
	int state;
	int step;
	bool start_action = false;
	float charge_y;
	float time_look = 0;
	bool is_look_up;
	bool is_fire_up;
	float time_hide;
	float time_fire;
	bool bullet_was_thrown = false;
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt);
	virtual void Render();
	void setStep(int step);
	FirePiranhaPlant();
	void startLook();
	void startFire();
	int GetState() { return this->state; }
	virtual void SetState(int state);
	void handleIsAttacked();

};