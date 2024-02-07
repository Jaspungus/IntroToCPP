// Pointers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

void RevString(char* array);
int CountEven(int array, int array_size);
double* Maximum(double* array, int array_size);
bool Contains(char* array, char search_value);

int main()
{
    std::cout << "Hello World!\n";

    char blocks[3] = { 'A','B','C' };
    char* ptr = &blocks[0];
    char temp;

    temp = blocks[0];
    temp = *(blocks + 2); //Arrays ARE pointers. Adding to one is just adding to the pointer
    temp = *(ptr + 1);
    temp = *ptr;

    ptr = blocks + 1;
    temp = *ptr;
    temp = *(ptr + 1);

    ptr = blocks;
    temp = *++ptr;
    temp = ++ * ptr;
    temp = *ptr++;
    temp = *ptr;

    char string[5] = { 'p','o','r','p','\0' };
    std::cout << string << std::endl;
    RevString(string);
    std::cout << string << std::endl;

    double intArray[5] = { 2,4,1,6,7 };
    std::cout << Maximum(intArray, 5) << std::endl;

    char stringContain[7] = "pleepl";
    std::cout << Contains(stringContain, 'p') << std::endl;
    



    return 0;

}

//Now i get why they made C#
void RevString(char* array) {
    
    int strLen = strlen(array);
    std::cout << strLen << std::endl;
    char temp;

    
    for (int i = 0; i < strLen - 1; i++) {
        temp = array[i];
        array[i] = array[strLen - i - 1];
        array[strLen - i - 1] = temp;

    }
}

int CountEven(int* array, int array_len) {
    int evens = 0;
    for (int i = 0; i < array_len; i++) 
    {
        if (i % 2 == 0) evens++;
    }
    return evens;
}

double* Maximum(double* array, int array_size) {
    double max = 0;
    double* maxPtr = nullptr;
    for (int i = 0; i < array_size; i++) {
        if (array[i] > max) maxPtr = &array[i];
    }
    return maxPtr;
}

bool Contains(char* array, char search_value) {
    int strLen = strlen(array);
    for (int i = 0; i < strLen; i++) 
    {
        if (array[i] == search_value) return true;
    }
    return false;
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
