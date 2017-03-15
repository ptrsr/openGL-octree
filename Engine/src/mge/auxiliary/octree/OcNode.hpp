#ifndef OCNODE_H
#define OCNODE_H

#include "glm.hpp"
#include <GL\glew.h>

#include <vector>

#include "mge/core/ShaderProgram.hpp"

class OcNode
{
public:
	OcNode(OcNode* pParentNode, glm::vec3 offset = glm::vec3(0));
	~OcNode();

	void render();

	//calculations
	bool isInside(glm::vec3 pPosition, float pRadius);

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
	int _maxLayers = 2;

	glm::mat4 _matrix;
	glm::vec3 _positon;
	float _size;
	
	OcNode* _parent;
	OcNode* _children[8];
};

#endif // !OCNODE_H
