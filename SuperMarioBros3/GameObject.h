#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
#include "Animations.h"


using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	
	float dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL) 
	{ 
		this->t = t; 
		this->nx = nx; 
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj; 
	}

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};


class CGameObject
{
public:
	int id;
	float x; 
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;
	string tag;
	
	bool is_dead = false;

	DWORD dt;

	bool ignore_collide_nx = false;
	bool ignore_check_collision = false;

	LPANIMATION_SET animation_set;



public:
	virtual void AddCoObjects(vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void AddCoObject(LPGAMEOBJECT coObject);
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	int getNx() { return this->nx; }
	void RenderBoundingBox();
	bool isIgnoreCollideNx() { return ignore_collide_nx; }
	bool isIgnoreCheckCollision() { return ignore_check_collision; }
	D3DXVECTOR3 GetPosition() { D3DXVECTOR3 p; p.x = x; p.y = y; return p; };
	
	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }
	void SetAnimationSetById(int ani_id) { SetAnimationSet(CAnimationSets::GetInstance()->Get(ani_id)); }

	virtual void SetInitInfoFromStringLine(string line);
	void SetId(int id) { this->id = id; }

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny, 
		float &rdx, 
		float &rdy);

	CGameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt);
	virtual void Render() = 0;
	~CGameObject();
};

