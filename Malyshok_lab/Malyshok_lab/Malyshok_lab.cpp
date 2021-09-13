// Malyshok_lab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Malyshok_lab.h"

void print_pipe(Pipe& pipe)
{
    std::cout << "Id: " << pipe.id << std::endl << "length: " << pipe.length << std::endl << "diameter: " <<pipe.diameter;
}

Pipe input_pipe()
{
    Pipe pipe;
    pipe.id = 0;
    std::cout << "Enter the length: ";
    std::cin >> pipe.length;
    std::cout << "Enter the diameter: ";
    std::cin >> pipe.diameter;
    return pipe;
}
int main()
{
    Pipe pipe;
    pipe = input_pipe();
    print_pipe(pipe);
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
