#pragma once
#include <string>
#include <iostream>
#include <conio.h>

using namespace std;
template <typename T>
T GetCorrectNumber(T min)
{
    T x;
    while ((cin >> x).fail() || x < min)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type number greater than: " << min;
    }
    return x;
}

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
int SearchId(const T& map, int id)
{
    if (map.find(id) != map.end()) return id;
    return -1;

}

template <typename T>
void del(T& map)
{
    cout << endl << "Type id: ";
    while (true) {
        int id = GetCorrectNumber(0);
        if (SearchId(map, id) != -1) {
            del_object(map, id);
            cout << "Object was deleted" << endl;
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
int check_id(const T& map, int id)
{

    while (SearchId(map, id) == -1)
    {
        cout << "No object with this id" << endl;
        cout << "Try again" << endl;
        id = GetCorrectNumber(0);
    }
    return id;
}
