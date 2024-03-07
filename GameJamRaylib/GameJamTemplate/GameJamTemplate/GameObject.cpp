#include "GameObject.h"
void GameObject::Update(float deltaTime)
{
	OnUpdate(deltaTime);

	for (int i = 0; i < children.size(); i++)
	{
		children[i]->Update(deltaTime);
	}
}

void GameObject::Draw()
{
	OnDraw();

	for (int i = 0; i < children.size(); i++)
	{
		children[i]->Draw();
	}
}

void GameObject::AddChild(GameObject* child)
{
	if (child->m_parent == nullptr)
	{
		child->m_parent = this;
		children.push_back(child);
	}
	else
	{
		//child cannot have two parents
	}
}
