#include "Knight.h"
#include "GameObject.h"
#include "Game.h"
#include "BlinkingObject.h"
Knight::Knight(GameObject * go)
	:Component(go), spawnDuration(1),speed(10),healthPoints(1),iFrameDuration(2), jumpSpeed(0.5f),grounded(false),wingsDowned(false), iFrameTimer(0),invulnerable(false), walkSpeed(20)
{
}

void Knight::Init()
{
	signalConnections.push_back(owner->OnCollisionEnter.connect(boost::bind(&Knight::OnCollisionEnter, this,_1)));
	pb = GetOwner()->GetActiveComponent<PhysicBody>();
	sd = GetOwner()->GetActiveComponent<SpriteDrawable>();
	sa = GetOwner()->GetActiveComponent<SpriteAnimator>();
	physics = &Game::GetInstance().GetPhysicsService();
	state = E_KNIGHTSTATE::IDLE;
	Spawn();
}


void Knight::Update()
{
	if (invulnerable && iFrameTimer < 0)
	{
		invulnerable = false;
		if(owner->GetComponent<BlinkingObject>())
			Game::GetInstance().Destroy(*owner->GetComponent<BlinkingObject>());
		if (state == E_KNIGHTSTATE::SPAWNING)
			state = E_KNIGHTSTATE::IDLE;
		if(healthPoints >= 0)
			owner->GetComponent<SpriteDrawable>()->enabled = true;
	}
	if (owner->GetWorldPosition().x > 34)
	{
		owner->position.x -= 67;
	}
	else if (owner->GetWorldPosition().x < -34)
	{
		owner->position.x += 67;
	}
	if (physics->Raycast(owner->GetWorldPosition(), glm::vec2(0, 1), owner->GetWorldSize().y/2, physics->GetMaskBits("Ground", true)))
		grounded = true;
	else
		grounded = false;

	if (!grounded && wingsDowned && state != E_KNIGHTSTATE::SPAWNING )
	{
		state = E_KNIGHTSTATE::JUMPING;
	}
	else if (!grounded && !wingsDowned && state != E_KNIGHTSTATE::SPAWNING)
	{
		state = E_KNIGHTSTATE::FLYING;
	}
	else if (state != E_KNIGHTSTATE::RUNNING && state != E_KNIGHTSTATE::SPAWNING)
	{
		state = E_KNIGHTSTATE::IDLE;
	}
	switch (state)
	{
	case E_KNIGHTSTATE::RUNNING:
		sa->PlayAnimation("Running");
		break;
	case E_KNIGHTSTATE::IDLE:
		sa->PlayAnimation("Idle");
		break;
	case E_KNIGHTSTATE::JUMPING:
		sa->PlayAnimation("Jumping");
		break;
	case E_KNIGHTSTATE::FLYING:
		sa->PlayAnimation("Flying");
		break;
	case E_KNIGHTSTATE::SPAWNING:
		sa->PlayAnimation("Spawning");
		break;
	}
	wingsDowned = false;
	iFrameTimer-=Game::GetInstance().GetTimeService().GetDeltaTime();

}
void Knight::Jump()
{
	if (state == E_KNIGHTSTATE::SPAWNING)
		return;
	pb->AddForce(glm::vec2(0, -1)*jumpSpeed, E_FORCE_TYPE::IMPULSE);
}
void Knight::MoveRight()
{
	if (state == E_KNIGHTSTATE::SPAWNING)
		return;
	if (grounded) 
	{
		state = E_KNIGHTSTATE::RUNNING;	
		pb->AddForce(glm::vec2(1, 0)*walkSpeed*Game::GetInstance().GetTimeService().GetDeltaTime());
	}
	else
	{
		pb->AddForce(glm::vec2(1, 0)*speed*Game::GetInstance().GetTimeService().GetDeltaTime());
	}
	sd->flipped = false;

}
void Knight::KeepWingsDown()
{
	if (state == E_KNIGHTSTATE::SPAWNING)
		return;
	wingsDowned = true;
}
void Knight::StopWalking()
{
	if (state == E_KNIGHTSTATE::SPAWNING)
		return;
	if(grounded)
		state = E_KNIGHTSTATE::IDLE;
	/*if(grounded)
		pb->SetVelocity(glm::vec2(0, pb->GetVelocity().y));*/
}
void Knight::MoveLeft()
{
	//if (grounded && pb->GetVelocity().x>0) //snappy movements when on the ground
	//{
	//	pb->SetVelocity(glm::vec2(0, pb->GetVelocity().y));
	//}
	if (state == E_KNIGHTSTATE::SPAWNING)
		return;
	if (grounded)
	{
		state = E_KNIGHTSTATE::RUNNING;
		pb->AddForce(glm::vec2(-1, 0)*walkSpeed*Game::GetInstance().GetTimeService().GetDeltaTime());
	}
	else
	{
		pb->AddForce(glm::vec2(-1, 0)*speed*Game::GetInstance().GetTimeService().GetDeltaTime());
	}
	sd->flipped = true;
	
}

void Knight::Spawn()
{
	iFrameTimer = spawnDuration;
	invulnerable = true;
	state = E_KNIGHTSTATE::SPAWNING;
	sa->PlayAnimation("Spawning");
}

void Knight::TakeDamage(GameObject* DamageCauser)
{
	healthPoints--;
	if (healthPoints <= 0)
	{
		Die(DamageCauser);
	}
	else
	{
		iFrameTimer = iFrameDuration;
		invulnerable = true;
		owner->AddComponent<BlinkingObject>()->ui=false;
		owner->GetComponent<BlinkingObject>()->secondsBeforeBlinks = 0.1;
	}
}

void Knight::OnCollisionEnter(Collision col)
{
	if (col.sensor && !invulnerable&& col.colliderOther->physicLayer != "Egg" && col.gameObject->GetComponent<Knight>() && !col.gameObject->GetComponent<Knight>()->invulnerable )//knight collision
	{
		if (col.gameObject->GetWorldPosition().y - owner->GetWorldPosition().y<-0.3f) //we lose
		{
			TakeDamage(col.gameObject);
		}
		else if (abs(col.gameObject->GetWorldPosition().y - owner->GetWorldPosition().y) < 0.3f)
		{
			glm::vec2 impulseB = col.gameObject->GetWorldPosition() - owner->GetWorldPosition();
			impulseB /= impulseB.length();
			impulseB *= -1;
			owner->GetComponent<PhysicBody>()->AddForce(impulseB, E_FORCE_TYPE::IMPULSE);
		}
	}
}





