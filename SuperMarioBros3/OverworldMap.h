#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "Grid.h"
struct BackgroundAni
{
	int ani_id;
	float x, y;
	BackgroundAni(int ani_id, float x, float y)
	{
		this->ani_id = ani_id;
		this->x = x;
		this->y = y;
	};
};
typedef  BackgroundAni* LPBACKGROUNDANI;

struct Point
{
	float x, y;
	int scene_id, canMoveUp, canMoveRight, canMoveDown, canMoveLeft;


	Point(int scene_id, float x, float y, int canMoveUp, int canMoveRight, int canMoveDown, int canMoveLeft)
	{
		this->scene_id = scene_id;
		this->x = x;
		this->y = y;
		this->canMoveUp = canMoveUp;
		this->canMoveDown = canMoveDown;
		this->canMoveRight = canMoveRight;
		this->canMoveLeft = canMoveLeft;
	}
};


class OverworldMap: public CScene
{
protected: 

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_FONT(string line);
	void _ParseSection_BACKGROUND_ANI(string line);
	void _ParseSection_POINTS(string line);
	
	vector<LPBACKGROUNDANI> background_ani;
	vector<Point*> points;
	LPBACKGROUNDANI mario;
	int current_point = 0;
	
	
public:
	float counter_time = 0;
	bool mario_is_moving = false;
	int GetCurrentSceneID() { return this->points.at(current_point)->scene_id; }
	OverworldMap(int id, LPCWSTR filePath);
	void handleMarioMoveUp();
	void handleMarioMoveRight();
	void handleMarioMoveDown();
	void handleMarioMoveLeft();
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
};

class OverworldMapKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	OverworldMapKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

