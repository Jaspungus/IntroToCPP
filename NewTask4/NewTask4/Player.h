#pragma once
#include "String.h"
#include "Item.h"
#include <list>
#include <vector>
using namespace std;

class Player
{
private:
	list<String> spells = {"Disintegrate", "Turn Pink", "Yellow"};
	list<Item> inventory;
	String m_name;
public:
	Player();
	Player(String a_name);
	~Player();
	bool FindSpell(String spell);
	void ListSpells();
	
	void UseItem(String a_item);
	void ListItems();

	void SetName(String a_name);
	String GetName();
};

