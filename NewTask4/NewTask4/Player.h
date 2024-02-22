#pragma once
#include "String.h"
#include "Item.h"
#include <list>
using namespace std;

class Player
{
private:
	list<String> spells = {"Disintegrate", "Turn Pink", "Yellow"};
	list<Item> inventory;
public:
	Player();
	~Player();
	bool FindSpell(String spell);
	void ListSpells();
};

