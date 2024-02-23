#pragma once
#include "Room.h"
#include "Player.h"
#include "String.h"

class Game
{
private:
	Room rooms[3][3] = {
		{ Room(), Room("Storage"), Room("Office"), },
		{ Room("Coolroom"), Room("Kitchen"), Room("Booths"), },
		{ Room("Toilet"), Room("Front Counter"), Room("Booths"), }
	};


	Player* player;
	int currentX, currentY;
public:
	Game();
	~Game();
	void MoveTo(int x, int y);
	void Run();
};

