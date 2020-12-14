#include "EffectFactory.h"
#include "Coin100.h"
#include "TextNumber.h"
#include "Utils.h"

EffectFactory *EffectFactory::_instance = NULL;

EffectFactory *EffectFactory::GetInstance()
{
	if (_instance == NULL) _instance = new EffectFactory();
	return _instance;
}

Effect* EffectFactory::create(int effect_type, int extra_param) {
	switch (effect_type)
	{
	case COIN_100:
		{
			Effect *effect = new Coin100();
			return effect;
			break;
		}
	case TEXT_NUMBER:
		{
			Effect* effect = new TextNumber(extra_param);
			return effect;
			break;
		}
		
	default:
		DebugOut(L"Can't find effect type: %d !\n", effect_type);
		break;
	}
}