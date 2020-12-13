#pragma once
#include <iostream>
#include "Effect.h"
#include "Utils.h"
#include <vector>

using namespace std;

class GameEffects {
	static GameEffects* _instance;
	vector<Effect*> m_gameEffects;
public:
	void addEffect(Effect* effect) { m_gameEffects.push_back(effect); }
	void Render();
	void Update(DWORD dt);
	static GameEffects* GetInstance();
};
