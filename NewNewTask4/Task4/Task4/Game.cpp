#include "Game.h"
#include "Vec2.h"
#include <stdlib.h>

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
	std::cout << "Enter Player Name" << std::endl;

	String command;
	String commandBuffer;
	//command.ReadFromConsole();

	//for (int i = 0; i < 2; i++) {
	//	for (int j = 0; j < 2; j++)
	//	{
	//		rooms[i][j].Description();
	//	

	//	}
	//}


	//for (int i = 0; i < 16; i++) {
	//	for (int j = 0; j < 16; j++)
	//	{
	//		std::cout << String::IntToASCII(i * 16 + j).CharacterAt(0);


	//	}
	//	std::cout << std::endl;
	//}

	isPlaying = true;

	while (isPlaying) {

		//If the last action was successful, use up a turn and update enemies.
		if (useTurn) {
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
			if (pathBlocked)
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
			if (direction == Vec2I::Zero()) direction = player->GetDirectionVector();
			else player->FaceDirection(direction);

			//Check if an item is present.
			Item* itemPtr = rooms[currentRoomY][currentRoomX].GetItem(player->GetPosition() + direction);
			if (itemPtr != nullptr) {

				//Repeated once. Could make function.
				//Adds value of item. Removes it from the playspace and adds to inventory.

				
				if (itemPtr->Take()) useTurn = true;
			}

			//If there is nothing present, state so. Don't use turn.
			else 
			{
				lastActionText = "Nothing to pick up.";

			}
		}

		//Using Item/Object in environment. Only works on objects within 1 tile.
		//If no direction is entered it will use the direction the player is facing.
		else if (command.Find("use") != -1 || command.Find("interact") != -1) {
			//If a direction is added, use that and turn player. Otherwise use player direction.
			Vec2I direction = GetDirectionFromInput(command);
			if (direction == Vec2I::Zero()) direction = player->GetDirectionVector();
			else player->FaceDirection(direction);

			//If there is an item present at the position 1 in that direction
			Item* itemPtr = rooms[currentRoomY][currentRoomX].GetItem(player->GetPosition() + direction);
			if (itemPtr != nullptr) {
				//If the item is imovable interact with it, otherwise pick it up first.
				if (itemPtr->GetStationary()) {
					itemPtr->Use();
				}
				else {
				/*	itemPtr->Take();
					player->SetCoinCount(player->GetCoinCount() + itemPtr->GetValue());
					rooms[currentRoomY][currentRoomX].m_items.remove(itemPtr);
					player->inventory.push_back(itemPtr);*/
					lastActionText = itemPtr->m_name;
				}
				useTurn = true;
			}
			//If there is nothing present, state so. Don't use turn.
			else
			{
				lastActionText = "Nothing to interact with.";
			}
		}

		//Add compatibility to look at items in range.
		else if (int lookIndex = command.Find("look") != -1 || command.Find("face") != -1) {
			
			bool itemFound = false;
			if (lookIndex != -1) {
				for (Item* itemPtr : GetCurrentRoom()->m_items) {
					if (itemPtr != nullptr) {
						//If within range, check if the name matches.
						if (player->GetPosition().DistanceSquared(itemPtr->GetPosition()) < pow(player->GetSight(), 2))
						{
							if (command.Substring(lookIndex + 4, command.Length()).Find(itemPtr->GetName()))
							{
								itemPtr->Description();
								itemFound = true;
								break;
							}
						}
					}
				}
			}

			if (!itemFound) {
				Vec2I direction = GetDirectionFromInput(command);
				Item* itemPtr = GetCurrentRoom()->GetItem(player->GetPosition() + direction);
				if (itemPtr != nullptr) {
					itemPtr->Description();
					player->FaceDirection(direction);
				}

				else
				{
					lastActionText = "There is nothing there.";
					player->FaceDirection(direction);
				}
			}
		}

		//Using items

		else if (int useIndex = command.Find("use") != -1) {
			player->UseItem(command);
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
					for (i; i <= 3; i++) {
						//Player pos, plus direction * i+1
						//At i = 0, check 1 tile in front. At i = 5, check the 6th tile.
						if (GetMovementBlocked(player->GetPosition() + (player->GetDirectionVector() * (i + 1)), 1)) {
							//Wall hit
							wallHit = true;
							teleport = true;
							break;
						}
						if (i == 3) { teleport = true; }
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
						lastActionText = "You successfully cast teleport.";
						useTurn = true;
					}

					else {
						lastActionText = "You cast teleport but there's nowhere to go.";
					}

					//int i = 0;
					//bool hasHitWall = false;
					//for (i = 0; i < 3; i++) {
					//	if (GetMovementBlocked(player->GetPosition() + (player->GetDirectionVector() * (i + 1)), 1))
					//	{
					//		hasHitWall = true;
					//		//break;
					//	}
					//}

					//if (i == 0) {
					//	lastActionText = "You cast teleport but theres nowhere to go.";
					//}
					//
					//else {
					//	for (i; i > 0; i--) {
					//		if (!(GetMovementBlocked(player->GetPosition() + (player->GetDirectionVector() * (i)), 0)))
					//		{
					//			player->SetPosition(player->GetPosition() + (player->GetDirectionVector() * i));
					//			player->SetMana(player->GetMana() - 5);
					//			lastActionText = "You successfully cast teleport.";
					//			useTurn = true;
					//		}
					//	}
					//}
				}
				else {
					lastActionText = "You do not have enough mana to cast teleport.";
				}
			}
			else if (command.Find(castIndex + 4, "Shock") != -1)
			{
				useTurn = true;
			}
			else if (command.Find(castIndex + 4, "Illusion") != -1)
			{
				useTurn = true;
			}
			else if (command.Find(castIndex + 4, "Turn Pink") != -1)
			{
 				player->SetColour(177);
				lastActionText = "You cast \"Turn Pink\" and turn a pinkish hue.";
				useTurn = true;
			}
			else if (command.Find(castIndex + 4, "Yellow") != -1)
			{
				std::cout << "You cast \"Yellow\"" << std::endl;
				useTurn = true;
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

	}
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

	HUD += "\t\033[38;5;178mo Coins: ";
	HUD.Append(String::IntToString(player->GetCoinCount()));
	HUD += "\033[m ";
	
	HUD += "\t\033[38;5;39m";
	HUD.Append(String::IntToASCII(15)); 
	HUD += " Mana: ";
	HUD.Append(String::IntToString(player->GetMana()));
	HUD += "\033[m ";
	


	HUD.WriteToConsole();


	LineDrawFunction = &GetLightBlocked;
	for (Guard* guardPtr : currentRoomPtr->m_guards) 
	{
		if (guardPtr != nullptr) 
		{
			guardPtr->UpdateConePoints();
			for (int i = 0; i < guardPtr->GetViewWidth(); i++) 
			{
				PlotLine(guardPtr->GetPosition() + guardPtr->GetDirectionVector(), guardPtr->GetConePoints()[i]);
			}
		}
	}

	//Printing the map
	String printParams = "\n\n";
	Vec2I currentTilePos = Vec2I(0,0);
	for (currentTilePos.Y = 0; currentTilePos.Y < currentRoomPtr->ROOMHEIGHT; currentTilePos.Y++) {
		//int mod2 = y % 5;
		//std::cout << currentTilePos.Y << ": ";
		printParams += "\t";
		for (currentTilePos.X = 0; currentTilePos.X < currentRoomPtr->ROOMWIDTH; currentTilePos.X++)
		{
			
			//std::cout << currentRoomPtr->GetTile(Vec2I(x, y)) << std::endl;
			int state = currentRoomPtr->GetTileState(currentTilePos);//currentRoomPtr->GetTile(Vec2I(x, y))->GetState();
			bool lit = currentRoomPtr->GetTileIsLit(currentTilePos);// currentRoomPtr->GetTile(Vec2I(x, y))->GetIsLit();
			currentRoomPtr->SetTileIsLit(currentTilePos, false);
			bool empty = true;
			printParams += "\033[48;5;";



			//Check if the player can see the tile.
			LineDrawFunction = &GetSightBlocked;
			if (!PlotLine(player->GetPosition(),currentTilePos)) {
				
				printParams += "m   \033[m";
				continue;
				//state = 2; //This makes it so icons still appear.
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

						//This also needs to draw their sight cones.
			//LineDrawFunction = &IsTileBlockedSetLit;
			for (Guard* guardPtr : currentRoomPtr->m_guards) {
				if (empty && guardPtr != nullptr) {
					if (currentTilePos == guardPtr->GetPosition()) {
						if (PlotLine(guardPtr->GetPosition(), player->GetPosition())
							&& currentRoomPtr->GetTileIsLit(player->GetPosition()))
						{ 
							//Add logic to spot player
						}
						printParams += ";38;5;";
						printParams += String::IntToString(guardPtr->GetColour());
						printParams += "m  ";
						printParams[printParams.Length() - 1] = guardPtr->m_icon;
						empty = false;
					}
				}
			}

			if (empty) {
				printParams += "m  ";
			}

			printParams += " \033[m";
		}
		//I made this print line by line to reduce the string length & thus memory usage(?)
		printParams.WriteToConsole(); 
		printParams = "";

	}
	lastActionText.WriteToConsole();
}

//The most disgusting setup you've ever seen
//It will only get worse as time goes on. ^ This was written before I added items.
void Game::SetupRooms()
{
	int* tiles = new int[16*16]{
		2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,
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

	rooms[0, 0]->m_tiles = tiles;
	rooms[0, 0]->m_items.push_back(new Coin(Vec2I(4, 1)));
	rooms[0, 0]->m_items.push_back(new ManaPotion(Vec2I(1, 3)));
	rooms[0, 0]->m_items.push_back(new Door(Vec2I(12, 0)));
	rooms[0, 0]->m_items.push_back(new Door(Vec2I(15, 5), false, Vec2I(0,1), Vec2I(1,5), 1));
	rooms[0, 0]->m_guards.push_back(new Guard(Vec2I(12, 5), 2));

	tiles = new int[16 * 16]{
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

	rooms[0, 1]->m_tiles = tiles;
	rooms[0, 1]->m_items.push_back(new Coin(Vec2I(4, 1)));
	rooms[0, 1]->m_items.push_back(new ManaPotion(Vec2I(1, 3)));
	rooms[0, 1]->m_items.push_back(new Door(Vec2I(0, 5), false, Vec2I(0, 0), Vec2I(14, 5), 1));
	rooms[0, 1]->m_guards.push_back(new Guard(Vec2I(10, 12), 0));
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

//Fundamental flaw in the line drawing logic. Half the time (based on the two coords)
//It will draw from the target to the origin, causing strange shadows. FIX
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