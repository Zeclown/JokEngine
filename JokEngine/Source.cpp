#include "Game.h"
#include "Resource_Manager.h"
#include "SpriteDrawable.h"
#include "PhysicBody.h"
using namespace Jokengine;

void main()
{

	Game& game = Game::GetInstance();
	game.Init();
	ResourceManager::LoadTexture("sprites/awesomeface.png", GL_TRUE, "Player");
	GameObject* go=game.Instantiate(GameObject("Player")).lock().get();
	go->position = glm::vec2(0,0);
	go->size = glm::vec2(1,1);
	SpriteDrawable *sd= go->AddComponent<SpriteDrawable>().lock().get();
	go->AddComponent<PhysicBody>();
	go->GetComponent<PhysicBody>().lock()->interpolate = true;
	sd->sprite= ResourceManager::GetTexture("Player");
	sd->color = glm::vec3(1.0f, 1.0f, 1.0f);



	//Game::GetPhysicsService().SetGravity(glm::vec2(0, 30));
	game.Loop();
}