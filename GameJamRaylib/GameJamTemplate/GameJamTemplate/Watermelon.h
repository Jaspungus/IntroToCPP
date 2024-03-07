#pragma once
#include "GameObject.h"

class Watermelon : public GameObject
{
public:
	Watermelon();
	Watermelon(Vector2 pos, Vector2 scale, Game* game, float a_fallSpeed);
	~Watermelon();

	void OnUpdate(float deltaTime) override;
	void OnDraw() override;
	void Destroy();

private:
	void UpdateRect();
	float m_fallSpeed = 300;


};

