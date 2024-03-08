#include "Seed.h"
#include "Enemy.h"
#include "raymath.h"


Seed::Seed() {

}

Seed::Seed(Vector2 pos, Vector2 scale, Game* game, Vector2 direction) : GameObject(game)
{
	m_position = pos;
	m_scale = scale;

	m_direction = Vector2Normalize(Vector2Subtract(direction, m_position));
	m_color = BLACK;
	UpdateRect();
}

Seed::~Seed()
{
}

void Seed::OnUpdate(float deltaTime)
{
	m_position = Vector2Add(m_position, Vector2Scale(m_direction, m_moveSpeed));


	for (GameObject* go : m_game->m_root->children)
	{
		Enemy* e = dynamic_cast<Enemy*>(go);
		//EnvironmentBlock* eb = dynamic_cast<EnvironmentBlock*>(go);
		//Dont want player to check collision with itself :x
		if (e != nullptr)
		{
			if (CheckCollisionRecs(m_gameRect, go->GetGameRect()))
			{
				delete go;
				m_game->m_root->children.erase(std::remove(m_game->m_root->children.begin(), m_game->m_root->children.end(), go));
				Destroy();
				return;
			}
		}

	}

	if (m_position.x < m_game->m_gameBLCorner.x || m_position.x > m_game->m_gameTRCorner.x || m_position.y > m_game->m_gameBLCorner.y || m_position.y < m_game->m_gameTRCorner.y) {
		Destroy();
	}

}

void Seed::OnDraw()
{
	UpdateRect();

	DrawEllipse(m_position.x + m_scale.x / 2, m_position.y + m_scale.y / 2, m_scale.x / 2, m_scale.y / 2, m_color);


}

void Seed::UpdateRect()
{
	m_gameRect.x = m_position.x;
	m_gameRect.y = m_position.y;
	m_gameRect.width = m_scale.x;
	m_gameRect.height = m_scale.y;
}

void Seed::Destroy() {
	m_game->m_root->children.erase(std::remove(m_game->m_root->children.begin(), m_game->m_root->children.end(), this));
	delete this;
}
