#include "Coin.h"
#include "Game.h"

Coin::Coin(Vec2I a_position)
{
	position = a_position;
	m_name = "Coin";
	colour = 178;
	icon = '.';
	stationary = false;
	value = 3;
}

Coin::~Coin() {

}

void Coin::Description() const {
	Game* currentGame = Game::GetInstance();
	currentGame->lastActionText += "A big gold dubloon. Frustratingly worth $3 which makes foreign currency exchange needlessly difficult.";
}

void Coin::Use() {

	Game* gameInstance = Game::GetInstance();
	Player* player = gameInstance->GetPlayer();

	int i = 0;
	bool wallHit = false;
	bool throwCoin = false;
	for (i; i <= 3; i++) {
		//Player pos, plus direction * i+1
		//At i = 0, check 1 tile in front. At i = 5, check the 6th tile.


		if (gameInstance->GetMovementBlocked(player->GetPosition() + (player->GetDirectionVector() * (i + 1)), 1)) {
			//Wall hit
			wallHit = true;
			throwCoin = true;
			break;
		}
		if (i == 3) { throwCoin = true; }
	}


	for (i; i > 0; i--) {
		if (!gameInstance->GetMovementBlocked(player->GetPosition() + (player->GetDirectionVector() * (i)), 0))
		{
			throwCoin = true;
			break;
		}
	}


	if (throwCoin && i != 0) {
		position = (player->GetPosition() + (player->GetDirectionVector() * i));

		gameInstance->GetCurrentRoom()->m_items.push_back(this);
		player->inventory.remove(this);
		player->SetCoinCount(player->GetCoinCount() - value);

		gameInstance->lastActionText = "You successfully throw a coin, letting out a high pitched ring sure to attract attention.";
		gameInstance->EmitNoise(player->GetPosition() + (player->GetDirectionVector() * i));
		gameInstance->useTurn = true;
	}

	else {
		gameInstance->lastActionText = "You try to throw a coin but there's nowhere for it to go.";
	}
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