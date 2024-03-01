#include "Room.h"
#include "Game.h"

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
	//delete[] m_guards;
	delete m_description;
}

void Room::Description() const
{
	Game::GetInstance()->lastActionText += *m_description;
	for (Item* itemPtr : m_items) {
		Game::GetInstance()->lastActionText += "\n";
		itemPtr->Description();
	}
}


const int Room::GetTileIsLit(Vec2I a_position) const 
{
	return m_litStates[a_position.Y][a_position.X];
}

void Room::SetTileIsLit(Vec2I a_position, bool a_isLit) {
	m_litStates[a_position.Y][a_position.X] = a_isLit;
}

const int Room::GetTileState(Vec2I a_position) const 
{
	return m_tiles[a_position.Y * ROOMWIDTH + a_position.X];
}

Item* Room::GetItem(Vec2I a_position) 
{
	for (Item* item : m_items) {
		if (item->GetPosition() == a_position) return item;
	}
	return nullptr;
}

Item* Room::GetItem(size_t index)
{
	if (index > 0 && index < m_items.size())
	{
		size_t i = 0;
		for (Item* item : m_items) {
			if (i == index) return item;
			i++;
		}
	}
	return nullptr;
}