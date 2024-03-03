#pragma once
#include "Item.h"
struct Diamond : public Item
{
public:
	Diamond(Vec2I a_position);
	~Diamond();

public:
	void Description() const override;
	void Use() override;
	bool Take() override;

};

