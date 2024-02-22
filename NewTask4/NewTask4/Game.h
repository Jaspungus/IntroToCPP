#pragma once
#include "Room.h"
#include "Player.h"

class Game
{
private:
	Room rooms[5][5];
	Player* player;
public:
	Game();
	~Game();
	void Run();
};

