#include "Game.h"
#include "Vec2.h"
#include <stdlib.h>
#include <ctime>

bool GetSightBlocked(Vec2I a_position);
bool GetLightBlocked(Vec2I a_position);

Game::Game() {
	player = new Player(Vec2I(3,3));
	SetupRooms();
	LineDrawFunction = &GetSightBlocked;
}

Game::~Game() {

}

Game Game::gameInstance;

void Game::Run() {
	struct tm newTime;
	time_t startTime = time(NULL);
	localtime_s(&newTime, &startTime);

	String command;
	String commandBuffer;


	GetCurrentRoom()->Description();
	

	isPlaying = true;

	while (isPlaying) {

		//If the last action was successful, use up a turn and update enemies.
		if (useTurn && !stopTime) {

			//Code for guards spotting the player/updating each guards position & behaviour state
			//It is important for this call to happen first so the guard's position is updated and then the light cone is drawn.
			//This (as of 12:10 2/03) has issues surrounding it as light data is cleared and redrawn every frame.
			//Should be good now, and guards should only update every time the player uses a turn.

			LineDrawFunction = &GetSightBlocked;
			for (Guard* guardPtr : GetCurrentRoom()->m_guards)
			{
				if (guardPtr != nullptr)
				{
					if (guardPtr->GetState() != 4)
					{

						//Guards will spot the player IF:
						//There is nothing blocking the line of sight
						//The player is on a tile that is lit
						//The player is within 180 degrees of vision.
						if (GetCurrentRoom()->GetTileIsLit(player->GetPosition())
						//	&& guardPtr->GetDirectionVector().DotProduct(player->GetPosition() - guardPtr->GetPosition()) > 0
							&& PlotLine(guardPtr->GetPosition(), player->GetPosition())	)
						{

							guardPtr->SetSeesPlayer(true);
							guardPtr->GeneratePath(player->GetPosition()); //For some reason, it fails to generate a path if the player is directly below the guard. Up is fine.
							lastActionText = "A guard can see you!";

							//Player loses
						}

						else { guardPtr->SetSeesPlayer(false); }

						guardPtr->UpdateState();
					}
				}
			}
			
			useTurn = false;
			turnCount++;
		}

		//Update game state
		system("CLS");
		UpdateDisplay();
		lastActionText = "";

		//Handle player input
		commandBuffer.ReadFromConsole();
		if (commandBuffer != "") command = commandBuffer;


		//Movement
		if (command.Find("move") != -1 || command.Find("go") != -1) {
			Vec2I direction = GetDirectionFromInput(command);
			
			bool pathBlocked = GetMovementBlocked(player->GetPosition() + direction);
			//If the space is free, move the player there.
			//Diagonals work and only use one turn.
		
			//If the player cannot move that way, state so. Don't use turn.
			if (direction == Vec2I::Zero()) {
				lastActionText = "Move where? North? South? East? West? Be more specific.";
			}
			else if (pathBlocked)
			{
				player->FaceDirection(direction);
				lastActionText = "You cannot go that way.";
			}
			else {
				player->Move(direction);
				useTurn = true;
			}


			std::cout << command.CStr() << endl;
		}

		//Taking Item
		//If no direction is entered it will use the direction the player is facing.
		else if (command.Find("take") != -1 || command.Find("grab") != -1 || command.Find("pick up") != -1) {
			//If a direction is added, use that and turn player. Otherwise use player direction.
			Vec2I direction = GetDirectionFromInput(command);
			bool itemUsed = false;
			if (direction == Vec2I::Zero()) {

				Item* itemPtr = GetCurrentRoom()->GetItem(player->GetPosition());
				if (itemPtr != nullptr) {
					//If the item is imovable interact with it, otherwise pick it up first.
					if (itemPtr->Take()) {
						useTurn = true;
					}
					itemUsed = true;
				}
					
				
				direction = player->GetDirectionVector();
			}
			else player->FaceDirection(direction);

			if (!itemUsed) {
				//Check if an item is present.
				Item* itemPtr = GetCurrentRoom()->GetItem(player->GetPosition() + direction);
				if (itemPtr != nullptr) {
					
					if (itemPtr->Take()) {
						
						useTurn = true;
					}
					itemUsed = true;
				}
			}
			//If there is nothing present, state so. Don't use turn.
			if (!itemUsed)
			{
				lastActionText = "Nothing to pick up.";

			}
		}

		//Using Item/Object in environment. Only works on objects within 1 tile.
		//If no direction is entered it will use the direction the player is facing.
		else if (int useIndex = command.Find("use") != -1 || command.Find("interact") != -1) {

			
				//If a direction is added, use that and turn player. Otherwise use player direction.
				Vec2I direction = GetDirectionFromInput(command);
				bool itemUsed = false;
				if (direction == Vec2I::Zero()) {

					if (useIndex != -1) { itemUsed = player->UseItem(useIndex + 3, command); }
					if (!itemUsed) {
						Item* itemPtr = GetCurrentRoom()->GetItem(player->GetPosition());
						if (itemPtr != nullptr) {
							//If the item is imovable interact with it, otherwise pick it up first.
							if (itemPtr->GetStationary()) {
								itemPtr->Use();
							}
							else {
								itemPtr->Take();
							}
							itemUsed = true;
							useTurn = true;
						}
					}
					direction = player->GetDirectionVector();


				}
				else player->FaceDirection(direction);

				if (!itemUsed) {
					//If there is an item present at the position 1 in that direction
					Item* itemPtr = GetCurrentRoom()->GetItem(player->GetPosition() + direction);
					if (itemPtr != nullptr) {
						//If the item is imovable interact with it, otherwise pick it up first.
						if (itemPtr->GetStationary()) {
							itemPtr->Use();
						}
						else {
							itemPtr->Take();
						}
						useTurn = true;
					}
					//If there is nothing present, state so. Don't use turn.
					else
					{
						lastActionText = "Nothing to interact with.";
					}
				}
		}

		//Add compatibility to look at items in range.
		else if (int lookIndex = command.Find("look") != -1 || command.Find("face") != -1) {
			
			bool itemFound = false;
			//Turns out this was broken literally until now 4:21 3/03 
			//And absolutely does not work.
			//It does not add much. And you can inspect stuff directly in front of you which is fine.
			//:)
			//if (lookIndex != -1) {
			//	for (Item* itemPtr : GetCurrentRoom()->m_items) {
			//		if (itemPtr != nullptr) {
			//			//If within range, check if the name matches.
			//			if (player->GetPosition().DistanceSquared(itemPtr->GetPosition()) < pow(player->GetSight(), 2))
			//			{
			//				if (command.Substring(lookIndex + 4, command.Length()).Find(itemPtr->GetName()))
			//				{
			//					itemPtr->Description();
			//					lastActionText += itemPtr->GetName();
			//					itemFound = true;
			//					break;
			//				}
			//			}
			//		}
			//	}
			//}

			Vec2I direction = GetDirectionFromInput(command);
			if (!itemFound) {

				if (direction == Vec2I::Zero()) {
					Item* itemPtr = GetCurrentRoom()->GetItem(player->GetPosition());
					if (itemPtr != nullptr) {
						itemPtr->Description();
						itemFound = true;
					}
					direction = player->GetDirectionVector();
				}
			}
			if (!itemFound) {
				Item* itemPtr = GetCurrentRoom()->GetItem(player->GetPosition() + direction);
				if (itemPtr != nullptr) {
					itemPtr->Description();
					player->FaceDirection(direction);
					itemFound = true;
				}
			}
			if (!itemFound)
			{
				lastActionText = "There is nothing there.";
				player->FaceDirection(direction);
			}
			
		}

		else if (command.Find("spellbook") != -1) {
			lastActionText = player->ListSpells();
		}

		else if (int checkIndex = command.Find("spell ") != -1) {
			String spellString = command.Substring(checkIndex + 5, command.Length());
			if (player->FindSpell(spellString))
			{
				lastActionText = "You know the spell ";
				lastActionText += spellString;
				lastActionText += "\n";
				lastActionText += player->ExplainSpell(spellString);
			}
			else 
			{
				lastActionText = "You do not know the spell ";
				lastActionText += spellString;
			}
		}


		//Casting Spells
		//You never said we had to be smart with it.
		else if (int castIndex = command.Find("cast") != -1) {

			if (command.Find(castIndex + 4, "Teleport") != -1)
			{
				if (player->GetMana() >= 5)
				{

					int i = 0;
					bool wallHit = false;
					bool teleport = false;
					for (i; i <= 4; i++) {
						//Player pos, plus direction * i+1
						//At i = 0, check 1 tile in front. At i = 5, check the 6th tile.
						if (GetSightBlocked(player->GetPosition() + (player->GetDirectionVector() * (i + 1)))) {
							//Wall hit
							wallHit = true;
							teleport = true;
							break;
						}
						if (i == 4) { teleport = true; }
					}

					
					for (i; i > 0; i--) {
						if (!GetMovementBlocked(player->GetPosition() + (player->GetDirectionVector() * (i)), 0))
						{
							teleport = true;
							break;
						}
					}
					

					if (teleport && i != 0) {
						player->SetPosition(player->GetPosition() + (player->GetDirectionVector() * i));
						player->SetMana(player->GetMana() - 5);
						lastActionText = "You successfully cast \"Teleport\".";
						useTurn = true;
					}

					else {
						lastActionText = "You cast \"Teleport\" but there's nowhere to go.";
					}
				}
				else {
					lastActionText = "You do not have enough mana to cast \"Teleport\".";
				}
			}
			else if (command.Find(castIndex + 4, "Shock") != -1)
			{
				if (player->GetMana() >= 5)
				{

					int i = 0;
					bool succeeded = false;
					for (i; i < 3; i++) {

						if (!GetSightBlocked(player->GetPosition() + (player->GetDirectionVector() * (i + 1)))) {
							
							for (Guard* guardPtr : GetCurrentRoom()->m_guards) {
								if (guardPtr->GetPosition() == (player->GetPosition() + (player->GetDirectionVector() * (i + 1)))) {
									//Shock guard
									guardPtr->SetState(guardPtr->Unconscious);
									EmitNoise(guardPtr->GetPosition());

									succeeded = true;
									player->SetMana(player->GetMana() - 5);
									lastActionText = "You with a crackle of lightning successfully cast \"Shock\". The guard drops to the ground unconscious and only slightly fried.";
									useTurn = true;

									break;
								}
							}
						}
						else { break; }
					}

					if (!succeeded) {
						lastActionText = "You cast \"Shock\" but there is nothing to shock.";
					}
				}
				else {
					lastActionText = "You do not have enough mana to cast \"Shock\".";
				}
			}
			else if (command.Find(castIndex + 4, "Sense") != -1)
			{
				GetCurrentRoom()->DescribeItems();
			}

			//else if (command.Find(castIndex + 4, "Illusion") != -1)
			//{
			//	//This is the doozy.
			//  //So much so I've removed it. It was going to spawn a hologram of the player. Which would alert guards. So I figured coins were just better at that.
			//	useTurn = true;
			//}
			else if (command.Find(castIndex + 4, "Turn Pink") != -1)
			{
 				player->SetColour(177);
				lastActionText = "You cast \"Turn Pink\" and turn a pinkish hue.";
				useTurn = true;
			}
			else if (command.Find(castIndex + 4, "Yellow") != -1)
			{
				lastActionText = "You cast \"Yellow\"";
				useTurn = true;
			}
			else {
				lastActionText = "You can only cast spells found in your spellbook. You're not carrying around that brick sized tome for nothing.";
			}
		}

		else if (command.Find("inventory") != -1)
		{
		lastActionText = player->ListItems();
		}

		else if (command.Find("wait") != -1) 
		{
			lastActionText = "You wait.";
			useTurn = true;
		}

		else if (command.Find("xray") != -1)
		{
			allSeeing = !allSeeing;
		}
		else if (command.Find("freeze") != -1)
		{
			stopTime = !stopTime;
		}
	}

	//End of game stuff.
	system("CLS");

	if (failed) lastActionText = "\nYou \033[38;5;196mwere caught\033[m with \033[38;5;178m$";
	else lastActionText = "\nYou \033[38;5;40mexfiltrated successfully\033[m and made it away\033[m with \033[38;5;178m$";
	lastActionText += String::IntToString(player->GetCoinCount());
	lastActionText += " worth of stolen loot!\033[m";

	time_t endTime = time(NULL);
	localtime_s(&newTime, &endTime);

	lastActionText += "\n\nYou took ";
	lastActionText += String::IntToString(turnCount);
	lastActionText += " turns over ";
	lastActionText += String::IntToString((int)difftime(endTime, startTime) / 60);
	lastActionText += " minutes and ";
	lastActionText += String::IntToString((int)difftime(endTime, startTime) % 60);
	lastActionText += " seconds!\n";

	lastActionText.WriteToConsole();

	player->ListItems().WriteToConsole();

}

Vec2I Game::GetDirectionFromInput(const String& command) const {
	Vec2I direction = Vec2I(0, 0);
	if (command.Find("north") != -1 || command.Find("up") != -1) {
		//pathState = GetRoom(currentRoomX, currentRoomY)->GetTile(player->GetPosition())->GetIsLit();
		direction.Y = -1;

	}
	if (command.Find("east") != -1 || command.Find("right") != -1) {
		//pathState = GetRoom(currentRoomX, currentRoomY)->GetTile(player->GetPosition())->GetIsLit();
		direction.X = 1;
	}
	if (command.Find("south") != -1 || command.Find("down") != -1) {
		//pathState = GetRoom(currentRoomX, currentRoomY)->GetTile(player->GetPosition())->GetIsLit();
		direction.Y = 1;
	}
	if (command.Find("west") != -1 || command.Find("left") != -1) {
		//pathState = GetRoom(currentRoomX, currentRoomY)->GetTile(player->GetPosition())->GetIsLit();
		direction.X = -1;
	}
	return direction;
}


void Game::UpdateDisplay()
{
	
	Room* currentRoomPtr = GetCurrentRoom();
	//Printing the heads up display. Probably not the right term given the context.

	HUD = "Turn Count: ";
	HUD.Append(String::IntToString(turnCount));

	HUD += "\t\033[38;5;178m$ Current Haul: ";
	HUD.Append(String::IntToString(player->GetCoinCount()));
	HUD += "\033[m ";
	
	HUD += "\t\033[38;5;39m";
	HUD.Append(String::IntToASCII(15)); 
	HUD += " Mana: ";
	HUD.Append(String::IntToString(player->GetMana()));
	HUD += "\033[m ";
	


	HUD.WriteToConsole();


	Vec2I currentTilePos = Vec2I(0, 0);
	for (currentTilePos.Y = 0; currentTilePos.Y < currentRoomPtr->ROOMHEIGHT; currentTilePos.Y++) {

		for (currentTilePos.X = 0; currentTilePos.X < currentRoomPtr->ROOMWIDTH; currentTilePos.X++)
		{
			currentRoomPtr->SetTileIsLit(currentTilePos, false);
		}
	}

	//This loop sets flashlight vision for each guard. The linedraw function GetLightBlocked sets the tile position to lit before it exits.
	//This means the first obstacle hit is set to lit. It could also just not do that it doesnt really matter.
	LineDrawFunction = &GetLightBlocked;
	for (Guard* guardPtr : currentRoomPtr->m_guards)
	{
		if (guardPtr != nullptr)
		{

			if (guardPtr->GetState() != 4)
			{
				guardPtr->UpdateConePoints();
				for (int i = 0; i < guardPtr->GetViewWidth(); i++)
				{
					PlotLine(guardPtr->GetPosition() + guardPtr->GetDirectionVector(), guardPtr->GetConePoints()[i]);
				}
			}

		}
	}

	LineDrawFunction = &GetSightBlocked;

	//Printing the map
	String printParams = "\n\n";
	currentTilePos = Vec2I(0,0);
	for (currentTilePos.Y = 0; currentTilePos.Y < currentRoomPtr->ROOMHEIGHT; currentTilePos.Y++) {
		//int mod2 = y % 5;
		//std::cout << currentTilePos.Y << ": ";
		printParams += "\t";
		for (currentTilePos.X = 0; currentTilePos.X < currentRoomPtr->ROOMWIDTH; currentTilePos.X++)
		{
			
			//std::cout << currentRoomPtr->GetTile(Vec2I(x, y)) << std::endl;
			int state = currentRoomPtr->GetTileState(currentTilePos);//currentRoomPtr->GetTile(Vec2I(x, y))->GetState();
			bool lit = currentRoomPtr->GetTileIsLit(currentTilePos);// currentRoomPtr->GetTile(Vec2I(x, y))->GetIsLit();
			bool empty = true;
			printParams += "\033[48;5;";



			//Check if the player can see the tile.
			//LineDrawFunction = &GetSightBlocked;
			if (!allSeeing) {
				if (!PlotLine(player->GetPosition(), currentTilePos) || currentTilePos.Distance(player->GetPosition()) > player->GetSight()) {

					printParams += "m   \033[m";
					continue;
					//state = 2; //This makes it so icons still appear.
				}
			}
			//All within, if in sight.
			//If empty space
			if (state == 0) {
				if (lit) {
					//Light grey 7
					printParams += "7";
				}
				else {
					//Shadow Grey 240
					printParams += "235";
				}
			}
			//If object
			else if (state == 1) {
				if (lit) {
					//Grey 248
					printParams += "248";
				}
				else {
					//Dark Grey 237
					printParams += "234";
				}
			}
			//If wall
			else if (state == 2) {
				//Black 0
				printParams += "0";
			}

			//Colour for Foreground
			//Character to represent

			//If player on tile.
			if (empty && currentTilePos == player->GetPosition()) {
				printParams += ";38;5;";
				printParams += String::IntToString(player->GetColour());
				printParams += "m ";
				printParams += player->GetIcon();
				empty = false;
			}

			//This also needs to draw their sight cones.
//LineDrawFunction = &IsTileBlockedSetLit;
			for (Guard* guardPtr : currentRoomPtr->m_guards) {
				if (empty && guardPtr != nullptr) {
					if (currentTilePos == guardPtr->GetPosition()) {
						printParams += ";38;5;";
						printParams += String::IntToString(guardPtr->GetColour());
						printParams += "m  ";
						printParams[printParams.Length() - 1] = guardPtr->m_icon;
						empty = false;
					}
				}
			}


			for (Item* itemPtr : currentRoomPtr->m_items) {
				if (empty && itemPtr != nullptr){
					if (currentTilePos == itemPtr->GetPosition()) {
						printParams += ";38;5;";
						printParams += String::IntToString(itemPtr->GetColour());
						printParams += "m  ";
				
						//This is what I have to do to get it to display right.
						//Terribly upsetting.
						printParams[printParams.Length()-1] = itemPtr->GetIcon();
						empty = false;
					}
				}
			}

		
			if (empty) {
				printParams += "m  ";
			}

			printParams += " \033[m";
		}

		//Suuuuper dodgy command inputs.
		switch (currentTilePos.Y) {
			case 0: {
				printParams += "\tCommands";
				break;
			}
			case 1: {
				printParams += "\t\"Move\\Go + Direction\" to move.";
				break;
			}
			case 2: {
				printParams += "\t\"Look\\Face + Direction\" to face a direction.";
				break;
			}
			case 3: {
				printParams += "\t\"Take\\Grab\\Pick up + Direction\" to collect items.";
				break;
			}
			case 4: {
				printParams += "\t\"Use\\Interact + Direction\" to interact with objects.";
				break;
			}
			case 5: {
				printParams += "\t\"Use + Item\" to use an item from your inventory.";
				break;
			}
			case 6: {
				printParams += "\t\"Inventory\" to view your inventory.";
				break;
			}
			case 7: {
				printParams += "\t\"Spellbook\" to view your available spells.";
				break;
			}
			case 8: {
				printParams += "\t\"Spell + Name\" to check the use of a particular spell.";
				break;
			}
			case 9: {
				printParams += "\t\"Cast + Spell\" to cast a spell from your spellbook.";
				break;
			}
			case 10: {
				printParams += "\t\"Wait\" to pass a turn without acting.";
				break;
			}
		}




		//I made this print line by line to reduce the string length & thus memory usage(?)
		printParams.WriteToConsole(); 
		printParams = "";

	}

	lastActionText.WriteToConsole();
}

//The most disgusting setup you've ever seen
//It will only get worse as time goes on. ^ This was written before I added items.
//It has gotten so much worse. This is written after all items and guards have been implemented.
void Game::SetupRooms()
{
	int* tiles00 = new int[16*16]{
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		2,1,1,1,1,1,1,1,0,2,0,0,0,0,0,2,
		2,1,0,0,0,0,0,0,0,2,0,0,0,0,0,2,
		2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
		2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,
		2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,1,
		2,0,2,0,2,0,2,1,1,2,0,0,0,0,0,2,
		2,0,2,0,2,0,2,0,0,2,0,0,0,0,0,2,
		2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
		2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,2,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
		2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,
		2,0,2,0,2,0,2,0,0,2,0,0,0,0,0,2,
		2,0,2,0,2,0,2,1,1,2,0,0,0,0,0,2,
		2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,
	};

	rooms[0][0].m_tiles = tiles00;
	rooms[0][0].m_items.push_back(new Coin(Vec2I(4, 1)));
	rooms[0][0].m_items.push_back(new Ham(Vec2I(7, 14)));
	rooms[0][0].m_items.push_back(new SightPotion(Vec2I(8, 6)));

	//rooms[0][0].m_items.push_back(new Door(Vec2I(12, 0))); Having a locked door was misleading to the player and only 1 was present so I got rid of it.
	rooms[0][0].m_items.push_back(new Door(Vec2I(15, 5), false, Vec2I(1,0), Vec2I(1,5), 1));
	rooms[0][0].m_items.push_back(new Door(Vec2I(12, 15), false, Vec2I(0,1), Vec2I(12, 1), 2));
	

	rooms[0][0].m_items.push_back(new Toilet(Vec2I(1, 6)));
	rooms[0][0].m_items.push_back(new Toilet(Vec2I(3, 6), true));
	rooms[0][0].m_items.push_back(new Toilet(Vec2I(5, 6)));

	rooms[0][0].m_items.push_back(new Toilet(Vec2I(1, 14), true));
	rooms[0][0].m_items.push_back(new Toilet(Vec2I(3, 14)));
	rooms[0][0].m_items.push_back(new Toilet(Vec2I(5, 14)));

	
	//Guards
	rooms[0][0].m_guards.push_back(new Guard(Vec2I(12, 5), 2));
	rooms[0][0].m_guards.back()->m_patrolRoute = new Vec2I[1]{ Vec2I(12, 5) };
	rooms[0][0].m_guards.back()->m_patrolPointCount = 1;




	int* tiles01 = new int[16 * 16]{
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,
		2,1,0,0,0,0,0,0,0,0,0,2,0,0,1,2,
		2,1,0,0,1,1,1,0,0,0,0,0,0,0,1,2,
		2,0,0,0,1,1,1,0,0,0,0,2,0,0,1,2,
		1,0,0,0,0,0,0,0,0,0,0,2,1,1,1,2,
		2,1,1,1,1,1,1,1,1,0,0,2,2,2,2,2,
		2,1,0,0,0,0,0,0,0,0,0,1,1,1,1,2,
		2,1,0,0,1,1,1,1,2,0,0,0,0,0,1,2,
		2,1,0,0,1,1,1,1,2,0,0,0,0,0,1,2,
		2,1,0,0,0,0,0,0,0,0,0,1,1,0,1,2,
		2,1,0,0,1,1,1,1,2,0,0,1,1,0,1,2,
		2,1,0,0,1,1,1,1,2,0,0,1,1,0,1,2,
		2,1,0,0,0,0,0,0,0,0,0,0,0,0,1,2,
		2,1,1,1,1,1,1,1,1,0,0,0,0,0,1,2,
		2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,
	};

	rooms[0][1].m_tiles = tiles01;
	rooms[0][1].m_items.push_back(new Ham(Vec2I(5, 3)));
	rooms[0][1].m_items.push_back(new Ham(Vec2I(14, 4)));
	rooms[0][1].m_items.push_back(new ManaPotion(Vec2I(4, 9)));
	rooms[0][1].m_items.push_back(new SightPotion(Vec2I(3, 1)));
	rooms[0][1].m_items.push_back(new Coin(Vec2I(6, 12)));
	rooms[0][1].m_items.push_back(new Coin(Vec2I(1, 13)));
	rooms[0][1].m_items.push_back(new Ham(Vec2I(14, 8)));
	rooms[0][1].m_items.push_back(new Ham(Vec2I(13, 1)));
	rooms[0][1].m_items.push_back(new Coin(Vec2I(12, 11)));

	rooms[0][1].m_items.push_back(new Door(Vec2I(0, 5), false, Vec2I(0, 0), Vec2I(14, 5), 3));
	rooms[0][1].m_items.push_back(new Door(Vec2I(13, 15), false, Vec2I(1, 1), Vec2I(13, 1), 2));
	rooms[0][1].m_guards.push_back(new Guard(Vec2I(10, 12), 0));
	rooms[0][1].m_guards.back()->m_patrolRoute = new Vec2I[4]{ Vec2I(9,13), Vec2I(9,7), Vec2I(3,7), Vec2I(3,13)}; 
	//Okay this guy just has a super weird route. I think there's something wrong with my a*. It is a nonsense route but hey its regular so whatever.
	rooms[0][1].m_guards.back()->m_patrolPointCount = 4;
	

	int* tiles10 = new int[16 * 16] {
		2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
		2,0,0,0,0,0,0,0,0,1,1,0,0,0,0,2,
		2,1,1,0,2,0,0,0,2,1,1,0,0,0,0,1,
		2,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,
		2,0,0,0,0,1,1,0,0,0,0,0,0,0,0,2,
		2,0,0,0,0,0,0,0,0,1,1,0,1,1,1,2,
		2,1,1,0,2,0,0,0,2,1,1,0,1,0,0,2,
		2,1,1,0,0,1,1,0,0,0,0,0,1,0,0,2,
		2,0,0,0,0,1,1,0,0,0,0,0,1,0,0,1,
		2,0,0,0,0,0,0,0,0,1,1,0,1,0,0,2,
		2,1,1,0,2,0,0,0,2,1,1,0,1,1,0,2,
		2,1,1,0,0,1,1,0,0,0,0,0,0,0,0,2,
		2,0,0,0,0,1,1,0,1,1,0,0,0,0,0,2,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
		2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,
		};

	rooms[1][0].m_tiles = tiles10;
	rooms[1][0].m_items.push_back(new Door(Vec2I(12, 0), false, Vec2I(0, 0), Vec2I(12, 14), 0));
	rooms[1][0].m_items.push_back(new Door(Vec2I(15, 3), false, Vec2I(1, 1), Vec2I(1, 3), 1));
	rooms[1][0].m_items.push_back(new Door(Vec2I(15, 4), false, Vec2I(1, 1), Vec2I(1, 4), 1));
	rooms[1][0].m_items.push_back(new Door(Vec2I(15, 9), false, Vec2I(1, 1), Vec2I(1, 9), 1));
	//SetupExitDoorClass
	rooms[1][0].m_items.push_back(new ExitDoor(Vec2I(8, 15)));
	rooms[1][0].m_items.push_back(new ExitDoor(Vec2I(9, 15)));

	rooms[1][0].m_items.push_back(new Diamond(Vec2I(1, 11)));
	rooms[1][0].m_items.push_back(new ManaPotion(Vec2I(12, 8)));
	rooms[1][0].m_items.push_back(new Coin(Vec2I(9, 13)));
	rooms[1][0].m_items.push_back(new Ham(Vec2I(5, 8)));
	rooms[1][0].m_items.push_back(new Coin(Vec2I(2, 7)));
	rooms[1][0].m_items.push_back(new Coin(Vec2I(10, 2)));
	rooms[1][0].m_items.push_back(new Diamond(Vec2I(6, 5)));
	rooms[1][0].m_items.push_back(new SightPotion(Vec2I(1, 4)));
	rooms[1][0].m_items.push_back(new Coin(Vec2I(6, 12)));


	rooms[1][0].m_guards.push_back(new Guard(Vec2I(13, 9), 3));
	rooms[1][0].m_guards.back()->m_patrolRoute = new Vec2I[1]{ Vec2I(13,9) };
	rooms[1][0].m_guards.back()->m_patrolPointCount = 1;

	rooms[1][0].m_guards.push_back(new Guard(Vec2I(9, 5), 1));
	rooms[1][0].m_guards.back()->m_patrolRoute = new Vec2I[4]{ Vec2I(11,5), Vec2I(7,5), Vec2I(7,12), Vec2I(11,12) };
	rooms[1][0].m_guards.back()->m_patrolPointCount = 4;

	rooms[1][0].m_guards.push_back(new Guard(Vec2I(3, 8), 0));
	rooms[1][0].m_guards.back()->m_patrolRoute = new Vec2I[2]{ Vec2I(3,3), Vec2I(3, 12) };
	rooms[1][0].m_guards.back()->m_patrolPointCount = 2;

	int* tiles11 = new int[16 * 16] {
		2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
		2,0,0,0,0,0,0,0,0,2,1,1,0,1,1,2,
		1,0,0,0,0,0,1,1,0,2,1,1,0,1,1,2,
		1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,2,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
		2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,2,
		2,0,0,1,0,0,0,0,0,2,1,1,0,1,1,2,
		2,0,0,1,0,0,1,1,0,2,1,1,0,1,1,2,
		1,0,0,1,0,0,1,1,0,0,0,0,0,0,0,2,
		2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,2,
		2,0,1,1,0,0,0,0,0,0,0,0,0,0,0,2,
		2,0,0,0,0,0,0,0,0,2,1,1,0,1,1,2,
		2,0,0,0,0,0,1,1,0,2,1,1,0,1,1,2,
		2,0,0,0,0,0,1,1,0,0,0,0,0,0,0,2,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	};

	rooms[1][1].m_tiles = tiles11;

	rooms[1][1].m_items.push_back(new Door(Vec2I(13, 0), false, Vec2I(1, 0), Vec2I(13, 14), 0));
	rooms[1][1].m_items.push_back(new Door(Vec2I(0, 3), false, Vec2I(0, 1), Vec2I(14, 3), 3));
	rooms[1][1].m_items.push_back(new Door(Vec2I(0, 4), false, Vec2I(0, 1), Vec2I(14, 4), 3));
	rooms[1][1].m_items.push_back(new Door(Vec2I(0, 9), false, Vec2I(0, 1), Vec2I(14, 9), 3));
	
	rooms[1][1].m_items.push_back(new Diamond(Vec2I(13, 13)));
	rooms[1][1].m_items.push_back(new Ham(Vec2I(10, 8)));
	rooms[1][1].m_items.push_back(new Coin(Vec2I(11, 7)));
	rooms[1][1].m_items.push_back(new Coin(Vec2I(7, 14)));
	rooms[1][1].m_items.push_back(new Diamond(Vec2I(6, 13)));
	rooms[1][1].m_items.push_back(new ManaPotion(Vec2I(2, 6)));
	rooms[1][1].m_items.push_back(new Coin(Vec2I(3, 8)));
	rooms[1][1].m_items.push_back(new SightPotion(Vec2I(3, 10)));
	rooms[1][1].m_items.push_back(new Diamond(Vec2I(6, 13)));
	rooms[1][1].m_items.push_back(new Ham(Vec2I(6, 8)));
	rooms[1][1].m_items.push_back(new Coin(Vec2I(10, 2)));
	
	
	
	rooms[1][1].m_guards.push_back(new Guard(Vec2I(10, 5), 3));
	rooms[1][1].m_guards.back()->m_patrolRoute = new Vec2I[2]{ Vec2I(9,5), Vec2I(14,5) };
	rooms[1][1].m_guards.back()->m_patrolPointCount = 2;

	rooms[1][1].m_guards.push_back(new Guard(Vec2I(4, 5), 3));
	rooms[1][1].m_guards.back()->m_patrolRoute = new Vec2I[2]{ Vec2I(4,4), Vec2I(4,12) };
	rooms[1][1].m_guards.back()->m_patrolPointCount = 2;

}

Room* Game::GetRoom(const int x, const int y) {
	if (x >= 0 && y >= 0 && x < MAPWIDTH && y < MAPHEIGHT) return &rooms[y][x];
	else return nullptr;
}

Room* Game::GetRoom(const Vec2I a_pos) {
	return GetRoom(a_pos.X, a_pos.Y);
}

Room* Game::GetCurrentRoom() {
	return GetRoom(currentRoomX, currentRoomY);
}

void Game::MoveRoom(int x, int y) {
	GetRoom(x,y)->Description();
	if (x < 0) x = 0;
	else if (x >= MAPWIDTH) x = MAPHEIGHT - 1;
	if (y < 0) y = 0;
	else if (y >= MAPHEIGHT) y = MAPHEIGHT - 1;

	currentRoomX = x;
	currentRoomY = y;
}

void Game::MoveRoom(Vec2I a_pos) {
	MoveRoom(a_pos.X, a_pos.Y);
}

Player* Game::GetPlayer() {
	return player;
}


bool Game::CheckClearLine(Vec2I start, Vec2I direction) {
	int x0 = start.X;
	int y0 = start.Y;
	int x1 = direction.X;
	int y1 = direction.Y;


	//Make sure the line draws from left to right.
	if (std::abs(start.X) < std::abs(direction.X)) {
		x0 = start.X;
		y0 = start.Y;
		x1 = direction.X;
		y1 = direction.Y;
	}
	else {
		x0 = direction.X;
		y0 = direction.Y;
		x1 = start.X;
		y1 = start.Y;
	}
	return false;
}


//Does all slopes and directions. Has replaced the old functions.
//Returns a new list of Vec2I positions.
bool Game::PlotLine(Vec2I start, Vec2I end) {
	int x0 = start.X;
	int y0 = start.Y;
	int x1 = end.X;
	int y1 = end.Y;
	
	
	
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int error = dx + dy;
	//int xi = 1; // This determines whether the next y is up or down.


	while (true) {
		//Plot thing.
		if (LineDrawFunction(Vec2I(x0, y0))) return false;
		if (x0 == x1 && y0 == y1) break;
		int e2 = error * 2;
		if (e2 >= dy) {
			if (x0 == x1) break;
			error += dy;
			x0 += sx;
		}
		if (e2 <= dx) {
			if (y0 == y1) break;
			error += dx;
			y0 += sy;
		}
	}
	return true;
}




//These are all very slightly different

bool GetSightBlocked(Vec2I a_position) {

	if (Game::GetInstance()->GetCurrentRoom()->GetTileState(a_position) == 2) return true;
	return false;
}

//Players and guards won't cast shadows now too. Can be reversed with GetMovementBlocked.
bool GetLightBlocked(Vec2I a_position) {

	Game* gamePtr = Game::GetInstance();
	gamePtr->GetCurrentRoom()->SetTileIsLit(a_position, true);

	if (gamePtr->GetCurrentRoom()->GetTileState(a_position) != 0){
		return true;
	}

	return false;
}

bool Game::GetMovementBlocked(Vec2I a_position) {

	return GetMovementBlocked(a_position, 0);
}

//Allows up to a_freeTiles to be moved through.
//i.e. a value of 0 means obstacles block.
//a value of 1 lets the player pass through/over obstacles
//a value of 2 or higher lets the player noclip.
bool Game::GetMovementBlocked(Vec2I a_position, int a_freeTiles) {

	if (GetCurrentRoom()->GetTileState(a_position) > a_freeTiles || player->GetPosition() == a_position)
	{
		return true;
	}

	for (Guard* guard : GetCurrentRoom()->m_guards) {
		if (guard->GetPosition() == (a_position)) {
			return true;
		}
	}
	return false;
}

bool Game::GetGuardMovementBlocked(Guard* a_guardPtr, Vec2I a_position) {

	if (GetCurrentRoom()->GetTileState(a_position) > 0)
	{
		return true;
	}

	//for (Guard* guard : GetCurrentRoom()->m_guards) {
	//	if (guard->GetPosition() == (a_position) && a_guardPtr != guard) {
	//		return true;
	//	}
	//}
	return false;
}

void Game::EmitNoise(Vec2I a_position) {
	for (Guard* guard : GetCurrentRoom()->m_guards) {
		if (guard->GetState() != 4) {
			guard->GeneratePath(a_position);
			guard->SetState(guard->Investigating);
		}
	}
}

void Game::GameOver(bool failed) {
	this->failed = failed;
	isPlaying = false;

}