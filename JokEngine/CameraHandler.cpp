#include"CameraHandler.h"
namespace Jokengine
{
	CameraHandler::CameraHandler()
	{

	}
	void CameraHandler::RegisterCamera(Camera &cam)
	{
		mainCamera.reset(&cam);
	}
	std::shared_ptr<Camera> CameraHandler::GetMainCamera()
	{
		return mainCamera;
	}
	 
}