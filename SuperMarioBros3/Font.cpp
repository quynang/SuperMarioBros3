#include "Font.h"
#include "Sprites.h"
#include "Textures.h"
#include "Utils.h"

Font* Font::_instance = NULL;

Font* Font::GetInstance()
{
	if (_instance == NULL) _instance = new Font();
	return _instance;
}

void Font::Load(int id, LPCWSTR filePath, int num_cols, int fontSize, int sprite_spacing)
{
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	textures->Add(id, filePath, D3DCOLOR_XRGB(0, 224, 142));
	LPDIRECT3DTEXTURE9 _texture = textures->Get(id);

	int index = 0;
	int left, top;

	//asii dec.
	for (int i = 48; i <= 90; i++)
	{	
		//ignore special character.
		if (i >= 58 && i <= 64) continue;

        int x = index % num_cols;
        int y = index / num_cols;

		left = (x*fontSize + x*sprite_spacing);
		top = (y * fontSize + y*sprite_spacing);

		//is is negative to avoid duplcation sprite id.
		CSprites::GetInstance()->Add(-i, left, top, left + fontSize, top + fontSize, _texture, 0, 0);

		index++;
	}
}

void Font::Draw(string text, float x, float y, int letter_spacing)
{

	float temp = x; 
	for (int i = 0; i < text.length(); i++)
	{
		if (int(text.at(i)) == ASII_HEC_CODE_SPCACE) {
			temp += FONT_SIZE;
			continue;
		}

		CSprites::GetInstance()->Get(int(-text.at(i)))->DrawOnScreen(temp, y);
		temp = temp + FONT_SIZE + letter_spacing;
	}

}