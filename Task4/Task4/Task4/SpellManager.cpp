#include "SpellManager.h"
#include "Spell.h"

const String SpellManager::spellList[] = { "Power Word: Scrunch", "Squelch", "Lick" };


int SpellManager::CheckSpellList(String& a_spellName)
{
	std::cout << "It went through checklist!" << std::endl;
	int i = 0;
	for (const String& spellName : spellList) 
	{
		if (a_spellName == spellName) {
			return i;
		}
		i++;
	}
	return -1;
}

void SpellManager::CastSpell(int index, HealthModule* a_caster, HealthModule* a_target) {
	
	std::cout << "It went through castspell!" << std::endl;
	
	switch (index) {
	case 0:
		{
		std::cout << "it got 0" << std::endl;
			Scrunch scrunch;
			scrunch.Cast(a_caster, a_target);
			break;
		}
		case 1:
			break;
		default:
			return;
	}
}
