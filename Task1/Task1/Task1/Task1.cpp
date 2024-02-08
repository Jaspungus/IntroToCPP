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
	

	std::cout << plorgoString.Find(2, "rgo") << std::endl;

	plorgoString.ConcatAt("guspin", 4);
	std::cout << plorgoString.CStr() << std::endl;


	plorgoString.DeleteRange(4, 10);
	std::cout << plorgoString.CStr() << std::endl;

	

	/*
	plorgoString.WriteToConsole();
	plorgoStr2.WriteToConsole();

	plorgoStr2.ReadFromConsole();

	plorgoString.Append(pingusString);
	plorgoStr2.Append(pingusString);

	plorgoString.WriteToConsole();
	plorgoStr2.WriteToConsole();
	*/
	//plorgoString += "plorgoStr2";
	/*
	plorgoString += "pungus";

	String testString(plorgoString.ToUpper());
	std::cout << testString.CStr() << "AAAA" << std::endl;
	std::cout << plorgoString.CStr() << "???" << std::endl;
	std::cout << plorgoString.ToUpper().CStr() << "???" << std::endl;
	plorgoString.WriteToConsole();*/
	
	//plorgoString = plorgoString.Append(pingusString);
	//plorgoString.WriteToConsole();

	/*
	if ((plorgoString != pingusString)) std::cout << plorgoStr2[2] << std::endl;

	plorgoString = String("plorgo").ToUpper();
	plorgoString.WriteToConsole();
	std::cout << plorgoString.CStr() << std::endl;
	//std::cout << (plorgoStr2.ToUpper()).CStr() << std::endl;
	*/
	

	
	/*plorgoString.Prepend(pingusString);

	plorgoString.WriteToConsole();
	plorgoString.ToUpper();
	plorgoString.WriteToConsole();

	plorgoString.ToLower();
	plorgoString.WriteToConsole();
	*/

	//string.ReadFromConsole();
	//string.WriteToConsole();
	
}