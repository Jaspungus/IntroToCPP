#pragma once
#include "Room.h"
#include "Player.h"
#include "String.h"
#include "Coin.h"
#include "ManaPotion.h"
#include "Door.h"
#include "ExitDoor.h"
#include "Toilet.h"
#include "Ham.h"
#include "Diamond.h"
#include "SightPotion.h"
//Yeah yeah i should have made one file that had all of the items in it.

class Game
{

private:
	const int MAPHEIGHT = 2;
	const int MAPWIDTH = 2;
	Room rooms[2][2] = 
	{ {Room("\nYou're in the back of the building now. There's nothing around but toilets and offices. Miserable."), Room("\nThe kitchen. Where the magic happens, if reheating week old jerky and assembling it into a heap with stale bread and molting lettuce is considered magic.")},
	  {Room("\nThe front room. It somehow looks less miserable in the dark. The shadows concealing peeling wallpaper, stained carpets, questionably clean tables and a cocktail bar that only ever serves beer."), Room("\nThe second dining hall. Like the first but without the half hearted attempts to impress new diners. Here lies the second side of the bar, this one without the rows of bottles that nobody orders.")}
	};
	int currentRoomX = 0;
	int currentRoomY = 0;

	Player* player;

	bool isPlaying = false;
	bool failed = false;

	int turnCount = 0;
	String HUD;

public:
	String lastActionText;
	bool useTurn = false;
	bool allSeeing = false;
	bool stopTime = false;

public:
	Game();
	~Game();


private:
	static Game gameInstance;

public:
	static Game* GetInstance() { return &gameInstance; }

public:
	bool (*LineDrawFunction)(Vec2I a_position) = nullptr;

public:
	Room* GetRoom(const int x, const int y);
	Room* GetRoom(const Vec2I a_pos);
	Room* GetCurrentRoom();

	void MoveRoom(int x, int y);
	void MoveRoom(const Vec2I a_pos);
	void Run();

	bool CheckClearLine(Vec2I start, Vec2I direction);

	Player* GetPlayer();
	bool GetMovementBlocked(Vec2I a_position);
	bool GetMovementBlocked(Vec2I a_position, int a_freeTiles);
	bool GetGuardMovementBlocked(Guard* a_guardPtr, Vec2I a_position);

	void EmitNoise(Vec2I a_position);

	void GameOver(bool failed);

private:
	void SetupRooms();
	
	void UpdateDisplay();
	Vec2I GetDirectionFromInput(const String& command) const;

	bool PlotLine(Vec2I start, Vec2I end);

//Function Pointer Functions
//Dude I am probably breaking OOP rules so hard
private:
	//bool IsTileBlocked(Vec2I a_position);
	//bool SetTileToLit(Vec2I a_position);
};

