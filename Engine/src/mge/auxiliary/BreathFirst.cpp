#include "BreathFirst.hpp"

#include <algorithm>

BreathFirst::BreathFirst()
{

}

void BreathFirst::connect(Tile* pTile, bool pConnect)
{
	if (pTile->_connected == pConnect)
		return;

	_todoList.push_back(pTile);

	while (_todoList.size() != 0)
	{
		Tile* tile = _todoList[0];

		_todoList.erase(_todoList.begin());
		_doneList.push_back(tile);

		tile->_connected = pConnect;

		for each (Tile* connectedTile in tile->getConnections())
			if (connectedTile->getOwner() == pTile->getOwner() && std::find(_doneList.begin(), _doneList.end(), connectedTile) == _doneList.end())
				_todoList.push_back(connectedTile);
	}

	_todoList.clear();
	_doneList.clear();
}

glm::vec4 BreathFirst::getBounds(Tile* pTile)
{
	glm::vec4 bounds = glm::vec4(-1);

	if (pTile->_connected == false)
		return bounds;

	_todoList.push_back(pTile);

	while (_todoList.size() != 0)
	{
		Tile* tile = _todoList[0];

		_todoList.erase(_todoList.begin());
		_doneList.push_back(tile);

		for each (Tile* connectedTile in tile->getConnections())
		{
			if (connectedTile == NULL)
				continue;

			if (connectedTile->getOwner() == tile->getOwner() && std::find(_doneList.begin(), _doneList.end(), connectedTile) == _doneList.end())
				_todoList.push_back(connectedTile);
		}

		//calculate bounds
		glm::vec2 boardPos = tile->getBoardPos();

		if (bounds == glm::vec4(-1))
			bounds = glm::vec4(boardPos, boardPos);

		if (boardPos.x < bounds.x)
			bounds.x = boardPos.x;

		if (boardPos.x > bounds.z)
			bounds.z = boardPos.x;

		if (boardPos.y < bounds.y)
			bounds.y = boardPos.y;

		if (boardPos.y > bounds.w)
			bounds.w = boardPos.y;
	}
	bool minimumReached = false;

	if (_doneList.size() >= 8)
		minimumReached = true;

	_todoList.clear();
	_doneList.clear();

	if (minimumReached)
		return bounds;
	
	return glm::vec4(0);
}

void BreathFirst::fill(Tile* pTile, Id pId, glm::vec4 pBounds)
{

	_todoList.push_back(pTile);

	while (_todoList.size() != 0)
	{
		Tile* tile = _todoList[0];

		_todoList.erase(_todoList.begin());
		_doneList.push_back(tile);

		glm::vec2 boardPos = tile->getBoardPos();

		if (boardPos.x <= pBounds.x || boardPos.x >= pBounds.z || boardPos.y <= pBounds.y || boardPos.y >= pBounds.w)
		{
			_todoList.clear();
			_doneList.clear();
			return;
		}

		for each (Tile* connectedTile in tile->getConnections())
			if (connectedTile->getOwner() != pId && std::find(_doneList.begin(), _doneList.end(), connectedTile) == _doneList.end())
				_todoList.push_back(connectedTile);
	}

	for each (Tile* tile in _doneList)
		tile->setOwner(pId);

	_todoList.clear();
	_doneList.clear();
}