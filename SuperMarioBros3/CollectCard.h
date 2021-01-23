#pragma once
#include "Effect.h"
#define STEP_DRAWING_TEXT_1	0
#define STEP_DRAWING_TEXT_2	1

#define CARD_TYPE_STAR	0
#define CARD_TYPE_PLANT	1
#define CARD_TYPE_MUSHROOM	2

#define CARD_TYPE_STAR_SPRITE_ID	94003
#define CARD_TYPE_PLANT_SPRITE_ID	94004
#define CARD_TYPE_MUSHROOM_SPRITE_ID	94005

#define TIME_STEP_1	200
#define TIME_STEP_2	400
#define TIME_STEP_3	2000

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