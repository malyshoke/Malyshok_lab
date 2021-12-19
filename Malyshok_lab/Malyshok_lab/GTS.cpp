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


bool DepthFirstSearch(int v, vector<char>& cl, vector<int>& p, int& start, const vector<vector<int>>& ribs) {
    cl[v] = 1;
    for (size_t i = 0; i < ribs[v].size(); ++i) {
        int to = ribs[v][i];
        if (cl[to] == 0) {
            p[to] = v;
            if (DepthFirstSearch(to, cl, p, start, ribs))
                return true;
        }
        else if (cl[to] == 1) {
            start = to;
            return true;
        }
    }
    cl[v] = 2;
    return false;
}


