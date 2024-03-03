#include "Toilet.h"
#include "Game.h"

Toilet::Toilet(Vec2I a_position)
{
	position = a_position;
	m_name = "Toilet";
	colour = 253;
	icon = '0';
	//219 is also good. Annoyyed I cant use union.
	stationary = true;
	value = 10;
}


Toilet::Toilet(Vec2I a_position, bool a_isLoose)
{

	position = a_position;
	m_name = "Toilet";
	colour = 253;
	icon = '0';
	stationary = true;
	loose = a_isLoose;
	value = 10;
}

Toilet::~Toilet() {

}

void Toilet::Description() const {
	Game* currentGame = Game::GetInstance();
	currentGame->lastActionText += "A toilet. You know what those are. I don't need to describe it.";
}


void Toilet::Use() {
	Game* currentGame = Game::GetInstance();

	if (!loose) {
		currentGame->lastActionText = "You flush the toilet. It's loud. It gurgles and everyone conscious probably heard it.";
		currentGame->EmitNoise(position);
	}
	else {
		currentGame->lastActionText = "You try to flush it but realise this toilet isn't connected and is in fact loose.";
	}
}

bool Toilet::Take() {
	Game* currentGame = Game::GetInstance();
	if (!loose) {
		currentGame->lastActionText = "Unsurprisingly the porcelain throne literally bolted into the ground and wall can't be easily lifted.";
	}
	else {
		Player* playerPtr = currentGame->GetPlayer();
		playerPtr->SetCoinCount(playerPtr->GetCoinCount() + value);
		playerPtr->inventory.push_back(this);
		currentGame->GetCurrentRoom()->m_items.remove(this);
		currentGame->lastActionText = "The loose toilet may be heavy, but it's not bolted down. You do your best to squeeze it into your pack. Kleptomaniac."; 
		return true;
	}
	return false;
}