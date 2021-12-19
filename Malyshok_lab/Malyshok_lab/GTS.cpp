#include "pch.h"
#include "GTS.h"
using namespace std;
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

GTS::GTS(const vector<vector<int>>& r)
{
    ribs = r;
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


