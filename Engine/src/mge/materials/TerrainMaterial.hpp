#ifndef TERRAINMATERIAL_H
#define TERRAINMATERIAL_H

#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"
#include "mge/materials/LitMaterial.hpp"
#include <SFML\System.hpp>

class TerrainMaterial : public LitMaterial
{
    public:
        TerrainMaterial (std::string pHeight, std::string pDifR, std::string pDifG, std::string pDifB, std::string pDifA, std::string pSplat);
        virtual ~TerrainMaterial ();

        virtual void render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;
		virtual glm::vec3 getColor();

		void enableWater(bool enabled = true, int waterTexture = 4, glm::vec2 wavePoint = glm::vec2(0.5f), float shininess = 400.0f);

    private:

		static GLint _uClock;
		static GLint _uWaterTexture;
		static GLint _uWavePoint;

        Texture* _difR;
		Texture* _difG;
		Texture* _difB;
		Texture* _difA;

		Texture* _heightMap;
		Texture* _splatMap;

		//for water
		sf::Clock _clock;
		int _waterTexture;
		glm::vec2 _wavePoint;
};

#endif // TEXTUREMATERIAL_H
