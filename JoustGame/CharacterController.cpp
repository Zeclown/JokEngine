#include "CharacterController.h"
#include "PhysicBody.h"
CharacterController::CharacterController(GameObject *gameObject)
	:ComponentCloneable(gameObject)
{
	
}
void CharacterController::Init()
{
	owner->Update.connect(boost::bind(&CharacterController::Update, this));
}
void CharacterController::Update()
{
	if (InputReader::instance().isButtonDown(GLFW_KEY_W))
	{
		owner->GetComponent<PhysicBody>()->AddForce(glm::vec2(0,-1),E_FORCE_TYPE::IMPULSE);
	}
	if (InputReader::instance().isButton(GLFW_KEY_A))
	{
		owner->GetComponent<PhysicBody>()->AddForce(glm::vec2(-1.0f, 0)*Game::GetInstance().GetTimeService().GetDeltaTime(), E_FORCE_TYPE::IMPULSE);
	}
	if(InputReader::instance().isButton(GLFW_KEY_D))
	{
		owner->GetComponent<PhysicBody>()->AddForce(glm::vec2(1.0f, 0)*Game::GetInstance().GetTimeService().GetDeltaTime(), E_FORCE_TYPE::IMPULSE);
	}
	if (InputReader::instance().isButton(GLFW_KEY_P))
	{
		Game::GetInstance().Destroy(*owner,3);
	}
}