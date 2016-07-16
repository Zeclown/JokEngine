#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "GameObject.h"
namespace Jokengine
{
	Camera::Camera()
		:frustum(glm::vec2(800,800))
	{
		std::cout << "please";
	}

	glm::mat4 Camera::GetViewMatrix()
	{
		glm::vec2 worldPos = owner.get()->getWorldPosition();
		glm::mat4 view = glm::ortho(0-frustum.x / 2, frustum.x / 2, frustum.y / 2, 0-frustum.y / 2);
		
		return glm::translate(view,glm::vec3(worldPos.x,worldPos.y,0));
	}
}