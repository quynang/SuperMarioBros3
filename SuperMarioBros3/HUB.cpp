#include "HUB.h"
#include "Sprites.h"
#include "Game.h"
#include "Font.h"
#include <string>
#include "Textures.h"
#include "Camera.h"
#include "Utils.h"
HUB* HUB::_instance = NULL;
HUB::HUB() {

	CTextures::GetInstance()->Add(BLACK_BACKGROUND_TEXTURE_ID, L"textures\\BlackBackGround.png", D3DCOLOR_XRGB(255, 255, 255));
	this->y = Camera::GetInstance()->getHeight();
}
HUB* HUB::GetInstance()
{
	if (_instance == NULL) _instance = new HUB();
	return _instance;
}

void HUB::Render()
{

	LPDIRECT3DTEXTURE9 blackBackGround = CTextures::GetInstance()->Get(BLACK_BACKGROUND_TEXTURE_ID);

	CGame *game = CGame::GetInstance();
	int screen_width = 	game->GetScreenWidth();
	game->DrawOnScreen(x, y, blackBackGround, 0, 0, screen_width, 50, 255);
	CSprites::GetInstance()->Get(HUB_SPRITE_ID)->DrawOnScreen(x + 5, y + 3, 255);
	CSprites::GetInstance()->Get(CARD_SPRITE_ID)->DrawOnScreen(160, y + 3, 255);

	for (int i = 0; i < 6; i++)
	{
		CSprites::GetInstance()->Get(BLACK_TRIANGLE_TEXTURE_ID)->DrawOnScreen(51 + i*8, y + 10, 255);
	}

	CSprites::GetInstance()->Get(BLACK_P_TEXTURE_ID)->DrawOnScreen(100, y + 10, 255);
	CSprites::GetInstance()->Get(M_TEXTURE_ID)->DrawOnScreen(9, y + 18, 255);
	Font::GetInstance()->Draw(this->timeString, 130, y + 18);
	Font::GetInstance()->Draw(this->score, 51, y + 18);
}

void HUB::Update(int time, int score)
{
	this->timeString = to_string(time);
	this->score = to_string(score);

	while (this->timeString.length() < 3)
		this->timeString = "0" + timeString;
	while (this->score.length() < 7)
		this->score = "0" + this->score;
}