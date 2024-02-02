// Intro Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int TriangleNumber();
void NumberSwap();
void C2F();
void RectArea();
void AvgOfFive();
void Fibonacci();
void FibonacciRecursive(int fibInput);
void Factorial();
void SumMean();

int main()
{

    /*std::cout << TriangleNumber() << std::endl;
    NumberSwap();
    C2F();
    RectArea();
    AvgOfFive();*/
    //Fibonacci();
   // Factorial();
    SumMean();
    int fibInput = 0;
    std::cin >> fibInput;
    FibonacciRecursive(fibInput);

    return 0;
}

int TriangleNumber() {
    int n = 0;
    std::cin >> n;
    return n * (n + 1) / 2;
}

void NumberSwap()
{
    int x = 13;
    int y = 24;

    // <Your work goes here>
    std::cout << "Put in 2 numbers wah wah" << std::endl;

    int z = x;
    x = y;
    y = x;


    std::cout << "Number Swap)" << std::endl;
    std::cout << "x is " << x << std::endl;
    std::cout << "y is " << y << std::endl;
}

void RectArea() {
    float rectWidth = 0.0f;  // Modify this variable below.
    float rectHeight = 0.0f; // Modify this variable below.
    float rectArea = 0.0f;   // Modify this variable below.

    std::cout << "Input 2 numbers" << std::endl;
    std::cin >> rectWidth;
    std::cin >> rectHeight;
    rectArea = rectWidth * rectHeight;

    std::cout << "Area of a Rectangle)" << std::endl;
    std::cout << "H: " << rectHeight << " , W: " << rectWidth << std::endl;
    std::cout << "Area: " << rectArea << std::endl;
}

void AvgOfFive() {
    float a, b, c, d, e;    // Modify these variables below.
    float avg;              // Modify this variable below.
    avg = a = b = c = d = e = 0.0f; // Initialize all to zero.

    std::cout << "Put in 5 numbers wah wah" << std::endl;
        
    std::cin >> a >> b >> c >> d >> e;

    avg = (a + b + c + d + e) / 5.0f;

    std::cout << "Average of Five)" << std::endl;
    std::cout << a << "," << b << "," << c << "," << d << "," << e << std::endl;
    std::cout << "avg: " << avg << std::endl;
}

void C2F() {

    float degCelsius = 78.0f;
    float degFahrenheit = 0.0f; // Modify this variable below.

    std::cin >> degCelsius;
    degFahrenheit = (degCelsius) * (9.0f / 5.0f) + 32.0f;

    std::cout << "Celsius to Fahrenheit)" << std::endl;
    std::cout << "Celsius:    " << degCelsius << std::endl;
    std::cout << "Fahrenheit: " << degFahrenheit << std::endl;
}


void Fibonacci() {
    int iterations = 0;
    int j = 0;
    int k = 1;
    std::cin >> iterations;

    //Its just wrong it turns out. Think i need a 3rd value.
    for (int i = 0; i < iterations; i++) {
        std::cout << j << std::endl;
        j += k;
        k = j - k;
    }
}

int recursiveX = 0;
int recursiveY = 1;
//You can put these in. You just need to pass them on each time. I simply don't care to do that.
//Really you'd have a setup function that takes the input establishes the values etc. I don't wanna do that.
void FibonacciRecursive(int fibInput) {
    static int fibCount = 0;
    std::cout << recursiveX << std::endl;
    recursiveX += recursiveY;
    recursiveY = recursiveX - recursiveY;
    if (fibCount++ < fibInput) FibonacciRecursive(fibInput);
}

void Factorial() {
        int input;
        int output = 1;
        std::cin >> input;
        for (int i = 1; i <= input; i++){
            output *= i;
        }
        std::cout << output << std::endl;
}

void SumMean() {
    int count = 0;
    int sum = 0;
    bool quitting = false;
    std::string input = "";
    while (!quitting) {
        bool failed = false;
        int inputNum = 0;
        do {
            std::cin >> input;
            failed = false;
            if (input == "q" || input == "Q") {
                std::cout << "Quitting." << std::endl;
                quitting = true;
            }
            else if (sscanf_s(input.c_str(), "%d", &inputNum) != 1)  
            {
                failed = true;
                std::cout << "Waiter waiter! An actual number please!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::cin.rdbuf()->in_avail());
            }
        } while (failed);


        count++;
        sum += inputNum;
        std::cout << count << " Numbers have been entered." << std::endl;
        std::cout << "The current average is: " << sum/count << std::endl;
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
