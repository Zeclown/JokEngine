#include "Collision.h"

Collision::Collision(Collider *colliderSelf, Collider *colliderOther, PhysicBody *physicBody, GameObject *gameObject, std::vector<glm::vec2> contacts,GLboolean sensor)
: colliderSelf(colliderSelf),colliderOther(colliderOther),physicBody(physicBody),gameObject(gameObject),contacts(contacts),sensor(sensor)
{

}
