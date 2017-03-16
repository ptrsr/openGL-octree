#include <glm.hpp>
#include <iostream>
#include <string>
using namespace std;

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"

#include "mge/core/Camera.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/LitMaterial.hpp"

#include "mge/behaviours/OrbitBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "OctreeScene.hpp"

#include "mge/auxiliary/octree/Ball.hpp"

OctreeScene::OctreeScene():AbstractGame (),_hud(0)
{
}

void OctreeScene::initialize() {
    AbstractGame::initialize(1280, 720);

	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;
}

void OctreeScene::_initializeScene()
{
    _renderer->setClearColor(0,0,0);

    Camera* camera = new Camera ();
    _world->add(camera);
    _world->setMainCamera(camera);

	_ocNode = new OcNode(NULL, glm::vec3(0));

	GameObject* empty = new GameObject("empty");
	camera->setBehaviour(new OrbitBehaviour(empty, 2));
	_world->add(empty);


	GameObject* light = new GameObject("light");
	light->setBehaviour(new DirectionalLight());
	light->rotate(1, glm::vec3(1, 1, 0));
	_world->add(light);

	spawnBalls(1, 3);
}

void OctreeScene::spawnBalls(int count, float speed, int seed)
{
	std::srand(seed);

	Mesh* mesh = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");

	for (int i = 0; i < count; i++)
	{
		Ball* ball = new Ball(_ocNode, glm::vec3(0), glm::ballRand(speed));

		ball->setMesh(mesh);
		ball->setMaterial(new LitMaterial());

		_world->add(ball);
		balls.push_back(ball);
	}
}


void OctreeScene::_render() {
    AbstractGame::_render();
	if (_ocNode)
		_ocNode->render();
}

void OctreeScene::_updateHud() {
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string((int)_fps)+"\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

OctreeScene::~OctreeScene()
{
	delete _ocNode;

	for each (GameObject* object in balls)
		delete object;
}
