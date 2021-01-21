#pragma once
#include "StaticObject.h"
#define PIPE_EXIT_BBOX_WIDTH	32
#define PIPE_EXIT_BBOX_HEIGHT	16

class PipeExit : public StaticObject
{
	float player_x = 0;
	float player_y = 0;
	int scene_id = -1;
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void getExitInfo(int& id, float& x, float& y) { id = this->scene_id; x = this->player_x; y = this->player_y; }
	void SetInitInfoFromStringLine(string line);
};