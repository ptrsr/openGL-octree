#include "OcNode.hpp"
#include "mge/config.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Camera.hpp"

#include <vector>

//shader
ShaderProgram* OcNode::_shader = NULL;

GLuint OcNode::_aVertex = -1;
GLuint OcNode::_uMVP	= -1;
GLuint OcNode::_uColor	= -1;

//cube
GLuint OcNode::_bufferId   = -1;
GLuint OcNode::_bufferSize = 0;


OcNode::OcNode(glm::mat4 pMatrix, glm::vec3 pPosition, int pLayer)
	: _matrix(pMatrix), _position(pPosition), _layer(pLayer)
{
	if (_layer != 0)
	{
		_matrix *= glm::scale(glm::vec3(0.5f));
		_matrix *= glm::translate(pPosition);
	}

	if (!_shader)
		initShader();

	if (_bufferId == -1)
		initCube();

	if (_layer < 4)
		spawnChildren();
}

void OcNode::spawnChildren()
{
	int count = 0;

	for (int x = 0; x < 2; x++)
		for (int y = 0; y < 2; y++)
			for (int z = 0; z < 2; z++)
			{
				glm::vec3 position = glm::vec3(x, y, z) - glm::vec3(0.5f);
				_children[count] = new OcNode(_matrix, position, _layer + 1);
				count++;
			}
}

void OcNode::render()
{
	_shader->use();

	glEnableVertexAttribArray(_aVertex);
	glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
	glVertexAttribPointer(_aVertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	Camera* camera = World::getMainCamera();
	glm::mat4 vpMatrix = camera->getProjection() *glm::inverse(camera->getWorldTransform());

	renderSelf(vpMatrix);

	glDisableVertexAttribArray(_aVertex);
}

void OcNode::renderSelf(glm::mat4 vpMatrix)
{
	glm::mat4 mvpMatrix = vpMatrix * _matrix;

	glUniformMatrix4fv(_uMVP, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
	glUniform3fv(_uColor, 1, glm::value_ptr(glm::vec3(0, 1, 0)));

	glDrawArrays(GL_LINES, 0, _bufferSize);

	renderChildren(vpMatrix);
}

void OcNode::renderChildren(glm::mat4 vpMatrix)
{
	if (_layer < 4)
		for (int i = 0; i < 8; i++)
			_children[i]->renderSelf(vpMatrix);
}

void OcNode::initShader()
{
	std::cout << "initializing octree shader" << std::endl;

	_shader = new ShaderProgram();

	_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "color.vs");
	_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "color.fs");
	_shader->finalize();

	_aVertex = _shader->getAttribLocation("vertex");
	_uMVP	 = _shader->getUniformLocation("mvpMatrix");
	_uColor  = _shader->getUniformLocation("color");
}

void OcNode::initCube()
{
	std::cout << "initializing octree cube" << std::endl;

	glm::vec3 ind[] = {
		glm::vec3(-0.5f, -0.5f, -0.5f),	// 0
		glm::vec3(0.5f, -0.5f, -0.5f),	// 1
		glm::vec3(0.5f, 0.5f, -0.5f),	// 2
		glm::vec3(-0.5f, 0.5f, -0.5f),	// 3

		glm::vec3(-0.5f, -0.5f, 0.5f),	// 4
		glm::vec3(0.5f, -0.5f, 0.5f),	// 5
		glm::vec3(0.5f, 0.5f, 0.5f),	// 6
		glm::vec3(-0.5f, 0.5f, 0.5f)	// 7
	};

	std::vector<glm::vec3> lines; // contains the lines for the cube

	// front quad
	lines.push_back(ind[0]); lines.push_back(ind[1]);
	lines.push_back(ind[1]); lines.push_back(ind[2]);
	lines.push_back(ind[2]); lines.push_back(ind[3]);
	lines.push_back(ind[3]); lines.push_back(ind[0]);

	// rear quad
	lines.push_back(ind[4]); lines.push_back(ind[5]);
	lines.push_back(ind[5]); lines.push_back(ind[6]);
	lines.push_back(ind[6]); lines.push_back(ind[7]);
	lines.push_back(ind[7]); lines.push_back(ind[4]);

	// lines inbetween
	lines.push_back(ind[0]); lines.push_back(ind[4]);
	lines.push_back(ind[1]); lines.push_back(ind[5]);
	lines.push_back(ind[2]); lines.push_back(ind[6]);
	lines.push_back(ind[3]); lines.push_back(ind[7]);

	_bufferSize = lines.size();

	// put the lines into a buffer
	glGenBuffers(1, &_bufferId);
	glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
	glBufferData(GL_ARRAY_BUFFER, lines.size() * sizeof(lines), &lines[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

OcNode::~OcNode()
{
	delete[] _children;
}