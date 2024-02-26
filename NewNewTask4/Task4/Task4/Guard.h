#pragma once
#include "Vec2.h"
#include "String.h"

class Guard
{
private:
	Vec2I m_position;
	Vec2I m_targetPosition;
	int m_direction;
	char m_icon = '^';
	int m_colour = 88;

	int m_state = 0; 
	//0 is calm. 
	//1 is for investigating a noise/sighting. 
	//2 is for paranoid after seeing an incapacitated guard
	//3 is when the player is in sight. Player gets 1 turn to escape.
	//4 is incapacitated

public:
	Guard();
	Guard(Vec2I a_position);
	~Guard();

public:

	const Vec2I GetPosition() const;
	void SetPosition(Vec2I a_position);
	void SetPosition(int x, int y);

	const int GetDirection() const;
	void SetDirection(int a_direction);

	const char* GetIcon() const;
	const int GetColour() const;


};

