#include "Game.h"

void Game::Run() {

	bool isPlaying = true;

	while (isPlaying) {

		String command;
		command.ReadFromConsole();

		//Movement
		if (command.ToLower() == "move north") {

		}
		if (command.ToLower() == "move east") {

		}
		if (command.ToLower() == "move south") {

		}
		if (command.ToLower() == "move west") {

		}

		//Using items



		//Casting Spells
		//You never said we had to be smart with it.
		//And yes you can cast multiple at once.

		if (command.Find("cast")) {
			int spellIndex = 0;
			spellIndex = command.Find(5, "Disintegrate");
			if (spellIndex != -1) 
			{
				if (command.Find(spellIndex + 12, "All") != -1);
				
			}
			if (command.Find(5, "Disintegrate")) {}
			if (command.Find(5, "Disintegrate")) {}
		}


	}
	

}