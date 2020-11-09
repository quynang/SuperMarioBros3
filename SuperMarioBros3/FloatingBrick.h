#pragma once
#include "GameObject.h"
#define DEFLECT_STATE	100
#define FALLING_STATE	200
#define STATIC_STATE	300

#define MAX_HEIGHT	15

#define BRICK_ANI_QUESTION_MARK	0
#define BRICK_ANI_COLLECTED	1
#define BRICK_BOX_WIDTH	16
#define BRICK_BOX_HEIGHT	16

#define DEFLECT_SPEED_Y	0.5f

class CFloatingBrick : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

public:
	int flag_ = 0;
	float countY_ = 0;
	float init_y;
	
	CFloatingBrick(float y) { init_y = y; };
	virtual void SetState(int state);
};