#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:

	Player();
	Player(Vector2 pos, Vector2 scale, Game* game);
	~Player();

	void OnUpdate(float deltaTime) override;
	void OnDraw() override;

	int GetSeedCount();
	void EnableFreeMovement();

private:

	float m_maxMoveSpeed = 400;
	float m_acceleration = 100;
	float m_deceleration = 50;

	float m_moveSpeed = 300;

	Vector2 m_velocity = { 0,0 };
	Vector2 m_direction = { 0,0 };

	float m_dashStrength = 1000;



	bool m_isColliding = false;
	bool m_freeMovement = false;

	int m_seedCount = 0;

	Rectangle m_groundedRect {0,0,0,0};

	void UpdateRect();
};

