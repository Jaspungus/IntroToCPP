#include "Diamond.h"
#include "Game.h"

Diamond::Diamond(Vec2I a_position)
{
	position = a_position;
	m_name = "Diamond";
	colour = 86;
	icon = String::IntToASCII(4).CharacterAt(0);;
	//219 is also good. Annoyyed I cant use union.
	stationary = true;
	value = 15;
}


Diamond::~Diamond() {

}

void Diamond::Description() const {
	Game* currentGame = Game::GetInstance();
	currentGame->lastActionText += "A diamond. Not like an actual precious gem. Just a playing card someone left behind.";
}


void Diamond::Use() {
	Game* currentGame = Game::GetInstance();

	currentGame->lastActionText = "It's a diamond. Get 4 more and you'll have a flush.";
	currentGame->useTurn = true;
}

bool Diamond::Take() {
	Game* currentGame = Game::GetInstance();
	Player* playerPtr = currentGame->GetPlayer();
	playerPtr->SetCoinCount(playerPtr->GetCoinCount() + value);
	playerPtr->inventory.push_back(this);
	currentGame->GetCurrentRoom()->m_items.remove(this);
	currentGame->lastActionText = "You place the glimmering diamond into your pouch.";
	return true;
}