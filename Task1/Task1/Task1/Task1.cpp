// Task1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "String.h"

int main() {
	
	//char* poopgisPtr = new char['p','o','o','p','g','i','s','\0'];
	char plorgo[] = "plorgo";
	char pingus[] = "pingus";
	
	String plorgoString = String("plorgo");
	String pingusString = String(pingus);
	//string = poopgisPtr;
	//string = plorgo;

	String plorgoStr2 = String(plorgoString);
	
	/*
	plorgoString.WriteToConsole();
	plorgoStr2.WriteToConsole();

	plorgoStr2.ReadFromConsole();

	plorgoString.Append(pingusString);
	plorgoStr2.Append(pingusString);

	plorgoString.WriteToConsole();
	plorgoStr2.WriteToConsole();
	*/
	plorgoString += "plorgoStr2";
	plorgoString.WriteToConsole();
	
	if ((plorgoString != pingusString)) std::cout << plorgoStr2[2] << std::endl;

	std::cout << plorgoStr2.CharacterAt(2) << std::endl;

	/*
	plorgoString.Append(pingusString);
	plorgoString.Prepend(pingusString);

	plorgoString.WriteToConsole();
	plorgoString.ToUpper();
	plorgoString.WriteToConsole();

	plorgoString.ToLower();
	plorgoString.WriteToConsole();
	*/

	//string.ReadFromConsole();
	//string.WriteToConsole();
	
}