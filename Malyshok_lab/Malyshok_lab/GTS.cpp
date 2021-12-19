#include "pch.h"
#include "GTS.h"
using namespace std;
//из main
int EditPipes(unordered_map <int, Pipe>& pipes)
{
    cout << endl << "Type id: ";
    while (true) {
        int id = GetCorrectNumber(0);
        if (SearchId(pipes, id) != -1) {
            pipes[id].edit();
            cout << "Object was edited" << endl;
            return id;
        }
        else cout << "No object with this id" << endl;
    }
}

int EditStations(unordered_map <int, Station>& stations)
{
    cout << endl << "Type id: ";
    while (true) {
        int id = GetCorrectNumber(0);
        if (SearchId(stations, id) != -1) {
            stations[id].edit();
            cout << "Object was edited" << endl;
            return id;
        }
        else cout << "No object with this id" << endl;
    }
}

void PrintPipes(const unordered_map<int, Pipe>& pipes)
{
    for (auto& [id, p] : pipes)
        cout << p;
}

void PrintStations(const unordered_map<int, Station>& stations)
{
    for (const auto& [id, s] : stations)
        cout << s;
}

void GTS::AddPipe()
{
    Pipe pipe;
    cin >> pipe;
    pipes.insert({ pipe.getId(),pipe });
}

void GTS::AddStation()
{
    Station station;
    cin >> station;
    stations.insert({ station.getId(),station });
}

void GTS::EditStation()
{
        if (stations.size() == 0) {
            cout << "No station to edit" << endl;
        }
        else {
            int id = EditStations(stations);
            cout << stations[id];
        }
    }

    void GTS::EditPipe()
    {
        if (pipes.size() == 0)
            cout << "No pipe to edit" << endl;
        else {
            int id = EditPipes(pipes);
            cout << pipes[id];
        }
    }

    void GTS::ShowInfo()
    {
        cout << "Information about pipes:" << endl;
        if (pipes.size() == 0) {
            cout << "No pipes" << endl;
        }
        else
            PrintPipes(pipes);
        cout << "Information about stations:" << endl;
        if (stations.size() == 0) {
            cout << "No stations" << endl;
        }
        else
            PrintStations(stations);
    }

    void GTS::DeletePipe()
    {
        if (pipes.size() == 0)
            cout << "No pipes to delete" << endl;
        else {
            PrintPipes(pipes);
            del(pipes);
        }
    }

    void GTS::DeleteStation()
    {
        if (stations.size() == 0)
            cout << "No stations to delete" << endl;
        else {
            PrintStations(stations);
            del(stations);
        }
    }


unordered_map<int, int> GTS::GetVerticesIndex()
{
    set<int> vertices;
    for (const auto& [i, p] : pipes)
        if (p.CanBeUsed() && stations.count(p.in) && stations.count(p.out)) {
            vertices.insert(p.out);
            vertices.insert(p.in);
        }
    unordered_map<int, int> VerticesIndex;
    int i = 0;
    for (const int& v : vertices) 
        VerticesIndex.insert({ v, i++ });
    return VerticesIndex;
}


void DepthFirstSearch(int v, vector<char>& cl, vector<int>& p, int& start, const vector<vector<int>>& ribs, vector<int>& result) 
{
    cl[v] = 1;
    for (size_t i = 0; i < ribs[v].size(); ++i) {
        int to = ribs[v][i];
        if (cl[to] == 0) {
            p[to] = v;
            DepthFirstSearch(to, cl, p, start, ribs, result);
        }
        else if (cl[to] == 1) {
            start = to;
            return;
        }
    }
    result.push_back(v);
    cl[v] = 2;
}

void GTS::TopologicalSort(const unordered_map<int, int>& VerticesIndex) {
    int n = ribs.size();
    vector<int> result;
    vector<char> cl;
    vector<int> p;
    int cycle_start;
    p.assign(n, -1);
    cl.assign(n, 0);
    cycle_start = -1;
    result.clear();
    for (int i = 0; i < n; ++i)
        if (cl[i] != 2)
            DepthFirstSearch(i, cl, p, cycle_start, ribs, result);
    if (cycle_start == -1) {
        reverse(result.begin(), result.end());
        for (int i = 0; i < result.size(); i++) {
            cout << " Station "  << VerticesIndex.at(result[i]) << " -> ";
        }
        cout << endl;
    }
    else
        cout << "Sorting cannot be applied to a graph containing a cycle " << endl;
}


