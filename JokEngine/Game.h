
#ifndef GAME_H
#define GAME_H
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include"GameRoom.h"
#include<boost\signals2.hpp>
#include "Resource_Manager.h"
#include "InputReader.h"
#include "SpriteRenderingService.h"
#include "CameraService.h"
#include "TimeService.h"
#include "PhysicsService.h"
#include "AudioService.h"
#include "TextRenderingService.h"

	//Main game state manager
	//It is where all the services are located
	//Handles the initialisation process, the game loop and the window management
	// Example:
	//
	//  Game& game = Game::GetInstance(); //get a handle on the game instance
	//  game.Init(); //Initialise the game application and all the services and engines (OpenGL,OpenAL,Box2D,...)
	//  GameObject go = GameObject("Player"); //Make a new prototype to instantiate
	//  game.Instantiate(go); //Instantiate a copy of the prototype in the gamespace
	//	game.Loop();//Starts the gameloop, locking the application
class Game
{
public:
	GLfloat const BOX2D_TO_WORLD;
	GLfloat const WORLD_TO_BOX2D;
	//Destructor
	~Game();
	static Game& GetInstance()
	{
		if (!instance)
			instance = new Game;
		return *instance;
	}
	// Initialize game state (load all shaders/textures/levels/services)
	void Init();
	// Start GameLoop
	void Loop();
	GameObject *Instantiate(GameObject &toInstantiate);
	void ClearRoom();
	void Destroy(GameObject &toDestroy,GLfloat after=0);
	void RegisterSpriteRendererService(SpriteRenderingService *service);
	void RegisterCameraService(CameraService *service);
	void RegisterTimeService(TimeService *service);
	void RegisterPhysicsService(PhysicsService *service);
	void RegisterAudioService(AudioService *service);
	void RegisterTextRendererService(TextRenderingService *service);
	void EnablePhysicsDebug(GLboolean drawColliders, GLboolean logCollisions);

	GLfloat fixedRefreshTime;

	GameObject* FindByID(GLint objectID);
	AudioService& GetAudioService();
	SpriteRenderingService& GetSpriteRendererService();
	CameraService& GetCameraService();
	TimeService& GetTimeService();
	PhysicsService& GetPhysicsService();
	TextRenderingService& GetTextRendererService();

	boost::signals2::signal<void()> initSignal;
	boost::signals2::signal<void()> updateSignal;
	boost::signals2::signal<void()> fixedSignal;


private:
	Game(GLuint width=1280, GLuint height=720, const std::string &gameName="JokEngine");
	void UpdateAnimation();
	void Update();
	void FixedUpdate();
	void Render();
	void ProcessInput();
	void CleanUpResources();
	static Game *instance;
	GLuint	   width, height;

	std::string gameName;
	GameRoom gameroom;
	GLFWwindow * window;
	//services
	SpriteRenderingService  *renderer;
	CameraService *cameras;
	TimeService *time;
	PhysicsService *physics;
	AudioService *audio;
	TextRenderingService *text;

	//GameLoop internal timers
	GLfloat fixedUpdateTimer;
};

#endif