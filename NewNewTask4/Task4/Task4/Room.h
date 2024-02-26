#pragma once
#include "Item.h"
#include "Guard.h"
#include "Tile.h"
#include "Vec2.h"
#include <list>
using namespace std;


class Room
{
private:
	String* m_description;

public:
	const int ROOMWIDTH = 16;
	const int ROOMHEIGHT = 16;

	//Stored as an array of pointers in order to check whether the object
	//Is initialised first when updating display and other things.
	size_t itemCount;
	list<Item*> m_items;
	//Item** m_items = nullptr;

	size_t guardCount = 2;
	Guard** m_guards = new Guard * [guardCount] {nullptr};

	//
	int* m_tiles = nullptr;
	bool m_litStates[16][16] = { false };

public:
	Room();
	Room(const char* a_description);
	//Room(const char* a_description, Item** a_item);
	~Room();
	void Description() const;

	int GetTileIsLit(Vec2I a_position);
	int GetTileState(Vec2I a_position);

	Item* GetItem(Vec2I a_position);
	Item* GetItem(size_t index);
	Guard* GetGuard(Vec2I a_position);
};

