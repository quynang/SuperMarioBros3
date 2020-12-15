#include "MovableObject.h"
#include "StaticObject.h"
void MovableObject::AddCoObjects(vector<LPGAMEOBJECT>* coObjects) {

	for (size_t i = 0; i < coObjects->size(); i++) {
		if (dynamic_cast<MovableObject*>(coObjects->at(i)))
		{
			MovableObject* m_obj = dynamic_cast<MovableObject*>(coObjects->at(i));
			coMovableObjects.push_back(m_obj);
			m_obj->AddCoMovableObject(this);
		}

		else if (dynamic_cast<StaticObject*>(coObjects->at(i)))
		{
			StaticObject* s_obj = dynamic_cast<StaticObject*>(coObjects->at(i));
			coStaticObjects.push_back(s_obj);
		}
	}
}