#pragma once
#include "Effect.h"
#define SMOKE_ANI_SET_ID	14

#define MAX_TIME_SMOKE_EFFECT	400
class Smoke : public Effect
{
	float counter_time = 0;
public:
	Smoke(float x, float y);
	void Update(DWORD dt);
	void Render();

};