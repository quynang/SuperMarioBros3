#pragma once
#include "Effect.h"
#define BROKEN_ANI_SET_ID	21
#define SPEED_X 0.1f
#define SPEED_Y	0.1f
#define MAX_TIME	200
#define SPACING	5

class Broken : public Effect
{
	float counter_time = 0;
	D3DXVECTOR3 point_1;
	D3DXVECTOR3 point_2;
	D3DXVECTOR3 point_3;
	D3DXVECTOR3 point_4;
public:
	Broken(float x, float y);
	void Update(DWORD dt);
	void Render();

};