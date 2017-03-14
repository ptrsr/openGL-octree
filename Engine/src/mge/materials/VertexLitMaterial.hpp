#ifndef VERTEXLITMATERIAL_H
#define VERTEXLITMATERIAL_H

#include <vector>
#include <glm.hpp>

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/behaviours/AbstractLight.hpp"
#include "mge/core/World.hpp"

class VertexLitMaterial : public AbstractMaterial
{
public:
	VertexLitMaterial(glm::vec3 pModelColor = glm::vec3(1), float pShininess = 10.0f, std::vector<AbstractLight*>* pLights = World::get()->GetLights());
	virtual ~VertexLitMaterial();

	virtual void render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

private:
	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	//vertex uniforms
	static GLint _uMVPMatrix;
	static GLint _uModelMatrix;

	//vertex attributes
	static GLint _aVertex;
	static GLint _aNormal;

	//fragment uniforms
	static GLint _uModelColor;
	static GLint _uShininess;
	static GLint _uCameraPos;

	std::vector<AbstractLight*>* _lights;
	glm::vec3 _modelColor;
	float _shininess;

	VertexLitMaterial(const VertexLitMaterial&);

	void addLights();
};

#endif // VERTEXLITMATERIAL_H
