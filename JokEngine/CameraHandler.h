#ifndef CAMERA_HANDLER
#define CAMERA_HANDLER
#include "CameraService.h"

//Default Camera Service
class CameraHandler : public CameraService
{
public:
	CameraHandler();
		void RegisterCamera(Camera &cam);
		void RegisterUICamera(Camera &cam);
		std::shared_ptr<Camera> GetMainCamera();
		std::shared_ptr<Camera> GetUICamera();
private:
	std::shared_ptr<Camera> mainCamera;
	std::shared_ptr<Camera> uiCamera;
};

#endif
