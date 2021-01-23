#pragma once
#include "Effect.h"
#define TEXT_NUMBER_ANI_SET_ID	10
#define TEXT_NUMBER_SPEED_UP	-0.1f
#define BOUNCING_STEP	100
#define MAX_Y	20

#define ANI_NUMBER_100	0
#define ANI_NUMBER_200	1
#define ANI_NUMBER_400	2
#define ANI_NUMBER_800	3
#define ANI_NUMBER_1000	4
#define ANI_1_UP	5
class TextNumber : public Effect
{
	float vy;
	float dy;
	int step;
	float charge_Y = 0;
	int number;
public:
	TextNumber(float x, float y, int num_val);
	void Update(DWORD dt);
	void Render();
	void SetStep(int step);
};