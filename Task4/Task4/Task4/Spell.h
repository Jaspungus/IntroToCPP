#pragma once
#include "String.h"
#include "HealthModule.h"
#include "Player.h"


class Spell
{
public:
	void Cast(HealthModule* a_caster, HealthModule* a_target);
	virtual void CombatCast(HealthModule* a_caster, HealthModule* a_target);
	virtual void PassiveCast(HealthModule* a_caster);
	String GetName();
	String GetDesc();
	size_t GetHealthDamage();
	size_t GetDignityDamage();

public:
	const static char* spellList[];
	

private:
	String m_name;
	String m_desc;
	size_t m_healthDamage;
	size_t m_dignityDamage;
	
};

class Scrunch : public Spell
{
public:
	void CombatCast(HealthModule* a_caster, HealthModule* a_target) override;
	void PassiveCast(HealthModule* a_caster) override;

private:
	//String m_name = "Power Word: Scrunch";
	//String m_desc = "Instantly scrunch whatever target this spell is directed at.\nOne of the most horrifying spells ever concieved.";
	size_t m_healthDamage = 9999;
	size_t m_dignityDamage = 10;
};

