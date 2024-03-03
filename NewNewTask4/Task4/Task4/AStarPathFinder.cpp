#include "AStarPathFinder.h"
#include "Game.h"

AStarPathFinder::AStarPathFinder()
{
}

AStarPathFinder::~AStarPathFinder()
{
}


bool AStarPathFinder::IsValid(Vec2I a_position)
{
	if (a_position.X >= 0 && a_position.Y >= 0 && a_position.X < MAPX && a_position.Y < MAPY) return true;
	else return false;
}

bool AStarPathFinder::IsBlocked(Guard* guardPtr, Vec2I a_position)
{
	return Game::GetInstance()->GetGuardMovementBlocked(guardPtr, a_position);
}

bool AStarPathFinder::IsDestination(Vec2I a_position, Vec2I a_goal)
{
	return a_position == a_goal;
}

int AStarPathFinder::CalculateHeuristic(Vec2I a_position, Vec2I a_goal)
{
	return abs(a_position.X - a_goal.X) + abs(a_position.Y - a_goal.Y);
}



void AStarPathFinder::TracePath(Guard* guardPtr, Vec2I a_destination)
{
	int row = a_destination.X;
	int col = a_destination.Y;

	while (!guardPtr->path.empty()) {
		guardPtr->path.pop();
	}
	

	while (!(cellDetails[row][col].parentPos.X == row && cellDetails[row][col].parentPos.Y == col)) {
		guardPtr->path.push(make_pair(row, col));
		int temp_row = cellDetails[row][col].parentPos.X;
		int temp_col = cellDetails[row][col].parentPos.Y;
		row = temp_row;
		col = temp_col;
	}


	//This one was adding the starting position to the list. Which I kind of don't want. Otherwise guards become paralysed when the player remains in vision.
	//This is fine for just 1 turn. I want the player to realise they've been spotted before the guard moves. But staying completely still is dumb.
	//guardPtr->path.push(make_pair(row, col));
}

void AStarPathFinder::AStarSearch(Guard* guardPtr, Vec2I a_source, Vec2I a_destination)
{

	if (!IsValid(a_source)) { std::cout << "Source invalid." << std::endl; return; }
	if (!IsValid(a_destination)) { std::cout << "Destination invalid." << std::endl; return; }
	if (IsBlocked(guardPtr, a_source) || IsBlocked(guardPtr, a_destination)) { std::cout << "Source or destination blocked." << std::endl; return; }
	if (IsDestination(a_source, a_destination)) { std::cout << "Already at Destination" << std::endl; return; }

	//Closed list of all the tiles to ignore. This will start as empty. It is a 2D array the size of the map.
	bool closedList[MAPY][MAPX];
	memset(closedList, false, sizeof(closedList)); //?????

	//An array of the cell structure to hold informationa about each cells heuristic and whatever g is.
	//A 2D array the size of the map.

	//These are used to loop through the map.
	int i, j;
	//Consider changing to a Vec2I so I dont have to call the constructor every 2 lines.

	//vector<Vec2I> path;

	//Initialise each cell to 0

	for (i = 0; i < MAPY; i++) {
		for (j = 0; j < MAPX; j++) {
			cellDetails[i][j].f = INT_MAX;
			cellDetails[i][j].g = INT_MAX;
			cellDetails[i][j].h = INT_MAX;
			cellDetails[i][j].parentPos = -Vec2I::One();
		}
	}

	//Dude i dont know how this works
	i = a_source.X, j = a_source.Y;

	cellDetails[i][j].f = 0;
	cellDetails[i][j].g = 0;
	cellDetails[i][j].h = 0;
	cellDetails[i][j].parentPos = Vec2I(i,j);


	set<std::pair<int, std::pair<int,int>>> openList;

	openList.insert(make_pair(0, make_pair(i, j)));

	bool foundDest = false;

	while (!openList.empty()) {
		std::pair<int, std::pair<int, int>> p = *openList.begin();

		openList.erase(openList.begin());

		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;

		//        N
		//        |
		//W --- Cell --- E
		//		  |
		//		  S

		// fuck if i know 

		int gNew = 0, hNew = 0, fNew = 0;


		//North
		if (IsValid(Vec2I(i - 1, j))) {
			if (IsDestination(Vec2I(i - 1, j), a_destination))
			{
				cellDetails[i - 1][j].parentPos = Vec2I(i, j);
				//std::cout << "found it" << std::endl;
				//Trace path????
				foundDest = true;
				return;
			}

			else if (!closedList[i - 1][j] && !IsBlocked(guardPtr, Vec2I(i - 1, j))) {
				gNew = cellDetails[i][j].g + 1;
				hNew = CalculateHeuristic(Vec2I(i - 1, j), a_destination);
				fNew = gNew + hNew;
			//	if (gNew < 0) gNew = INT_MAX;
			//	if (fNew < 0) fNew = INT_MAX;

				//If it is not on the open list, add it and make the current square it's parent.
				//If record f,g,h
				//OR
				//If it is on the list, check if the path to that square is better, measuring with f.

				if (cellDetails[i - 1][j].f == INT_MAX || cellDetails[i - 1][j].f > fNew) {
					openList.insert(make_pair(fNew, make_pair(i - 1, j)));

					cellDetails[i - 1][j].f = fNew;
					cellDetails[i - 1][j].g = gNew;
					cellDetails[i - 1][j].h = hNew;
					cellDetails[i - 1][j].parentPos = Vec2I(i, j);
				}
			}
		}

		//South
		if (IsValid(Vec2I(i + 1, j))) {
			if (IsDestination(Vec2I(i + 1, j), a_destination))
			{
				cellDetails[i + 1][j].parentPos = Vec2I(i, j);
				//std::cout << "found it" << std::endl;
				//Trace path????
				foundDest = true;
				return;
			}

			else if (!closedList[i + 1][j] && !IsBlocked(guardPtr, Vec2I(i + 1, j))) {
				gNew = cellDetails[i][j].g + 1;
				hNew = CalculateHeuristic(Vec2I(i + 1, j), a_destination);
				fNew = gNew + hNew;
			//	if (gNew < 0) gNew = INT_MAX;
			//	if (fNew < 0) fNew = INT_MAX;

				//If it is not on the open list, add it and make the current square it's parent.
				//If record f,g,h
				//OR
				//If it is on the list, check if the path to that square is better, measuring with f.

				if (cellDetails[i + 1][j].f == INT_MAX || cellDetails[i + 1][j].f > fNew) {
					openList.insert(make_pair(fNew, make_pair(i + 1, j)));

					cellDetails[i + 1][j].f = fNew;
					cellDetails[i + 1][j].g = gNew;
					cellDetails[i + 1][j].h = hNew;
					cellDetails[i + 1][j].parentPos = Vec2I(i, j);
				}
			}
		}

		//I had to do some bugfixing here (was missetting parentpos) And I think this might actually be south. Which would make sense because my coords are not in 2D array form.
		//East
		if (IsValid(Vec2I(i, j + 1))) {
			if (IsDestination(Vec2I(i, j + 1), a_destination))
			{
				cellDetails[i][j + 1].parentPos = Vec2I(i, j);
				//std::cout << "found it" << std::endl;
				//Trace path????
				foundDest = true;
				return;
			}

			else if (!closedList[i][j + 1] && !IsBlocked(guardPtr, Vec2I(i, j + 1))) {
				gNew = cellDetails[i][j + 1].g + 1;
				hNew = CalculateHeuristic(Vec2I(i, j + 1), a_destination);
				fNew = gNew + hNew;
				//if (gNew < 0) gNew = INT_MAX;
				//if (fNew < 0) fNew = INT_MAX;

				//If it is not on the open list, add it and make the current square it's parent.
				//If record f,g,h
				//OR
				//If it is on the list, check if the path to that square is better, measuring with f.

				if (cellDetails[i][j + 1].f == INT_MAX || cellDetails[i][j + 1].f > fNew) {
					openList.insert(make_pair(fNew, make_pair(i, j + 1)));

					cellDetails[i][j + 1].f = fNew;
					cellDetails[i][j + 1].g = gNew;
					cellDetails[i][j + 1].h = hNew;
					cellDetails[i][j + 1].parentPos = Vec2I(i, j);
				}
			}
		}

		//West
		if (IsValid(Vec2I(i, j - 1))) {
			if (IsDestination(Vec2I(i, j - 1), a_destination))
			{
				cellDetails[i][j - 1].parentPos = Vec2I(i, j);
				//std::cout << "found it" << std::endl; This works now.
				//Trace path????
				//Trace path????
				foundDest = true;
				return;
			}

			else if (!closedList[i][j - 1] && !IsBlocked(guardPtr, Vec2I(i, j - 1))) {
				gNew = cellDetails[i][j - 1].g + 1;
				hNew = CalculateHeuristic(Vec2I(i, j - 1), a_destination);
				fNew = gNew + hNew;
			//	if (gNew < 0) gNew = INT_MAX;
			//	if (fNew < 0) fNew = INT_MAX;

				//If it is not on the open list, add it and make the current square it's parent.
				//If record f,g,h
				//OR
				//If it is on the list, check if the path to that square is better, measuring with f.

				if (cellDetails[i][j - 1].f == INT_MAX || cellDetails[i][j - 1].f > fNew) {
					openList.insert(make_pair(fNew, make_pair(i, j - 1)));

					cellDetails[i][j - 1].f = fNew;
					cellDetails[i][j - 1].g = gNew;
					cellDetails[i][j - 1].h = hNew;
					cellDetails[i][j - 1].parentPos = Vec2I(i, j);
				}
			}
		}
	}
	//if (foundDest) {//didnt find it	}
	return;

}