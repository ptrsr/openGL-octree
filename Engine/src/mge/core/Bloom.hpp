#ifndef BLOOM_H
#define BLOOM_H

#include "glm.hpp"
#include "GL/glew.h"
#include "ShaderProgram.hpp"

class Bloom
{
public:
	static void initialize(int screenWidth, int screenHeight);
	static void blur(int amount);
	static void renderToFBO();

private:
	static Bloom* _bloom;
	static Bloom* get();

	Bloom(unsigned int screenWidth, unsigned int screenHeight);

	void setupShaders();
	void setupQuad();
	void setupFBO(int screenWidth, int screenHeight);
	void setupPingPong(int screenWidth, int screenHeight);
	void renderQuad();

	ShaderProgram* _blurShader;
	ShaderProgram* _blendShader;

	//rendering
	GLuint _renderFBO;
	GLuint _colorBuffers[2];

	//blurring
	GLuint _pingpongFBO[2];
	GLuint _pingpongBuffers[2];

	GLuint _uHorizontal;
	GLuint _uBlur;
	GLuint _uMultiplier;

	GLuint _finalBlur;
	GLuint _scene;


	//quad
	GLuint _aQuad;

	GLuint _uQuad;

	//singleton
	Bloom(const Bloom&) = delete;
	Bloom& operator=(const Bloom&) = delete;
};

#endif