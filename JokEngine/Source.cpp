#include "Game.h"
#include "Resource_Manager.h"
#include "SpriteDrawable.h"
#include "PhysicBody.h"
#include "CircleCollider.h"
using namespace Jokengine;

void main()
{

	Game& game = Game::GetInstance();
	game.Init();
	GameObject go = GameObject("Player");
	ResourceManager::LoadTexture("sprites/awesomeface.png", GL_TRUE, "Player");
	go.position = glm::vec2(0, 0);
	go.size = glm::vec2(40, 40);
	SpriteDrawable *sd = go.AddComponent<SpriteDrawable>();
	go.AddComponent<PhysicBody>();
	go.AddComponent<CircleCollider>();
	sd->sprite = ResourceManager::GetTexture("Player");
	sd->color = glm::vec3(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 1; i++)
	{
		game.Instantiate(go);
	}

	GameObject groundVisual = GameObject("Ground");
	groundVisual.position = glm::vec2(0,60);
	groundVisual.size = glm::vec2(80, 4);
	SpriteDrawable *sd2 = groundVisual.AddComponent<SpriteDrawable>();
	sd2->sprite = ResourceManager::GetTexture("Player");
	sd2->color = glm::vec3(1.0f, 1.0f, 1.0f);
	game.Instantiate(groundVisual);
	//test ground
	b2BodyDef groundDef;
	groundDef.position.Set(0,4);
	groundDef.type = b2_staticBody;
	b2Body* body = game.GetPhysicsService().RegisterBody(groundDef, 1);
	game.GetPhysicsService().RegisterFixtureEdge(body, glm::vec2(-40, 60), glm::vec2(40, 60));


	//Game::GetPhysicsService().SetGravity(glm::vec2(0, 30));
	game.Loop();
}