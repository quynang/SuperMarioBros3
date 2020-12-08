#pragma once
#include "GameObject.h"
class MovableObject : public CGameObject {

	void AddCoObjects(vector<LPGAMEOBJECT>* coObjects) {

		CGameObject::AddCoObjects(coObjects);

		for (size_t i = 0; i < coObjects->size(); i++) {
			if (dynamic_cast<MovableObject*>(coObjects->at(i)))
			{
				MovableObject *m_obj = dynamic_cast<MovableObject *>(coObjects->at(i));
				m_obj->AddCoObject(this);
			}
		}
	}
};