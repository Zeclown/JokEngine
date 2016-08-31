#include"CameraHandler.h"

CameraHandler::CameraHandler()
{

}
void CameraHandler::RegisterCamera(Camera &cam)
{
	mainCamera.reset(&cam);
}
void CameraHandler::RegisterUICamera(Camera &cam)
{
	uiCamera.reset(&cam);
}
std::shared_ptr<Camera> CameraHandler::GetMainCamera()
{
	return mainCamera;
}

std::shared_ptr<Camera> CameraHandler::GetUICamera()
{
	return uiCamera;
}
	 
