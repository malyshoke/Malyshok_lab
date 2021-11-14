// Malyshok_lab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Malyshok_lab.h"
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

template <typename T>
T GetCorrectNumber1(T min, T max)
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
int SearchId(const T& map, int id)
{
    if (map.find(id) != map.end()) return id;
    return -1;

}

template <typename T>
T GetCorrectNumber2(T min)
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

Pipe input_pipe()
{
    char variant;
    Pipe pipe;
    cout << "Please, enter the information about pipe " << endl;
    cout << "Enter the length: ";
    pipe.length = GetCorrectNumber2(0);
    cout << "Enter the diameter: ";
    pipe.diameter = GetCorrectNumber2(0);
    cout << "Enter 1 if pipe in process or 0 if pipe is not in process" << endl;
    do {
        variant = _getch();
        if (variant != '0' && variant != '1') cout << "Enter the correct value" << endl;
    } while (variant != '0' && variant != '1');
    pipe.in_process = variant == '1';
    pipe_process(pipe);
    return pipe;
}

Station input_station()
{
    Station station;
    cout << "Please, enter the information about station " << endl;
    cout << "Enter the name: ";
    cin.ignore(10000, '\n');
    getline(cin, station.name);
    cout << "Enter the number of factories: ";
    station.num = GetCorrectNumber2(0);
    cout << "Enter the number of factories in process: ";
    station.num_process = GetCorrectNumber1(0, station.num);
    cout << "Enter the efficiency: ";
    station.eff = GetCorrectNumber1(0, 100);
    return station;
}
Pipe load_pipe(ifstream& fin)
{

    if (fin.is_open()) {
        Pipe pipe;
        string s;
        fin >> pipe.id;
        fin >> pipe.length;
        fin >> pipe.diameter;
        fin >> pipe.in_process;
        return pipe;
    }
    return {};
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
    return {};
}

void load_all(unordered_map <int, Pipe>& pipes, unordered_map <int, Station>& stations, ifstream& fin)
{
    int pipecount, stationcount;
    string str;
    fin >> pipecount;
    fin >> stationcount;
    if (pipecount != 0) {
        for (int i = 0; i < pipecount; ++i) {
            Pipe mypipe;
            int id;
            fin >> id;
            fin >> mypipe.length;
            fin >> mypipe.diameter;
            fin >> mypipe.in_process;
            pipes.insert({ id, mypipe });

        }
    }
    if (stationcount != 0) {
        for (int i = 0; i < stationcount; ++i) {
            Station mystation;
            int id;
            fin >> id; 
            getline(fin, str);
            getline(fin, str);
            mystation.name = str;
            //fin >> mystation.name;
            fin >> mystation.num;
            fin >> mystation.num_process;
            fin >> mystation.eff;
            stations.insert({ id, mystation });
        }
    }
}



void print_pipe(const pair <int, Pipe>& pipe)
{
    cout << "\tId: " << pipe.first
        << "\tLength: " << pipe.second.length
        << "\tDiameter: " << pipe.second.diameter << endl;
    pipe_process(pipe.second);
    cout << endl;
}

void print_station(const pair <int, Station>& station)
{
      cout << "\tId: " << station.first
        << "\tName: " << station.second.name << endl
        << "\tNumber of factories: " << station.second.num << endl
        << "\tNumber of factories in process: " << station.second.num_process << endl
        << "\tEfficiency: " << station.second.eff << endl;
      cout << endl; 
}

void print_pipes(const unordered_map <int, Pipe>& pipes)
{
    for (auto& p : pipes) print_pipe(p);
}

void print_stations(const unordered_map <int, Station>& stations)
{
    for (auto& s : stations) print_station(s);
}

void print_menu()
{
    cout << " Menu " << endl
        << "1. Add pipe" << endl
        << "2. Add station" << endl
        << "3. Edit pipe" << endl
        << "4. Edit station" << endl
        << "5. Show " << endl
        << "6. Delete pipe" << endl
        << "7. Delete station" << endl
        << "8. Search station by name" << endl
        << "9. Save" << endl
        << "10. Load " << endl
        << "0. Exit" << endl;
}

void pipe_process(const Pipe& pipe)
{
    if (pipe.in_process)
        cout << "Pipe is in process" << endl;
    else
        cout << "Pipe is not in process" << endl;
}

void edit_pipe(Pipe & pipe)
{
        pipe.in_process = !pipe.in_process;
        //pipe_process(pipe);
}

void edit_pipes(unordered_map <int, Pipe>& pipes)
{
    int id; 
    cout << endl << "Type id: ";
    while (true) {
        int id = GetCorrectNumber2(0);
        if (SearchId( pipes, id) != -1) {
            edit_pipe(pipes[id]);
            cout << "Object was edited" << endl;
            return;
        }
        else cout << "No object with this id" << endl;
    }
}

void edit_station(Station& station)
{
    int n;
    char variant;
        cout << "Enter 1 if factories were added to work or 0 if factories were excluded from work" << endl;
        do {
            variant = _getch();
            if (variant != '0' && variant != '1') cout << "Enter the correct value" << endl;
        } while (variant != '0' && variant != '1');
        if (variant == '1') {
            cout << "Enter how many factories were added to work " << endl;
            n = GetCorrectNumber1(0, (station.num - station.num_process));
            station.num_process = station.num_process + n;
        }
        else {
            cout << "Enter how many factories were excluded from work " << endl;
            n = GetCorrectNumber1(0, (station.num_process));
            station.num_process = station.num_process - n;
        }
}

void edit_stations(unordered_map <int, Station>& stations)
{
    int id;
    cout << endl << "Type id: ";
    while (true) {
        int id = GetCorrectNumber2(0);
        if (SearchId(stations, id) != -1) {
            edit_station(stations[id]);
            cout << "Object was edited" << endl;
            return;
        }
        else cout << "No object with this id" << endl;
    }
}

template <typename T>
void del_object(T& map, int id)
{
    if (map.find(id) != map.end()) {
        map.erase(id);
    }
}

template <typename T>
void del(T& map)
{
    cout << endl << "Type id: ";
    while (true) {
        int id = GetCorrectNumber2(0);
        if (SearchId(map, id) != -1) {
            del_object(map, id);
            cout << "Object was deleted" << endl;
            return;
        }
        else cout << "No object with this id" << endl;
    }
}
void save_pipe(const Pipe& pipe, ofstream& fout)
{   
   
    if (fout.is_open()) {
        fout << pipe.id << endl
            << pipe.length << endl
            << pipe.diameter << endl
            << pipe.in_process << endl;
    }

}

void save_station(const Station& station, ofstream& fout)
{
    
    if (fout.is_open()) {
        fout << station.id << endl
            << station.name << endl
            << station.num << endl
            << station.num_process << endl
            << station.eff << endl;
     
    }
}

void save_pipes(const unordered_map <int, Pipe>& pipes, ofstream& fout)
{
    for (auto& p : pipes)         
        fout << p.first << endl
        << p.second.length << endl
        << p.second.diameter << endl
        << p.second.in_process << endl;;
}

void save_stations(const unordered_map <int, Station>& stations, ofstream& fout)
{
    for (auto& s : stations)         
        fout << s.first << endl
        << s.second.name << endl
        << s.second.num << endl
        << s.second.num_process << endl
        << s.second.eff << endl;;
}

//template <typename T>
//T& select(const T& map)
//{
//    cout << endl << "Type id: ";
//    while (true) {
//        int id = GetCorrectNumber2(0);
//        if (SearchId(map, id) != -1) {
//
//            return (map, id);
//        }
//        else cout << "No object with this id" << endl;
//    }
//}


//
//Pipe& SelectPipe(const unordered_map <int, Pipe>& p)
//{
//    cout << "Enter index: " << endl;
//    unsigned int index = GetCorrectNumber1<uint64_t>(1, p.size());
//    return { index, p[index-1] };
// }

//Station& SelectStation(const unordered_map <int, Station>& s)
//{
//    cout << "Enter index: " << endl;
//    unsigned int index = GetCorrectNumber1<uint64_t>(1, s.size());
//    return s[index - 1];
//}

template <typename T>
int search_name(const unordered_map <int, T>& t, string name)
{
    int i = 0;
    for (auto& s : t) {
        if (s.second.name == name)
            return s.first;
    }
    return -1;
}

vector<int> search_repair(const unordered_map <int, Pipe>& pipes, const bool& r)
{
    int i = 0;
    vector<int> index;
    for (auto& p : pipes) {
        if (p.second.in_process == r)
            index.emplace_back(p.first);
    }
    return index;
}

vector<int> search_ratio(const unordered_map <int, Station>& stations, double per)
{
    int i = 0;
    vector<int> index;
    for (auto& s : stations) {
        if (round(((double(s.second.num) - double(s.second.num_process)) / double(s.second.num)) * 100) == per)
            index.emplace_back(s.first);
    }
    return index;
}

int main()
{
    unordered_map<int, Pipe> pipes;
    unordered_map<int, Station> stations;
    int stationcount = 1;
    int pipecount = 1;
    while (1)
    {
    print_menu();
    switch (GetCorrectNumber1(0,11))
    {
    case 1:
    {  
        int id = pipes.size() + 1;
        pipes.insert({id, input_pipe()});
        break;
    }
    case 2:
    {
        int id = stations.size() + 1;
        stations.insert({id, input_station()});
        break;
    }

    case 3:

    {   if (pipes.size() == 0) 
        cout << "No pipe to edit" << endl;
    else {
        edit_pipes(pipes);
        print_pipes(pipes);
    }
    break;
    }

    case 4:
    {   if (stations.size() == 0) {
        cout << "No station to edit" << endl;
    }
    else {
       edit_stations(stations);
       print_stations(stations);
    }
    break;
    }

    case 5:
    {
        cout << "Information about pipes:" << endl;
        if (pipes.size() == 0) {
            cout << "No pipes" << endl;
        }
        else
        print_pipes(pipes);
        cout << "Information about stations:" << endl;
        if (stations.size() == 0) {
            cout << "No stations" << endl;
        }
        else
            print_stations(stations);
        break;
    }

    case 6:
    {  
        if (pipes.size() == 0)
            cout << "No pipes to delete" << endl;
        else {
            print_pipes(pipes);
            del(pipes);
    }
        break;
    }

    case 7:
    {
        if (stations.size() == 0)
            cout << "No stations to delete" << endl;
        else {
            print_stations(stations);
            del(stations);
        }
        break;
    }

    case 8:
    {   //поиск по имени
        string name = "";
        cout << "Type name of station: ";
        cin.ignore(10000, '\n');
        getline(cin, name);
        int i = search_name(stations, name);
        if (i != -1) {
            cout << "Stations with this name: " << endl;
            print_station({ i,stations[i] });
        }
        else 
            cout << "No stations with this name" << endl;

        //поиск по признаку "в ремонте"
        char variant;
        cout << "Enter 1 if you want to search pipe is under repair, 0 if is not under repair: " << endl;
        do {
            variant = _getch();
            if (variant != '0' && variant != '1') cout << endl << "Enter the correct value" << endl;
        } while (variant != '0' && variant != '1'); 
         if (variant == '1' || variant == '0') {
          (variant == '1') ? cout << "Pipes is in process: " << endl : cout << "Pipes is not in process:" << endl; 
                vector<int> index = search_repair(pipes, (variant == '1') ? true : false);
                if (index.size() != 0) {
                    for (auto& p : index) {
                        print_pipe({ p,pipes[p] });
                    }
                }
                else cout << "No pipes" << endl;
            }

        //поиск по проценту задействованных цехов
        cout << "Type percentage of factories is not in process: ";
        double percent = GetCorrectNumber1(0, 100);
        vector<int> index = search_ratio(stations, percent);
        if (index.size() != 0) {
            cout << "Stations with this ratio: " << endl;
            for (auto& i : index) {
                print_station({i,stations[i]});
            }
        }
        else cout << "No stations" << endl;
        break;

    }
    case 9:
    {
        string name = "";
        cout << "Type name of file: ";
        cin.ignore(10000, '\n');
        getline(cin, name);
        name = name + ".txt";
        ofstream fout;
        fout.open(name, ios::out);
        if (!fout.is_open())
            cout << "Unable to open file" << endl;
        else {
            if (pipes.size() != 0)
                fout << pipes.size() << endl;
            else fout << 0 << endl;
            if (stations.size() != 0)
                fout << stations.size() << endl;
            else fout << 0 << endl;
            if (pipes.size() != 0)
                save_pipes(pipes, fout);
            if (stations.size() != 0)
                save_stations(stations, fout);
        }
        fout.close();
        break;
    }
       
    case 10:
    {
        string name = " ";
        cout << "Type name of file: ";
        cin.ignore(10000, '\n');
        getline(cin, name);
        name = name + ".txt";
        ifstream fin;
        fin.open(name, ios::in);
        if (!fin.is_open())
            cout << "Unable to open file" << endl;
        else {
            load_all(pipes, stations, fin);
            cout << "Information about pipes:" << endl;
            if (pipes.size() == 0) {
                cout << "No pipes" << endl;
            }
            else
                print_pipes(pipes);
            cout << "Information about stations:" << endl;
            if (stations.size() == 0) {
                cout << "No stations" << endl;
            }
            else
                print_stations(stations);
            
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


