#ifndef SKYMATERIAL_H
#define SKYMATERIAL_H

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/ShaderProgram.hpp"

#include "mge/core/Texture.hpp"


class SkyMaterial : public AbstractMaterial
{
public:
	SkyMaterial(Texture* pRexture);
	virtual ~SkyMaterial();

	virtual void render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	virtual inline glm::vec3 getColor() { return glm::vec3(0); }
	virtual inline void setColor(glm::vec3 newColor) { };
	virtual void setLight(bool outside);

private:
	ShaderProgram* _shader;

	//attributes
	GLint _aVertex;
	GLint _aNormal;
	GLint _aUV;

	//uniforms
	GLint _uMVmatrix;
	GLint _uTexture;

	Texture* _texture;
};

#endif // COLORMATERIAL_H
