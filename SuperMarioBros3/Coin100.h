#pragma once
#include "Effect.h"
#define COIN_100_ANI_SET_ID	8
#define COIN_GRAVITY	0.07f
#define COIN_SPEED_Y	0.4f
#define BOUNCING_STEP	100
#define FALL_DOWN_STEP	200
#define MAX_Y	40
class Coin100 : public Effect
{
	float vy;
	float dy;
	int step;
	float charge_Y = 0;
public:
	Coin100();
	void Update(DWORD dt);
	void Render();
	void SetStep(int step);

};