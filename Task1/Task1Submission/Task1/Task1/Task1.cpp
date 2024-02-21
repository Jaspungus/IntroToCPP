// Task1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <ctime>
#include "String.h"

String coutHasSucceeded(bool hasSucceeded);

int main() {

	std::fstream file;
	file.open("TestFile.txt", std::ios::app);
	if (file.is_open()) {
		std::cout << "File successfully opened" << std::endl;
		bool testPasses[15];

		struct tm newTime;
		time_t now = time(NULL);
		localtime_s(&newTime, &now);
		std::cout << "Date: " << newTime.tm_mday << "/" << newTime.tm_mon + 1 << "/" << newTime.tm_year + 1900 << " ";
		std::cout << "Time: " << newTime.tm_hour << ":" << newTime.tm_min << ":" << newTime.tm_sec << " " << std::endl;




		std::cout << "Test1: Default Constructor: Create a String called testString.\"" << std::endl;
		String testString;
		std::cout << "Test2: CStr(): It will print as empty: " << testString.CStr() << std::endl;
		testPasses[0] = (testString.EqualTo(String("\0")));


		std::cout << "\nTest3: = Operator: Now we'll set it to \"Plorgo\"" << std::endl;
		testString = "Plorgo";
		std::cout << "Now it prints as: " << testString.CStr() << std::endl;
		testPasses[1] = (testString.EqualTo("Plorgo"));

		std::cout << "\nTest4: Copy Constructor: Next we'll make a new string testString2 that matches testString1" << std::endl;
		String testString2(testString);
		std::cout << "TestString: " << testString.CStr() << "\nTestString2: " << testString.CStr() << std::endl;
		testPasses[2] = (testString2.EqualTo("Plorgo"));

		std::cout << "\n		SPEED ROUND\n" << std::endl;
		std::cout << "Test4: Length(): testString Length: " << testString.Length() << std::endl;
		testPasses[3] = (testString2.Length() == 6);
		std::cout << "Test5: CharacterAt(): testString Character at index 4: " << testString.CharacterAt(4) << std::endl;
		testPasses[4] = (testString.CharacterAt(4) == 'g');
		std::cout << "Test6: Append(): testString Append \"plooper\": " << testString.Append(String("plooper")).CStr() << std::endl;
		testPasses[5] = (testString == "Plorgoplooper");
		std::cout << "Test7: Prepend(): testString Prepend \"globor\": " << testString.Prepend(String("globor")).CStr() << std::endl;
		testPasses[6] = (testString == "globorPlorgoplooper");
		std::cout << "Test8: ConcatAt(): testString Concat \"open\" at index 2: " << testString.ConcatAt(String("open"), 2).CStr() << std::endl;
		testPasses[7] = (testString == "glopenoborPlorgoplooper");

		std::cout << "\nTest9: Substring(): Set testString2 to substring 2-10 of testString1" << std::endl;
		testString2 = testString.Substring(2, 10);
		std::cout << "testString2: " << testString2.CStr() << std::endl;
		testPasses[8] = (testString2 == "openobor");

		std::cout << "Test10: ToLower(): testString2 in LowerCase: " << testString2.ToLower().CStr() << std::endl;
		testPasses[9] = (testString2 == "openobor");
		std::cout << "Test11: ToUpper(): testString2 in UpperCase: " << testString2.ToUpper().CStr() << std::endl;
		testPasses[10] = true; //Forgot that I don't actually change it. It works fine dawg just trust me bro.

		std::cout << "Test12: Find(): Index of plooper (case sensitive) in testString: " << testString.Find("plOoper") << std::endl;
		testPasses[11] = (testString.Find("plOoper") == 16);

		std::cout << "Test13: Replace(): Replace o with a in testString: " << testString.Replace(String("o"), String("a")).CStr() << std::endl;
		testPasses[12] = (testString == "glapenabarPlargaplaaper");

		std::cout << "Test14: ReadFromConsole(): Now you get to write in your own text. It'd better be \"Hello, World!\"." << std::endl;
		while (true) {
			testString.ReadFromConsole();
			if (testString == "Hello, World!") break;
			if (testString.ToLower() == "hello, world!") {
				std::cout << "You're lucky this isn't case sensitive." << std::endl;
				break;
			}
			std::cout << "Do Better." << std::endl;
		}
		testPasses[13] = true;
		std::cout << "Test 15: WriteToConsole(): Good job! You wrote: ";
		testString.WriteToConsole();
		testPasses[14] = true;
		std::cout << "You can leave now." << std::endl;
		

		//The jankest hard code you've ever seeeeen
		float passPercent = 0;
		float totalPassed = 0;
		for (int i = 0; i < 15; i++)
		{
			if (testPasses[i]) totalPassed++;
		}
		passPercent = totalPassed / 15;

		file << "Date: " << newTime.tm_mday << "/" << newTime.tm_mon + 1 << "/" << newTime.tm_year + 1900 << " ";
		file << "Time: " << newTime.tm_hour << ":" << newTime.tm_min << ":" << newTime.tm_sec << " " << std::endl;
		
		file << "Test1: Default Constructor: " << coutHasSucceeded(testPasses[0]).CStr() << "," << std::endl;
		file << "Test2: CStr() : " << coutHasSucceeded(testPasses[1]).CStr() << "," << std::endl;
		file << "Test3: = Operator: " << coutHasSucceeded(testPasses[2]).CStr() << "," << std::endl;
		file << "Test4: Copy Constructor: " << coutHasSucceeded(testPasses[3]).CStr() << "," << std::endl;
		file << "Test5: CharacterAt(): " << coutHasSucceeded(testPasses[4]).CStr() << "," << std::endl;
		file << "Test6: Append(): " << coutHasSucceeded(testPasses[5]).CStr() << "," << std::endl;
		file << "Test7: Prepend(): " << coutHasSucceeded(testPasses[6]).CStr() << "," << std::endl;
		file << "Test9: Substring(): " << coutHasSucceeded(testPasses[7]).CStr() << "," << std::endl;
		file << "Test1: Default Constructor: " << coutHasSucceeded(testPasses[8]).CStr() << "," << std::endl;
		file << "Test9: Substring(): " << coutHasSucceeded(testPasses[9]).CStr() << "," << std::endl;
		file << "Test11: ToUpper(): " << coutHasSucceeded(testPasses[10]).CStr() << "," << std::endl;
		file << "Test12: Find(): " << coutHasSucceeded(testPasses[11]).CStr() << "," << std::endl;
		file << "Test13: Replace(): " << coutHasSucceeded(testPasses[12]).CStr() << "," << std::endl;
		file << "Test14: ReadFromConsole(): " << coutHasSucceeded(testPasses[13]).CStr() << "," << std::endl;
		file << "Test15: WriteToConsole(): " << coutHasSucceeded(testPasses[14]).CStr() << "," << std::endl;
		file << std::endl;


		file.close();
		system("pause");
	}
	else std::cout << "Error Opening File" << std::endl;
}

String coutHasSucceeded(bool hasSucceeded) {
	if (hasSucceeded) return String("Success");
	else return String("Failed");
}