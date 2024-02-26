#include "Door.h"
#include "Game.h"

Door::Door(Vec2I a_position)
{
	position = a_position;
	m_name = "Door";
	colour = 130;
	icon = String::IntToASCII(209).CharacterAt(0);
	//219 is also good. Annoyyed I cant use union.
	stationary = true;
	value = 15;

	isLocked = true;
	connectedRoom = Vec2I(0, 0);
	playerSpawn = Vec2I(0, 0);
	exitDirection = 0;
}


Door::Door(Vec2I a_position, bool a_isLocked, Vec2I a_connectedRoom, Vec2I a_playerSpawn, int a_exitDirection)
{
	isLocked = a_isLocked;
	connectedRoom = a_connectedRoom;
	playerSpawn = a_playerSpawn;
	exitDirection = a_exitDirection;

	position = a_position;
	m_name = "Door";
	colour = 130;
	icon = String::IntToASCII(209).CharacterAt(0);
	stationary = true;
	value = 15;
}

Door::~Door() {

}

void Door::Description() const {

}

void Door::Use() {
	Game* currentGame = Game::GetInstance();

	if (isLocked) {
		currentGame->lastActionText = "Despite your best efforts the door will not budge.";
	}
	else {
		currentGame->MoveRoom(connectedRoom);
		Player* playerPtr = currentGame->GetPlayer();
		playerPtr->SetPosition(playerSpawn);
		playerPtr->SetDirection(exitDirection);
		currentGame->lastActionText = "You quietly open the door and enter the next room.";
	}
}

bool Door::Take() {
	Game* currentGame = Game::GetInstance();
	currentGame->lastActionText = "Although you tug and tug, you cannot seem to get the door off it's hinges.";
	return false;
}