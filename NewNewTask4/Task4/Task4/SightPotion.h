#pragma once
#include "Item.h"
struct SightPotion : public Item
{
public:
	SightPotion(Vec2I a_position);
	~SightPotion();

public:
	void Description() const override;
	void Use() override;
	bool Take() override;
};

