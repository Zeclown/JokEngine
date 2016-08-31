#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "GameObject.h"
#include "Game.h"

Camera::Camera(GameObject* gameObject)
	:frustum(glm::vec2(200.0f,200.0f)), ComponentCloneable(gameObject)
{

}

glm::mat4 Camera::GetViewMatrix()
{
	glm::vec2 worldPos = owner->GetWorldPosition();
	glm::mat4 view = glm::ortho(0-frustum.x  / 2 , frustum.x / 2 , frustum.y / 2 , 0-frustum.y / 2 );
		
	return glm::translate(view,glm::vec3(worldPos.x,worldPos.y,0));
}
