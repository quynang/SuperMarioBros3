#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Utils.h"
#include "TileSet.h"
using namespace std;
#define FRAME_WIDTH  16
#define FRAME_HEIGHT 16
#define FRAME_SIZE 16

class CMap {
	static CMap* __instance;
public:
	CMap();
	~CMap();
	int getWidth();
	int getHeight();
	void Load(LPCWSTR gameFile);
	void Render();
	void Update();
	int valueAt(int i, int j);
	static CMap* GetInstance();
	void Clear();
private:
	void _ParseSection_TILE_SET(string line);
	void _ParseSection_MAP_MATRIX(string line);
	vector< vector<int> > mapMatrix;
	LPTILESET mTileSet;
};