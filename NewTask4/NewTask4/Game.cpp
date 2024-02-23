#include "Game.h"

Game::Game() {
	player = new Player("Grublo grimblar");
	currentX = 1;
	currentY = 2;

	//Empty Room
	//rooms[0, 0];

	//StockRoom
	rooms[0][1].GetGnomeList().push_back(Gnome("Harry", "Employee", "A short, dark haired man, unpacking boxes that appear to be full of stacks of packaged pink discs."));
	rooms[0][1].SetDoor(2, 1);
	//Office
	rooms[0][2].GetGnomeList().push_back(Gnome("Garry", "Manager", "A short, dark haired man, unpacking boxes that appear to be full of stacks of packaged pink discs."));
	rooms[0][2].SetDoor(2, 1);

	//Cool Room
	rooms[1][0].GetGnomeList().push_back(Gnome("Harry", "Employee", "A short, dark haired man, unpacking boxes that appear to be full of stacks of packaged pink discs."));
	rooms[1][0].SetDoor(1, 1);
	//Kitchen
	rooms[1][1].GetGnomeList().push_back(Gnome("Harry", "Employee", "A short, dark haired man, unpacking boxes that appear to be full of stacks of packaged pink discs."));
	rooms[1][1].SetDoor(0, 1);
	rooms[1][1].SetDoor(1, 1);
	rooms[1][1].SetDoor(3, 1);
	//Booths
	rooms[1][2].GetGnomeList().push_back(Gnome("Harry", "Employee", "A short, dark haired man, unpacking boxes that appear to be full of stacks of packaged pink discs."));
	rooms[1][2].SetDoor(0, 1);
	rooms[1][2].SetDoor(2, 1);
	rooms[1][2].SetDoor(3, 1);

	//Bathroom
	rooms[2][0].GetGnomeList().push_back(Gnome("Harry", "Employee", "A short, dark haired man, unpacking boxes that appear to be full of stacks of packaged pink discs."));
	rooms[2][0].SetDoor(1, 1);
	//Front Counter
	rooms[2][1].GetGnomeList().push_back(Gnome("Juliet", "Teller", "The teller is at the desk is a young blonde-haired woman staring dead-eyed into the middle-distance."));
	rooms[2][1].SetDoor(1, 1);
	rooms[2][1].SetDoor(3, 1);
	//Booths
	rooms[2][2].GetGnomeList().push_back(Gnome("Harry", "Person", "A woman sits."));
	rooms[2][2].SetDoor(0, 1);
	rooms[2][2].SetDoor(3, 1);


}

Game::~Game() {

}

void Game::Run() {

	bool isPlaying = true;


	std::cout << "Enter Player Name" << std::endl;

	String command;
	command.ReadFromConsole();

	player->SetName(command);
	
	MoveTo(currentX, currentY);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
		{
			rooms[i][j].Description();
			std::cout << rooms[i][j].GetDoor(0) << rooms[i][j].GetDoor(1) << rooms[i][j].GetDoor(2) << rooms[i][j].GetDoor(3) << std::endl;
		
		}
	}


	while (isPlaying) {

		command.ReadFromConsole();


		//Movement
		if (command.Find("move") != -1) {
			int	moveY = 0;
			int moveX = 0;
			int pathState = -1;
			
			if (command.Find("north") != -1) {
				pathState = rooms[currentY][currentX].GetDoor(0);
				moveY = 1;
			}
			else if (command.Find("east") != -1) {
				pathState = rooms[currentY][currentX].GetDoor(1);
				moveX = 1;
			}
			else if (command.Find("south") != -1) {
				pathState = rooms[currentY][currentX].GetDoor(2);
				moveY = -1;
			}
			else if (command.Find("west") != -1) {
				pathState = rooms[currentY][currentX].GetDoor(3);
				moveX = -1;
			}

			std::cout << rooms[currentY][currentX].GetDoor(0) << rooms[currentY][currentX].GetDoor(1) << rooms[currentY][currentX].GetDoor(2) << rooms[currentY][currentX].GetDoor(3) << std::endl;
			std::cout << pathState << std::endl;
			std::cout << command.CStr() << endl;
			
			switch (pathState) {
				case 0: {
					std::cout << "You cannot go that way." << std::endl;
					break;
				}
				case 1: {
					MoveTo(currentX + moveX, currentY + moveY);
					std::cout << currentX << currentY << std::endl;
					break;
				}
				case 2: {
					std::cout << "You cannot go that way. A locked door bars your progress." << std::endl;
					std::cout << currentX << currentY << std::endl;
					break;
				}
			}
		}

		//Using items

		if (int useIndex = command.Find("use") != -1) {
			player->UseItem(command);
		}


		//Casting Spells
		//You never said we had to be smart with it.
		//And yes you can cast multiple at once.
		if (int castIndex = command.Find("cast") != -1) {
			
			int spellIndex = 0;
			if (spellIndex = command.Find(castIndex + 5, "Disintegrate") != -1)
			{
				if (command.Find(spellIndex + 12, "All") != -1)
				{
					for (Gnome& gnome : rooms[currentY][currentX].GetGnomeList()) 
					{
						gnome.TurnToAsh();
					}
				}
				
			}
			else if (spellIndex = command.Find(castIndex + 5, "Turn Pink") != -1) 
			{
				std::cout << "You cast \"Turn Pink\" and turn a pinkish hue." << std::endl;
			}
			else if (spellIndex = command.Find(castIndex + 5, "Yellow") != -1) 
			{
				std::cout << "You cast \"Yellow\"" << std::endl;
			}
		}


	}
}

void Game::MoveTo(int x, int y) {
	currentX = x;
	currentY = y;
	rooms[currentY][currentX].Description();
	for (Gnome gnome : rooms[currentY][currentX].GetGnomeList())
	{
		std::cout << gnome.m_description.CStr() << std::endl;
	}
}