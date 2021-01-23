#pragma once
#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "Grid.h"

class IntroScene: public CScene
{
protected: 
	float curtain_y = 0;
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	
	
public:
	
	IntroScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void RenderAction1();
	void RenderAction2();
};

class IntroSceneKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	IntroSceneKeyHandler(CScene *s) :CScenceKeyHandler(s) {};

};

