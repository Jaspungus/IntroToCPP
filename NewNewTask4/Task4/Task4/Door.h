#pragma once
#include "Item.h"

struct Door : public Item
{
private:
	bool isLocked = true;
	Vec2I connectedRoom = Vec2I(0, 0);
	Vec2I playerSpawn = Vec2I(0, 0);
	int exitDirection = 0;
public:
	Door(Vec2I a_position);
	Door(Vec2I a_position, bool a_isLocked, Vec2I a_connectedRoom, Vec2I a_playerSpawn, int a_exitDirection);
	~Door();

public:
	void Description() const override;
	void Use() override;
	bool Take() override;
};

