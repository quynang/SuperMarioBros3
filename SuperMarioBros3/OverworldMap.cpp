#include <iostream>
#include <fstream>
#include "OverworldMap.h"
#include "HUB.h"
#include "Font.h"
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

OverworldMap::OverworldMap(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	key_handler = new OverworldMapKeyHandler(this);
}

void OverworldMap::_ParseSection_TEXTURES(string line)
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

void OverworldMap::_ParseSection_POINTS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines
	int scene_id = atoi(tokens[0].c_str());
	int x = atoi(tokens[1].c_str());
	int y = atoi(tokens[2].c_str());
	int canMoveUp = atoi(tokens[3].c_str());
	int canMoveRight = atoi(tokens[4].c_str());
	int canMoveDown = atoi(tokens[5].c_str());
	int canMoveLeft  = atoi(tokens[6].c_str());
	Point* point = new Point(scene_id, x, y, canMoveUp, canMoveRight, canMoveDown, canMoveLeft);
	this->points.push_back(point);
	
}

void OverworldMap::_ParseSection_BACKGROUND_ANI(string line)
{
	
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines

	int ani_id = atoi(tokens[0].c_str());
	float x = atoi(tokens[1].c_str());
	float y = atoi(tokens[2].c_str());
	LPBACKGROUNDANI background_ani = new BackgroundAni(ani_id, x, y);
	this->background_ani.push_back(background_ani);

	
}
void OverworldMap::_ParseSection_FONT(string line)
{
	vector<string> tokens = split(line);
	int id = atoi(tokens[0].c_str());
	LPCWSTR filePath = ToLPCWSTR(tokens[1].c_str());
	int num_cols = atoi(tokens[2].c_str());
	int fontSize = atoi(tokens[3].c_str());
	int sprite_spacing = atoi(tokens[4].c_str());
	Font::GetInstance()->Load(id, filePath, num_cols, fontSize, sprite_spacing);
}

void OverworldMap::_ParseSection_SPRITES(string line)
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

void OverworldMap::_ParseSection_ANIMATIONS(string line)
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

void OverworldMap::Load()
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
		if (line == "[FONT]") { section = SCENE_SECTION_FONT; continue; }
		if (line == "[BACKGROUND_ANI]")  { section = SCENE_SECTION_BACKGROUND_ANI; continue; }
		if (line == "[POINTS]")  { section = SCENE_SECTION_POINTS; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
			case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
			case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
			case SCENE_SECTION_FONT: _ParseSection_FONT(line); break;
			case SCENE_SECTION_BACKGROUND_ANI: _ParseSection_BACKGROUND_ANI(line); break;
			case SCENE_SECTION_POINTS: _ParseSection_POINTS(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	mario = new BackgroundAni(2, this->points.at(0)->x , this->points.at(0)->y);
	
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void OverworldMap::Update(DWORD dt)
{
	HUB::GetInstance()->Update(0, 0);
}

void OverworldMap::Render()
{
	for (size_t i = 0; i < background_ani.size(); i++)
	{
		CAnimations::GetInstance()->Get(background_ani.at(i)->ani_id)->Render(background_ani.at(i)->x + BACKGROUND_MARGIN_X , background_ani.at(i)->y + BACKGROUND_MARGIN_Y);
	}
	CAnimations::GetInstance()->Get(mario->ani_id)->Render(mario->x + BACKGROUND_MARGIN_X ,mario->y + BACKGROUND_MARGIN_Y);
	HUB::GetInstance()->Render();
}

/*
	Unload current scene
*/

void OverworldMap::handleMarioMoveUp()
{
	if (points.at(current_point)->canMoveUp)
	{
		mario_is_moving = true;
		points.at(current_point + 1)->y < points.at(current_point)->y ? current_point++ : current_point--;
		mario->x = points.at(current_point)->x;
		mario->y = points.at(current_point)->y;
	}
}
void OverworldMap::handleMarioMoveRight()
{
	if (points.at(current_point)->canMoveRight)
	{
		mario_is_moving = true;

		points.at(current_point + 1)->x > points.at(current_point)->x ? current_point++ : current_point--;
		mario->x = points.at(current_point)->x;
		mario->y = points.at(current_point)->y;
	}
}
void OverworldMap::handleMarioMoveDown()
{
	if (points.at(current_point)->canMoveDown)
	{
		mario_is_moving = true;
		points.at(current_point + 1)->y > points.at(current_point)->y ? current_point++ : current_point--;
		mario->x = points.at(current_point)->x;
		mario->y = points.at(current_point)->y;
	}
}
void OverworldMap::handleMarioMoveLeft()
{
	if (points.at(current_point)->canMoveLeft)
	{
		mario_is_moving = true;

		if (current_point - 1 == 0) 
			current_point--;
		else if (current_point == points.size() - 1) 
			current_point--;
		else 
			points.at(current_point + 1)->x < points.at(current_point)->x  ? current_point++ : current_point--;

		mario->x = points.at(current_point)->x;
		mario->y = points.at(current_point)->y;
	}
}

void OverworldMap::Unload()
{
	for (auto p : points)
	   {
		 delete p;
	   } 
	points.clear();
	current_point = 0;
}


void OverworldMapKeyHandler::OnKeyDown(int KeyCode)
{
	OverworldMap* scene = (OverworldMap*)(CGame::GetInstance()->GetCurrentScene());

	switch (KeyCode)
	{
	case DIK_UP:
		scene->handleMarioMoveUp();
		break;
	case DIK_RIGHT:
		scene->handleMarioMoveRight();
		break;
	case DIK_DOWN:
		scene->handleMarioMoveDown();
		break;
	case DIK_LEFT:
		scene->handleMarioMoveLeft();
		break;
	case DIK_S:
		int scene_id = scene->GetCurrentSceneID();
		if (scene_id != 0)
		{
			CGame::GetInstance()->SwitchScene(scene_id);
		}
		break;
	}

}

void OverworldMapKeyHandler::OnKeyUp(int KeyCode)
{

}

void OverworldMapKeyHandler::KeyState(BYTE *states)
{
}

