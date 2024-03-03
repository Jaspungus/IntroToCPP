#pragma once
#include "Item.h"

struct ExitDoor : public Item
{
public:
	ExitDoor(Vec2I a_position);
	~ExitDoor();

public:
	void Description() const override;
	void Use() override;
	bool Take() override;
};


