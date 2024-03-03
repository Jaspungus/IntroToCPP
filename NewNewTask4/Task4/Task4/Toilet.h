#pragma once
#include "Item.h"
struct Toilet : public Item
{
private:
	bool loose = false;

public:
	Toilet(Vec2I a_position);
	Toilet(Vec2I a_position, bool a_isLoose);
	~Toilet();

public:
	void Description() const override;
	void Use() override;
	bool Take() override;
};

