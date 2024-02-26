#pragma once
#include "String.h"
#include "Vec2.h"

//#include "Player.h" //Okay literally cannot include a reference to player.
//Need it to be extern and fetch at runtime?

struct Item
{
public:
	String m_name = "";
	int colour = 0;
	char icon = 'o';

	bool stationary = false;
	Vec2I position = Vec2I(0,0);
	int value = 0;

public:
	Item();
	~Item();

public:
	const String GetName() const;
	const int GetColour() const;
	const char GetIcon() const;
	const bool GetStationary() const;
	const int GetValue() const;


	Vec2I GetPosition() const;
	void SetPosition(const Vec2I a_position);

	virtual void Description() const;
	virtual void Use();
	virtual bool Take();
};

