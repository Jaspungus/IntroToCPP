#pragma once
#include "Vec2.h"
#include <vector>
#include <set>
#include <stack>


#define MAPX 16
#define MAPY 16

class Guard;

struct Cell {
	Vec2I parentPos = Vec2I(-1, -1);
	int f = 0, g = 0, h = 0;
};

class AStarPathFinder
{
public:
	Cell cellDetails[MAPX][MAPY];

public:
	AStarPathFinder();
	~AStarPathFinder();

public:
	void TracePath(Guard* guardPtr, Vec2I a_destination);
	void AStarSearch(Guard* guardPtr, Vec2I a_source, Vec2I a_destination);

private:

	bool IsValid(Vec2I a_position);
	bool IsBlocked(Guard* guardPtr, Vec2I a_position);
	bool IsDestination(Vec2I a_position, Vec2I a_goal);
	int CalculateHeuristic(Vec2I a_position, Vec2I a_goal);

};

