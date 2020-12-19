#pragma once
#include "GameObject.h"
#include "MovableObject.h"
class StaticObject : public CGameObject {
public:
	void AddCoObjects(vector<LPGAMEOBJECT>* objects);

	void AddCoObject(LPGAMEOBJECT object);
};