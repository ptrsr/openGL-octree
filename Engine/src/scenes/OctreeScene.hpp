#ifndef MGEDEMO_H
#define MGEDEMO_H

#include <mge/core/AbstractGame.hpp>
#include "mge/auxiliary/octree/OcNode.hpp"

#include "mge/core/GameObject.hpp"

class DebugHud;

class OctreeScene: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		OctreeScene();
		virtual ~OctreeScene();

        virtual void initialize();

	protected:
        virtual void _initializeScene();

	    //override render to render the hud as well.
	    virtual void _render();

	private:
		DebugHud* _hud;                   //hud display
		OcNode* _ocNode = NULL;

		vector<GameObject*> balls;

        void _updateHud();
		void spawnBalls(int count, float speed, int seed = 0);

        OctreeScene(const OctreeScene&);
        OctreeScene& operator=(const OctreeScene&);
};

#endif // MGEDEMO_H
