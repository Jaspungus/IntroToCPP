#include "Player.h"

Player::Player() {

}

Player::Player(String a_name) {
	m_name = a_name;
}

Player::~Player() {

}


bool Player::FindSpell(String spell) {

	for (String name : spells) {
		if (name == spell) return true;
	}

	return false;
}

void Player::ListSpells() {

}

void Player::UseItem(String a_item)
{
	for (Item item : inventory)
	{
		if (item.GetName() == a_item) item.Use();
	}
}

void Player::ListItems()
{
	for (Item item : inventory) {
		std::cout << item.GetName().CStr() << std::endl;
	}
}

String Player::GetName() {
	return m_name;
}

void Player::SetName(String a_name) {
	m_name = a_name;
}
