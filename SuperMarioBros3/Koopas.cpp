#include "Koopas.h"
#include "BigBox.h"
#include "Ground.h"
#include "BrickAbstract.h"
#include "PlayScence.h"
#include "Utils.h"
#include "Boundary.h"
CKoopas::CKoopas()
{
	SetState(KOOPAS_STATE_WALKING);
	this->nx = 1;
	SetAnimationSetById(KOOPAS_ANI_SET_ID);
}

void CKoopas::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;

	if (state == KOOPAS_STATE_HIDE_IN_SHELL || state == KOOPAS_STATE_SLIDING)
		bottom = y + KOOPAS_BBOX_HEIGHT_SHELL;
	else
		bottom = y + KOOPAS_BBOX_HEIGHT;
	
}

void CKoopas::Update(DWORD dt)
{
	if (!is_updating) return;
	proccessOverlapping();
	MovableObject::Update(dt);

	if(this->state != KOOPAS_STATE_HIDE_IN_SHELL)
		vy += dt * KOOPAS_GRAVITY;

	if (this->state == KOOPAS_STATE_HIDE_IN_SHELL)
	{
		counter_time += dt;

		if (counter_time >= MAX_TIME_HIDING)
		{
			counter_time = 0;
			y -= KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_SHELL;
			SetState(KOOPAS_STATE_WALKING);
		}	
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(&coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.1f;
		y += min_ty * dy + ny * 0.1f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->nx != 0)
			{
				this->nx = e->nx;

				if (state == KOOPAS_STATE_SLIDING)
				{
					vx = this->nx * KOOPAS_SLIDING_SPEED;
				}
				else
				{
					vx = this->nx * KOOPAS_WALKING_SPEED;
				}
					
				if (state == KOOPAS_STATE_SLIDING)
				{
					if(dynamic_cast<BrickAbstract*>(e->obj))
						((BrickAbstract*)(e->obj))->handleWasAttacked();

					if(dynamic_cast<Enemy*>(e->obj))
						((Enemy*)(e->obj))->handleIsAttacked();
				}
			}
		}
	}

	

	coObjects.clear();

}

void CKoopas::handleJumpingOn() {
	switch (state)
	{
	case KOOPAS_STATE_WALKING:
		SetState(KOOPAS_STATE_HIDE_IN_SHELL);
		break;
	case KOOPAS_STATE_HIDE_IN_SHELL:
		{
			float player_x, player_y;
			int nx_ = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->getNx();
			this->nx = nx_;
			SetState(KOOPAS_STATE_SLIDING);
		}
		break;
	case KOOPAS_STATE_SLIDING:
		SetState(KOOPAS_STATE_HIDE_IN_SHELL);
		break;
	}
}

void CKoopas::handleIsKicked(int nx) {
	this->nx = nx;
	SetState(KOOPAS_STATE_SLIDING);
}

void CKoopas::Render()
{
	int ani = -1;
	switch (state)
	{
	case KOOPAS_STATE_WALKING:
		if (nx > 0)
			ani = KOOPAS_ANI_WALKING_RIGHT;
		else
			ani = KOOPAS_ANI_WALKING_LEFT;
		break;
	case KOOPAS_STATE_HIDE_IN_SHELL:
		ani = KOOPAS_ANI_HIDE_IN_SHELL;
		break;
	case KOOPAS_STATE_SLIDING: 
		ani = KOOPAS_ANI_SLIDING;
		break;
	}
	
	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	int current_state = this->state;
	this->state = state;
	switch (state)
	{
	case KOOPAS_STATE_HIDE_IN_SHELL:
		this->can_be_kicked = true;
		this->can_be_picked_up = true;
		vy = 0;
		if(current_state == KOOPAS_STATE_WALKING) y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_SHELL;
		vx = 0;
		break;
	case KOOPAS_STATE_WALKING:
		this->can_be_kicked = false;
		this->can_be_picked_up = false;
		vx = this->nx*KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_SLIDING:
		this->can_be_kicked = false;
		this->can_be_picked_up = false;
		vx = this->nx*KOOPAS_SLIDING_SPEED;
		break;

	}
}


void CKoopas::handleIsAttacked() {

	if (this->state != KOOPAS_STATE_HIDE_IN_SHELL)
		SetState(KOOPAS_STATE_HIDE_IN_SHELL);
}

void CKoopas::proccessOverlapping()
{
	RECT koopas_rect;
	float m_l, m_t, m_r, m_b;
	GetBoundingBox(m_l, m_t, m_r, m_b);

	koopas_rect.top = m_t;
	koopas_rect.left = m_l;
	koopas_rect.right = m_r;
	koopas_rect.bottom = m_b;

	for (size_t i = 0; i < coObjects.size(); i++)
	{
		RECT obj_rect;
		float l, t, r, b;
		coObjects.at(i)->GetBoundingBox(l, t, r, b);
		obj_rect.top = t;
		obj_rect.left = l;
		obj_rect.right = r;
		obj_rect.bottom = b;

		bool isOverlapping = CGame::GetInstance()->isColliding(koopas_rect, obj_rect);

		if (isOverlapping && dynamic_cast<Boundary*>(coObjects.at(i)) && this->state == KOOPAS_STATE_WALKING) {
			this->nx = ((Boundary*)coObjects.at(i))->getDirection();
			vx = this->nx * KOOPAS_WALKING_SPEED;
		}
	}
}