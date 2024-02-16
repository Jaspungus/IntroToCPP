// Task4.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <stdlib.h>
#include "String.h"
#include "Player.h"
#include "SpellManager.h"

using namespace std;

//Coloured text yippee
//Perhaps but this in a different script so anywhere can access it. For like item pick ups etc.
//We'll see. Or do like an if based on Item.Name and Item.Quality. Figure that out.
// ESC[background_colour;Text_colourm output Esc[m
#define ESC "\033["
#define BLACK "0"
#define RED "1"
#define GREEN "2"
#define YELLOW "3"
#define BLUE "4"
#define PURPLE "5"
#define LIGHT_BLUE "6"
#define WHITE "7"
#define RESET "\033[m"

void ColouredText(const char* a_string, const char* a_backgroundColour, const char* a_foregroundColour);

Player* player = new Player((size_t)20, (size_t)20);
SpellManager* spellManager = new SpellManager();
String m_inputString = "";
bool m_isPlaying = true;


int main()
{
	while (m_isPlaying) {
		m_inputString.ReadFromConsole();
		std::cout << m_inputString.CStr() << std::endl;
		std::cout << m_inputString.Find("cast") << std::endl;

		//Can't use switch statement. Now I have to do icky if-else;
		if (m_inputString == "Plorgo") {
			cout << "You have contracted " << ESC << "106" << ";" << "35m" << "Bowel Cancer" << RESET << endl;
			cout << "You have contracted "; ColouredText("Bowel Cancer", RED, LIGHT_BLUE); cout << endl;
		}
		std::cout << "It got to line 43!" << std::endl;
		if (m_inputString.Find(0, "Cast") != -1) {
			String testString("Power Word: Scrunch");
			player->CastSpell(testString);
		}
	}
}

void ColouredText(const char* a_string, const char* a_backgroundColour, const char* a_foregroundColour) {
	cout << ESC << "3" << a_backgroundColour << ";" << "4" << a_foregroundColour << "m" << a_string << RESET;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
