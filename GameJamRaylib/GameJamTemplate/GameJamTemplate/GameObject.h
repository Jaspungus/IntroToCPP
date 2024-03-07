#pragma once
#include "raylib.h"
#include "Game.h"
#include <vector>

class GameObject

{

public:
	GameObject() {};
	GameObject(Game* game) { this->m_game = game; };
	~GameObject() {};

	virtual void OnUpdate(float deltaTime) {};
	virtual void OnDraw() {};
	void Update(float deltaTime);
	void Draw();
	void AddChild(GameObject* child);
	const Vector2 GetPos() {
		return m_position;
	}
	const Rectangle GetGameRect() {
		return m_gameRect;
	}

	std::vector<GameObject*> children;

protected:
	Vector2 m_position = { 0,0 };
	Vector2 m_scale = { 0,0 };
	float m_rotation = 0; //Currently does nothing
	GameObject* m_parent = nullptr;
	Game* m_game = nullptr;



	//Rectangle = {posX, posY, width, height)
	Rectangle m_gameRect = {0,0,0,0}; //Every object in this game can only be a rectangle by this logic (made this way to simplify collision checking)
	Color m_color = BLANK; //Every game object gets it's own color :-)




};

