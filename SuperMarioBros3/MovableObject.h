#pragma once
#include "GameObject.h"

class MovableObject : public CGameObject {
protected:
	vector<LPGAMEOBJECT> coObjects;
public:

	void AddCoObjects(vector<LPGAMEOBJECT>* objects);

	void AddCoObject(LPGAMEOBJECT obj);

};