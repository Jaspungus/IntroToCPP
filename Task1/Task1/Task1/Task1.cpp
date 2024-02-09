// Task1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "String.h"

int main() {
	
	std::cout << "Create a String called testString with the value \"Pingunk\"" << std::endl;
	String testString("Pingunk");
	std::cout << "It will print as empty: " << testString.CStr() << std::endl;

	std::cout << "\nNow we'll set it to \"Plorgo\"" << std::endl;
	testString = "Plorgo";
	std::cout << "Now it prints as: " << testString.CStr() << std::endl;
	
	std::cout << "\nNext we'll make a new string testString2 that matches testString1" << std::endl;
	String testString2(testString);
	std::cout << "TestString: " << testString.CStr() << "\nTestString2: " << testString.CStr() << std::endl;

	std::cout << "\n		SPEED ROUND\n" << std::endl;
	std::cout << "testString Length: " << testString.Length() << std::endl;
	std::cout << "testString Character at index 4: " << testString.CharacterAt(4) << std::endl;
	std::cout << "testString Append \"plooper\": " << testString.Append(String("plooper")).CStr() << std::endl;
	std::cout << "testString Prepend \"globor\": " << testString.Prepend(String("globor")).CStr() << std::endl;
	std::cout << "testString Concat \"open\" at index 2: " << testString.ConcatAt(String("open"), 2).CStr() << std::endl;

	std::cout << "\nSet testString2 to substring 2-10 of testString1" << std::endl;
	testString2 = testString.Substring(2, 10);
	std::cout << "testString2: " << testString2.CStr() << std::endl;

	std::cout << "testString2 in LowerCase: " << testString2.ToLower().CStr() << std::endl;
	std::cout << "testString2 in UpperCase: " << testString2.ToUpper().CStr() << std::endl;

	std::cout << "Index of plooper (case sensitive) in testString: " << testString.Find("plOoper") << std::endl;

	std::cout << "Replace o with a in testString: " << testString.Replace(String("o"), String("a")).CStr() << std::endl;
	
	std::cout << "Now you get to write in your own text. It'd better be \"Hello, World!\"." << std::endl;
	while (true) {
		testString.ReadFromConsole();
		if (testString == "Hello, World!") break;
		if (testString.ToLower() == "hello, world!") {
			std::cout << "You're lucky this isn't case sensitive." << std::endl;
			break;
		}
		std::cout << "Do Better." << std::endl;
	}
	std::cout << "Good job! You wrote: ";
	testString.WriteToConsole();
	std::cout << "You can leave now." << std::endl;
	system("pause");
}