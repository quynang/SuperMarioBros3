#pragma once
#include <iostream>
#include <string>
using namespace std;
#define HUB_SPRITE_ID	0
#define BOTTOM_Y	200
#define BLACK_BACKGROUND_TEXTURE_ID	-500
#define CARD_SPRITE_ID	-1
#define BLACK_TRIANGLE_TEXTURE_ID	-2	
#define WHITE_TRIANGLE_TEXTURE_ID	-3
#define BLACK_P_TEXTURE_ID	-4
#define WHITE_P_TEXTURE_ID	-5
#define M_TEXTURE_ID	-6
#define L_TEXTURE_ID	-7

class HUB
{
	static HUB* _instance;
	HUB();
	string timeString;
public:
	
	void Render();
	void Update(int time);
	static HUB* GetInstance();
};
