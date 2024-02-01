// Constants.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Static local exists for the runtime of the file but is only accessible within its scope
//

#include <iostream>

char choice = 'Y';
int flag = 1;
long date = 23132, timeValue = 2412;
extern char bondType;

double roi();
double average();
double variance();
double watts();
double thrust();

void counter() {
	static int i = 0;
	std::cout << "I have been called " << i << " times before." << std::endl;
	std::cout << "That makes " << i++ << " times now. Have an extra line of text." << std::endl;

}

float askForGallons() {
	
	float gallons = 0;
	bool failed = false;
	

	do {
		failed = false;
		std::cin >> gallons;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << "DO IT AGAIN" << std::endl;
			failed = true;
			
		}
	}
	while (failed == true);
	return gallons * 3.78533;
}

int main()
{
	for (int i = 0; i < 11; i++) {
		counter();
	}
	std::cout << askForGallons() << std::endl;

	roi();
	average();
	variance();
}

double factor = 0.0;
double watts()
{
	return 0.0;
}
double thrust()
{
	return 0.0;
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
