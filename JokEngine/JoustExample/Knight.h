#pragma once
#include "Component.h"
#include "PhysicBody.h"
#include "SpriteDrawable.h"
#include "SpriteAnimator.h"
enum E_KNIGHTSTATE{IDLE,RUNNING,FLYING};
class Knight :public Component
{
public:
	Knight(GameObject* go);
	virtual void Init();
	virtual void Update();
	virtual void Jump();
	virtual void MoveRight();
	virtual void MoveLeft();
	float speed;
	float jumpSpeed;
	float healthPoints;
	//The time in seconds it takes for the knight to become vulnerable again after losing one hp
	float iFrameDuration;
	E_KNIGHTSTATE state;
private:
	PhysicBody* pb;
	SpriteDrawable* sd;
	SpriteAnimator* sa;

};