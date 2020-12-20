#pragma once
#include "Mario.h"
#include "Const.h"
#include "Utils.h"
class CMario; //TODO: Why this line avoid circular denpendency ? How it work. Are there any efficent way for that?

class MarioState {

public:

	int current_state = 0;
	
	virtual void handleOnKeyUp(CMario& mario, int keyCode) = 0;

	virtual void handleOnKeyDown(CMario& mario, int keyCode) = 0;

	virtual void handleKeyState(CMario& mario, BYTE* states) = 0;

	virtual void update(CMario& mario, DWORD dt) = 0;

	virtual int getAni(CMario& mario) = 0;
};