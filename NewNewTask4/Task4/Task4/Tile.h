#pragma once
#include "Item.h"
class Tile
{
private:
	int m_state = 0; //0 is empty, 1 is not walkable (does not block vision, 2 is wall (blocks vision)
	bool m_isLit = false; //0 is bright //1 is shadow //2 is obstacles, 3 is shadow.
	Item* m_item = nullptr;

public:
	Tile();
	Tile(const int m_defaultLight);

public:
	bool GetIsLit();
	void SetIsLit(bool a_isLit);

	int GetState();
	void SetState(int a_state);

};

