#ifndef PHYSICS_SERVICE_H
#define PHYSICS_SERVICE_H
#include <gl\glew.h>
#include <glm\glm.hpp>
#include "Box2D\Dynamics\b2Body.h"
#include <vector>
#include <string>
#include "Collider.h"
#include "PhysicBody.h"
#include "RaycastHit.h"
namespace Jokengine
{
	//Physic Service working as a wrapper to Box2D. It also handles physic layer management
	// Example:
	//
	//  if(game.GetPhysicsService().Raycast(glm::vec2(0,0),glm::vec2(1,1),300f)) //
	//		DoSomethingRad();

	class PhysicsService
	{	
		public:
			//Get the gravity currently used by the physic engine
			virtual glm::vec2 GetGravity() = 0;
			//Set the gravity used by the physic engine
			virtual void SetGravity(glm::vec2 gravity) = 0;
			//Registers a new body in the physic engine (Used internally by Physicbody)
			virtual b2Body* RegisterBody(PhysicBody *pb, glm::vec2 position, GLboolean isKinematic, GLboolean isGravity, GLfloat rotation, GLfloat angularDrag, GLfloat drag, GLint mass)=0;
			//Registers a new Box Collider
			virtual b2Fixture* RegisterFixtureBox(b2Body *body, Collider* col, glm::vec2 size = glm::vec2(1, 1),GLboolean sensor=false, glm::vec2 offset = glm::vec2(0, 0), std::string layerName = "default")=0;
			//Registers a new Circle Collider
			virtual b2Fixture* RegisterFixtureCircle(b2Body *body, Collider* col, GLfloat radius = 1,GLboolean sensor=false, glm::vec2 offset = glm::vec2(0, 0), std::string layerName = "default")=0;
			//Registers a new Edge Collider
			virtual b2Fixture* RegisterFixtureEdge(b2Body *body, Collider* col, glm::vec2 pointA, glm::vec2 pointB, std::string layerName = "default")=0;
			//Change a layer mask so it collides/ignores a set of other layer
			virtual void SetMaskBits(std::string layerName, std::vector<std::string> otherLayers, GLboolean isColliding = true)=0;
			//Change a layer mask so it collides/ignores another layer
			virtual void SetMaskBits(std::string layerName, std::string otherLayer, GLboolean isColliding = true) = 0;
			//Register a new layer
			virtual void RegisterPhysicLayer(std::string layerName, uint16 maskBits = -1)=0;
			//Get the category bits of a registered layer
			virtual uint16 GetCategoryBits(std::string layerName)=0;
			//Get the cummulative layer mask of a set of registered layers, isColliding to false will invert the mask
			virtual uint16 GetMaskBits(std::vector<std::string> layerNames, GLboolean isColliding = true)=0;
			//Get the layer mask of a registered layer, isColliding to false will invert the mask
			virtual uint16 GetMaskBits(std::string layerName, GLboolean isColliding=true)=0;
			//Raycast from an origin to a direction that will return if something is hit or not
			virtual GLboolean Raycast(glm::vec2 origin, glm::vec2 direction, GLfloat maxDistance=1000, uint16 physicMask=-1)=0;
			//Raycast from an origin to a direction that will return if something is hit or not and will populate the output with the collision data
			virtual GLboolean Raycast(glm::vec2 origin, glm::vec2 direction, RaycastHit &output, GLfloat maxDistance=1000, uint16 physicMask=-1)=0;
			//Raycast from an origin to a direction that will not stop at the first object and will return a vector of collision data
			virtual std::vector<RaycastHit> RaycastAll(glm::vec2 origin, glm::vec2 direction, GLfloat maxDistance=1000, uint16 physicMask=-1)=0;
			virtual void FixedUpdate() = 0;


	};
}
#endif // !PHYSICS_SERVICE_H

