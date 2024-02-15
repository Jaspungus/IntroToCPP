#pragma once
#include "HealthModule.h"
#include "String.h"
#include "Spell.h"


class Player : public HealthModule
{
public:
	Player();
	~Player();

public:
	//Figure out whether it should take a direction or nah
	void Move();

	//These Spells can misfire, causing horrible damage to player & surroundings.
	void CastSpell(String& a_spellName);
	bool CheckSpell(String& a_spellName);


private:

	String m_name = "Player";
	//Could make my own custom struct. Or could simply not.
	size_t m_posX = 0;
	size_t m_posY = 0;

	bool m_inCombat = false;
	HealthModule* m_enemyP = nullptr;

	//Just make an array class dawg. Won't work with strings, as they will need to become string literals. Which cannot be edited. Otherwise it would work fine.
	//Then a list of all spells and their class locations maybe. Known spells can be added, because the string won't be changed. 
	Spell* m_knownSpells;
	size_t m_knownCount;
	
};

