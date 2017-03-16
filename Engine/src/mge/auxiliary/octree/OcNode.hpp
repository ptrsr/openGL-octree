#ifndef OCNODE_H
#define OCNODE_H

#include "glm.hpp"
#include <GL\glew.h>

#include <vector>

#include "mge/core/ShaderProgram.hpp"

class Ball;

class OcNode
{

public:
	OcNode(OcNode* pParentNode, glm::vec3 offset = glm::vec3(0));
	~OcNode();

	void render();

	void updateObject(Ball* object);
	void resolveCollision(Ball* ball);


private:
	bool isInside(Ball* ball);

	OcNode* getParentNode(Ball* ball);
	OcNode* searchChildren(Ball* ball);
	OcNode* searchParent(Ball* ball, OcNode* currentNode);

	void addChild(Ball* ball);
	void removeChild(Ball* ball);

	void renderSelf(const glm::mat4& vpMatrix, glm::vec3 color);

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
	static std::vector<OcNode*> emptyNodes;
	static std::vector<OcNode*> inUseNodes;

	static int _maxLayers;
	int _layer = 0;

	glm::mat4 _matrix;
	glm::vec3 _position;
	float _size;
	
	OcNode* _parentNode;
	OcNode* _childNodes[8];

	vector<Ball*> _childObjects;
};

#endif // !OCNODE_H
