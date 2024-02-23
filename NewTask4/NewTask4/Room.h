#pragma once
#include "Item.h"
#include "Gnome.h"
#include <list>
using namespace std;


class Room
{
private:
	String m_description;

	int m_gnomeCount = 0;

	int m_doors[4] = { 0 };

public:
	Item* m_item;
	list<Gnome> m_gnomes;
public:
	Room();
	Room(const char* a_description);
	Room(const char* a_description, Item* a_item);
	Room(const char* a_description, Item* a_item, int a_gnomeCount);
	~Room();
	void Description() const;
	Gnome* GetGnome(String str);
	list<Gnome> GetGnomeList();

	//0,1,2,3 = n,e,s,w for direction. 0,1,3, = Wall, No wall, Locked Door
	int GetDoor(int a_direction);
	void SetDoor(int a_direction, int a_state);
};

