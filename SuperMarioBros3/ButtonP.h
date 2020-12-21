#pragma once
#include "Utils.h"
#include "Item.h"

#define BUTTON_P_BBOX_WIDTH  16
#define	BUTTON_P_BBOX_HEIGHT 16
#define BUTTON_P_PRESSED_BBOX_HEIGHT	7
#define BUTTON_P_ANI_SET_ID	24

#define BUTTON_P_SPEED_Y	-0.07f

#define BUTTON_P_STATE_MOVE_UP	100
#define BUTTON_P_STATE_NORMAL	200
#define BUTTON_P_STATE_PRESSED	300

#define BUTTON_P_MOVE_UP_ANI_INDEX	0
#define BUTTON_P_PRESSED_ANI_INDEX	1

#define MAX_Y	14

class ButtonP : public Item
{
	int state;
	float charge_y = 0;
public:
	ButtonP() {};
	ButtonP(float x, float y);
	virtual void Render();
	virtual void Update(DWORD dt);
	void SetState(int state);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void handlePressed();
};