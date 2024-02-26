#include "Guard.h"

Guard::Guard() {
	m_position = Vec2I(0, 0);
	m_direction = 0;
}

Guard::Guard(Vec2I a_position) {
	m_position = a_position;
	m_direction = 0;
}

Guard::~Guard()
{
}

const Vec2I Guard::GetPosition() const {
	return m_position;
}

void Guard::SetPosition(Vec2I a_position) {
	SetPosition(a_position.X, a_position.Y);
}

void Guard::SetPosition(int x, int y) {

	int newDir = -1;
	if (y < m_position.Y) newDir = 0;
	if (y > m_position.Y) newDir = 2;
	if (x < m_position.X) newDir = 3;
	if (x > m_position.X) newDir = 1;

	SetDirection(newDir);

	m_position.X = x;
	m_position.Y = y;
	if (m_position.X <= 0) m_position.X = 0;
	if (m_position.Y <= 0) m_position.Y = 0;
}

const int Guard::GetDirection() const {
	return m_direction;
}

void Guard::SetDirection(int a_direction) {
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

const char* Guard::GetIcon() const {
	return &m_icon;
}

const int Guard::GetColour() const {
	return m_colour;
}