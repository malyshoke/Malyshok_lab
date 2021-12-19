#include "pch.h"
#include "Filters.h"
using namespace std;

template <typename T>
bool search_name(const T& map, string name)
{

    return map.getName() == name;
}

bool search_repair(const Pipe& pipes, const bool& r)
{

    return pipes.getProc() == r;
}

vector<int> search_repair(const unordered_map <int, Pipe>& pipes, const bool& r)
{
    int i = 0;
    vector<int> index;
    for (auto& p : pipes) {
        if (p.second.getProc() == r)
            index.emplace_back(p.first);
    }
    return index;
}

bool search_ratio(const Station& stations, double per)
{
    return (round(((double(stations.getNum()) - double(stations.getNumP()) / double(stations.getNum()) * 100) == per)));
}
void PrintPipesFilters(std::unordered_map<int, Pipe>& pipes)
{
    if (pipes.size() == 0) {
        cout << "No pipes " << endl;
        return;
    }
    while (true) {
        cout << endl << "Pipe editing" << endl << "1. Search for pipes by name" << endl
            << "2. Search for pipes on the basis of repair" << endl << "3. Search for pipes by id " << endl << "0. Exit "
            << endl;
        switch (GetCorrectNumber(0, 3)) {
        case 1: {
            cout << "Type name of pipe: ";
            string name = "";
            cin.ignore(10000, '\n');
            getline(cin, name);
            vector<int> index = search_filter(pipes, search_name, name);
            if (index.size() != 0) {
                cout << "Found " << index.size() << " pipes" << endl;
                for (auto& id : index) {
                    cout << pipes[id];
                }
                cout << "1. Edit found pipes" << endl << "2. Delete found pipes" << endl << "0. Exit" << endl;
                switch (GetCorrectNumber(0, 2)) {
                case 1: {
                    for (auto& id : index) {
                        pipes[id].edit();
                        cout << pipes[id];
                    }
                    break;
                }
                case 2: {
                    for (auto& id : index) {
                        del_object(pipes, id);
                    }
                    cout << "Objects were deleted" << endl;
                    break;
                }
                case 0:
                    return;
                default:
                    cout << "Wrong action" << endl;
                    break;
                }
            }
            else cout << "No pipes" << endl;
            break;
        }
        case 2: {
            char variant;
            cout << "Enter 1 if you want to search pipe is not under repair, 0 if is under repair: " << endl;
            do {
                variant = _getch();
                if (variant != '0' && variant != '1') cout << endl << "Enter the correct value" << endl;
            } while (variant != '0' && variant != '1');
            if (variant == '1' || variant == '0') {
                (variant == '1') ? cout << "Pipes is in process: " << endl : cout << "Pipes is not in process:" << endl;
                vector<int> index = search_repair(pipes, (variant == '1') ? true : false);
                if (index.size() != 0) {
                    cout << "Found " << index.size() << " pipes" << endl;
                    for (auto& id : index) {
                        cout << pipes[id];
                    }
                    cout << "1. Edit found pipes" << endl << "2. Delete found pipes" << endl << "0. Exit" << endl;
                    switch (GetCorrectNumber(0, 2)) {
                    case 1: {
                        for (auto& id : index) {
                            pipes[id].edit();
                            cout << pipes[id];
                        }
                        break;
                    }
                    case 2: {
                        for (auto& id : index) {
                            del_object(pipes, id);
                        }
                        cout << "Objects were deleted" << endl;
                        break;
                    }
                    case 0:
                        return;
                    default:
                        cout << "Wrong action" << endl;
                        break;
                    }
                }
                else cout << "No pipes" << endl;
            }
            else
                cout << "Wrong action " << endl;
            break;
        }
        case 3: {
            cout << "Enter id of pipes you want to edit or 0 to complete the entry: " << endl;
            int variant;
            vector<int> edit_id;
            do {
                variant = GetCorrectNumber(0);
                if (SearchId(pipes, variant) != -1)
                    edit_id.emplace_back(variant);
            } while (variant != 0);
            if (edit_id.size() != 0) {
                cout << "Objects were edited" << endl;
                for (auto& id : edit_id) {
                    pipes[id].edit();
                    cout << pipes[id] << endl;
                }
            }
            else cout << "No pipes with this id" << endl;
            break;
        }
        case 0:
            return;
        default:
            cout << "Wrong action" << endl;
            break;
        }
    }
}

void PrintStationsFilters(std::unordered_map<int, Station>& stations)
{
    if (stations.size() == 0) {
        cout << "No stations" << endl;
        return;
    }
    while (true) {
        cout << endl << "Stations editing" << endl << "1. Search for stations by name" << endl
            << "2. Search for stations by ratio" << endl << "3. Search for stations by id " << endl << "0. Exit" << endl;
        int FilterCase = GetCorrectNumber(0, 3);
        switch (FilterCase) {
        case 1: {
            cout << "Type name of station: " << endl;
            string name = "";
            cin.ignore(10000, '\n');
            getline(cin, name);
            vector<int> index = search_filter(stations, search_name, name);
            if (index.size() != 0) {
                cout << "Found " << index.size() << " stations" << endl;
                for (auto& id : index) {
                    cout << stations[id];
                }
                cout << "1. Edit found stations" << endl << "2. Delete found stations" << endl << "0. Exit" << endl;
                switch (GetCorrectNumber(0, 2)) {
                case 1: {
                    for (auto& id : index) {
                        cout << stations[id];
                        stations[id].edit();
                        cout << stations[id] << endl;
                    }
                    break;
                }
                case 2: {
                    for (auto& id : index) {
                        del_object(stations, id);
                    }
                    cout << "Objects were deleted" << endl;
                    break;
                }
                case 0:
                    return;
                default:
                    cout << "Wrong action" << endl;
                    break;
                }
            }
            else cout << "No stations" << endl;
            break;
        }
        case 2: {
            cout << "Type percentage of factories is not in process: " << endl;
            double percent = GetCorrectNumber(0);
            if (percent <= 100 && percent >= 0) {
                vector<int> index = search_filter(stations, search_ratio, percent);
                if (index.size() != 0) {
                    cout << "Found " << index.size() << " stations" << endl;
                    for (auto& id : index) {
                        cout << stations[id];
                    }
                    cout << "1. Edit found stations" << endl << "2. Delete found stations" << endl << "0. Exit" << endl;
                    switch (GetCorrectNumber(0, 2)) {
                    case 1: {
                        for (auto& id : index) {
                            cout << stations[id];
                            stations[id].edit();
                            cout << stations[id] << endl;
                        }
                        break;
                    }
                    case 2: {
                        for (auto& id : index) {
                            del_object(stations, id);
                        }
                        cout << "Objects were deleted" << endl;
                        break;
                    }
                    case 0:
                        return;
                    default:
                        cout << "Wrong action" << endl;
                        break;
                    }
                }
                else
                    cout << "No stations " << endl;
            }
            else
                cout << "Wrong action " << endl;
            break;
        }
        case 3: {
            cout << "Enter id of stations you want to edit or 0 to complete the entry: " << endl;
            int variant;
            vector<int> edit_id;
            do {
                variant = GetCorrectNumber(0);
                if (SearchId(stations, variant) != -1)
                    edit_id.emplace_back(variant);
            } while (variant != 0);
            if (edit_id.size() != 0) {
                for (auto& id : edit_id) {
                    cout << stations[id] << endl;
                    stations[id].edit();
                    cout << "Object was edited" << endl;
                    cout << stations[id];
                }
            }
            else cout << "No stations with this id" << endl;
            break;
        }
        case 0:
            return;
        default:
            cout << "Wrong action" << endl;
            break;
        }
    }
}
