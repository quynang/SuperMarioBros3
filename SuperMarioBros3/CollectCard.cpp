#include "CollectCard.h"
#include "EffectFactory.h"
#include "Font.h"
#include "Game.h"
CollectCard::CollectCard(float x, float y, int card_type) {
	this->x = x;
	this->y = y;
	this->card_type = card_type;
	SetStep(STEP_DRAWING_TEXT_1);
	CGame::GetInstance()->DisableKeyboard();
}

void CollectCard::Update(DWORD dt) {
	counter_time += dt;
	if (counter_time > 200)
		SetStep(STEP_DRAWING_TEXT_1);

	if (counter_time > 400) {
		SetStep(STEP_DRAWING_TEXT_2);
	}

	if (counter_time > 2000)
	{
		this->is_finished = true;
		CGame::GetInstance()->SwitchScene(2);
	}
		
};

void CollectCard::Render() {
	Font::GetInstance()->Draw("COURSE CLEAR", 70, 50);
	if (step > STEP_DRAWING_TEXT_1) {
		Font::GetInstance()->Draw("YOU GOT A CARD", 40, 70);
		float card_sprite_id;
		switch (card_type)
		{
		case 0:
			card_sprite_id = 94003;
			break;
		case 1:
			card_sprite_id = 94005;
			break;
		case 2:
			card_sprite_id = 94004;
			break;
			
		}
		CSprites::GetInstance()->Get(card_sprite_id)->DrawOnScreen(160, 65);
	}
		
}

void CollectCard::SetStep(int step) {
	this->step = step;
}