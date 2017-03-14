#ifndef TEXTUREMATERIAL_H
#define TEXTUREMATERIAL_H

#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "SFML/Graphics.hpp"

class TextureMaterial : public AbstractMaterial
{
 public:
        TextureMaterial (Texture* pTexture, glm::vec3 pModelColor = glm::vec3(1), float pShininess = 10.0f, std::vector<AbstractLight*>* pLights = World::get()->GetLights());
		virtual void render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

        void setTexture (Texture* pDiffuseTexture);
		void setSpecular(Texture* pSpecularTexture);

		glm::vec3 getColor();
		virtual void setColor(glm::vec3 pColor);
		virtual void setLight(bool outside);

private:
	static void _lazyInitializeShader();
	void renderLights();
	void renderTexture();

	static ShaderProgram* _shader;

	//vertex uniforms
	static GLint _uMVPMatrix;
	static GLint _uModelMatrix;

	//fragment uniforms
	static GLint _uModelColor;
	static GLint _uTexture;
	static GLint _uShininess;
	static GLint _uCameraPos;

	//vertex attributes
	static GLint _aVertex;
	static GLint _aNormal;
	static GLint _aUV;

	//lights
	std::vector<AbstractLight*>* _lights;

	//settings
	glm::vec3 _modelColor;
	Texture* _texture;
	Texture* _specular;
	float _shininess;
};

#endif // TEXTUREMATERIAL_H
