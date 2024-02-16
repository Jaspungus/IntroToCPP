#include "HealthModule.h"

//Delete after
#include <iostream>

HealthModule::HealthModule() {
	
}

HealthModule::HealthModule(size_t a_maxHealth, size_t a_maxDignity) {
	m_currentHealth = a_maxHealth;
	m_maxHealth = a_maxDignity;
}

HealthModule::~HealthModule() {

}



//Text for this should be handled elsewhere.
void HealthModule::TakeHealthDamage(size_t a_damage) {
	if (a_damage > m_currentHealth){
		m_currentHealth = 0;
		
	}
	m_currentHealth -= a_damage;
}

void HealthModule::HealHealth(size_t a_health) {
	m_currentHealth += a_health;
	if (m_currentHealth > m_maxHealth) m_currentHealth = m_maxHealth;
}
void HealthModule::TakeDignityDamage(size_t a_damage)
{
	if (a_damage > m_currentDignity) {
		m_currentDignity = 0;

	}
	m_currentDignity -= a_damage;
	std::cout << m_currentDignity << std::endl;
}
void HealthModule::HealDignity(size_t a_health)
{
	m_currentDignity += a_health;
	if (m_currentDignity > m_maxDignity) m_currentDignity = m_maxDignity;
}
//
//void Die() {
//	return;
//	//I guess I can't call the deconstructor. Don't think I need to anyway but haha I'm exhausted and grumpy and this is helping. :)))
//}