#pragma once
#include <vector>
#include <raylib.h>
#include "String.h"

class GameObject;
class Player;

class Game
{
public:
	Game();
	~Game();

	void Run();
	void Load();
	void Unload();
	void Update(float deltaTime);
	void Draw();
	void ResetSpawnDelay();
	void ResetFallSpeed();

public:
	GameObject* m_root;
	Player* m_player;
	Camera2D m_camera = { 0 };
	String seedCountUI = "0";

	int m_windowHeight = 750;
	int m_windowWidth = 1200;
	

	Vector2 m_screenTLCorner = { -600, -375 };
	Vector2 m_screenBRCorner = { 600, 375 };
	Vector2 m_gameTRCorner = { 200, -375 };
	Vector2 m_gameBLCorner = { -200, 375 };

	int m_gameState = 0;

private:
	
	Vector2 m_spawnableRange = { -200, 350 }; //x is offset, y is range.
	float m_spawnTimer = 1;
	float m_spawnDelay = 3;
	float m_spawnDelayDefault = 3;
	float m_minSpawnDelay = 0.5;
	float m_currentFallSpeed = 200;
	float m_maxFallSpeed = 500;
	float m_startingFallSpeed = 200;

	float m_delayDecreaseTimer = 3;


	float m_roundTimer = 20;

	
	bool bordersOn = true;

	Rectangle cursorRect = { 0,0,0,0 };
	
};

