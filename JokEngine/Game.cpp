
#include "game.h"
#include "GameObject.h"
#include "SpriteDrawable.h"
#include "PhysicBody.h"
#include "SpriteRenderer.h"
#include "CameraHandler.h"
#include "Clock.h"
#include "Physics.h"

namespace Jokengine
{
	Game *Game::instance = 0;
	Game::Game(GLuint width, GLuint height, const std::string &gameName)
		: width(width), height(height), gameroom(GameRoom::instance()), gameName(gameName), fixedRefreshTime(0.03), fixedUpdateTimer(0),BOX2D_TO_WORLD(130),WORLD_TO_BOX2D(0.013)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		window = glfwCreateWindow(width, height, gameName.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);

		glewExperimental = GL_TRUE;
		glewInit();
		glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.


					  // OpenGL configuration
		glViewport(0, 0, width, height);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	Game::~Game()
	{

	}
	GameObject* Game::Instantiate(GameObject &toInstantiate)
	{
		return gameroom.Instantiate(toInstantiate);
	}
	GameObject* Game::FindByID(GLint objectID)
	{
		return gameroom.FindByID(objectID);
	}
	void Game::Init()
	{

		// Load basic shaders
		ResourceManager::LoadShader("shaders/baseSprite.vshader", "shaders/baseSprite.fshader", nullptr, "sprite");
		// Configure shaders

		ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);

		//input callbacks setup

		glfwSetKeyCallback(window, InputReader::KeyCallback);
		glfwSetMouseButtonCallback(window, InputReader::MouseButtonCallback);

		//Service Registration
		if (!renderer)//if the rendering service is not initialised yet
		{
			SpriteRenderer *renderingService = new SpriteRenderer(ResourceManager::GetShader("sprite"));
			Game::RegisterSpriteRendererService(renderingService);
		}
		if (!cameras)//if the camera service is not initialised yet
		{
			CameraHandler *cameraService = new CameraHandler();
			Game::RegisterCameraService(cameraService);
		}
		if (!time)//if the time service is not initialised yet
		{
			Clock *timeService = new Clock();
			Game::RegisterTimeService(timeService);
		}
		if (!physics)//if the physic service is not initialised yet
		{
			Physics *physicsService = new Physics();
			Game::RegisterPhysicsService(physicsService);
		}
		//Instantiate base camera
		GameObject mainCam =   GameObject("CameraMain");
		mainCam.AddComponent<Camera>();
		Camera* camComp=Instantiate(mainCam)->GetComponent<Camera>();
		cameras->RegisterCamera(*camComp);

	}
	void Game::Loop()
	{

		//gameloop
		while (!glfwWindowShouldClose(window))
		{
			initSignal();
			time->UpdateTime(glfwGetTime());
			fixedUpdateTimer += time->GetDeltaTime();
			glfwPollEvents();		
			ProcessInput();
			while (fixedUpdateTimer>=fixedRefreshTime)
			{
				FixedUpdate();
				fixedSignal();
				fixedUpdateTimer -= fixedRefreshTime;

			}
			Update();
			updateSignal();
			glm::mat4 projection = cameras->GetMainCamera()->GetViewMatrix();
			ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			// Render
			Render();
			glfwSwapBuffers(window);
		}
	}
	void Game::RegisterSpriteRendererService(SpriteRenderingService *service)
	{
		if(renderer)
			delete renderer;
		renderer = service;
	}
	void Game::RegisterPhysicsService(PhysicsService *service)
	{
		if (physics)
			delete physics;
		physics = service;
	}
	void Game::RegisterTimeService(TimeService *service)
	{
		if (time)
			delete time;
		time = service;
	}
	void Game::RegisterCameraService(CameraService *service)
	{
		if (cameras)
			delete cameras;
		cameras = service;
	}
	void Game::EnablePhysicsDebug(GLboolean drawColliders, GLboolean logCollisions)
	{

	}
	SpriteRenderingService& Game::GetSpriteRendererService()
	{
		return *renderer;
	}
	CameraService& Game::GetCameraService()
	{
		return *cameras;
	}
	TimeService& Game::GetTimeService()
	{
		return *time;
	}
	PhysicsService& Game::GetPhysicsService()
	{
		return *physics;
	}
	void Game::ProcessInput()
	{
		InputReader::instance().UpdateInput();
	}
	void Game::Update()
	{
		updateSignal();
	}
	void Game::Render()
	{
		for (auto &iter : gameroom.RoomObjects)
		{
			auto drawPtr = iter.second->GetComponent<SpriteDrawable>();
			if (drawPtr)
			{
				glm::vec2 extrapolationMod = glm::vec2(0, 0);
				auto physicPtr = iter.second->GetComponent<PhysicBody>();
				if (physicPtr && physicPtr->interpolate)
				{
					GLfloat alpha = fixedUpdateTimer / fixedRefreshTime;
					extrapolationMod = iter.second->position- (iter.second->position * alpha + physicPtr->lastPos*(1-alpha));
				}
				drawPtr->Draw(*renderer, extrapolationMod);
			}
		}
	}
	void Game::FixedUpdate()
	{
		physics->FixedUpdate();
		for (auto &iter : gameroom.RoomObjects)
		{
			auto physPtr = iter.second->GetComponent<PhysicBody>();
			if (physPtr)
			{
				physPtr->FixedUpdate();
			}
		}
	}
}