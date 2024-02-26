#include "Player.h"
#include "Vec2.h"

Player::Player() {
	m_position = Vec2I(0, 0);
	m_direction = 0;
}


Player::Player(Vec2I a_pos) {
	m_position = a_pos;
	m_direction = 0;
}


Player::~Player() {

}


bool Player::FindSpell(String spell) {
	//Binary Search.
	return false;
}

void Player::ListSpells() {

}

void Player::UseItem(String a_item)
{
	for (Item* itemPtr : inventory)
	{
		if (a_item == itemPtr->GetName()) itemPtr->Use();
	}
}

String Player::ListItems()
{
	String output = "Inventory:";
	for (Item* itemPtr : inventory) {
		if (output.Find(itemPtr->m_name) == -1)
		{
			output += "\n";
			output += itemPtr->m_name;
		}
	}
	return output;
}

//Delete probably. These seem to not do anything really.
void Player::Move(const int x, const int y) {
	SetPosition(m_position.X + x, m_position.Y + y);
}

void Player::Move(const Vec2I direction)
{
	SetPosition(m_position + direction);
}

const Vec2I Player::GetPosition() const {
	return m_position;
}

void Player::SetPosition(const Vec2I a_position) {
	FaceDirection(a_position - m_position);

	m_position = a_position;
	if (m_position.X <= 0) m_position.X = 0;
	if (m_position.Y <= 0) m_position.Y = 0;
}

void Player::SetPosition(const int x, const int y) {

	SetPosition(Vec2I(x, y));
}

const int Player::GetDirection() const {
	return m_direction;
}

const Vec2I Player::GetDirectionVector() const {
	switch (m_direction) {
	case 0: {
		return Vec2I::Up();
		break;
		}
	case 1: {
		return Vec2I::Right();
		break;
		}
	case 2: {
		return Vec2I::Down();
		break;
		}
	case 3: {
		return Vec2I::Left();
		break;
		}
	}
	return Vec2I::Zero();
}

void Player::SetDirection(int a_direction) {
	if (a_direction < 0) m_direction = 0;
	else if (a_direction > 3) m_direction = 3;
	else m_direction = a_direction;

	switch (m_direction) {
		case 0: {
			m_icon = '^';
			break;
		}
		case 1: {
			m_icon = '>';
			break;
		}
		case 2: {
			m_icon = 'v';
			break;
		}
		case 3: {
			m_icon = '<';
			break;
		}
	}
}

void Player::FaceDirection(Vec2I a_direction)
{
	int newDir = -1;
	if (a_direction.Y < 0) newDir = 0;
	if (a_direction.Y > 0) newDir = 2;
	if (a_direction.X < 0) newDir = 3;
	if (a_direction.X > 0) newDir = 1;

	SetDirection(newDir);
}

const char* Player::GetIcon() const{
	return &m_icon;
}

const int Player::GetColour() const{
	return m_colour;
}

void Player::SetColour(const int a_colourCode){
	if (a_colourCode < 0) m_colour = 0;
	if (a_colourCode > 255) m_colour = 255;
	else m_colour = a_colourCode;
}

const int Player::GetSight() const {
	return m_sightRange;
}

void Player::SetSight(const int a_sight) {
	if (a_sight > 0) m_sightRange = a_sight;
	else m_sightRange = 1;
}

const int Player::GetCoinCount() const {
	return m_coinCount;
}

void Player::SetCoinCount(int a_coins) {
	if (a_coins <= 0) m_coinCount = 0;
	else m_coinCount = a_coins;
}

const int Player::GetMana() const {
	return m_mana;
}

void Player::SetMana(int a_mana) {
	if (a_mana <= 0) m_mana = 0;
	else if (a_mana > m_maxMana) m_mana = m_maxMana;
	else m_mana = a_mana;
}
