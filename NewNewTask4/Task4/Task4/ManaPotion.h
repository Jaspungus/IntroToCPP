#pragma once
#include "Item.h"

struct ManaPotion : public Item
{
public:
	ManaPotion(Vec2I a_position);
	~ManaPotion();

public:
	void Description() const override;
	void Use() override;
	bool Take() override;
};

