#include"CameraHandler.h"

CameraHandler::CameraHandler()
{

}
void CameraHandler::RegisterCamera(Camera &cam)
{
	mainCamera=&cam;
}
void CameraHandler::RegisterUICamera(Camera &cam)
{
	uiCamera=&cam;
}
Camera* CameraHandler::GetMainCamera()
{
	return mainCamera;
}

Camera* CameraHandler::GetUICamera()
{
	return uiCamera;
}
	 
