#pragma once
#include <iostream>
#include "Sprites.h"
#include "Textures.h"
using namespace std;
#define FONT_SIZE	8
#define ASII_HEC_CODE_SPCACE	32
class Font
{
	static Font* _instance;
public:
	void Load(int id, LPCWSTR filePath, int num_cols, int fontSize, int sprite_spacing);
	void Draw(string text, float x, float y, int letter_spacing = 0);
	static Font* GetInstance();
};