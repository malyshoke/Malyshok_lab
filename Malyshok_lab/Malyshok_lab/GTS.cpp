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

void SavePipes(const unordered_map <int, Pipe>& pipes, ofstream& fout)
{
    for (auto& p : pipes)
        fout << p.second;
}

void SaveStations(const unordered_map <int, Station>& stations, ofstream& fout)
{
    for (auto& s : stations)
        fout << s.second;
}

void LoadAll(unordered_map <int, Pipe>& pipes, unordered_map <int, Station>& stations, ifstream& fin)
{
    int pipecount, stationcount, MaxPipeId, MaxStationId;
    string str;
    fin >> pipecount;
    fin >> MaxPipeId;
    fin >> stationcount;
    fin >> MaxStationId;
    for (int i = 0; i < pipecount; ++i) {
        Pipe mypipe;
        fin >> mypipe;
        pipes.insert({ mypipe.getId(), mypipe });

    }
    for (int i = 0; i < stationcount; ++i) {
        Station mystation;
        fin >> mystation;
        stations.insert({ mystation.getId(), mystation });
    }
    Pipe::setMaxID(MaxPipeId);
    Station::setMaxID(MaxStationId);
}

void AddBranch(unordered_map<int, Pipe>& pipes, unordered_map<int, Station>& stations) {
    cout << "Enter id of pipe you want to link: " << endl;
    int pipeId = check_id(pipes, GetCorrectNumber(0));
    cout << "Enter the id of station where the pipe enters: " << endl;
    int in = check_id(stations, GetCorrectNumber(0));
    cout << "Enter the id of station where the pipe comes out: " << endl;
    int out = check_id(stations, GetCorrectNumber(0));
    if (pipes[pipeId].in == 0 && pipes[pipeId].out == 0 && out != in) {
        pipes[pipeId].link(in, out);
        stations[in].link();
        stations[out].link();
    }
    else
        cout << "Wrong action" << endl;
}

void ShowConnection(const unordered_map<int, Pipe>& pipes, unordered_map<int, Station>& stations)
{
    if (pipes.size() > 0 && stations.size() > 1) {
        cout << "\tPipe's id " << "\tStation's id (pipe in) " << "\tStation's id (pipe out)" << "\tPipe's status" << endl;
        for (auto& [id, p] : pipes)
            if (p.linked())
                p.showLink(id);
            else cout << "\tPipe " << id << " has no connection" << endl;
    }
    else cout << "No connection " << endl;
}

void Disconnect(unordered_map<int, Pipe>& pipes, unordered_map<int, Station>& stations) {
    ShowConnection(pipes, stations);
    cout << "Enter id of pipe you want to disconnect: " << endl;
    int pipeId = check_id(pipes, GetCorrectNumber(0));
    if (pipes[pipeId].linked()) {
        stations[pipes[pipeId].in].untie();
        stations[pipes[pipeId].out].untie();
        pipes[pipeId].untie();
    }
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

    void GTS::SaveInfo()
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
                fout << pipes.size() << endl << Pipe::getMaxID() << endl;
            else fout << 0 << endl << 0 << endl;
            if (stations.size() != 0)
                fout << stations.size() << endl << Station::getMaxID() << endl;
            else fout << 0 << endl << 0 << endl;
            if (pipes.size() != 0)
                SavePipes(pipes, fout);
            if (stations.size() != 0)
                SaveStations(stations, fout);
        }
        fout.close();
    }

    void GTS::LoadInfo()
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
            LoadAll(pipes, stations, fin);
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
        fin.close();
    }

    void GTS::ConnectionWork()
    {
            while (true) {
                cout << endl << "Connection menu" << endl << "1. Connect pipe " << endl << "2. Disconnect pipe " << endl << "3. Show links " << endl
                    << "0. Exit " << endl;
                int input = GetCorrectNumber(0, 4);
                switch (input) {
                case 1: {

                    if (pipes.size() > 0 && stations.size() > 1)
                        AddBranch(pipes, stations);
                    else
                        cout << "No objects to connect " << endl;
                    break;
                }
                case 2: {
                    if (pipes.size() > 0 && stations.size() > 1)
                        Disconnect(pipes, stations);
                    else
                        cout << "No objects to disconnect" << endl;
                    break;

                }
                case 3: {
                    ShowConnection(pipes, stations);
                    break;
                }
                case 0: {
                    return;
                }
                default: {
                    cout << "Wrong action" << endl;
                    break;
                }
                }
            }
        }

    void GTS::DoSort()
    {
        if (pipes.size() > 0 && stations.size() > 1) {
            ribs = AddGraph();
            unordered_map<int, int> VerticesIndex = GetIndexVerticesBack();
            TopologicalSort(VerticesIndex);
        }
        else cout << "No connected objects" << endl;

    }

    vector<vector<int>> GTS::AddGraph()
    {
        unordered_map<int, int> VerticesIndex = GetIndexVertices();
        vector<vector<int>> ribs;
        ribs.resize(VerticesIndex.size());
        for (const auto& [i, p] : pipes)
            if (p.CanBeUsed())
                ribs[VerticesIndex[p.out]].push_back(VerticesIndex[p.in]);
        return ribs;;
    }

    unordered_map<int, int> GTS::GetIndexVertices()
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

    std::unordered_map<int, int> GTS::GetIndexVerticesBack()
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
                VerticesIndex.insert({ i++, v });
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


