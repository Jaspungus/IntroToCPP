#include "Spell.h"

void Spell::Cast() {

}

void Spell::CombatCast(HealthModule* a_target)
{
}

String Spell::GetName()
{
	return m_name;
}

String Spell::GetDesc()
{
	return m_desc;
}

size_t Spell::GetHealthDamage()
{
	return m_healthDamage;
}

size_t Spell::GetDignityDamage()
{
	return m_dignityDamage;
}




const char* Spell::spellList[2] = { "Power Word: Scrunch", "Lick" };

void Scrunch::Cast() {

}

