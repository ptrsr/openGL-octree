#include <glm.hpp>

#include "mge/materials/WobbleMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/config.hpp"


ShaderProgram* WobbleMaterial::_shader = NULL;

WobbleMaterial::WobbleMaterial(Texture * pDiffuseTexture) :_diffuseTexture(pDiffuseTexture) 
{
	timer = new sf::Clock();
	_lazyInitializeShader();
}

WobbleMaterial::~WobbleMaterial() {}

void WobbleMaterial::_lazyInitializeShader() {
	if (!_shader) {
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "wobble.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "texture.fs");
		_shader->finalize();
	}
}

void WobbleMaterial::setDiffuseTexture(Texture* pDiffuseTexture) {
	_diffuseTexture = pDiffuseTexture;
}

void WobbleMaterial::render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
	if (!_diffuseTexture) return;

	_shader->use();

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
	glUniform1i(_shader->getUniformLocation("textureDiffuse"), 0);

	glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
	glUniformMatrix4fv(_shader->getUniformLocation("mvpMatrix"), 1, GL_FALSE, glm::value_ptr(mvpMatrix));
	glUniform1f(_shader->getUniformLocation("clock"), timer->getElapsedTime().asSeconds());
	
	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(
		_shader->getAttribLocation("vertex"),
		-1,
		_shader->getAttribLocation("uv")
	);
}
