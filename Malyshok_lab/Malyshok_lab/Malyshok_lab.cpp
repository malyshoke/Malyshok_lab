// Malyshok_lab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Malyshok_lab.h"
#include <fstream>


using namespace std;

void print_pipe(Pipe& pipe)
{
    cout << "Information about pipe: " << endl
         << "\tId: " << pipe.id  
         << "\tLength: "  << pipe.length  
         << "\tDiameter: " << pipe.diameter << endl;
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

Pipe load_pipe()
{
    ifstream fin;
    fin.open("data.txt", ios::in);
    if (fin.is_open()) {
        Pipe pipe;
        fin >> pipe.id;
        fin >> pipe.length;
        fin >> pipe.diameter;
        fin.close();
        return pipe;
    }
}

Station load_station()
{
    ifstream fin;
    fin.open("data.txt", ios::in);
    if (fin.is_open()) {
        Station station;
        fin >> station.id;
        fin >> station.name;
        fin >> station.num;
        fin >> station.num_process;
        fin >> station.eff;
        fin.close();
        return station;
    }
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
   // if (station.num_process )
    cout << "Enter the efficiency: ";
    cin >> station.eff;
    return station;
}

void print_station(Station& station)
{
    cout << "Information about station: " << endl 
         << "\tId: " << station.id  
         << "\tName: " << station.name << endl 
         << "\tNumber of factories: " << station.num << endl
         << "\tNumber of factories in process: " << station.num_process << endl
         << "\tEfficiency: " << station.eff << endl;
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

void edit_pipe(Pipe& pipe)
{
    cout << "Please, enter the information about pipe " << endl;
    cout << "Enter the length: ";
    cin >> pipe.length;
    cout << "Enter the diameter: ";
    cin >> pipe.diameter;
}

void edit_station(Station& station)
{
    cout << "Please, enter the information about station " << endl;
    cout << "Please, enter the information about station " << endl;
    cout << "Enter the name: ";
    cin >> station.name;
    cout << "Enter the number of factories: ";
    cin >> station.num;
    cout << "Enter the number of factories in process: ";
    cin >> station.num_process;
    cout << "Enter the efficiency: ";
    cin >> station.eff;
}

void save_pipe(Pipe& pipe)
{
    ofstream fout;
    fout.open("data.txt", ios::out);
    if (fout.is_open()) {
        fout << pipe.id << endl
            << pipe.length << endl
            << pipe.diameter << endl;
        fout.close();
    }

}

void save_station(Station& station)
{
    ofstream fout; 
    fout.open("data.txt", ios::out);
    if (fout.is_open()) {
        fout << station.id << endl
            << station.name << endl
            << station.num << endl
            << station.num_process << endl
            << station.eff << endl;
        fout.close();
    }
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
    while (1)
    {
    print_menu();
    int i = 0;
    cin >> i;
    switch (i)
    {
    case 1:
    {
        pipe = input_pipe();
        break;
    }
    case 2:
    {
        station = input_station();
        break;
    }
    case 3:
    {
        break;
    }
    case 4:
    {   
        edit_pipe(pipe);
        break;
    }
    case 5:
    {
        edit_station(station);
        break;
    }
    case 6:
    {
        save_station(station);
        save_pipe(pipe);
        break;
    }

    case 7:
    {
        station = load_station();
        pipe = load_pipe();
        break;
    }

    case 0:
    {
        return 0;
    }
    default:
    {
        cout << "Wrong action" << endl;
    }   
    }
    }
    
    return 0;
}


