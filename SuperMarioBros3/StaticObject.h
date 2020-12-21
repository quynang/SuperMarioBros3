#pragma once
#include "GameObject.h"
#include "MovableObject.h"
class StaticObject : public CGameObject {
public:
	StaticObject() { this->tag = "STATIC_OBJECT"; }
	void AddCoObjects(vector<LPGAMEOBJECT>* objects);

	void AddCoObject(LPGAMEOBJECT object);
};