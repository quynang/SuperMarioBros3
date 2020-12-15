#pragma once
#include "GameObject.h"

class MovableObject : public CGameObject {
protected:
	vector<LPGAMEOBJECT> coStaticObjects;
	vector<LPGAMEOBJECT> coMovableObjects;

public:

	void AddCoObjects(vector<LPGAMEOBJECT>* coObjects);

	void AddCoStaticObject(LPGAMEOBJECT obj) {
		coStaticObjects.push_back(obj);
	}
	void AddCoMovableObject(LPGAMEOBJECT obj) {
		coMovableObjects.push_back(obj);
	}


};