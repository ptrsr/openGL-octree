#include "Skybox.hpp"

#include "mge/config.hpp"
#include "mge/core/Mesh.hpp"

#include "mge/materials/SkyMaterial.hpp"
#include "Camera.hpp"
#include "World.hpp"

Skybox* Skybox::_skybox = NULL;

Skybox::Skybox() : GameObject("skybox")
{
	setMesh(Mesh::load(config::MGE_MODEL_PATH + "skybox_cube.obj"));
	setMaterial(new SkyMaterial(Texture::load(config::MGE_TEXTURE_PATH + "skybox/skybox.png")));
}

void Skybox::render()
{
	Skybox* skybox = Skybox::get();
	Camera* camera = World::getMainCamera();

	skybox->getMaterial()->render(skybox->getMesh(), glm::mat4(), glm::inverse(camera->getWorldTransform()), camera->getProjection());
}

Skybox* Skybox::get()
{
	if (!_skybox)
		_skybox = new Skybox();

	return _skybox;
}
