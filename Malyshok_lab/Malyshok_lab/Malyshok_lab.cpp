// Malyshok_lab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Malyshok_lab.h"


using namespace std;

void print_pipe(Pipe& pipe)
{
    cout << "Information about pipe: " << endl
         << "Id: " << pipe.id << endl << "Length: " 
         << pipe.length << endl << "Diameter: " 
         << pipe.diameter;
}

Pipe input_pipe()
{
    Pipe pipe;
    pipe.id = 0;
    cout << "Please, enter the information about pipe " << endl;
    cout << "Enter the length: ";
    cin >> pipe.length;
    cout << "Enter the diameter: ";
    cin >> pipe.diameter;
    return pipe;
}

Station input_station()
{
    Station station;
    station.id = 0;
    cout << "Please, enter the information about station "<< endl;
    cout << "Enter the name: ";
    cin >> station.name;
    cout << "Enter the number of factories: ";
    cin >> station.num;
    cout << "Enter the number of factories in process: ";
    cin >> station.num_process;
    cout << "Enter the efficiency: ";
    cin >> station.eff;
    return station;
}

void print_station(Station& station)
{
    cout << "Information about station: " << endl
         << "Id: " << station.id << endl 
         << "Name: " << station.name << endl 
         << "Number of factories: " << station.num << endl
         << "Number of factories in process: " << station.num_process << endl
         << "Efficiency: " << station.eff << endl;
}

void print_menu()
{
    system("cls");
    cout << " Menu " << endl
        << "1. Add pipe" << endl
        << "2. Add station" << endl
        << "3. View all pipes" << endl
        << "4. Edit pipe" << endl
        << "5. Edit station" << endl
        << "6. Save" << endl
        << "7. Download" << endl
        << "0. Exit" << endl
        << " > " << endl;
}

Pipe edit_pipe()
{
    Pipe pipe;
    cout << "Please, enter the information about pipe " << endl;
    cout << "Enter the length: ";
    cin >> pipe.length;
    cout << "Enter the diameter: ";
    cin >> pipe.diameter;
    return pipe;
}


//int get_variant(int count) {
   // int variant;
   // string s;
  //  getline(cin, s);


int main()
{
    int variant;
    Pipe pipe;
    Station station;
    print_menu();
    station = input_station();
    print_station(station);
    pipe = input_pipe();
    print_pipe(pipe);
    pipe = edit_pipe();
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
