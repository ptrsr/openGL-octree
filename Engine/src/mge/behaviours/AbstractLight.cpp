#include "AbstractLight.hpp"
#include "mge/core/World.hpp"


AbstractLight::AbstractLight() 
{ 
	World::get()->addLight(this);
}

AbstractLight::~AbstractLight()
{
	World::get()->removeLight(this);
}

glm::vec3 AbstractLight::getWorldPosition()
{
	return _owner->getWorldPosition();
}

glm::vec3 AbstractLight::getDirection()
{
	return glm::normalize(_owner->getWorldTransform()[2]);
}

//void AbstractLight::message(send::Message message)
//{
//	std::cout << "received message" << std::endl;
//	switch (message)
//	{
//	case send::addedToScene:
//		World::get()->addLight(this);
//		std::cout << "light added to scene!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
//		break;
//
//	case send::removedFromScene:
//		World::get()->removeLight(this);
//		break;
//	}
//}