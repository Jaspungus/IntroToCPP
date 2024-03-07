#include "Enemy.h"
#include "Player.h"

Enemy::Enemy()
{
	m_color = RED;
}

Enemy::Enemy(Vector2 pos, Vector2 scale, Game* game) : GameObject(game)
{
	
	m_position = pos;
	m_scale = scale;
	UpdateRect();

	m_color = GREEN;
}

Enemy::~Enemy()
{
}

void Enemy::OnUpdate(float deltaTime)
{
	//REWORK OH MY GOD ITS BAD HOLY
	//ITS ALSO FRAME DEPENDANT OOPS
	if (m_game->m_player->GetPos().x > m_position.x) { m_position.x += moveSpeed; }
	else if (m_game->m_player->GetPos().x < m_position.x) m_position.x -= moveSpeed;
	
	if (m_game->m_player->GetPos().y > m_position.y) { m_position.y += moveSpeed; }
	else if (m_game->m_player->GetPos().y < m_position.y) m_position.y -= moveSpeed;
}

void Enemy::OnDraw()
{
	UpdateRect();

	DrawEllipse(m_position.x + m_scale.x / 2, m_position.y + m_scale.y / 2, m_scale.x, m_scale.y, m_color);
	
}

void Enemy::UpdateRect()
{
	m_gameRect.x = m_position.x;
	m_gameRect.y = m_position.y;
	m_gameRect.width = m_scale.x;
	m_gameRect.height = m_scale.y;

}

void Enemy::MoveTo(Vector2 pos)
{
}

