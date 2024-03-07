#pragma once
#include "GameObject.h"

class EnvironmentBlock : public GameObject
{
public:

	EnvironmentBlock();
	EnvironmentBlock(Vector2 pos, Vector2 scale, Game* game);
	~EnvironmentBlock();

	void OnUpdate(float deltaTime) override;
	void OnDraw() override;

private:
	void UpdateRect();
};

