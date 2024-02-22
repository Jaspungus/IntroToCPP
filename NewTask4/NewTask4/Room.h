#pragma once
#include "Item.h"

class Room
{
private:
	String description;
public:
	Item* item;
public:
	Room(String description, Item* item);
	~Room();
	void Description() const;
};

