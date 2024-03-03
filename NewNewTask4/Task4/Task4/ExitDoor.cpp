#include "ExitDoor.h"
#include "Game.h"

ExitDoor::ExitDoor(Vec2I a_position)
{
	position = a_position;
	m_name = "Exit Door";
	colour = 34;
	icon = String::IntToASCII(209).CharacterAt(0);
	//219 is also good. Annoyyed I cant use union.
	stationary = true;
	value = 15;
}

ExitDoor::~ExitDoor() {

}

void ExitDoor::Description() const {
	Game* currentGame = Game::GetInstance();
	currentGame->lastActionText += "An exit to the outside world. Only go through once you're ready to leave.";
}

void ExitDoor::Use() {
	Game* currentGame = Game::GetInstance();
	currentGame->lastActionText = "You slip out of the building with little more than a squeak of unoiled hinges. Well done.";
	currentGame->GameOver(false);
	
}

bool ExitDoor::Take() {
	Game* currentGame = Game::GetInstance();
	currentGame->lastActionText = "Despite your fervent desire to tear this exit door off its hinges it remains resolutely bolted to the doorframe.";
	return false;
}