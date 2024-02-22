#pragma once
#include "String.h"
#include <list>
using namespace std;

class Player
{
private:
	list<String> spells;
public:
	Player();
	~Player();
	bool FindSpell(String spell);
};

