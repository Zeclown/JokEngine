
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
	GLfloat const Game::PTM=0.005;
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
	std::weak_ptr<GameObject> Game::FindByID(GLint objectID)
	{
		return gameroom.FindByID(objectID);
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
		GameObject *mainCam =  Instantiate(GameObject("CameraMain")).lock().get();
		std::shared_ptr<Camera> mainCamComp=mainCam->AddComponent<Camera>().lock();
		mainCamComp->frustum=glm::vec2(1250,720);
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
			auto drawPtr = iter.second->GetComponent<SpriteDrawable>().lock();
			if (drawPtr)
			{
				glm::vec2 extrapolationMod = glm::vec2(0, 0);
				auto physicPtr = iter.second->GetComponent<PhysicBody>().lock();
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
			auto physPtr = iter.second->GetComponent<PhysicBody>().lock();
			if (physPtr)
			{
				physPtr->FixedUpdate();
			}
		}
	}
}