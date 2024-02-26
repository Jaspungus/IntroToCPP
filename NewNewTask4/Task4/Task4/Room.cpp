#include "Room.h"

Room::Room() {
	m_description = new String("An empty Room");
	//m_items = nullptr;
	m_tiles = nullptr;

	//for (int y = 0; y < ROOMHEIGHT; y++) {
	//	for (int x = 0; x < ROOMWIDTH; x++) {
	//		m_tiles[y][x] = new int ;
	//	}
	//}

}

Room::Room(const char* a_description)
{
	m_description = new  String(a_description);
	//m_items = nullptr;
	m_tiles = nullptr;
}

//Room::Room(const char* a_description, Item** a_item)
//{
//	m_description = new String(a_description);
//	//m_items = a_item;
//	m_tiles = nullptr;
//}

Room::~Room()
{
	delete[] m_tiles;
	//delete[] m_items;
	delete[] m_guards;
	delete m_description;
}

void Room::Description() const
{
	m_description->WriteToConsole();
}


int Room::GetTileIsLit(Vec2I a_position)
{
	return m_litStates[a_position.Y][a_position.X];
}

int Room::GetTileState(Vec2I a_position)
{
	return m_tiles[a_position.Y * ROOMWIDTH + a_position.X];
}

Item* Room::GetItem(Vec2I a_position) {
	for (Item* item : m_items) {
		if (item->GetPosition() == a_position) return item;
	}
	return nullptr;
}

Item* Room::GetItem(size_t index) {
	if (index > 0 && index < itemCount)
	{
		size_t i = 0;
		for (Item* item : m_items) {
			if (i == index) return item;
			i++;
		}
	}
	return nullptr;
}