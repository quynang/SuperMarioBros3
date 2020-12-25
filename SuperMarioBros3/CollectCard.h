#pragma once
#include "Effect.h"
#define STEP_DRAWING_TEXT_1	0
#define STEP_DRAWING_TEXT_2	1
#define MAX_Y	40
class CollectCard : public Effect
{
	int step;
	float counter_time = 0;
	float charge_Y = 0;
	int card_type;
public:
	CollectCard(float x, float y, int card_type);
	void Update(DWORD dt);
	void Render();
	void SetStep(int step);

};