#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(Vector2 pos, Vector2 scale, Game* game);
	~Enemy();

	void OnUpdate(float deltaTime) override;
	void OnDraw() override;

	void UpdateRect();

	void MoveTo(Vector2 pos);


private:
	float moveSpeed = 20;

};

