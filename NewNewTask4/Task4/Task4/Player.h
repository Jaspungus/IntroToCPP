#pragma once
#include "String.h"
#include "Item.h"
#include <list>
#include <vector>
#include "Vec2.h"
using namespace std;

class Player
{
private:
	vector<String> spells = { "Sense", "Shock", "Teleport", "Turn Pink", "Yellow" };

	Vec2I m_position;
	int m_direction = 0;
	char m_icon = String::IntToASCII(30)[0];// '^';
	int m_colour = 40;
	//This is the range the player can see at.
	int m_sightRange = 8;
	//This represents the value of the current haul.
	int m_coinCount = 0;
	//Show these as like 10x less. 
	int m_mana = 25;
	int m_maxMana = 25;

public:
	list<Item*> inventory;

public:
	Player();
	Player(Vec2I a_pos);
	~Player();

public:
	bool FindSpell(String spell);
	String ListSpells();
	String ExplainSpell(String spell);

	bool UseItem(int startIndex, String a_item);
	String ListItems();

	void Move(const int x, const int y);
	void Move(const Vec2I direction);

	const Vec2I GetPosition() const;
	void SetPosition(const Vec2I a_position);
	void SetPosition(const int x, const int y);

	const int GetDirection() const;
	const Vec2I GetDirectionVector() const;
	void SetDirection(int a_direction);
	void FaceDirection(Vec2I a_direction);

	const char* GetIcon() const;

	const int GetColour() const;
	void SetColour(const int a_colourCode);

	const int GetSight() const;
	void SetSight(const int a_sight);

	const int GetCoinCount() const;
	void SetCoinCount(int a_coins);

	const int GetMana() const;
	void SetMana(int a_mana);
};

