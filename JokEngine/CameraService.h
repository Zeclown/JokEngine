#ifndef CAMERA_SERVICE_H
#define CAMERA_SERVICE_H

#include <memory>
#include <iostream>
#include "Camera.h"
namespace Jokengine
{

	class CameraService
	{
	public:
		virtual void RegisterCamera(Camera &cam)= 0;
		virtual std::shared_ptr<Camera> GetMainCamera()=0;
	};
}
#endif