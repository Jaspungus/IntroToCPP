#pragma once
#include "Item.h"
struct Ham : public Item
{
public:
	Ham(Vec2I a_position);
	~Ham();

public:
	void Description() const override;
	void Use() override;
	bool Take() override;
};

