#pragma once
class HealthModule
{
private: 
	HealthModule();
	HealthModule(size_t a_maxHealth);
	~HealthModule();

private:
	virtual void TakeDamage(size_t a_damage);
	virtual void Heal(size_t a_damage);
	virtual void Die();

private:
	size_t m_maxHealth = 0;
	size_t m_currentHealth = 0;
	
};

