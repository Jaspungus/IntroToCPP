#include "ManaPotion.h"
#include "Game.h"

ManaPotion::ManaPotion(Vec2I a_position)
{
	position = a_position;
	m_name = "Mana Potion";
	colour = 39;
	icon = String::IntToASCII(15).CharacterAt(0);
	stationary = false;
	value = 1;
}

ManaPotion::~ManaPotion() {

}

void ManaPotion::Description() const {

}

void ManaPotion::Use() {
	Game* currentGame = Game::GetInstance();
	Player* playerPtr = currentGame->GetPlayer();
	playerPtr->SetMana(playerPtr->GetMana() + 15);
	playerPtr->SetCoinCount(playerPtr->GetCoinCount() - value);
	playerPtr->inventory.remove(this);
	currentGame->lastActionText = "You drink the potion and swiftly feel your mana restored.";
}

bool ManaPotion::Take() {
	Game* currentGame = Game::GetInstance();
	Player* playerPtr = currentGame->GetPlayer();
	playerPtr->SetCoinCount(playerPtr->GetCoinCount() + value);
	playerPtr->inventory.push_back(this);
	currentGame->GetCurrentRoom()->m_items.remove(this);
	currentGame->lastActionText = "You slip the mana potion into your satchel.";
	return true;
}