#include "Enemy.h"
#include "PlayScence.h"
void Enemy::handleJumpingOn()
{

}

void Enemy::handleIsKicked(int nx)
{

}

void Enemy::handleIsAttacked()
{

}

void Enemy::Update(DWORD dt) {

	CMario* mario = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float player_x, player_y;
	mario->GetPosition(player_x, player_y);
	if (abs(this->x - player_x) > 140) return;
	if (abs(this->x - player_x) < 140 && player_y - this->y < -50) return;
	MovableObject::Update(dt);
}