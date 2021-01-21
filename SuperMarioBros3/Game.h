#pragma once

#include <unordered_map>

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>


#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include "Scence.h"

using namespace std;

#define KEYBOARD_BUFFER_SIZE 1024

#define INTRO_SCENE_ID	-1
#define WORLD_MAP_SCENE_ID	0
#define PLAYSCENE_ID	1
#define WORLD_1_4_ID	4
#define SCENE_1_1_PIPE	5


class CGame
{
	static CGame * __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;		
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;

	int screen_width;
	int screen_height;

	unordered_map<int, LPSCENE> scenes;
	int current_scene;
	int current_mario_type;
	bool is_disable_keyboard = false;

	void _ParseSection_SETTINGS(string line);
	void _ParseSection_SCENES(string line);

public:
	void InitKeyboard();
	void DisableKeyboard() { this->is_disable_keyboard = true; }
	void EnableKeyboard() { this->is_disable_keyboard = false; }
	void SetKeyHandler(LPKEYEVENTHANDLER handler) { keyHandler = handler; }
	void Init(HWND hWnd);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha, float dx = 0.0f, float dy = 0.0f);
	void DrawOnScreen(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha);
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();
	void Load(LPCWSTR gameFile);
	int GetCurrentSceneId() { return this->current_scene; }
	LPSCENE GetCurrentScene() { return scenes[current_scene]; }
	void SwitchScene(int scene_id);
	void SwitchSceneAndSetPosition(int scene_id, float x, float y);
	int GetScreenWidth() { return screen_width; }
	int GetScreenHeight() { return screen_height; }

	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st, 
		float sr, 
		float sb,
		float &t, 
		float &nx, 
		float &ny);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }
	static bool isColliding(const RECT& object, const RECT& other);

	static CGame * GetInstance();

	~CGame();
};


