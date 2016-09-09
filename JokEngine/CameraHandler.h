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
		Camera* GetMainCamera();
		Camera* GetUICamera();
private:
	Camera* mainCamera;
	Camera* uiCamera;
};

#endif
