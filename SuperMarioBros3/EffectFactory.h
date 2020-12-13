#pragma once
#include <iostream>
#include "Effect.h"

#define COIN_100	1
class EffectFactory {
	static EffectFactory* _instance;
public:
	Effect* create(int effect_type);
	static EffectFactory* GetInstance();
};