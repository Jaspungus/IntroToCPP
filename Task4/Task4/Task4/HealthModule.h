#pragma once
class HealthModule
{
public: 
	HealthModule();
	HealthModule(size_t a_maxHealth, size_t a_maxDignity);
	~HealthModule();

public:
	virtual void TakeHealthDamage(size_t a_damage);
	virtual void HealHealth(size_t a_damage);
	virtual void TakeDignityDamage(size_t a_damage);
	virtual void HealDignity(size_t a_damage);

	//virtual void Die();

private:
	size_t m_maxHealth = 0;
	size_t m_currentHealth = 0;
	size_t m_maxDignity = 0;
	size_t m_currentDignity = 0;
};

