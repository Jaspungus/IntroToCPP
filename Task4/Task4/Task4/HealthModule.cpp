#include "HealthModule.h"

HealthModule::HealthModule() {
	
}

HealthModule::HealthModule(size_t a_maxHealth) {
	m_currentHealth = a_maxHealth;
	m_maxHealth = a_maxHealth;
}

HealthModule::~HealthModule() {

}



//Text for this should be handled elsewhere.
void HealthModule::TakeDamage(size_t a_damage) {
	if (a_damage > m_currentHealth){
		m_currentHealth = 0;
		
	}
	m_currentHealth -= a_damage;
}

void HealthModule::Heal(size_t a_health) {
	m_currentHealth += a_health;
	if (m_currentHealth > m_maxHealth) m_currentHealth = m_maxHealth;
}

void Die() {
	//I guess I can't call the deconstructor. Don't think I need to anyway but haha I'm exhausted and grumpy and this is helping. :)))
}