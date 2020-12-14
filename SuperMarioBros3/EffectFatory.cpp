#include "EffectFactory.h"
#include "GameEffects.h"
#include "Coin100.h"
#include "TextNumber.h"
#include "Utils.h"

EffectFactory *EffectFactory::_instance = NULL;

EffectFactory *EffectFactory::GetInstance()
{
	if (_instance == NULL) _instance = new EffectFactory();
	return _instance;
}

Effect* EffectFactory::create(int effect_type, float x, float y, int extra_param) {
	switch (effect_type)
	{
	case COIN_100:
		{
			Effect *effect = new Coin100(x, y);
			GameEffects::GetInstance()->addEffect(effect);
			return effect;
			break;
		}
	case TEXT_NUMBER:
		{
			Effect* effect = new TextNumber(x, y, extra_param);
			GameEffects::GetInstance()->addEffect(effect);
			return effect;
			break;
		}
		
	default:
		DebugOut(L"Can't find effect type: %d !\n", effect_type);
		break;
	}
}