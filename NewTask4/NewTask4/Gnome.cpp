#include "Gnome.h"

Gnome::Gnome() {
	m_name = "";
	m_title = "";
	m_description = "";
	m_isAsh = false;
}

Gnome::Gnome(const char* a_name, const char* a_title, const char* a_description) {
	m_name = a_name;
	m_title = a_title;
	m_description = a_description;
	m_isAsh = false;
}

Gnome::~Gnome() {

}

void Gnome::TurnToAsh() {
	m_isAsh = true;
	m_description = String("A pile of ash sits where ") + m_name + " once stood.";
}