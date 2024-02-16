#include "Player.h"
#include "Spell.h"
#include "SpellManager.h"

extern SpellManager* spellManager;

Player::Player() {
	delete[] m_knownSpells;
	//m_knownSpells = new Spell[1]{new Scrunch};
	m_knownSpells = new int[3] {0,1,2};	
}

Player::Player(size_t a_maxHealth, size_t a_maxDignity) {
	m_currentHealth = a_maxHealth;
	m_maxHealth = a_maxDignity;

	delete[] m_knownSpells;
	//m_knownSpells = new Spell[1]{new Scrunch};
	m_knownSpells = new int[3] {0, 1, 2};
}


Player::~Player()
{
	delete[] m_knownSpells;
}

void Player::CastSpell(String& a_spellName) {
	std::cout << "It went through player!" << std::endl;
	spellManager->CastSpell(spellManager->CheckSpellList(a_spellName), this, m_enemyP);
	
}

bool Player::CheckSpell(String& a_spellName) {
	
	return false;

}
