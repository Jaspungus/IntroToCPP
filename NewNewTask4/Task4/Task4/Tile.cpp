#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(const int a_state)
{
    if (a_state < 0) m_state = 0;
    else if (a_state > 2) m_state = 2;
    else m_state = a_state;
}

bool Tile::GetIsLit()
{
    return m_isLit;
}

void Tile::SetIsLit(bool a_isLit)
{
    m_isLit = a_isLit;
}

int Tile::GetState()
{
    return 0;
}

void Tile::SetState(int a_state)
{
    if (a_state >= 0 && a_state <= 2) m_state = a_state;
}
