#pragma once
#include "StaticObject.h"
void StaticObject::AddCoObjects(vector<LPGAMEOBJECT>* objects) {

	for (size_t i = 0; i < objects->size(); i++) {
		objects->at(i)->AddCoObject(this);
	}
}

void StaticObject::AddCoObject(LPGAMEOBJECT object) {

}
