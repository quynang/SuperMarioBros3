#pragma once
#include "MovableObject.h"

#define SPEED_X_FIRE_BULLET	0.1f
#define BBOX_WIDTH_PLANT_FIRE_BULLET	8
#define BBOX_HEIGHT_PLANT_FIRE_BULLET	8

#define ANI_SET_ID_FIRE_BULLET	6
#define INDEX_ANI_FIRE_BULLET_LEFT	0
#define INDEX_ANI_FIRE_BULLET_RIGHT	1

#define MAX_SPEED_Y	0.13f
#define MAX_X	150.0f
class PlantFireBullet : public MovableObject
{
	float charge_x = 0;
public:
	PlantFireBullet();
	PlantFireBullet(float x, float y, int nx);
	virtual void Render();
	virtual void Update(DWORD dt);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	float calculateSpeedY();

};