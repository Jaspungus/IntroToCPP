#pragma once
#include "Vec2.h"
#include "String.h"
#include "AStarPathFinder.h"
#include <stack>

class Guard
{
public:
	enum AIState {
		Calm,
		Investigating,
		Paranoid,
		Alert,
		Unconscious
	};

private:
	Vec2I m_position;
	int m_direction = 0;

	int m_colour = 93;
	// Change to 226 for investigating
	// 202 for paranoid 
	// 196 for alert
	
	int m_viewDistance = 8;
	int m_viewWidth = 5;
	Vec2I* m_conePoints = new Vec2I[m_viewWidth];
	
	//AI stuff
	AStarPathFinder* m_AStar = new AStarPathFinder();


	bool m_seesPlayer = false; //for if they have at some point seen the player.
	bool m_hasSeenPlayer = false;

	AIState m_state = Calm;
	//0 is calm. 
	//1 is for investigating a noise/sighting. 
	//2 is for paranoid after seeing an incapacitated guard
	//3 is when the player is in sight. Player gets 1 turn to escape.
	//4 is incapacitated

	Vec2I m_targetPosition = -Vec2I::One();

public:
	int m_patrolCurrentIndex = 0;
	int m_patrolPointCount = 0;
	Vec2I* m_patrolRoute = nullptr;



public:
	char m_icon = String::IntToASCII(30)[0]; //'^'
	std::stack<std::pair<int, int>> path;
	//God forbid I ask for help to fix something. 

public:
	Guard();
	Guard(Vec2I a_position);
	Guard(Vec2I a_position, int a_direction);
	~Guard();

public:

	const Vec2I GetPosition() const;
	void SetPosition(Vec2I a_position);
	void SetPosition(int x, int y);

	const int GetDirection() const;
	const Vec2I GetDirectionVector() const;
	void SetDirection(int a_direction);
	void FaceDirection(Vec2I a_direction);

	const char* GetIcon() const;
	const int GetColour() const;

	const int GetViewWidth() const;
	const Vec2I* GetConePoints() const;
	void UpdateConePoints();

	void UpdateState();
	void SetState(AIState state);
	void SetSeesPlayer(bool alert);
	int GetState();
	

	void GeneratePath(Vec2I a_destination);
};

