//#include "JokEngine.h"
//#include "CharacterController.h"
//
//void main()
//{
//
//	Game& game = Game::GetInstance();
//	game.Init();
//	GameObject go = GameObject("Player");
//	go.AddComponent<CharacterController>();
//	ResourceManager::LoadAudioFile("test.wav", "test");
//	AudioSource *audioSource=go.AddComponent<AudioSource>();
//	AudioFile aFile = ResourceManager::GetAudioFile("test");
//	audioSource->RegisterSound(aFile,"test");
//	audioSource->AddToQueue("test");
//	ResourceManager::LoadSpritesheet("sprites/awesomeface2-sheet.png", GL_TRUE, glm::vec2(64,64),"Player");
//	ResourceManager::LoadSprite("sprites/ground.png", GL_TRUE, "Ground");
//	go.position = glm::vec2(0, 0);
//	go.size = glm::vec2(10, 10);
//	SpriteDrawable *sd = go.AddComponent<SpriteDrawable>();
//	go.AddComponent<PhysicBody>();
//	go.AddComponent<BoxCollider>();
//	sd->sprite = ResourceManager::GetSpritesheet("Player").sprites[0];
//	SpriteAnimator* sp= go.AddComponent<SpriteAnimator>();
//	sp->AddAnimation(Animation(ResourceManager::GetSpritesheet("Player")),"Idle");
//	sp->AddToQueue("Idle");
//	sd->color = glm::vec3(1.0f, 1.0f, 1.0f);
//	GameObject* parent=game.Instantiate(go);
//	
//	GameObject child=GameObject("childPlayer");
//	child.position += glm::vec2(4, -4);
//	child.AddComponent<SpriteDrawable>()->sprite= ResourceManager::GetSpritesheet("Player").sprites[0];
//	game.Instantiate(child)->SetParent(parent);
//	GameObject groundVisual = GameObject("Ground");
//	groundVisual.position = glm::vec2(0,80);
//	groundVisual.size = glm::vec2(90, 4);
//	SpriteDrawable *sd2 = groundVisual.AddComponent<SpriteDrawable>();
//	sd2->sprite = ResourceManager::GetSprite("Ground");
//	sd2->color = glm::vec3(1.0f, 1.0f, 1.0f);
//	groundVisual.AddComponent<PhysicBody>()->SetKinematic(true);
//	groundVisual.AddComponent<BoxCollider>();
//	game.Instantiate(groundVisual);
//
//	game.Loop();
//}