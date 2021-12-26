// Malyshok_lab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Malyshok_lab.h"
#include "Pipe.h"
#include "Station.h"
#include "GTS.h"
#include "Utils.h"
#include <fstream>
#include <set>
#include <vector>
#include <unordered_map>

using namespace std;
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
        << "8. Batch editing" << endl
        << "9. Save" << endl
        << "10. Load " << endl
        << "11. Communication work " << endl
        << "12. Topological sort " << endl
        << "0. Exit" << endl;
}

int main()
{
    vector<vector<int>> ribs;
    unordered_map<int, Pipe> pipes;
    unordered_map<int, Station> stations;
    GTS gts;
    while (1)
    {
    print_menu();
    switch (GetCorrectNumber(0,13))
    {
    case 1:
    {   
        gts.AddPipe();
        break;
    }
    case 2:
    {   
        gts.AddStation();
        break;
    }

    case 3:

    {   
        gts.EditPipe();
        break;
    }

    case 4:
    {
        gts.EditStation();
        break;
    }
    case 5:
    {
        gts.ShowInfo();
        break;
    }

    case 6:
    {  
        gts.DeletePipe();
        break;
    }

    case 7:
    {
        gts.DeleteStation();
        break;
    }

    case 8:
    {   
        gts.BatchEditing();
        break;

    }
    case 9:
    {
        gts.SaveInfo();
        break;
    }
       
    case 10:
    {
        gts.LoadInfo();
        break;
    }
    case 11:
    {
        gts.ConnectionWork();
        break;
    }
    case 12:
    {
        gts.DoSort();
        break;
    }
    case 13:
    {
        gts.FindStream();
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


