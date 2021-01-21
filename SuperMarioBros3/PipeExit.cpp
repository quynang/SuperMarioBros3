#include "PipeExit.h"
#include "Utils.h"

void PipeExit::Render()
{
	//RenderBoundingBox();
}

void PipeExit::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + PIPE_EXIT_BBOX_WIDTH;
	b = y + PIPE_EXIT_BBOX_HEIGHT;
}

void PipeExit::SetInitInfoFromStringLine(string line)
{
	vector<string> tokens = split(line);
	int scene_id = atoi(tokens[4].c_str());
	float player_x = atof(tokens[5].c_str());
	float player_y = atof(tokens[6].c_str());
	this->scene_id = scene_id;
	this->player_x = player_x;
	this->player_y = player_y;
}
