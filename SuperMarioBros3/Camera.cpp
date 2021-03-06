#include "Camera.h"
#include "PlayScence.h"
#include "Mario.h"
#include "Map.h"
#include "Game.h"
#include "Utils.h"

#define HUB_HEIGHT	35
#define CAMERA_SPEED_X	0.06f

#define START_Y_CAMERA_DOWN	350
#define STAT_Y_CAMERA_UP 200
Camera* Camera::_instance = NULL;

Camera::Camera()
{
	this->width = CGame::GetInstance()->GetScreenWidth();
	this->height = CGame::GetInstance()->GetScreenHeight() - HUB_HEIGHT;
}
Camera* Camera::GetInstance()
{
	if (_instance == NULL) _instance = new Camera();
	return _instance;
}

void Camera::Update(DWORD dt)
{
	CMap* map = CMap::GetInstance();
	float player_x, player_y;
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	mario->GetPosition(player_x, player_y);

	if (CGame::GetInstance()->GetCurrentSceneId() == WORLD_1_4_ID)
	{
		x += CAMERA_SPEED_X * dt;
		y = 0;
		if (player_x < this->x)
		{
			mario->SetPosition(this->x, player_y);
		}
		
	}
	else
	{
	
		this->x = player_x - this->width / 2;

		this->y = CMap::GetInstance()->getHeight() - this->height;
		if(mario->getCurrentState() == FLYING)
			this->y = player_y - this->height / 2;
		if(player_y < STAT_Y_CAMERA_UP)
			this->y = player_y - this->height / 2;
		if (mario->getCurrentState() == FALLING && mario->camera_flag)
		{		
			this->y = player_y - this->height / 2;
		}
		if (player_y >= START_Y_CAMERA_DOWN) mario->camera_flag = false;

	}

	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (y > map->getHeight() - this->height ) y = map->getHeight() - this->height;
	if (x > map->getWidth() - this->width) x = map->getWidth() - this->width;
	
}
