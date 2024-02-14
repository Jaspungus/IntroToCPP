#pragma once
#include "HealthModule.h"
#include "String.h"


class Player : public HealthModule
{
private:
	//Figure out whether it should take a direction or nah
	void Move();

	//These Spells can misfire, causing horrible damage to player & surroundings.
	void CastSpell(String& a_spellName);
	void CheckSpell(String& a_spellName);
	void CombatCast(String& a_spellName, HealthModule& a_target);

private:
	String name;
	//Could make my own custom struct. Or could simply not.
	size_t posX;
	size_t posY;


};

