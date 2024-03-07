#include "EnvironmentBlock.h"

EnvironmentBlock::EnvironmentBlock()
{
	m_color = GRAY;
}

EnvironmentBlock::EnvironmentBlock(Vector2 pos, Vector2 scale, Game* game) : GameObject(game)
{
	m_position = pos;
	m_scale = scale;
	m_color = GRAY;
	UpdateRect();
}

EnvironmentBlock::~EnvironmentBlock()
{
}

void EnvironmentBlock::OnUpdate(float deltaTime)
{
	
}

void EnvironmentBlock::OnDraw()
{
	UpdateRect();

	DrawRectangleRec(m_gameRect, m_color);
}

void EnvironmentBlock::UpdateRect()
{
	m_gameRect.x = m_position.x;
	m_gameRect.y = m_position.y;
	m_gameRect.width = m_scale.x;
	m_gameRect.height = m_scale.y;
}
