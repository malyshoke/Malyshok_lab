// Malyshok_lab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Malyshok_lab.h"
#include <fstream>


using namespace std;
template <typename T>

T GetCorrectNumber(T min, T max)
{
    T x;
    while ((cin >> x).fail() || x < min || x > max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type number (" << min << "-" << max << "):";
    }
    return x;
}

template <typename T>
T GetCorrectNumber(T min)
{
    T x;
    while ((cin >> x).fail() || x < min)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type number (0...): ";
    }
    return x;
}

void print_pipe(Pipe& pipe)
{
    cout << "Information about pipe: " << endl
         << "\tId: " << pipe.id  
         << "\tLength: "  << pipe.length  
         << "\tDiameter: " << pipe.diameter << endl;
}

Pipe input_pipe()
{
    char variant;
    Pipe pipe;
    pipe.id = 1;
    cout << "Please, enter the information about pipe " << endl;
    cout << "Enter the length: ";
    pipe.length = GetCorrectNumber(0);
    cout << "Enter the diameter: ";
    pipe.diameter = GetCorrectNumber(0);
    cout << "Enter 1 if pipe in process or 0 if pipe is not in process" << endl;
    do {
    variant = _getch();
    if (variant != '0' && variant != '1') cout << "Enter the correct value" << endl;
     } while (variant != '0' && variant != '1');
    variant == '1' ? pipe.in_process = true : pipe.in_process = false;
    if (pipe.in_process)
        cout << "Pipe in process" << endl;
    else 
        cout << "Pipe is not in process" << endl;
    return pipe;
}

Pipe load_pipe(ifstream& fin)
{
   
    if (fin.is_open()) {
        Pipe pipe;
        fin >> pipe.id;
        fin >> pipe.length;
        fin >> pipe.diameter;
        return pipe;
    }
}

Station load_station(ifstream& fin)
{
  
    if (fin.is_open()) {
        Station station;
        fin >> station.id;
        fin >> station.name;
        fin >> station.num;
        fin >> station.num_process;
        fin >> station.eff;
        return station;
    }
}

Station input_station()
{
    Station station;
    station.id = 1;
    cout << "Please, enter the information about station "<< endl;
    cout << "Enter the name: ";
    cin >> station.name;
    cout << "Enter the number of factories: ";
    cin >> station.num;
    cout << "Enter the number of factories in process: ";
    station.num_process = GetCorrectNumber(0, station.num);
    cout << "Enter the efficiency: ";
    station.eff = GetCorrectNumber(0, 100);
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
    cout << " Menu " << endl
        << "1. Add pipe" << endl
        << "2. Add station" << endl
        << "3. Edit pipe" << endl
        << "4. Edit station" << endl
        << "5. Save" << endl
        << "6. Load " << endl
        << "0. Exit" << endl;
}

void edit_pipe(Pipe& pipe)
{
    char variant;
    cout << "Enter 1 if pipe in process or 0 if pipe is not in process" << endl;
    do {
    variant = _getch();
    if (variant != '0' && variant != '1') cout << "Enter the correct value" << endl;
     } while (variant != '0' && variant != '1');
    variant == '1' ? pipe.in_process = true : pipe.in_process = false;
    if (pipe.in_process)
        cout << "Pipe in process" << endl;
    else 
        cout << "Pipe is not in process" << endl;
    pipe.in_process = !pipe.in_process;
}

void edit_station(Station& station)
{
    int n;
    char variant;
    cout << "Enter 1 if factories were added to work or 0 if factories were ecluded from work" << endl;
    do {
        variant = _getch();
        if (variant != '0' && variant != '1') cout << "Enter the correct value" << endl;
    } while (variant != '0' && variant != '1');
    if (variant) {
        cout << "Enter how many factories were added to work " << endl;
        n = GetCorrectNumber(0, (station.num - station.num_process));
        station.num_process = station.num_process + n;
    }
    else cout << "Enter how many factories were ecluded from work " << endl;
         n = GetCorrectNumber(0, (station.num_process));
         station.num_process = station.num_process - n;

}

void save_pipe(Pipe& pipe, ofstream& fout)
{   
   
    if (fout.is_open()) {
        fout << pipe.id << endl
            << pipe.length << endl
            << pipe.diameter << endl;
    }

}

void save_station(Station& station, ofstream& fout)
{
    
    if (fout.is_open()) {
        fout << station.id << endl
            << station.name << endl
            << station.num << endl
            << station.num_process << endl
            << station.eff << endl;
        
    }
}

int main()
{
    
    Pipe pipe = {};
    Station station;
    station.id = 0;
    pipe.id = 0;
    while (1)
    {
    print_menu();
    switch (GetCorrectNumber(0,6))
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
        edit_pipe(pipe);
        break;
    }
    case 4:
    {   
        edit_station(station);
        break;
    }

    case 5:

    {   ofstream fout;
        fout.open("data.txt", ios::out);
        if (station.id != 0)
            save_station(station, fout);
        if (pipe.id != 0)
            save_pipe(pipe, fout);
        fout.close();
        break;
    }

    case 6:
    {   ifstream fin;
        fin.open("data.txt", ios::in);

        if (station.id == 0) {
            cout << "No station" << endl;
        }
        else
        {
            station = load_station(fin);
            print_station(station);
        }

        if (pipe.id == 0) {
            cout << "No pipe" << endl;
        }
        else {
            pipe = load_pipe(fin);
            print_pipe(pipe);
        }
        fin.close();
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


