#ifndef CAMERA_SERVICE_H
#define CAMERA_SERVICE_H

#include <memory>
#include <iostream>
#include "Camera.h"

//The Camera Service stores a set of cameras to be used by the renderers
class CameraService
{
public:
	virtual void RegisterCamera(Camera &cam)= 0;
	virtual void RegisterUICamera(Camera &cam) = 0;
	virtual std::shared_ptr<Camera> GetMainCamera()=0;
	virtual std::shared_ptr<Camera> GetUICamera() = 0;
};

#endif