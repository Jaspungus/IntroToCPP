#pragma once
#include "Room.h"
#include "Player.h"
#include "String.h"
#include "Coin.h"
#include "ManaPotion.h"
#include "Door.h"

class Game
{

private:
	const int MAPHEIGHT = 2;
	const int MAPWIDTH = 2;
	Room rooms[2][2];
	int currentRoomX = 0;
	int currentRoomY = 0;

	Player* player;

	bool isPlaying = false;
	bool useTurn = false;
	int turnCount = 0;
	String HUD;

public:
	String lastActionText;

public:
	Game();
	~Game();


private:
	static Game gameInstance;

public:
	static Game* GetInstance() { return &gameInstance; }



public:
	Room* GetRoom(const int x, const int y);
	Room* GetRoom(const Vec2I a_pos);
	Room* GetCurrentRoom();

	void MoveRoom(int x, int y);
	void MoveRoom(const Vec2I a_pos);
	void Run();

	bool CheckClearLine(Vec2I start, Vec2I direction);

	Player* GetPlayer();

private:
	void SetupRooms();
	
	void UpdateDisplay();
	Vec2I GetDirectionFromInput(const String& command) const;

	bool IsLineClear(Vec2I a_start, Vec2I a_end);
	bool PlotLineLow(Vec2I start, Vec2I end);
	bool PlotLineHigh(Vec2I start, Vec2I end);
};

