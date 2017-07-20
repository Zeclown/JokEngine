#pragma once
#include "Component.h"
#include "PhysicBody.h"
#include "SpriteDrawable.h"
#include "SpriteAnimator.h"
#include "Collision.h"
#include "PhysicsService.h"
enum E_KNIGHTSTATE{IDLE,RUNNING,FLYING,JUMPING,SPAWNING};
class Knight :public Component
{
public:
	Knight(GameObject* go);
	virtual void Init();
	virtual void Update();
	virtual void Jump();
	virtual void MoveRight();
	virtual void KeepWingsDown();
	virtual void StopWalking();
	virtual void MoveLeft();
	virtual void Spawn();
	virtual void TakeDamage(GameObject* DamageCauser);
	virtual void Die(GameObject* DamageCauser) = 0;
	virtual void OnCollisionEnter(Collision col);

	float speed;
	float jumpSpeed;
	float walkSpeed;
	float healthPoints;
	//The time in seconds it takes for the knight to become vulnerable again after losing one hp
	float iFrameDuration;
	float spawnDuration;
	E_KNIGHTSTATE state;
private:
	PhysicBody* pb;
	SpriteDrawable* sd;
	SpriteAnimator* sa;
	PhysicsService* physics;
	GLboolean grounded;
	GLboolean wingsDowned;
	GLboolean invulnerable;
	float iFrameTimer;
	
	

};