// FileSearch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>
#include <string>

void printDirectory(std::string directory, int depth);
double fileSize;

int main()
{    
    printDirectory("D:\\Jasper AIE", 0);
    std::cout << "Directory size: " << fileSize / 1e+6 << "Mb" << std::endl;
    return 0;
}

void printDirectory(std::string directory, int depth) {
    HANDLE hFind;
    WIN32_FIND_DATAA data;

    std::string padding(depth + 1, ' ');
    std::string searchPath = directory + "\\*";

    hFind = FindFirstFileA(searchPath.c_str(), &data);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            //dont process . or .. entries
            if (strcmp(data.cFileName, ".") == 0 || strcmp(data.cFileName, "..") == 0)
                continue;
            std::cout << padding << data.cFileName << std::endl;
            if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) 
            {
                printDirectory(directory + "\\" + data.cFileName, depth+1);
            }
            else {
                fileSize += (data.nFileSizeHigh * (MAXDWORD + 1.0)) + data.nFileSizeLow;
            }
        } while (FindNextFileA(hFind, &data));
        FindClose(hFind);
    }
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
