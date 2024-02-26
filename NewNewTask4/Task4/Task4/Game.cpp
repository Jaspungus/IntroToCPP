#include "Game.h"
#include "Vec2.h"
#include <stdlib.h>

Game::Game() {
	player = new Player(Vec2I(3,3));
	SetupRooms();
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
			
			//If the space is free, move the player there.
			//Diagonals work and only use one turn.
			if (rooms[currentRoomY][currentRoomX].GetTileState(player->GetPosition() + direction) == 0)
			{
				player->Move(direction);
				useTurn = true;
			}
			//If the player cannot move that way, state so. Don't use turn.
			else {
				player->FaceDirection(direction);
				lastActionText = "You cannot go that way.";
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
		else if (int lookIndex = command.Find("look") != -1) {
			
			bool itemFound = false;
			for (size_t i = 0; i < rooms[currentRoomY][currentRoomX].itemCount; i++) {
				Item* itemPtr = rooms[currentRoomY][currentRoomX].GetItem(i);
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
			
			if (!itemFound) {
				Vec2I direction = GetDirectionFromInput(command);
				Item* itemPtr = rooms[currentRoomY][currentRoomX].GetItem(player->GetPosition() + direction);
				if (itemPtr != nullptr) {
					itemPtr->Description();
				}

				else
				{
					lastActionText = "There is nothing there.";
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
				useTurn = true;
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
	
	Room* currentRoomPtr = GetRoom(currentRoomX, currentRoomY);
	
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
			bool empty = true;
			printParams += "\033[48;5;";

			if (!IsLineClear(player->GetPosition(),currentTilePos)) {
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
			for (size_t i = 0; i < currentRoomPtr->guardCount; i++) {
				if (empty && currentRoomPtr->m_guards[i] != nullptr) {
					if (IsLineClear(currentTilePos, currentRoomPtr->m_guards[i]->GetPosition()))
					if (currentTilePos == currentRoomPtr->m_guards[i]->GetPosition()) {
						printParams += ";38;5;";
						printParams += String::IntToString(currentRoomPtr->m_guards[i]->GetColour());
						printParams += "m ";
						printParams += currentRoomPtr->m_guards[i]->GetIcon();
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
	rooms[0, 0]->m_items.push_back(new Door(Vec2I(15, 5), false, Vec2I(0,1), Vec2I(3,3), 1));

	tiles = new int[16 * 16]{
		2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,
		2,1,1,1,1,1,1,1,0,2,0,0,0,0,0,2,
		2,1,0,0,0,0,0,0,0,2,0,0,0,0,0,2,
		2,1,0,0,0,0,0,0,0,0,0,0,2,0,0,2,
		2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,
		2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,1,
		2,0,2,0,2,0,2,1,1,2,0,0,2,0,0,2,
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

	rooms[0, 1]->m_tiles = tiles;
	rooms[0, 1]->m_items.push_back(new Coin(Vec2I(4, 1)));
	rooms[0, 1]->m_items.push_back(new ManaPotion(Vec2I(1, 3)));
	rooms[0, 1]->m_items.push_back(new Door(Vec2I(12, 0)));
	rooms[0, 1]->m_items.push_back(new Door(Vec2I(15, 5), false, Vec2I(0, 0), Vec2I(3, 3), 1));

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

//Adjust this later to work for enemies too.
bool Game::IsLineClear(Vec2I a_start, Vec2I a_end)
{
	if (abs(a_end.Y - a_start.Y) < abs(a_end.X - a_start.X))
	{
		if (a_start.X > a_end.X)
		{
			return PlotLineLow(a_end, a_start);
		}
		else return PlotLineLow(a_start, a_end);
	}
	else 
	{
		if (a_start.Y > a_end.Y) {
			return PlotLineHigh(a_end, a_start);
		}
		else {
			return PlotLineHigh(a_start, a_end);
		}
	}
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

//For shallow slopes. Where Y will increase/decrease by only 1 value at a time.
//Y is a functoin of X
bool Game::PlotLineLow(Vec2I start, Vec2I end) {
	int dx = end.X - start.X;
	int dy = end.Y - start.Y;
	int yi = 1; // This determines whether the next y is up or down.
	
	if (dy < 0) {
		yi = -1;
		dy = -dy;
	}
	int D = (2 * dy) - dx; 
	//D returns a signed int. It is used to determine whether to stay at the same y
	//Or move according up/down according to yi
	int y = start.Y;

	for (int x = start.X; x < end.X; x++) {
		//Draw tile / return whatever.
		if (rooms[currentRoomY][currentRoomX].GetTileState(Vec2I(x, y)) == 2) return false;
		if (D > 0) {
			y = y + yi;
			D = D + (2 * (dy - dx));
		}
		else {
			D = D + 2 * dy;
		}
	}

	return true;
}

//For steep slopes where x is increasing by 1 or 2. 
//X is a function of Y.
//Returns a new list of Vec2I positions.
bool Game::PlotLineHigh(Vec2I start, Vec2I end) {
	int dx = end.X - start.X;
	int dy = end.Y - start.Y;
	int xi = 1; // This determines whether the next y is up or down.

	if (dx < 0) {
		xi = -1;
		dx = -dx;
	}
	int D = (2 * dx) - dy;
	//D returns a signed int. It is used to determine whether to stay at the same y
	//Or move according up/down according to yi
	int x = start.X;


	for (int y = start.Y; y < end.Y; y++) {
		//Draw tile / return whatever.
		if (rooms[currentRoomY][currentRoomX].GetTileState(Vec2I(x, y)) == 2) return false;
		if (D > 0) {
			x = x + xi;
			D = D + (2 * (dx - dy));
		}
		else {
			D = D + 2 * dx;
		}
	}

	return true;
}

