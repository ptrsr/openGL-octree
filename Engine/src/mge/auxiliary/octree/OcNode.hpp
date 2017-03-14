#ifndef OCNODE_H
#define OCNODE_H

#include "glm.hpp"
#include <GL\glew.h>

#include <vector>

#include "mge/core/ShaderProgram.hpp"

class OcNode
{
public:
	OcNode(glm::mat4 pMatrix = glm::mat4(), glm::vec3 pPosition = glm::vec3(0), int pLayer = 0);
	~OcNode();

	void render();

private:
	void renderSelf(glm::mat4 vpMatrix);
	void renderChildren(glm::mat4 vpMatrix);

	void spawnChildren();

	//cube
	void initCube();
	static GLuint _bufferId;
	static GLuint _bufferSize;

	//shader
	void initShader();
	static ShaderProgram* _shader;

	static GLuint _aVertex;
	static GLuint _uMVP;
	static GLuint _uColor;

	//variables
	int _layer = 0;
	
	glm::mat4 _matrix;

	glm::vec3 _position;
	float _size;
	OcNode* _children[8];
};

#endif // !OCNODE_H
