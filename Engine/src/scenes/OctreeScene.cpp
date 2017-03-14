#include <glm.hpp>
#include <iostream>
#include <string>
using namespace std;


#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"

#include "mge/core/Camera.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/LitMaterial.hpp"

#include "mge/behaviours/OrbitBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "OctreeScene.hpp"

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

	_ocNode = new OcNode();

	GameObject* empty = new GameObject("empty");
	//empty->setBehaviour(new DirectionalLight());
	//empty->setMesh(Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj"));
	//empty->setMaterial(new LitMaterial());
	_world->add(empty);

	camera->setBehaviour(new OrbitBehaviour(empty, 2));
}

void OctreeScene::_render() {
    AbstractGame::_render();
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
	//dtor
}
