
#include "game.h"
#include "GameObject.h"
#include "SpriteDrawable.h"
#include "PhysicBody.h"
#include "SpriteRenderer.h"
#include "CameraHandler.h"
#include "TextRenderer.h"
#include "Clock.h"
#include "Physics.h"
#include "Audio.h"
#include "SpriteAnimator.h"
#include "TextUI.h"
#include <tuple>

Game *Game::instance = 0;
Game::Game(GLuint width, GLuint height, const std::string &gameName)
	: width(width), height(height), gameroom(GameRoom::instance()), gameName(gameName), fixedRefreshTime(0.03f), fixedUpdateTimer(0.0f),BOX2D_TO_WORLD(15.0f),WORLD_TO_BOX2D(1.0f/BOX2D_TO_WORLD)
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
	
	//OPENAL initialization
	ALCdevice *device;
	device = alcOpenDevice(NULL);
	ALCcontext *context;

	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context))
		std::cout << "Audio Initialisation error";
		
}

Game::~Game()
{

}
GameObject* Game::Instantiate(GameObject &toInstantiate)
{
	return gameroom.Instantiate(toInstantiate);
}
void Game::Destroy(GameObject & toDestroy, GLfloat after)
{
	gameroom.Destroy(toDestroy, after);
}
void Game::Destroy(Component &toDestroy, GLfloat after)
{
	gameroom.Destroy(toDestroy, after);
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
	glfwSetCharModsCallback(window, InputReader::CharmodsCallback);
	//Service Registration
	if (!renderer)//if the rendering service is not initialised yet
	{
		SpriteRenderer *renderingService = new SpriteRenderer(ResourceManager::GetShader("sprite"));
		RegisterSpriteRendererService(renderingService);
	}
	if (!cameras)//if the camera service is not initialised yet
	{
		CameraHandler *cameraService = new CameraHandler();
		RegisterCameraService(cameraService);
	}
	if (!time)//if the time service is not initialised yet
	{
		Clock *timeService = new Clock();
		RegisterTimeService(timeService);
	}
	if (!physics)//if the physic service is not initialised yet
	{
		Physics *physicsService = new Physics();
		RegisterPhysicsService(physicsService);
	}
	if (!audio)//if the audio service is not initialised yet
	{
		Audio *audio = new Audio();
		RegisterAudioService(audio);
	}
	ClearRoom();

	if (!text)//if the text rendering service is not initialised yet
	{
		TextRenderer *textService = new TextRenderer(width, height);
		textService->Load("fonts/emulogic.TTF", 24);
		RegisterTextRendererService(textService);
	}

}
void Game::Loop()
{

	//gameloop
	while (!glfwWindowShouldClose(window))
	{
		initSignal();
		time->UpdateTime((float)glfwGetTime());
		fixedUpdateTimer += time->GetDeltaTime();
		glfwPollEvents();		
		ProcessInput();
		while (fixedUpdateTimer>=fixedRefreshTime)
		{
			FixedUpdate();
			for (auto &iter : gameroom.RoomObjects)
			{
				if(iter.second->isActive())
					iter.second->FixedUpdate();
			}
			fixedUpdateTimer -= fixedRefreshTime;

		}
		Update();
		UpdateAnimation();
		glm::mat4 projection = cameras->GetMainCamera()->GetViewMatrix();
		ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Render
		Render();
		CleanUpResources();
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
void Game::RegisterAudioService(AudioService *service)
{
	if (audio)
		delete audio;
	audio = service;
}
void Game::RegisterTextRendererService(TextRenderingService *service)
{
	if (text)
		delete text;
	text = service;
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
AudioService& Game::GetAudioService()
{
	return *audio;
}
PhysicsService& Game::GetPhysicsService()
{
	return *physics;
}
TextRenderingService &Game::GetTextRendererService()
{
	return *text;
}
void Game::ProcessInput()
{
	InputReader::instance().UpdateInput();
}
void Game::CleanUpResources()
{
	gameroom.CleanUpResources();
}
void Game::Update()
{
	for (auto &iter : gameroom.RoomObjects)
	{
		if (iter.second->isActive())
			iter.second->Update();
	}
}
void Game::UpdateAnimation()
{
	for (auto &iter : gameroom.RoomObjects)
	{
		if (iter.second->isActive())
		{
			auto drawPtr = iter.second->GetActiveComponent<SpriteAnimator>();
			if (drawPtr)
			{
				drawPtr->Update();
			}
		}
	}
}
void Game::Render()
{	
	typedef std::multimap<GLuint, SpriteDrawable*> RenderQueueType;
	typedef std::multimap<GLuint, TextUI*> RenderQueueUIType;

	std::multimap<GLuint, SpriteDrawable*> renderQueue;
	std::multimap<GLuint, TextUI*> renderQueueUI;
	//build the render queues
	for (auto &iter : gameroom.RoomObjects)
	{
		if (iter.second->isActive())
		{
			auto drawPtr = iter.second->GetActiveComponent<SpriteDrawable>();
			auto drawUIPts = iter.second->GetActiveComponent<TextUI>();
			if (drawPtr)
			{
				renderQueue.insert(RenderQueueType::value_type(drawPtr->drawOrder, drawPtr));
			}
			if (drawUIPts)
			{
				renderQueueUI.insert(RenderQueueUIType::value_type(drawUIPts->drawOrder, drawUIPts));
			}
		}
	}


	//Sprite Rendering

	//order the queue index
	std::vector<GLuint> drawIndexOrdered;
	for (auto it = renderQueue.begin(); it != renderQueue.end(); it = renderQueue.upper_bound(it->first))
	{
		drawIndexOrdered.push_back(it->first);
	}

	for (int i = 0; i < (int)drawIndexOrdered.size() - 1; ++i)
	{
		if (drawIndexOrdered[i] > drawIndexOrdered[i + 1])
		{
			std::swap(drawIndexOrdered[i], drawIndexOrdered[i + 1]);
			i = -1;
		}
	}
	//Go through the sprite render queue
	for (size_t i = 0; i < drawIndexOrdered.size(); i++)
	{
		GLuint keyIndex = drawIndexOrdered[i];
		auto range = renderQueue.equal_range(keyIndex);
		for (auto iter = range.first; iter != range.second; ++iter)
		{
			glm::vec2 extrapolationMod = glm::vec2(0, 0);
			auto physicPtr = iter->second->GetOwner()->GetActiveComponent<PhysicBody>();
			if (physicPtr && physicPtr->interpolate)
			{
			GLfloat alpha = fixedUpdateTimer / fixedRefreshTime;
			extrapolationMod = iter->second->GetOwner()->GetWorldPosition()- (iter->second->GetOwner()->GetWorldPosition() * alpha + physicPtr->lastPos*(1-alpha));
			}
			iter->second->Draw(*renderer, extrapolationMod);
		}
	}

	//UI Rendering
	//order the queue index
	drawIndexOrdered.clear();
	for (auto it = renderQueueUI.begin(); it != renderQueueUI.end(); it = renderQueueUI.upper_bound(it->first))
	{
		drawIndexOrdered.push_back(it->first);
	}

	for (int i = 0; i < (int)drawIndexOrdered.size() - 1; ++i)
	{
		if (drawIndexOrdered[i] > drawIndexOrdered[i + 1])
		{
			std::swap(drawIndexOrdered[i], drawIndexOrdered[i + 1]);
			i = -1;
		}  
	}
	//Go through the UI render queue
	for (size_t i = 0; i < drawIndexOrdered.size(); i++)
	{
		GLuint keyIndex = drawIndexOrdered[i];
		auto range = renderQueueUI.equal_range(keyIndex);
		for (auto iter = range.first; iter != range.second; ++iter)
		{
			iter->second->DrawText(*text);
		}
	}

	
}
void Game::ClearRoom()
{
	gameroom.ClearRoom();
	//Instantiate base camera
	GameObject mainCam = GameObject("CameraMain");
	mainCam.AddComponent<Camera>();
	Camera* camComp = Instantiate(mainCam)->GetComponent<Camera>();
	camComp->frustum = glm::vec2(width/20, height/20);
	cameras->RegisterCamera(*camComp);

	//Instantiate base UI camera
	GameObject uiCam = GameObject("UICamera");
	uiCam.AddComponent<Camera>();
	Camera* uiCamComp = Instantiate(uiCam)->GetComponent<Camera>();
	uiCamComp->frustum = glm::vec2(width, height);
	cameras->RegisterUICamera(*uiCamComp);

}
void Game::FixedUpdate()
{
	physics->FixedUpdate();
	for (auto &iter : gameroom.RoomObjects)
	{
		auto physPtr = iter.second->GetActiveComponent<PhysicBody>();
		if (physPtr)
		{
			physPtr->FixedUpdate();
		}
	}
}
