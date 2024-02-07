// Task1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "String.h"

int main() {
	
	char* poopgisPtr = new char['p','o','o','p','g','i','s','\0'];
	
	String string = String();
	string = poopgisPtr;

	string.WriteToConsole();
	
}