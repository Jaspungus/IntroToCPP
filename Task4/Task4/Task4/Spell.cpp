#include "Spell.h"

//Delete later
#include <iostream>


void Spell::Cast(HealthModule* a_caster,  HealthModule* a_target) {
	a_target == nullptr ? PassiveCast(a_caster) : CombatCast(a_caster, a_target);
}

void Spell::CombatCast(HealthModule* a_caster, HealthModule* a_target)
{
}


void Spell::PassiveCast(HealthModule* a_caster)
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

void Scrunch::CombatCast(HealthModule* a_caster, HealthModule* a_target) {
	std::cout << "its actually combat casting" << std::endl;
	//a_target->TakeHealthDamage(m_healthDamage);
	a_caster->TakeDignityDamage(m_dignityDamage);
}

void Scrunch::PassiveCast(HealthModule* a_caster) {
	std::cout << "its actually passive casting" << std::endl;
	//a_target->TakeHealthDamage(m_healthDamage);
	a_caster->TakeDignityDamage(m_dignityDamage);
}
