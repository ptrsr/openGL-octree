#include "Bloom.hpp"
#include "../config.hpp"

Bloom* Bloom::_bloom;

Bloom::Bloom(unsigned int screenWidth, unsigned int screenHeight)
{
	setupShaders();
	setupQuad();

	setupFBO(screenWidth, screenHeight);
	setupPingPong(screenWidth, screenHeight);

	glBindBuffer(GL_FRAMEBUFFER, 0);
}

void Bloom::setupFBO(int screenWidth, int screenHeight)
{
	// set up framebuffer to render scene to
	glGenFramebuffers(1, &_renderFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, _renderFBO);

	// gen texturebuffers to attach to the framebuffer
	glGenTextures(2, _colorBuffers);
	for (GLuint i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, _colorBuffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, screenWidth, screenHeight, 0, GL_RGB, GL_FLOAT, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// attach texture to framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, _colorBuffers[i], 0);
	}

	// gen depthbuffer
	GLuint depthBuffer;
	glGenTextures(1, &depthBuffer);
	glBindTexture(GL_TEXTURE_2D, depthBuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, screenWidth, screenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthBuffer, 0);

	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	// tell opengl to render to 2 texturebuffers instead of 1
	GLuint attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, attachments);
}

void Bloom::setupPingPong(int screenWidth, int screenHeight)
{
	glGenFramebuffers(2, _pingpongFBO);
	glGenTextures(2, _pingpongBuffers);

	for (GLuint i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _pingpongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, _pingpongBuffers[i]);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, screenWidth, screenHeight, 0, GL_RGB, GL_FLOAT, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _pingpongBuffers[i], 0);
	}
}

void Bloom::setupShaders()
{
	//blur
	_blurShader = new ShaderProgram();

	_blurShader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "bloom/quad.vs");
	_blurShader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "bloom/blur.fs");
	_blurShader->finalize();

	_uHorizontal = _blurShader->getUniformLocation("horizontal");
	_uBlur		 = _blurShader->getUniformLocation("image");
	_uMultiplier = _blurShader->getUniformLocation("multiplier");

	//blend
	_blendShader = new ShaderProgram();

	_blendShader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "bloom/quad.vs");
	_blendShader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "bloom/blend.fs");
	_blendShader->finalize();

	_scene = _blendShader->getUniformLocation("scene");
	_finalBlur = _blendShader->getUniformLocation("blur");

	//quad
	_aQuad = _blendShader->getAttribLocation("vertex");
}

void Bloom::setupQuad()
{
	const GLfloat vertices[] = 
	{
		 1, -1,
		 1,  1,
		-1, -1,
		-1,  1,
		-1, -1,
		 1 , 1
	};

	glGenBuffers(1, &_uQuad);
	glBindBuffer(GL_ARRAY_BUFFER, _uQuad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Bloom::blur(int amount)
{
	Bloom* bloom = Bloom::get();

	if (!bloom)
		return;

	bloom->_blurShader->use();

	GLboolean horizontal = true, first_iteration = true;
	for (GLuint i = 0; i < amount; i++)
	{
		glUniform1i(bloom->_uHorizontal, horizontal);
		glUniform1f(bloom->_uMultiplier, 1.f);

		glBindFramebuffer(GL_FRAMEBUFFER, bloom->_pingpongFBO[horizontal]);
		glBindTexture(GL_TEXTURE_2D, first_iteration ? bloom->_colorBuffers[1] : bloom->_pingpongBuffers[!horizontal]);
		
		bloom->renderQuad();
		
		horizontal = !horizontal;
		if (first_iteration)
			first_iteration = false;
	}

	bloom->_blendShader->use();

	glUniform1i(bloom->_scene, 0);
	glUniform1i(bloom->_finalBlur, 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, bloom->_colorBuffers[0]);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, bloom->_pingpongBuffers[!horizontal]);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	bloom->renderQuad();
}

void Bloom::renderQuad()
{
	//vertex data
	glEnableVertexAttribArray(_aQuad);
	glBindBuffer(GL_ARRAY_BUFFER, _uQuad);
	glVertexAttribPointer(_aQuad, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(_aQuad);

}

void Bloom::renderToFBO()
{
	glBindFramebuffer(GL_FRAMEBUFFER, Bloom::get()->_renderFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//singleton functions
Bloom* Bloom::get()
{
	return _bloom;
}

void Bloom::initialize(int screenWidth, int screenHeight)
{
	if (!_bloom)
		_bloom = new Bloom(screenWidth, screenHeight);
}

