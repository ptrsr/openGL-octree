#include "mge/materials/LitMaterial.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/config.hpp"

#include "mge/behaviours/DirectionalLight.hpp"
#include "mge/behaviours/PointLight.hpp"
#include "mge/behaviours/SpotLight.hpp"

#include <string>

//shader
ShaderProgram* LitMaterial::_shader = NULL;

//vertex uniforms
GLint LitMaterial::_uMVPMatrix = 0;
GLint LitMaterial::_uModelMatrix = 0;

//fragment uniforms
GLint LitMaterial::_uModelColor = 0;
GLint LitMaterial::_uShininess = 0;
GLint LitMaterial::_uCameraPos = 0;

//vertex attributes
GLint LitMaterial::_aVertex = 0;
GLint LitMaterial::_aNormal = 0;

LitMaterial::LitMaterial(glm::vec3 pModelColor, float pShininess, std::vector<AbstractLight*>* pLights)
	: _modelColor(pModelColor), _shininess(pShininess), _lights(pLights)
{
	_lazyInitializeShader();
}

void LitMaterial::_lazyInitializeShader() 
{
	if (!_shader)
	{
		_shader = new ShaderProgram();

		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "litFragment.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "litFragment.fs");
		_shader->finalize();

		//vertex uniforms
		_uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
		_uModelMatrix = _shader->getUniformLocation("modelMatrix");

		//fragment uniforms
		_uModelColor = _shader->getUniformLocation("modelColor");
		_uShininess = _shader->getUniformLocation("shininess");
		_uCameraPos = _shader->getUniformLocation("cameraPos");

		//vertex attributes
		_aVertex = _shader->getAttribLocation("vertex");
		_aNormal = _shader->getAttribLocation("normal");
	}
}

glm::vec3 LitMaterial::getColor() {
	return _modelColor;
}
void LitMaterial::setColor(glm::vec3 newColor) {
	_modelColor = newColor;
}
void LitMaterial::setLight(bool outside) {

}

void LitMaterial::render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) 
{
	_shader->use();

	//uniforms
	glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
	glUniformMatrix4fv(_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
	glUniformMatrix4fv(_uModelMatrix, 1, GL_FALSE, glm::value_ptr(pModelMatrix));

	glUniform3fv(_uCameraPos, 1, glm::value_ptr(((GameObject*)(World::get()->getMainCamera()))->getWorldPosition()));
	glUniform1f(_uShininess, _shininess);
	glUniform3fv(_uModelColor, 1, glm::value_ptr(_modelColor));

	renderLights();
	pMesh->streamToOpenGL(_aVertex, _aNormal, -1);
}

void LitMaterial::renderLights()
{
	int dLights = 0;
	int pLights = 0;
	int sLights = 0;

	for each (AbstractLight* abstractLight in *_lights)
	{
		std::string lType = "";
		std::string num   = "";

		if (typeid(*abstractLight) == typeid(DirectionalLight))
		{
			num = std::to_string(dLights);
			lType = "dirLight";

			glUniform3fv(_shader->getUniformLocation("dirLight[" + num + "].direction"), 1, glm::value_ptr(abstractLight->getDirection()));

			dLights++;
		}
		else if (typeid(*abstractLight) == typeid(PointLight))
		{
			num   = std::to_string(pLights);
			lType = "pointLight";

			PointLight* light = static_cast<PointLight*>(abstractLight);

			glUniform3fv(_shader->getUniformLocation("pointLight[" + num + "].position"), 1, glm::value_ptr(light->getWorldPosition()));

			glUniform1f(_shader->getUniformLocation("pointLight[" + num + "].constant"), light->_constant);
			glUniform1f(_shader->getUniformLocation("pointLight[" + num + "].linear"), light->_linear);
			glUniform1f(_shader->getUniformLocation("pointLight[" + num + "].quadratic"), light->_quadratic);
			pLights++;
		}
		else if (typeid(*abstractLight) == typeid(SpotLight))
		{
			num = std::to_string(sLights);
			lType = "spotLight";

			SpotLight* light = static_cast<SpotLight*>(abstractLight);

			glUniform3fv(_shader->getUniformLocation("spotLight[" + num + "].direction"), 1, glm::value_ptr(light->getDirection()));
			glUniform3fv(_shader->getUniformLocation("spotLight[" + num + "].position"), 1, glm::value_ptr(light->getWorldPosition()));

			glUniform1f(_shader->getUniformLocation("spotLight[" + num + "].constant"), light->_constant);
			glUniform1f(_shader->getUniformLocation("spotLight[" + num + "].linear"), light->_linear);
			glUniform1f(_shader->getUniformLocation("spotLight[" + num + "].quadratic"), light->_quadratic);

			glUniform1f(_shader->getUniformLocation("spotLight[" + num + "].cutOff"), 1 - glm::sin(light->_cutOff * (glm::pi<float>() / 180.0f)));
			glUniform1f(_shader->getUniformLocation("spotLight[" + num + "].outerCutOff"), glm::sin(light->_outerCutOff * (glm::pi<float>() / 180.0f)));

			sLights++;
		}

		//All lights have these values, so it's unnececary to cast
		glUniform3fv(_shader->getUniformLocation(lType + "[" + num + "].ambient"), 1, glm::value_ptr(abstractLight->_ambient));
		glUniform3fv(_shader->getUniformLocation(lType + "[" + num + "].diffuse"), 1, glm::value_ptr(abstractLight->_diffuse));
		glUniform3fv(_shader->getUniformLocation(lType + "[" + num + "].specular"), 1, glm::value_ptr(abstractLight->_specular));
	}
	glUniform3fv(_shader->getUniformLocation("lightCount"), 1, glm::value_ptr(glm::vec3(dLights, pLights, sLights)));
}

LitMaterial::~LitMaterial() { }