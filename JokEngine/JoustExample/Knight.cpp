#include "Knight.h"
#include "GameObject.h"
#include "Game.h"
Knight::Knight(GameObject * go)
	:Component(go),speed(10),healthPoints(1),iFrameDuration(2), jumpSpeed(0.5f)
{
}

void Knight::Init()
{
	pb = GetOwner()->GetActiveComponent<PhysicBody>();
	sd = GetOwner()->GetActiveComponent<SpriteDrawable>();
	sa = GetOwner()->GetActiveComponent<SpriteAnimator>();
	state = E_KNIGHTSTATE::IDLE;
}


void Knight::Update()
{
	if (abs(owner->GetComponent<PhysicBody>()->GetVelocity().x) >= 0.01f)
	{
		state = E_KNIGHTSTATE::RUNNING;
	}
	else
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
	}
}
void Knight::Jump()
{
	pb->AddForce(glm::vec2(0, -1)*jumpSpeed, E_FORCE_TYPE::IMPULSE);
}
void Knight::MoveRight()
{
	sd->flipped = false;
	pb->AddForce(glm::vec2(1, 0)*speed*Game::GetInstance().GetTimeService().GetDeltaTime());
}
void Knight::MoveLeft()
{
	sd->flipped = true;
	pb->AddForce(glm::vec2(-1, 0)*speed*Game::GetInstance().GetTimeService().GetDeltaTime());
}