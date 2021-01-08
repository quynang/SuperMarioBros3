#include "Koopas.h"
#include "BigBox.h"
#include "Ground.h"
#include "FloatingBrick.h"
#include "BreakableBrick.h"
#include "PlayScence.h"
#include "Utils.h"
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

	MovableObject::Update(dt);
	if(this->state != KOOPAS_STATE_HIDE_IN_SHELL)
		vy += dt * KOOPAS_GRAVITY;

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
			if (e->ny < 0)
			{
				if (this->state == KOOPAS_STATE_WALKING)
				{
					float l, t, r, b;
					e->obj->GetBoundingBox(l, t, r, b);
					if ((x + KOOPAS_BBOX_WIDTH/2 > r) || (x + KOOPAS_BBOX_WIDTH - KOOPAS_BBOX_WIDTH/2 < l))
					{
						this->nx = -this->nx;
						vx = this->nx * KOOPAS_WALKING_SPEED;
					}
				}
			}

			else if (e->nx != 0)
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
					if(dynamic_cast<CFloatingBrick*>(e->obj))
						((CFloatingBrick*)(e->obj))->SetState(STATIC_STATE);

					if(dynamic_cast<BreakableBrick*>(e->obj))
						((BreakableBrick*)(e->obj))->handleIsBroken();

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
		ani = KOOPAS_ANI_HIDE_IN_SHELL;
		break;
	}
	
	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	this->state = state;
	switch (state)
	{
	case KOOPAS_STATE_HIDE_IN_SHELL:
		this->can_be_kicked = true;
		this->can_be_picked_up = true;
		vy = 0;
		y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_SHELL;
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