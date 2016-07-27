
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
namespace Jokengine
{
	//Main game state manager
	//Also manages window inputs

	class Game
	{
	public:
		GLuint	   width, height;
		GLfloat fixedRefreshTime;
		std::string gameName;
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
		void Update();
		void FixedUpdate();
		void Render();
		void ProcessInput();
		GameObject *Instantiate(GameObject &toInstantiate);
		void RegisterSpriteRendererService(SpriteRenderingService *service);
		void RegisterCameraService(CameraService *service);
		void RegisterTimeService(TimeService *service);
		void RegisterPhysicsService(PhysicsService *service);

		GameObject* FindByID(GLint objectID);
		SpriteRenderingService& GetSpriteRendererService();
		CameraService& GetCameraService();
		TimeService& GetTimeService();
		PhysicsService& GetPhysicsService();

		boost::signals2::signal<void()> initSignal;
		boost::signals2::signal<void()> updateSignal;
		boost::signals2::signal<void()> fixedSignal;


	private:
		Game(GLuint width=1280, GLuint height=720, const std::string &gameName="JokEngine");

		static Game *instance;
		GameRoom gameroom;
		GLFWwindow * window;
		//services
		SpriteRenderingService  *renderer;
		CameraService *cameras;
		TimeService *time;
		PhysicsService *physics;
		//GameLoop internal timers
		GLfloat fixedUpdateTimer;
	};
}
#endif