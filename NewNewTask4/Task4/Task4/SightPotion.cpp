#include "SightPotion.h"
#include "Game.h"

SightPotion::SightPotion(Vec2I a_position)
{
	position = a_position;
	m_name = "Sight Potion";
	colour = 36;
	icon = String::IntToASCII(15).CharacterAt(0);
	stationary = false;
	value = 5;
}

SightPotion::~SightPotion() {

}

void SightPotion::Description() const {
	Game* currentGame = Game::GetInstance();
	currentGame->lastActionText += "A potion that improves ones vision in darkness. Convenient.";
}

void SightPotion::Use() {
	Game* currentGame = Game::GetInstance();
	Player* playerPtr = currentGame->GetPlayer();
	playerPtr->SetSight(playerPtr->GetSight() + 2);
	playerPtr->SetCoinCount(playerPtr->GetCoinCount() - value);
	playerPtr->inventory.remove(this);
	currentGame->lastActionText = "You drink the potion and feel your eyes better adjust to the darkness.";
}

bool SightPotion::Take() {
	Game* currentGame = Game::GetInstance();
	Player* playerPtr = currentGame->GetPlayer();
	playerPtr->SetCoinCount(playerPtr->GetCoinCount() + value);
	playerPtr->inventory.push_back(this);
	currentGame->GetCurrentRoom()->m_items.remove(this);
	currentGame->lastActionText = "You place the sight potion into your bag.";
	return true;
}