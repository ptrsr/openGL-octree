#ifndef SKYBOX_H
#define SKYBOX_H

#include "mge/core/GameObject.hpp"

#include "GL/glew.h"
#include <string>
#include <vector>

class Skybox : GameObject
{
public:
	static void render();

private:
	static Skybox* get();
	static Skybox* _skybox;

	//singleton
	Skybox();

	Skybox(const Skybox&) = delete;
	Skybox& operator=(const Skybox&) = delete;
};

#endif // !SKYBOX_H
