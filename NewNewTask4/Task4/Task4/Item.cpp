#include "Item.h"
#include "Game.h"

Item::Item() {

}

Item::~Item() {

}

const String Item::GetName() const
{
    return m_name;
}

const int Item::GetColour() const
{
    return colour;
}

//When trying to return &icon, it seemed to read more memory than it should have?
//As in isStationary was affecting the output and adding additional jumbled characters.
const char Item::GetIcon() const
{
    return icon;
}

const bool Item::GetStationary() const
{
    return stationary;
}

const int Item::GetValue() const {
    return value;
}


Vec2I Item::GetPosition() const
{
    return position;
}

void Item::SetPosition(const Vec2I a_position)
{
    if (a_position.X >= 0) position.X = a_position.X;
    if (a_position.X >= 0) position.Y = a_position.Y;
}

void Item::Description() const
{
    Game* currentGame = Game::GetInstance();
    currentGame->lastActionText += m_name;
}

void Item::Use()
{
}

bool Item::Take()
{
    return false;
}
