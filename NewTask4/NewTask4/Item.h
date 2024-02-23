#pragma once
#include "String.h"

class Item
{
private: 
	String m_name;
public:
	String GetName() const;
	virtual void Description() const;
	virtual void Use();
};

