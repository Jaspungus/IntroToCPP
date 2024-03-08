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
	void LerpTo(Vector2 pos, float duration);
	bool GetLerping();

	void Shoot(Vector2 targetPos);

private:

	float m_maxMoveSpeed = 100;
	float m_acceleration = 40;
	float m_deceleration = 30;

	float m_moveSpeed = 300;

	Vector2 m_velocity = { 0,0 };
	Vector2 m_direction = { 0,0 };

	float m_dashStrength = 500;
	float m_dashCooldown = 2;
	float m_dashTimer = 0;


	bool m_isColliding = false;
	bool m_freeMovement = false;

	int m_seedCount = 0;

	Rectangle m_groundedRect {0,0,0,0};

	bool m_isLerping = false;

	Vector2 m_targetPos = { 0,0 };
	Vector2 m_lerpRate = { 0,0 };



	void UpdateRect();

	
};

