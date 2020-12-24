#pragma once
#include <iostream>
#include <d3dx9.h>

class Camera
{
	
private:
	static Camera* _instance;
	int width;
	int height;
	float x = 0, y = 0;
	Camera();
public:
	void Clear() { _instance = NULL; delete _instance; };
	void Update();
	int getWidth() { return this->width; }
	int getHeight() { return this->height; }
	void GetCamPosition(float& x, float& y) { x = this->x; y = this->y; };
	static Camera* GetInstance();
};