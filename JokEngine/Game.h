
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
		std::weak_ptr<GameObject> Instantiate(GameObject &toInstantiate);
		static void RegisterSpriteRendererService(SpriteRenderingService *service);
		static void RegisterCameraService(CameraService *service);
		static void RegisterTimeService(TimeService *service);
		static void RegisterPhysicsService(PhysicsService *service);

		static SpriteRenderingService& GetSpriteRendererService();
		static CameraService& GetCameraService();
		static TimeService& GetTimeService();
		static PhysicsService& GetPhysicsService();

		static boost::signals2::signal<void()> initSignal;
		static boost::signals2::signal<void()> updateSignal;
		static boost::signals2::signal<void()> fixedSignal;


	private:
		Game(GLuint width=960, GLuint height=540, const std::string &gameName="JokEngine");
		static Game *instance;
		GameRoom gameroom;
		GLFWwindow * window;
		//services
		static SpriteRenderingService  *renderer;
		static CameraService *cameras;
		static TimeService *time;
		static PhysicsService *physics;
		//GameLoop internal timers
		GLfloat fixedUpdateTimer;
	};
}
#endif