#pragma once
#include "String.h"
#include "HealthModule.h"
class SpellManager
{
private:
	static const String spellList[];
public:
	int CheckSpellList(String& a_spellName);
	void CastSpell(int index, HealthModule* a_caster, HealthModule* a_target);
};

