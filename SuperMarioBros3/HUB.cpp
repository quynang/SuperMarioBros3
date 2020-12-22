#include "HUB.h"
#include "Sprites.h"
#include "Game.h"
#include "Font.h"
#include <string>
#include "Textures.h"
HUB* HUB::_instance = NULL;
HUB::HUB() {

	CTextures::GetInstance()->Add(BLACK_BACKGROUND_TEXTURE_ID, L"textures\\BlackBackGround.png", D3DCOLOR_XRGB(255, 255, 255));
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

	game->DrawOnScreen(0, BOTTOM_Y, blackBackGround, 0, 0, screen_width, 50, 255);
	CSprites::GetInstance()->Get(HUB_SPRITE_ID)->DrawOnScreen(5, BOTTOM_Y + 3, 255);
	CSprites::GetInstance()->Get(CARD_SPRITE_ID)->DrawOnScreen(160, 203, 255);

	for (int i = 0; i < 6; i++)
	{
		CSprites::GetInstance()->Get(BLACK_TRIANGLE_TEXTURE_ID)->DrawOnScreen(51 + i*8, BOTTOM_Y + 10, 255);
	}

	CSprites::GetInstance()->Get(BLACK_P_TEXTURE_ID)->DrawOnScreen(100, BOTTOM_Y + 10, 255);
	CSprites::GetInstance()->Get(M_TEXTURE_ID)->DrawOnScreen(9, BOTTOM_Y + 18, 255);
	Font::GetInstance()->Draw(this->timeString, 130, BOTTOM_Y + 18);
}

void HUB::Update(int time)
{
	timeString = to_string(time);
	while (timeString.length() < 3)
		timeString = "0" + timeString;
}