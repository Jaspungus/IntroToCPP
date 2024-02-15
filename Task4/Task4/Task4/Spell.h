#pragma once
#include "String.h"
#include "HealthModule.h"
class Spell
{
public:
	virtual void Cast();
	virtual void CombatCast(HealthModule* a_target);
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
	void Cast() override;

private:
	String m_name = "Power Word: Scrunch";
	String m_desc = "Instantly scrunch whatever target this spell is directed at.\nOne of the most horrifying spells ever concieved.";
	size_t m_healthDamage = 9999;
	size_t m_dignityDamage = 0;
};

