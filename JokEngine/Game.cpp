
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
	SpriteRenderingService  *Game::renderer;
	CameraService *Game::cameras;
	TimeService *Game::time;
	PhysicsService *Game::physics;
	boost::signals2::signal<void()> Game::initSignal;
	boost::signals2::signal<void()> Game::updateSignal;
	boost::signals2::signal<void()> Game::fixedSignal;

	Game::Game(GLuint width, GLuint height, const std::string &gameName)
		: width(width), height(height), gameroom(GameRoom::instance()), gameName(gameName), fixedRefreshTime(0.03), fixedUpdateTimer(0)
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
	std::weak_ptr<GameObject> Game::Instantiate(GameObject &toInstantiate)
	{
		return gameroom.Instantiate(toInstantiate);
	}
	void Game::Init()
	{

		// Load basic shaders
		ResourceManager::LoadShader("shaders/baseSprite.vshader", "shaders/baseSprite.fshader", nullptr, "sprite");
		// Configure shaders

		ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);

		//Service Registration
		SpriteRenderer *renderingService = new SpriteRenderer(ResourceManager::GetShader("sprite"));
		Game::RegisterSpriteRendererService(renderingService);

		glfwSetKeyCallback(window, InputReader::KeyCallback);
		glfwSetMouseButtonCallback(window, InputReader::MouseButtonCallback);

		CameraHandler *cameraService = new CameraHandler();
		Game::RegisterCameraService(cameraService);
		GameObject *mainCam = new GameObject("CameraMain");
		std::shared_ptr<Camera> mainCamComp=mainCam->AddComponent<Camera>().lock();
		mainCamComp->frustum=glm::vec2(width,height);
		Instantiate(*mainCam);
		cameras->RegisterCamera(*mainCamComp);

		Clock *timeService = new Clock();
		Game::RegisterTimeService(timeService);

		Physics *physicsService = new Physics();
		Game::RegisterPhysicsService(physicsService);


		initSignal();

	}
	void Game::Loop()
	{

		//gameloop
		while (!glfwWindowShouldClose(window))
		{
			time->UpdateTime(glfwGetTime());
			fixedUpdateTimer += time->GetDeltaTime();
			glfwPollEvents();		
			ProcessInput();
			while (fixedUpdateTimer>=fixedRefreshTime)
			{
				FixedUpdate();
				fixedUpdateTimer -= fixedRefreshTime;
			}
			Update();
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
		delete Game::renderer;
		Game::renderer = service;
	}
	void Game::RegisterPhysicsService(PhysicsService *service)
	{
		delete Game::physics;
		Game::physics = service;
	}
	void Game::RegisterTimeService(TimeService *service)
	{
		delete Game::time;
		Game::time = service;
	}
	void Game::RegisterCameraService(CameraService *service)
	{
		delete Game::cameras;
		Game::cameras = service;
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
		for (int i = 0; i < gameroom.RoomObjects.size(); i++)
		{
			auto drawPtr = gameroom.RoomObjects[i]->GetComponent<SpriteDrawable>().lock();
			if (drawPtr)
			{
				glm::vec2 extrapolationMod = glm::vec2(0, 0);
				auto physicPtr = gameroom.RoomObjects[i]->GetComponent<PhysicBody>().lock();
				if (physicPtr && physicPtr->interpolate)
				{
					GLfloat alpha = fixedUpdateTimer / fixedRefreshTime;
					extrapolationMod = gameroom.RoomObjects[i]->position- (gameroom.RoomObjects[i]->position * alpha + physicPtr->lastPos*(1-alpha));
				}
				drawPtr->Draw(*renderer, extrapolationMod);
			}
		}
	}
	void Game::FixedUpdate()
	{
		physics->FixedUpdate();
		for (int i = 0; i < gameroom.RoomObjects.size(); i++)
		{
			auto physPtr = gameroom.RoomObjects[i]->GetComponent<PhysicBody>().lock();
			if (physPtr)
			{
				physPtr->FixedUpdate();
			}
		}
	}
}