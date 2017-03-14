#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "mge/core/GameObject.hpp"
#include "mge/behaviours/DirectionalLight.hpp"

class Camera;

class World : public GameObject
{
	public:
		void setMainCamera (Camera* pCamera);

		static World* get();

		static Camera* getMainCamera();

		std::vector<AbstractLight*>* GetLights();

		void addLight(AbstractLight*);
		void removeLight(AbstractLight*);

		static void add(GameObject* pChild);
		static void remove(GameObject* pChild);

protected:
	virtual void _innerAdd(GameObject* pChild) override;
	virtual void _innerRemove(GameObject* pChild) override;

	private:
		World();

		static World * world;

	    Camera* _mainCamera;
		std::vector<AbstractLight*>* _lights;

        World(const World&) = delete;
        World& operator=(const World&) = delete;
};


#endif // WORLD_H
