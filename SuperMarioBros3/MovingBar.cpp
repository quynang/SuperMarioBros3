#include "MovingBar.h"
#include "Camera.h"
MovingBar::MovingBar()
{
	SetAnimationSetById(MOVING_BAR_ANI_SET_ID);
	SetState(MOVING_BAR_STATE_STATIC);
	this->nx = -1;
}

void MovingBar::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + MOVING_BAR_BBOX_WIDTH;
	bottom = y + MOVING_BAR_BBOX_HEIGHT;
}

void MovingBar::Update(DWORD dt)
{
	float cam_x, cam_y;
	int cam_width;
	Camera::GetInstance()->GetCamPosition(cam_x, cam_y);
	cam_width = Camera::GetInstance()->getWidth();

	if (cam_x + cam_width >= this->x && this->state == MOVING_BAR_STATE_STATIC)
		this->SetState(MOVING_BAR_STATE_MOVING);

	MovableObject::Update(dt);
	x += dx;
	y += dy;
}

void MovingBar::Render()
{
	int ani = 0;
	
	animation_set->at(ani)->Render(x,y);

	//RenderBoundingBox();
}

void MovingBar::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case MOVING_BAR_STATE_STATIC:
		vx = 0;
		vy = 0;
		break;
	case MOVING_BAR_STATE_MOVING:
		vx = MOVING_BAR_SPEED_X;
		break;
	case MOVING_BAR_STATE_FALLING:
		vx = 0;
		vy = MOVING_BAR_SPEED_FALLING;
		break;
	}
}
