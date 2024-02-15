#include "GameManager.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

void GameManager::Process() {

	while (m_isPlaying) {
		m_inputString.ReadFromConsole();

		//Can't use switch statement. Now I have to do icky if-else;
		if (m_inputString == "Plorgo") {
			cout << "You have contracted ";
			system("Color 04");
			cout << "Bowel Cancer";
			system("Color 07");
		}
	}
}