#pragma once
#include "StaticObject.h"
#include "Utils.h"
#define BOUNDARY_BBOX_WIDTH  4
#define BOUNDARY_BBOX_HEIGHT 16

class Boundary : public StaticObject
{
	int direction = 0;
public:
	Boundary() { this->ignore_check_collision = true; }
	void Render() {};
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x;
		t = y;
		r = x + BOUNDARY_BBOX_WIDTH;
		b = y + BOUNDARY_BBOX_HEIGHT;
	}
	
	int getDirection() { return this->direction; }
	void SetInitInfoFromStringLine(string line)
	{
		vector<string> tokens = split(line);
		int direction = atoi(tokens[4].c_str());
		this->direction = direction;
	}
};