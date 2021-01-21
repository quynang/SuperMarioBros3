#include "GameEffects.h"

GameEffects * GameEffects::_instance = NULL;

GameEffects *GameEffects::GetInstance()
{
	if (_instance == NULL) _instance = new GameEffects();
	return _instance;
}

void GameEffects::RenderByZIndex(int z_index) {
	for (size_t i = 0; i < m_gameEffects.size(); i++) {
		if(m_gameEffects.at(i)->getZIndex() == z_index)
			m_gameEffects.at(i)->Render();
	}
}

void GameEffects::Update(DWORD dt) {
	
	for (size_t i = 0; i < m_gameEffects.size(); i++) {
		
		m_gameEffects.at(i)->Update(dt);
		if (m_gameEffects.size() == 0) return;

		if (m_gameEffects.at(i)->isFinished())
			m_gameEffects.erase(m_gameEffects.begin() + i);
	}

}

void GameEffects::Clear() {
  
   for (auto x : m_gameEffects) {
	   x = NULL;
       delete x;
   }
   m_gameEffects.clear();
   m_gameEffects.resize(0);
   
}