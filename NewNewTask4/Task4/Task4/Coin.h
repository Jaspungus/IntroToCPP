#pragma once
#include "Item.h"

struct Coin : public Item
{
public:
	Coin(Vec2I a_position);
	~Coin();

public:
	void Description() const override;
	void Use() override;
	bool Take() override;
};

