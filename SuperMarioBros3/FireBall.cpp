#include "FireBall.h"
#include "PlayScence.h"
#include <math.h>
#include "Ground.h"

#define PI 3.14159265

FireBall::FireBall() {

}

FireBall::FireBall(float x, float y, int nx) {
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	SetAnimationSet(animation_sets->Get(FIRE_BALL_ANI_SET));
	this->x = x;
	this->y = y;
	this->angle = 0;
	this->nx = nx;
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(this);
}

void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {

	CGameObject::Update(dt, coObjects);
	time_elapsed += dt;

	//Apply projectile motion
	//Reference https://en.wikipedia.org/wiki/Projectile_motion

	//TODO: Apply Component Pattern for this. Let create MovementComponent class.
	//Component Pattern: https://gameprogrammingpatterns.com/component.html
	float move_angle = angle * PI / 180.0;
	this->vx = FIRE_BALL_V0 * cos(move_angle) * nx;
	this->vy = - (FIRE_BALL_V0 * sin(move_angle) - FIRE_BALL_GRAVITY * time_elapsed);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size()==0)
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
		y += min_ty * dy + ny * 0.2f;

		//TODO: Hanlde collision with enemies and wall.
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CGround*>(e->obj)) {
				//Reset and change angle
				this->angle = 38;
				this->time_elapsed = 0;
			}
		}
	}
}

void FireBall::Render() {

	int ani = -1;

	if (nx > 0)
		ani = FIRE_BALL_ANI_RIGHT;
	else
		ani = FIRE_BALL_ANI_LEFT;

	animation_set->at(ani)->Render(x,y);

	//RenderBoundingBox();
}

void FireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FIRE_BALL_BBOX_WIDTH;
	bottom = y + FIRE_BALL_BBOX_HEIGHT;
}
