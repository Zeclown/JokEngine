#ifndef CAMERA_HANDLER
#define CAMERA_HANDLER
#include "CameraService.h"
namespace Jokengine
{
	//Default Camera Service
	class CameraHandler : public CameraService
	{
	public:
		CameraHandler();
		 void RegisterCamera(Camera &cam);
		 std::shared_ptr<Camera> GetMainCamera();
	private:
		std::shared_ptr<Camera> mainCamera;
	};
}
#endif
