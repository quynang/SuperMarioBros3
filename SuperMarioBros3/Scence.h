#pragma once

#include <d3dx9.h>
#include "KeyEventHandler.h"

#define TIME_LIMIT 300
#define INIT_LIFE	3
class CScene
{
protected:
	CKeyEventHandler * key_handler;
	int id;
	LPCWSTR sceneFilePath;
	int score = 0;
	int money = 0;
	DWORD timeGone = 0;
	int timeLimit = TIME_LIMIT;
	int life = INIT_LIFE;

public: 
	CScene(int id, LPCWSTR filePath);

	CKeyEventHandler * GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0; 
	void GetHUBInfo(int& score, int& money, DWORD& timeGone)
	{
		score = this->score;
		money = this->money;
		timeGone = this->timeGone;
	}

	void SetHUBInfo(int score, int money, DWORD timeGone)
	{
		this->score = score;
		this->money = money;
		this->timeGone = timeGone;
	}

	void ResetHUBInfo()
	{
		this->score = 0;
		this->money = 0;
		this->timeGone = 0;
	}
};
typedef CScene * LPSCENE;


class CScenceKeyHandler : public CKeyEventHandler
{
protected: 
	CScene * scence; 

public:
	virtual void KeyState(BYTE *states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CScenceKeyHandler(CScene *s) :CKeyEventHandler() { scence = s; }
};