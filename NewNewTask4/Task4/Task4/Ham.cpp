#include "Ham.h"
#include "Game.h"

Ham::Ham(Vec2I a_position)
{
	position = a_position;
	m_name = "Ham";
	colour = 167;
	icon = String::IntToASCII(155).CharacterAt(0);;
	//219 is also good. Annoyyed I cant use union.
	stationary = false;
	value = 4;
}


Ham::~Ham() {

}

void Ham::Description() const {
	Game* currentGame = Game::GetInstance();
	currentGame->lastActionText += "A roast leg of ham. There are an unusual number of these lying around.";
}


void Ham::Use() {
	Game* currentGame = Game::GetInstance();
	Player* player = currentGame->GetPlayer();

	player->inventory.remove(this);
	player->SetCoinCount(player->GetCoinCount() - value);

	currentGame->lastActionText = "You carefully place the entire ham into your mouth, and pull out a perfectly clean leg bone.";
	currentGame->useTurn = true;
}

bool Ham::Take() {
	Game* currentGame = Game::GetInstance();
	Player* playerPtr = currentGame->GetPlayer();
	playerPtr->SetCoinCount(playerPtr->GetCoinCount() + value);
	playerPtr->inventory.push_back(this);
	currentGame->GetCurrentRoom()->m_items.remove(this);
	currentGame->lastActionText = "You place the ham silently into your bag.";
	return true;
}