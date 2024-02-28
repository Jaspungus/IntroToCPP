#pragma once
#include "Vec2.h"
#include "Game.h"
#include <vector>

#define MAPX 16
#define MAPY 16

//https://www.geeksforgeeks.org/a-search-algorithm/

struct Cell {
	Vec2I parentPos;
	int f, g, h;
};

typedef pair<int, int> Pair;
typedef pair<int, pair<int, int> > pPair;


bool IsValid(Vec2I a_position) {
	if (a_position.X >= 0 && a_position.Y >= 0 && a_position.X < MAPX && a_position.Y < MAPY) return true;
	else return false;
}

bool IsBlocked(Vec2I a_position) {
	return Game::GetInstance()->GetMovementBlocked(a_position);
}

bool IsDestination(Vec2I a_position, Vec2I a_goal) {
	return a_position == a_goal;
}

int calculateHeuristic(Vec2I a_position, Vec2I a_goal) {
	return abs(a_position.X - a_goal.X) + abs(a_position.Y - a_goal.Y);
}

void AStarSearch(int* tiles, Vec2I a_position, Vec2I a_destination) {

	bool closedList[MAPX][MAPY];
	memset(closedList, false, sizeof(closedList)); //?????

	Cell cellDetails[MAPX][MAPY];

	int i, j;

	vector<Vec2I> path;

	for (int i = 0; i < MAPX; i++) {
		for (int j = 0; j < MAPY; j++) {
			cellDetails[i][j].f = INT_MAX;
			cellDetails[i][j].g = INT_MAX;
			cellDetails[i][j].h = INT_MAX;
			cellDetails[i][j].parentPos = Vec2I::Zero();
		}
	}

	//Dude i dont know how this works
	i = a_position.X, j = a_position.Y;
	cellDetails[i][j].f = INT_MAX;
	cellDetails[i][j].g = INT_MAX;
	cellDetails[i][j].h = INT_MAX;
	cellDetails[i][j].parentPos = Vec2I::Zero();

	
	set<pPair> openList;

	openList.



}