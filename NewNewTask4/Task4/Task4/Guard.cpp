#include "Guard.h"
#include "Game.h"


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
	FaceDirection(a_position - m_position);

	m_position = a_position;
	if (m_position.X <= 0) m_position.X = 0;
	if (m_position.Y <= 0) m_position.Y = 0;
}

void Guard::SetPosition(int x, int y) {
	SetPosition(Vec2I(x, y));
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
		m_icon = String::IntToASCII(30)[0];//'^';
		break;
	}
	case 1: {
		m_icon = String::IntToASCII(16)[0];//'>';
		break;
	}
	case 2: {
		m_icon = String::IntToASCII(31)[0]; //'v';
		break;
	}
	case 3: {
		m_icon = String::IntToASCII(17)[0];// '<';
		break;
	}
	}
}

void Guard::FaceDirection(Vec2I a_direction)
{
	int newDir = -1;
	if (a_direction.Y < 0) newDir = 0;
	if (a_direction.Y > 0) newDir = 2;
	if (a_direction.X < 0) newDir = 3;
	if (a_direction.X > 0) newDir = 1;

	SetDirection(newDir);
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
		if (m_seesPlayer) { SetState(Alert); break; }
		
		if (m_targetPosition == -Vec2I::One() && m_patrolPointCount > 1) {
			m_patrolCurrentIndex = 1;
			m_targetPosition = m_patrolRoute[m_patrolCurrentIndex];
			GeneratePath(m_targetPosition);
		}

		if (m_position == m_targetPosition) {
			//Set next node as path
			m_patrolCurrentIndex++;
			if (m_patrolCurrentIndex >= m_patrolPointCount) m_patrolCurrentIndex = 0;
			m_targetPosition = m_patrolRoute[m_patrolCurrentIndex];
			GeneratePath(m_targetPosition);
		}
		else {
			if (!path.empty()) {
				SetPosition(Vec2I(path.top().first, path.top().second));
				path.pop();
			}
		}
		
		break;
	case Investigating:
		if (m_seesPlayer) { SetState(Alert); break; }

		//Move along path (should be set to a location)
		if (path.size() == 1) {
			
			FaceDirection(Vec2I(path.top().first, path.top().second) - m_position);
			path.pop();
			
		}

		else if (!path.empty()) {
			SetPosition(Vec2I(path.top().first, path.top().second));
			path.pop();
		}

		else {
			//Go to next patrol node. Return to regular behavior.
			SetState(Calm);
			if (m_patrolPointCount > 0) {
				m_targetPosition = m_patrolRoute[m_patrolCurrentIndex];
				GeneratePath(m_targetPosition);
			}
		}


		break;
	case Paranoid:
		if (m_seesPlayer) { SetState(Alert); break; }
		//Follow path. Turn round every x turns
		//Set next node as path, keep a turn counter.


		if (m_position == m_targetPosition) {
			//Set next node as path
			if (m_patrolCurrentIndex >= m_patrolPointCount) m_patrolCurrentIndex = 0;
			m_targetPosition = m_patrolRoute[m_patrolCurrentIndex];
			GeneratePath(m_targetPosition);
		}
		//This is where I would keep special behaviour for turning around randomly.
		//If I had some.
		else {
			if (!path.empty()) {
				SetPosition(Vec2I(path.top().first, path.top().second));
				path.pop();
			}
		}
		break;
	case Alert:
		if (!m_seesPlayer) { SetState(Investigating); UpdateState(); break; }

		if (path.size() == 1) {

			FaceDirection(Vec2I(path.top().first, path.top().second) - m_position);
			Game::GetInstance()->GameOver(true);
			std::cout << "PLAYER CAUGHT OOOOOOOOYEAAAAH BAAAYBE";
			path.pop();
		}

		if (!path.empty()) {
			SetPosition(Vec2I(path.top().first, path.top().second));
			path.pop();
		}


		break;
	case Unconscious:
		break;
	}
}

void Guard::SetState(AIState state) 
{
	switch (state) {
	case Calm:
	{
		m_colour = 93;
		break;
	}
	case Investigating:
	{
		m_colour = 226;
		break;
		}
	case Paranoid: {
		m_colour = 202;
		break;
		}

	case Alert: {
		m_colour = 196;
		break;
		}
	case Unconscious: {
		m_colour = 88;
		break;
		}
	}
	m_state = state;
}


//Vestigial functions from before I gave up on more complex AI.
void Guard::SetSeesPlayer(bool isAlert) {
	m_seesPlayer = isAlert;
	if (m_seesPlayer) m_hasSeenPlayer = true;
}

int Guard::GetState() {
	return m_state;
}


void Guard::GeneratePath(Vec2I a_destination) {

	m_AStar->AStarSearch(this, m_position, a_destination);

	m_AStar->TracePath(this, a_destination);
}