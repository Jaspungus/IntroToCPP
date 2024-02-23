#pragma once
#include "String.h"

struct Gnome
{
public:
	String m_name;
	String m_title;
	String m_description;
	bool m_isAsh;

public:
	Gnome();
	Gnome(const char* a_name, const char* a_title, const char* a_description);
	~Gnome();

	void TurnToAsh();
};

