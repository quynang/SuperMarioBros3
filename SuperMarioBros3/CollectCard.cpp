#include "CollectCard.h"
#include "EffectFactory.h"
#include "Font.h"
#include "Game.h"
#define WORD_MAP_SCENE_ID	0
CollectCard::CollectCard(float x, float y, int card_type) {
	this->x = x;
	this->y = y;
	this->card_type = card_type;
	SetStep(STEP_DRAWING_TEXT_1);
	CGame::GetInstance()->DisableKeyboard();
}

void CollectCard::Update(DWORD dt) {
	counter_time += dt;
	if (counter_time > TIME_STEP_1)
		SetStep(STEP_DRAWING_TEXT_1);

	if (counter_time > TIME_STEP_2) {
		SetStep(STEP_DRAWING_TEXT_2);
	}

	if (counter_time > TIME_STEP_3)
	{
		this->is_finished = true;
		CGame::GetInstance()->SwitchScene(WORD_MAP_SCENE_ID);
	}
		
};

void CollectCard::Render() {
	Font::GetInstance()->Draw("COURSE CLEAR", 70, 50);
	if (step > STEP_DRAWING_TEXT_1) {
		Font::GetInstance()->Draw("YOU GOT A CARD", 40, 70);
		float card_sprite_id;
		switch (card_type)
		{
		case CARD_TYPE_STAR:
			card_sprite_id = CARD_TYPE_STAR_SPRITE_ID;
			break;
		case CARD_TYPE_MUSHROOM:
			card_sprite_id = CARD_TYPE_PLANT_SPRITE_ID;
			break;
		case CARD_TYPE_PLANT:
			card_sprite_id = CARD_TYPE_MUSHROOM_SPRITE_ID;
			break;
			
		}
		CSprites::GetInstance()->Get(card_sprite_id)->DrawOnScreen(160, 65);
	}
		
}

void CollectCard::SetStep(int step) {
	this->step = step;
}