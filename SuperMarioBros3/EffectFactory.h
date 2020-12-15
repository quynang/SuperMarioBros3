#pragma once
#include <iostream>
#include "Effect.h"

#define COIN_100	1
#define TEXT_NUMBER	2
#define MARIO_TYPE_UP	3
class EffectFactory {
	static EffectFactory* _instance;
public:
	Effect* create(int effect_type, float x, float y, int extra_param = NULL);
	static EffectFactory* GetInstance();
};