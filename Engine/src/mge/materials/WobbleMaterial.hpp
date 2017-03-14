#ifndef WOBBLEMATERIAL_H
#define WOBBLEMATERIAL_H

#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include <SFML\System.hpp>

class WobbleMaterial : public AbstractMaterial
{
public:
	WobbleMaterial(Texture* pDiffuseTexture);
	virtual ~WobbleMaterial();

	virtual void render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	void setDiffuseTexture(Texture* pDiffuseTexture);

protected:
private:
	sf::Clock * timer;

	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	Texture* _diffuseTexture;

	WobbleMaterial(const WobbleMaterial&);
	WobbleMaterial& operator=(const WobbleMaterial&);

};

#endif // WOBBLEMATERIAL_H
