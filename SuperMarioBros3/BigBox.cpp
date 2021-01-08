#include "BigBox.h"

void CBigBox::Render()
{
	//RenderBoundingBox();
}

void CBigBox::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + FRAME_SIZE*size_width;
	b = y + FRAME_SIZE*size_height;
}

void CBigBox::SetInitInfoFromStringLine(string line)
{
	vector<string> tokens = split(line);
	int size_width = atoi(tokens[4].c_str());
	int size_height = atoi(tokens[5].c_str());
	this->size_width = size_width;
	this->size_height = size_height;
}
