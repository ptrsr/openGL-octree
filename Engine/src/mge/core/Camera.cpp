#include <iostream>
using namespace std;

#include <glm.hpp>
#include "mge/core/Camera.hpp"

Camera::Camera(glm::vec2 windowSize, std::string pName, glm::vec3 pPosition )
:	GameObject(pName, pPosition)
{
	_projection = glm::perspective(glm::radians(60.0f), windowSize.x / windowSize.y, 0.1f, 1000.0f);
}

Camera::~Camera()
{
	//dtor
}

glm::mat4& Camera::getProjection() {
    return _projection;
}
