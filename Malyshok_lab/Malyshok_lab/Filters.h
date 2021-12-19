#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Pipe.h"
#include "Station.h"
#include "Utils.h"
#include <unordered_map>
#include <set>


template<typename T, typename T_param>
using Filter = bool (*)(const T& map, T_param param);

void PrintPipesFilters(std::unordered_map<int, Pipe>& pipes);

void PrintStationsFilters(std::unordered_map<int, Station>& stations);

template<typename T, typename T_param>
vector<int> search_filter(const unordered_map<int, T>& map, Filter<T, T_param> f, T_param param) {
    vector<int> res;
    for (auto& m : map)
        if (f(m.second, param))
            res.push_back(m.first);
    return res;
}
