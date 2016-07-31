#include "Game.h"
#include "Resource_Manager.h"
#include "SpriteDrawable.h"
#include "PhysicBody.h"
#include "BoxCollider.h"
#include <math.h>
using namespace Jokengine;

void main()
{

	Game& game = Game::GetInstance();
	game.Init();
	GameObject go = GameObject("Player");
	ResourceManager::LoadTexture("sprites/awesomeface.png", GL_TRUE, "Player");
	ResourceManager::LoadTexture("sprites/ground.png", GL_TRUE, "Ground");
	go.position = glm::vec2(0, 0);
	go.size = glm::vec2(10, 10);
	SpriteDrawable *sd = go.AddComponent<SpriteDrawable>();
	go.AddComponent<PhysicBody>();
	go.AddComponent<BoxCollider>();
	sd->sprite = ResourceManager::GetTexture("Player");
	sd->color = glm::vec3(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 1; i++)
	{
		game.Instantiate(go);
	}

	GameObject groundVisual = GameObject("Ground");
	groundVisual.position = glm::vec2(0,80);
	groundVisual.size = glm::vec2(90, 4);
	SpriteDrawable *sd2 = groundVisual.AddComponent<SpriteDrawable>();
	sd2->sprite = ResourceManager::GetTexture("Ground");
	sd2->color = glm::vec3(1.0f, 1.0f, 1.0f);
	groundVisual.AddComponent<PhysicBody>()->kinematic=true;
	groundVisual.AddComponent<BoxCollider>();
	game.Instantiate(groundVisual);



	//Game::GetPhysicsService().SetGravity(glm::vec2(0, 30));
	game.Loop();
}