#include <glm.hpp>

#include "mge/materials/SkyMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"

#include "mge/core/World.hpp"
#include "mge/core/Camera.hpp"

SkyMaterial::SkyMaterial(Texture* pTexture) : _texture(pTexture)
{
	_shader = new ShaderProgram();
	_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "skybox.vs");
	_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "skybox.fs");
	_shader->finalize();

	//attributes
	_aVertex = _shader->getAttribLocation("vertex");
	//_aNormal = _shader->getAttribLocation("normal");
	_aUV = _shader->getAttribLocation("uv");

	//uniforms
	_uMVmatrix = _shader->getUniformLocation("MVmatrix");
	_uTexture   = _shader->getUniformLocation("skybox");

	std::cout << "CHECK THIS: " << _aUV << std::endl;
}

void SkyMaterial::setLight(bool outside){}


void SkyMaterial::render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) 
{
	glDepthMask(GL_FALSE);
	_shader->use();


	glm::mat4 mvMatrix = pProjectionMatrix * glm::mat4(glm::mat3(World::getMainCamera()->getWorldTransform()));
	glUniformMatrix4fv(_uMVmatrix, 1, GL_FALSE, glm::value_ptr(mvMatrix));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture->getId());
	glUniform1i(_uTexture, 0);

	pMesh->streamToOpenGL(_aVertex, -1, _aUV);

	glDepthMask(GL_TRUE);
}

SkyMaterial::~SkyMaterial()
{
	delete _texture;
}
