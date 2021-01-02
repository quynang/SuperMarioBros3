#include <iostream>
#include <fstream>
#include "IntroScene.h"
#include "Utils.h"
using namespace std;

#define BACKGROUND_MARGIN_X	5
#define BACKGROUND_MARGIN_Y	20

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 0
#define SCENE_SECTION_SPRITES 1
#define SCENE_SECTION_ANIMATIONS 2
#define SCENE_SECTION_FONT	3
#define SCENE_SECTION_BACKGROUND_ANI	4
#define SCENE_SECTION_POINTS	5
#define MAX_SCENE_LINE 1024

IntroScene::IntroScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	key_handler = new IntroSceneKeyHandler(this);
}

void IntroScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}


void IntroScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());
	float dx = 0;
	float dy = 0;

	if (tokens.size() == 8)
	{
		dx = atof(tokens[6].c_str());
		dy = atof(tokens[7].c_str());
	}

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex, dx, dy);
}

void IntroScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void IntroScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") { section = SCENE_SECTION_SPRITES; continue; }
		if (line == "[ANIMATIONS]") { section = SCENE_SECTION_ANIMATIONS; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
			case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
			case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void IntroScene::Update(DWORD dt)
{
}

void IntroScene::Render()
{
	CSprites::GetInstance()->Get(1)->DrawOnScreen(0, 5, 255);
	CAnimations::GetInstance()->Get(1)->Render(112, 101, 255);
}

/*
	Unload current scene
*/
void IntroScene::Unload()
{

}

void IntroSceneKeyHandler::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
		case DIK_S:
			CGame::GetInstance()->SwitchScene(2);
			break;
	}
}

void IntroSceneKeyHandler::OnKeyUp(int KeyCode)
{

}

void IntroSceneKeyHandler::KeyState(BYTE *states)
{
}

