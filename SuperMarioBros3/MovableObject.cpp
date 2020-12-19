#include "MovableObject.h"
#include "StaticObject.h"
void MovableObject::AddCoObjects(vector<LPGAMEOBJECT>* objects) {

	for (size_t i = 0; i < objects->size(); i++) {
		this->coObjects.push_back(objects->at(i));
		objects->at(i)->AddCoObject(this);
	}
}

void MovableObject::AddCoObject(LPGAMEOBJECT obj) {
	this->coObjects.push_back(obj);
}