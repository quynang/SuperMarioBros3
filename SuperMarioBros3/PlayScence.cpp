#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "BigBox.h"
#include "GreenPipe.h"
#include "FloatingBrick.h"
#include "Koopas.h"
#include "Coin50.h"
#include "WingGoomba.h"
#include "BreakableBrick.h"
#include "GameEffects.h"
#include "FirePiranhaPlant.h"
#include "PiranhaPlant.h"
#include "FloatingBrick_2.h"
#include "FirePiranhaGreenPlant.h"
#include "KoopaParatroopa.h"
#include "HUB.h"
#include "Font.h"
#include "Brick.h"
#include "BlockRandomItem.h"
#include "MovingBar.h"
#include "PipeExit.h"
#include "Camera.h"
using namespace std;

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAP	7
#define SCENE_SECTION_GRID	8
#define SCENE_SECTION_FONT	9

#define OBJECT_TYPE_BIG_BOX	100
#define OBJECT_TYPE_PIPE	101
#define OBJECT_TYPE_PIPE_EXIT	102
#define OBJECT_TYPE_GOOMBA	1
#define OBJECT_TYPE_BRICK	2
#define OBJECT_TYPE_FLOATING_BRICK	3
#define OBJECT_TYPE_FLOATING_BRICK_2	4
#define OBJECT_TYPE_GROUND	5
#define OBJECT_TYPE_PIRANHA_PLANT	6
#define OBJECT_TYPE_FIRE_PIRANHA_PLANT	7
#define OBJECT_TYPE_FIRE_PIRANHA_PLANT_GREEN	8
#define OBJECT_TYPE_COIN	9
#define OBJECT_TYPE_MARIO	10
#define OBJECT_TYPE_KOOPAS	11
#define OBJECT_TYPE_PARATROPA	12
#define OBJECT_TYPE_WING_GOOMBA	13
#define OBJECT_TYPE_BREAKABLE_BRICK	14
#define OBJECT_TYPE_BLOCK_RANDOM_ITEM	15
#define OBJECT_TYPE_MOVING_BAR	16


#define MAX_SCENE_LINE 1024

#define	OVER_WORD_MAP_SCENE_ID	0
#define PLAY_SCENE_ID	1

#define MAX_OUT_OF_MAP	100

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

void CPlayScene::_ParseSection_TEXTURES(string line)
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

void CPlayScene::_ParseSection_SPRITES(string line)
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

void CPlayScene::_ParseSection_ANIMATIONS(string line)
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

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());
		
		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int id = atoi(tokens[0].c_str());
	int object_type = atoi(tokens[1].c_str());
	float x = atof(tokens[2].c_str());
	float y = atof(tokens[3].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(); 
		player = (CMario*)obj;  

		DebugOut(L"[INFO] Player object created!\n");
	break;

	case OBJECT_TYPE_GROUND: obj = new CGround(); break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(); break;
	case OBJECT_TYPE_KOOPAS: obj = new CKoopas(); break;
	case OBJECT_TYPE_COIN: obj = new Coin50(); break;
	case OBJECT_TYPE_BREAKABLE_BRICK: obj = new BreakableBrick(); break;
	case OBJECT_TYPE_WING_GOOMBA: obj = new WingGoomba(); break;
	case OBJECT_TYPE_FIRE_PIRANHA_PLANT: obj = new FirePiranhaPlant(); break;
	case OBJECT_TYPE_PARATROPA: obj = new KoopaParatroopa(); break;
	case OBJECT_TYPE_FIRE_PIRANHA_PLANT_GREEN: obj = new FirePiranhaGreenPlant(); break;
	case OBJECT_TYPE_PIRANHA_PLANT: obj = new PiranhaPlant(); break;
	case OBJECT_TYPE_BRICK: obj = new Brick(); break;
	case OBJECT_TYPE_BLOCK_RANDOM_ITEM: obj = new BlockRandomItem(); break;
	case OBJECT_TYPE_FLOATING_BRICK: obj = new CFloatingBrick(); break;
	case OBJECT_TYPE_BIG_BOX: obj = new CBigBox(); break;
	case OBJECT_TYPE_PIPE: obj = new CGreenPipe(); break;
	case OBJECT_TYPE_FLOATING_BRICK_2: obj = new FloatingBrick_2(); break;
	case OBJECT_TYPE_MOVING_BAR: obj = new MovingBar(); break;
	case OBJECT_TYPE_PIPE_EXIT: obj = new PipeExit(); break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	obj->SetId(id);
	obj->SetPosition(x, y);
	obj->SetInitInfoFromStringLine(line);
	objects.push_back(obj);
}


void CPlayScene::_ParseSection_MAP(string line)
{
	LPCWSTR path = ToLPCWSTR(line);
	CMap::GetInstance()->Load(path);
	
}

void CPlayScene::_ParseSection_FONT(string line)
{
	vector<string> tokens = split(line);
	int id = atoi(tokens[0].c_str());
	LPCWSTR filePath = ToLPCWSTR(tokens[1].c_str());
	int num_cols = atoi(tokens[2].c_str());
	int fontSize = atoi(tokens[3].c_str());
	int sprite_spacing = atoi(tokens[4].c_str());
	Font::GetInstance()->Load(id, filePath, num_cols, fontSize, sprite_spacing);
}

void CPlayScene::Load()
{
	this->is_update = true;
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
		if (line == "[SPRITES]") { 
			section = SCENE_SECTION_SPRITES; continue; }
		if (line == "[ANIMATIONS]") { 
			section = SCENE_SECTION_ANIMATIONS; continue; }
		if (line == "[ANIMATION_SETS]") { 
			section = SCENE_SECTION_ANIMATION_SETS; continue; }
		if (line == "[OBJECTS]") { 
			section = SCENE_SECTION_OBJECTS; continue; }
		if (line == "[MAP]") { 
			section = SCENE_SECTION_MAP; continue; }
		if (line == "[GRID]") { 
			section = SCENE_SECTION_GRID; continue; }
		if (line == "[FONT]") { 
			section = SCENE_SECTION_FONT; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
			case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
			case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
			case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
			case SCENE_SECTION_GRID: _ParseSection_GRID(line); break;
			case SCENE_SECTION_FONT: _ParseSection_FONT(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));


	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	if (is_update) {

		m_grid->handleUpdate(dt);

		if (player == NULL) return;

		float player_x, player_y;

		player->GetPosition(player_x, player_y);

		
		if (player_y - CMap::GetInstance()->getHeight() >= MAX_OUT_OF_MAP)
		{
			player->SetType(MARIO_TYPE_SMALL);
			CGame::GetInstance()->SwitchScene(OVER_WORD_MAP_SCENE_ID);
			return;
		}
		
		timeGone +=  dt;
		int timeRemain =  timeLimit - (int) timeGone / 1000;
		HUB::GetInstance()->Update(timeRemain, score, player->power, money);
	}
	Camera::GetInstance()->Update(dt);
	GameEffects::GetInstance()->Update(dt);
}

void CPlayScene::_ParseSection_GRID(string line) {
	LPCWSTR path = ToLPCWSTR(line);
	m_grid = new Grid(path);
	m_grid->Load();
}
void CPlayScene::Render()
{
	CMap::GetInstance()->Render();
	GameEffects::GetInstance()->RenderByZIndex(0);
	m_grid->handleRender();
	GameEffects::GetInstance()->RenderByZIndex(1);
	
	HUB::GetInstance()->Render();
	
}

/*
	Unload current scene
*/

void CPlayScene::Unload()
{
	objects.clear();
	player = NULL;
	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScene::AddObject(LPGAMEOBJECT obj)
{
	//objects.insert(objects.begin(), obj);
	LPUNIT unit = new Unit();
	unit->object = obj;
	m_grid->addUnitToLastOfCell(unit);
}

void  CPlayScene::AddObjectIntoBeginning(LPGAMEOBJECT obj) {
	LPUNIT unit = new Unit();
	unit->object = obj;
	m_grid->addUnitToFirstOfCell(unit);
 }

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CGame* game = CGame::GetInstance();
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	if(mario)
		mario->handleOnKeyDown(KeyCode);
	switch (KeyCode)
	{
	case DIK_1:
		mario->SetType(MARIO_TYPE_SMALL);
		break;
	case DIK_2:
		if (mario->getCurrentType() == MARIO_TYPE_SMALL)
		{
			float player_x, player_y;
			mario->GetPosition(player_x, player_y);
			mario->SetPosition(player_x, player_y - (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT));
		}
		mario->SetType(MARIO_TYPE_BIG);
		break;
	case DIK_3:
		if (mario->getCurrentType() == MARIO_TYPE_SMALL)
		{
			float player_x, player_y;
			mario->GetPosition(player_x, player_y);
			mario->SetPosition(player_x, player_y - (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT));
		}
		mario->SetType(MARIO_TYPE_RACCOON);
		break;
	case DIK_4:
		if (mario->getCurrentType() == MARIO_TYPE_SMALL)
		{
			float player_x, player_y;
			mario->GetPosition(player_x, player_y);
			mario->SetPosition(player_x, player_y - (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT));
		}
		mario->SetType(MARIO_TYPE_FIRE);
		break;
	case DIK_R:
		game->SwitchScene(PLAY_SCENE_ID);
		break;
	case DIK_T:
		//Arbitrary position.
		//mario->SetPosition(250, 2070);
		CGame::GetInstance()->SwitchScene(4);
		break;
	case DIK_J:
		//Arbitrary position.
		mario->SetPosition(2010, 86);
		//CGame::GetInstance()->SwitchScene(4);
		break;
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	if(mario)
		mario->handleOnKeyUp(KeyCode);
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{

	CGame *game = CGame::GetInstance();
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	if(mario)
		mario->handleKeyState(states);

}

void CPlayScene::findGameObjectsByTag(string tagName, vector<LPGAMEOBJECT> &resultObjects)
{
	m_grid->findGameObjectsByTag(tagName, resultObjects);
}

CGameObject* CPlayScene::findObjectById(int id)
{
    for (size_t i = 0; i < objects.size(); i++)
    {
        if (objects.at(i)->id == id)
        {
            return objects.at(i);
            break;
        }     
    }
}
