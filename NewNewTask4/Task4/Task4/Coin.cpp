#include "Coin.h"
#include "Game.h"

Coin::Coin(Vec2I a_position)
{
	position = a_position;
	m_name = "Coin";
	colour = 178;
	icon = 'o';
	stationary = false;
	value = 1;
}

Coin::~Coin() {

}

void Coin::Description() const {

}

void Coin::Use() {
	//Ooh shit work this out.
}

bool Coin::Take() {
	Game* currentGame = Game::GetInstance();
	Player* playerPtr = currentGame->GetPlayer();
	playerPtr->SetCoinCount(playerPtr->GetCoinCount() + value);
	playerPtr->inventory.push_back(this);
	currentGame->GetCurrentRoom()->m_items.remove(this);
	currentGame->lastActionText = "You quietly pocket the coin.";
	return true;
}