#include "Watermelon.h"

Watermelon::Watermelon() {
	m_color = GREEN;
}

Watermelon::Watermelon(Vector2 pos, Vector2 scale, Game* game, float a_fallSpeed) : GameObject (game) {
	m_position = pos;
	m_scale = scale;
	m_color = GREEN;
	m_fallSpeed = a_fallSpeed;
	UpdateRect();
}

Watermelon::~Watermelon()
{
}

void Watermelon::OnUpdate(float deltaTime)
{
	m_position.y += m_fallSpeed * deltaTime;
	if (m_position.y > m_game->m_camera.target.y + 400){//m_game->m_windowHeight) {
		m_game->ResetSpawnDelay();
		m_game->ResetFallSpeed();
		Destroy();
	}
}

void Watermelon::OnDraw()
{
	UpdateRect();



	DrawEllipse(m_position.x + m_scale.x / 2, m_position.y + m_scale.y / 2, m_scale.x / 2, m_scale.y / 2, DARKGREEN);
	DrawEllipse(m_position.x + m_scale.x / 2, m_position.y + m_scale.y / 2, m_scale.x / 2 - 2, m_scale.y / 2 - 2, GREEN);
	DrawEllipse(m_position.x + m_scale.x / 2, m_position.y + m_scale.y / 2, m_scale.x / 2 - 4, m_scale.y / 2 - 4, RED);
	//DrawEllipseLines(m_position.x + m_scale.x / 2, m_position.y + m_scale.y / 2, m_scale.x / 2, m_scale.y / 2, DARKGREEN);
	
}

void Watermelon::UpdateRect()
{
	m_gameRect.x = m_position.x;
	m_gameRect.y = m_position.y;
	m_gameRect.width = m_scale.x;
	m_gameRect.height = m_scale.y;
}

void Watermelon::Destroy() {
	
	
	m_game->m_root->children.erase(std::remove(m_game->m_root->children.begin(), m_game->m_root->children.end(), this));
}


