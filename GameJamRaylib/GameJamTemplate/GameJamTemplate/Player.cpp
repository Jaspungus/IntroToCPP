#include "Player.h"
#include "EnvironmentBlock.h"
#include "Watermelon.h"

Player::Player()
{
	m_color = GREEN;
}

Player::Player(Vector2 pos, Vector2 scale, Game* game) : GameObject(game)
{
	m_position = pos;
	m_scale = scale;
	UpdateRect();

	m_color = GREEN;
}

Player::~Player()
{

}

void Player::OnUpdate(float deltaTime)
{
	if (m_isLerping) {
		m_position.x += m_lerpRate.x * deltaTime;
		m_position.y += m_lerpRate.y * deltaTime;

		if (abs(m_targetPos.x - m_position.x) < 10 && abs(m_targetPos.y - m_position.y) < 10) {
			m_position.x = m_targetPos.x;
			m_position.y = m_targetPos.y;
			m_isLerping = false;
			m_freeMovement = true;
			m_color = RED;
		}
	}
	else {
		m_direction = { 0,0 };

		if (IsKeyDown(KEY_A))
		{
			m_direction.x = -1;
			//m_velocity.x -= m_acceleration * deltaTime;

			//m_position.x -= m_moveSpeed * deltaTime;
		}
		if (IsKeyDown(KEY_D))
		{
			m_direction.x = 1;
			//m_velocity.x += m_acceleration * deltaTime;
		}




		if (m_freeMovement) {
			if (IsKeyDown(KEY_W))
			{
				m_direction.y = -1;
				//m_position.y -= m_moveSpeed * deltaTime;
				//m_velocity.y -= m_acceleration * deltaTime;
			}
			if (IsKeyDown(KEY_S))
			{
				//m_position.y += m_moveSpeed * deltaTime;
				m_direction.y = 1;
				//m_velocity.y += m_acceleration * deltaTime;
			}

		}

		m_dashTimer -= deltaTime;

		if (IsKeyDown(KEY_SPACE) && (m_direction.x != 0 || m_direction.y != 0) && m_dashTimer <= 0) {
			m_velocity.x += m_dashStrength * m_direction.x * deltaTime;
			m_velocity.y += m_dashStrength * m_direction.y * deltaTime;
			m_dashTimer = m_dashCooldown;
		}

		if (m_velocity.x < 0) {
			m_velocity.x += m_deceleration * deltaTime;
			if (m_velocity.x > 0) m_velocity.x = 0;
		}
		else if (m_velocity.x > 0) {
			m_velocity.x -= m_deceleration * deltaTime;
			if (m_velocity.x < 0) m_velocity.x = 0;
		}
		if (m_velocity.x < m_maxMoveSpeed)  m_velocity.x += m_acceleration * m_direction.x * deltaTime;
		else m_velocity.x += m_deceleration * -m_direction.x * deltaTime;

		if (m_velocity.y < 0) {
			m_velocity.y += m_deceleration * deltaTime;
			if (m_velocity.y > 0) m_velocity.y = 0;
		}
		else if (m_velocity.y > 0) {
			m_velocity.y -= m_deceleration * deltaTime;
			if (m_velocity.y < 0) m_velocity.y = 0;
		}
		if (m_velocity.y < m_maxMoveSpeed) m_velocity.y += m_acceleration * m_direction.y * deltaTime;
		else m_velocity.y += m_deceleration * -m_direction.y * deltaTime;

		//Update position

		m_position.x += m_velocity.x;
		m_position.y += m_velocity.y;


		//Keep player within bounds.

		if (m_position.x < (m_game->m_gameBLCorner.x)) {
			m_position.x = (m_game->m_gameBLCorner.x);
			m_velocity = { 0,0 };
		}

		if (m_position.x > (m_game->m_gameTRCorner.x - m_scale.x)) {
			m_position.x = (m_game->m_gameTRCorner.x - m_scale.x);
			m_velocity = { 0,0 };
		}


		if (m_position.y < (m_game->m_gameTRCorner.y)) {
			m_position.y = (m_game->m_gameTRCorner.y);
			m_velocity = { 0,0 };
		}

		if (m_position.y > (m_game->m_gameBLCorner.y - m_scale.y)) {
			m_position.y = (m_game->m_gameBLCorner.y - m_scale.y);
			m_velocity = { 0,0 };
		}
	}
	for (GameObject* go : m_game->m_root->children)
	{
		Watermelon* wm = dynamic_cast<Watermelon*>(go);
		//EnvironmentBlock* eb = dynamic_cast<EnvironmentBlock*>(go);
		//Dont want player to check collision with itself :x
		if (wm != nullptr)
		{
			m_isColliding = CheckCollisionRecs(m_gameRect, go->GetGameRect());
			if (m_isColliding)
			{
				m_seedCount += 5; //For each melon you hit, add to your seed counter. 
				//YOU START WITH NOTHING WOW
//m_game->m_root->children.erase(std::remove(m_game->m_root->children.begin(), m_game->m_root->children.end(), go));
				wm->Destroy();

			}
		}

		m_isColliding = false;
	}

}

void Player::OnDraw()
{
	UpdateRect();

	DrawRectangleRec(m_gameRect, m_color);
}

void Player::UpdateRect()
{
	m_gameRect.x = m_position.x;
	m_gameRect.y = m_position.y;
	m_gameRect.width = m_scale.x;
	m_gameRect.height = m_scale.y;

}

int Player::GetSeedCount() {
	return m_seedCount;
}

void Player::EnableFreeMovement() {
	m_freeMovement = true;
}

void Player::LerpTo(Vector2 pos, float duration) {
	m_isLerping = true;
	m_targetPos = pos;
	m_lerpRate = { (pos.x - m_position.x) / duration, (pos.y - m_position.y) / duration };

}

bool Player::GetLerping() {
	return m_isLerping;
}
