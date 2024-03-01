#include "Guard.h"

Guard::Guard() {
	m_position = Vec2I(0, 0);
}

Guard::Guard(Vec2I a_position) {
	m_position = a_position;
}

Guard::Guard(Vec2I a_position, int a_direction) {
	m_position = a_position;
	SetDirection(a_direction);
}

Guard::~Guard()
{
	delete[] m_conePoints;
	delete m_AStar;
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

const Vec2I Guard::GetDirectionVector() const {
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

const int Guard::GetViewWidth() const {
	return m_viewWidth;
}

const Vec2I* Guard::GetConePoints() const {
	return m_conePoints;
}

void Guard::UpdateConePoints() {
	Vec2I centrePoint = m_position + GetDirectionVector() * m_viewDistance;

	for (int i = 0; i < m_viewWidth; i++) {

		m_conePoints[i] = centrePoint + GetDirectionVector().Perpindicular() * (m_viewWidth / 2) + -GetDirectionVector().Perpindicular() * i;
		if (i > 0 && i < m_viewWidth - 1) m_conePoints[i] += GetDirectionVector();
	}
}

void Guard::UpdateState() {
	//Change colours and stuff.
	switch (m_state) {
	case Calm:
		if (m_seesPlayer) { m_state = Alert; break; }

		if (m_position == m_targetPosition) {
			//Set next node as path

		}
		else {
			if (!path.empty()) {
				SetPosition(Vec2I(path.top().second, path.top().first));
				path.pop();
			}
		}

		break;
	case Investigating:
		if (m_position == m_targetPosition) {
			if (m_hasSeenPlayer) m_state = Paranoid;
			else m_state = Calm;
		}

		//Move along path (should be set to a location)
		if (!path.empty()) {
			SetPosition(Vec2I(path.top().second, path.top().first));
			path.pop();
		}

		if (m_seesPlayer) { m_state = Alert; break; }
		break;
	case Paranoid:
		if (m_seesPlayer) { m_state = Alert; break; }

		//Follow path. Turn round every x turns
		//Set next node as path, keep a turn counter.

		break;
	case Alert:
		if (!m_seesPlayer) m_state = Paranoid;
		//else make player lose
		break;
	case Unconscious:
		break;
	}
	std::cout << m_seesPlayer;
}

void Guard::UpdateBehaviour() 
{
	switch (m_state) {
	case Calm:
		if (m_position == m_targetPosition) {
			//Set next node as path
			
		}
		else {
			if (!path.empty()) {
				SetPosition(Vec2I(path.top().second, path.top().first));
				path.pop();
			}
		}
		break;
	case Investigating:
		//Move along path (should be set to a location)
		if (!path.empty()) {
			SetPosition(Vec2I(path.top().second, path.top().first));
			path.pop();
		}

		break;
	case Paranoid:
		//Follow path. Turn round every x turns
		//Set next node as path, keep a turn counter.
		break;
	case Alert:
		if (m_seesPlayer) //Player lose
		break;
	case Unconscious:
		//Just like never do anything.
		break;

	}
}

void Guard::SetSeesPlayer(bool isAlert) {
	m_seesPlayer = isAlert;
	if (m_seesPlayer) m_hasSeenPlayer = true;
}

int Guard::GetState() {
	return m_state;
}


void Guard::GeneratePath(Vec2I a_destination) {
	m_AStar->AStarSearch(this, m_position, a_destination);

	path = m_AStar->TracePath(a_destination);
}