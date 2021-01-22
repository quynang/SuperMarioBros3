#include "FireBall.h"
#include "PlayScence.h"
#include "Goomba.h"
#include <math.h>
#include "Ground.h"
#include "BigBox.h"
#include "GreenPipe.h"
#include "Koopas.h"
#include "Camera.h"
#include "FloatingBrick.h"

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
	this->tag = "FIRE_BALL";
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(this);
}

void FireBall::Update(DWORD dt) {

	MovableObject::Update(dt);
	time_elapsed += dt;
	Camera* camera = Camera::GetInstance();
	float cam_x, cam_y;
	camera->GetCamPosition(cam_x, cam_y);
	if (this->x - cam_x < 0) this->is_dead = true;
	if (cam_x + camera->getWidth() - this->x < 0) this->is_dead = true;
	if (this->y - cam_y < 0) this->is_dead = true;
	if (this->y + camera->getHeight() - this->y < 0) this->is_dead = true;

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

	CalcPotentialCollisions(&coObjects, coEvents);

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
			if (dynamic_cast<StaticObject*>(e->obj))
			{
				if (e->ny < 0)
				{
					this->angle = 38;
					this->time_elapsed = 0;
				}
				//Reset and change angle
				else {
					is_dead = true;
				}
			}

			if (dynamic_cast<Enemy*>(e->obj))
			{
				((Enemy*)e->obj)->handleIsAttacked();
				is_dead = true;
			}
			
			else if (dynamic_cast<BrickAbstract*>(e->obj))
			{
				if (e->ny < 0)
				{
					this->angle = 38;
					this->time_elapsed = 0;
				}
				//Reset and change angle
				else {
					is_dead = true;
				}
			}

		}
	}
	coObjects.clear();

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
