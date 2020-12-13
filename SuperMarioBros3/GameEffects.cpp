#include "GameEffects.h"

GameEffects * GameEffects::_instance = NULL;

GameEffects *GameEffects::GetInstance()
{
	if (_instance == NULL) _instance = new GameEffects();
	return _instance;
}

void GameEffects::Render() {
	for (size_t i = 0; i < m_gameEffects.size(); i++) {
		m_gameEffects.at(i)->Render();
	}
}

void GameEffects::Update(DWORD dt) {
	
	for (size_t i = 0; i < m_gameEffects.size(); i++) {
		
		m_gameEffects.at(i)->Update(dt);

		if (m_gameEffects.at(i)->is_finished)
			m_gameEffects.erase(m_gameEffects.begin() + i);
	}

}