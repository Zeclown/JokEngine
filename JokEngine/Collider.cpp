#include "Collider.h"
#include "GameObject.h"
Collider::~Collider() {

	if(fixture && owner->GetComponent<PhysicBody>())
		fixture->GetBody()->DestroyFixture(fixture);
}
Collider::Collider(GameObject* gameObject)
	:Component(gameObject),offset(glm::vec2(0)),isSolid(true),physicLayer("default"),friction(0.1f)
{

}
GLfloat Collider::GetFriction()
{
	return friction;
}
void Collider::SetFriction(GLfloat f)
{
	friction = f;
	if (fixture)
	{
		fixture->SetFriction(f);
	}
}
	
