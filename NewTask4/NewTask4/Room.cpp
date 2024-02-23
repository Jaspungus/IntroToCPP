#include "Room.h"

Room::Room() {
	m_description = "An empty Room";
	m_item = nullptr;
	m_gnomeCount = 0;
}

Room::Room(const char* a_description)
{
	m_description = String(a_description);
	m_item = nullptr;
	m_gnomeCount = 0;

}

Room::Room(const char* a_description, Item* a_item)
{
	m_description = String(a_description);
	m_item = a_item;
	m_gnomeCount = 0;
}

Room::Room(const char* a_description, Item* a_item, int a_gnomeCount)
{
	m_description = String(a_description);
	m_item = a_item;
	m_gnomeCount = m_gnomeCount;
}

Room::~Room()
{

}

void Room::Description() const
{
	std::cout << m_description.CStr() << std::endl;
}


Gnome* Room::GetGnome(String str) {
	for (Gnome gnome : m_gnomes) {
		if (str == gnome.m_name || str == gnome.m_description) return &gnome;
	}
	return NULL;
}

list<Gnome> Room::GetGnomeList()
{
	return m_gnomes;
}

int Room::GetDoor(int a_direction)
{
	if (a_direction >= 0 && a_direction <= 3) return m_doors[a_direction];
	else return -1;
}

void Room::SetDoor(int a_direction, int a_state)
{
	if (a_state >= 0 && a_state <= 2) m_doors[a_direction] = a_state;
	for (int i : m_doors) {
		std::cout << i << std::endl;
	}
}

