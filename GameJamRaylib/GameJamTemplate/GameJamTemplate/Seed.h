#pragma once
#include "GameObject.h"
class Seed : public GameObject
{
public:
	Seed();
	Seed(Vector2 pos, Vector2 scale, Game* game, Vector2 direction);
	~Seed();

	void OnUpdate(float deltaTime) override;
	void OnDraw() override;

	void UpdateRect();
	void Destroy();

private:
	float m_moveSpeed = 50;
	Vector2 m_direction = { 0,0 };
};

