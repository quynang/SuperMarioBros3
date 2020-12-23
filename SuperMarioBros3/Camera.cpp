#include "Camera.h"
#include "PlayScence.h"
#include "Mario.h"
#include "Map.h"
#include "Game.h"
#include "Utils.h"

#define HUB_HEIGHT	35
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

void Camera::Update()
{
	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CMap* map = CMap::GetInstance();
	float player_x, player_y;
	mario->GetPosition(player_x, player_y);
	
	this->x = player_x - this->width / 2;
	//this->y = CMap::GetInstance()->getHeight() - this->height;

	this->y = player_y - this->height / 2;
	

	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (y > map->getHeight() - this->height ) y = map->getHeight() - this->height;
	if (x > map->getWidth() - this->width) x = map->getWidth() - this->width;
	
}
