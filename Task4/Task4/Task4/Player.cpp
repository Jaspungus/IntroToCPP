#include "Player.h"
#include "Spell.h"

//extern const char* spellList[2];

Player::Player() {
	delete[] m_knownSpells;
	m_knownSpells = new Spell[1]{new Scrunch};
}

Player::~Player()
{
	delete[] m_knownSpells;
}

void Player::CastSpell(String& a_spellName) {
	for (int i = 0; i < m_knownCount; i++)
	{
		if (m_knownSpells[i].GetName() == a_spellName) {
			m_inCombat ? m_knownSpells[i].CombatCast(m_enemyP) : m_knownSpells[i].Cast();
		}
	}
	
}

bool Player::CheckSpell(String& a_spellName) {
	for (int i = 0; i < m_knownCount; i++)
	{
		if (m_knownSpells[i].GetName() == a_spellName) {
			return true;
		}
	}
	return false;

}
