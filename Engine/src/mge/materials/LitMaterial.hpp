#ifndef LITMATERIAL_H
#define LITMATERIAL_H

#include <vector>
#include <glm.hpp>

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/behaviours/AbstractLight.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"

class LitMaterial : public AbstractMaterial
{
public:
	LitMaterial(glm::vec3 pModelColor = glm::vec3(1), float pShininess = 10.0f, std::vector<AbstractLight*>* pLights = World::get()->GetLights());
	
	virtual ~LitMaterial();

	virtual void render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;
	
	glm::vec3 getColor();
	virtual void setColor(glm::vec3 pColor);
	virtual void setLight(bool outside);

private:
	static void _lazyInitializeShader();
	void renderLights();

	static ShaderProgram* _shader;

	//vertex uniforms
	static GLint _uMVPMatrix;
	static GLint _uModelMatrix;

	//fragment uniforms
	static GLint _uModelColor;
	static GLint _uShininess;
	static GLint _uCameraPos;

	//vertex attributes
	static GLint _aVertex;
	static GLint _aNormal;
	static GLint _aU;

	//lights
	std::vector<AbstractLight*>* _lights;
	
	//settings
	glm::vec3 _modelColor;
	float _shininess;
};

#endif // LITMATERIAL_H
