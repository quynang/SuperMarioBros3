#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Ground.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Map.h"
#include "Grid.h"

class CPlayScene: public CScene
{
protected: 
	CMario *player;			// A play scene has to have player, right?

	vector<LPGAMEOBJECT> objects;

	Grid* m_grid;

	bool is_update = true;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);
	void _ParseSection_GRID(string line);
	void _ParseSection_FONT(string line);
	int timeLimit = 265;
	DWORD timeGone = 0;
	int score = 0;
	
public: 
	CPlayScene(int id, LPCWSTR filePath);
	virtual void AddObject(LPGAMEOBJECT object);
	virtual void AddObjectIntoBeginning(LPGAMEOBJECT object);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void findGameObjectsByTag(string tagName, vector<LPGAMEOBJECT> &resultObjects);
	void turnOffGameObjectUpdate() { this->is_update = false; }
	void turnOnGameObjectUpdate() { this->is_update = true; }
	CMario * GetPlayer() { return player; }
	void UpdateScore(int score) { this->score += score; }

	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

