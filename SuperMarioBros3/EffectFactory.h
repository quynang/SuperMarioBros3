#pragma once
#include <iostream>
#include "Effect.h"

#define COIN_100	1
#define TEXT_NUMBER	2
class EffectFactory {
	static EffectFactory* _instance;
public:
	Effect* create(int effect_type, int extra_param = NULL);
	static EffectFactory* GetInstance();
};