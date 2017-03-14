#ifndef BREATHFIRST_H
#define BREATHFIRST_H

#include "../game/Tile.hpp"

class BreathFirst
{
public:
	BreathFirst();
	void connect(Tile* pTile, bool pConnect);
	glm::vec4 getBounds(Tile* pTile);

	void fill(Tile* pTile, Id pId, glm::vec4 pBounds);

private:
	vector<Tile*> _todoList;
	vector<Tile*> _doneList;

};





#endif // !BREATHFIRST_H
