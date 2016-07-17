#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "GameObject.h"
#include "Game.h"
namespace Jokengine
{
	Camera::Camera(std::weak_ptr<GameObject> gameObject)
		:frustum(glm::vec2(1280,720)),Component(gameObject)
	{

	}

	glm::mat4 Camera::GetViewMatrix()
	{
		glm::vec2 worldPos = GetOwner()->getWorldPosition();
		glm::mat4 view = glm::ortho(0-frustum.x  / 2 * Game::PTM, frustum.x / 2 * Game::PTM, frustum.y / 2 * Game::PTM, 0-frustum.y / 2 * Game::PTM);
		
		return glm::translate(view,glm::vec3(worldPos.x,worldPos.y,0));
	}
}