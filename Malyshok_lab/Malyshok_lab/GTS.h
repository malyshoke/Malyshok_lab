#pragma once
#include "pch.h"
#include "Malyshok_lab.h"
#include "Pipe.h"
#include "Station.h"
#include <fstream>
#include <set>
#include <vector>
#include <unordered_map>
//using namespace std;
class GTS
{
	std::vector<std::vector<int>> ribs;
	std::unordered_map<int, Pipe> pipes;
	std::unordered_map<int, Station> stations;
public:
	std::unordered_map<int, int> GetVerticesIndex();
	GTS(const std::vector<std::vector<int>>& r);
	void TopologicalSort(const std::unordered_map<int, int>&);
	void setPipes(std::unordered_map<int, Pipe> p) { pipes = p; }
	void setStations(std::unordered_map<int, Station> s) { stations = s; }
	void setRibs(std::vector<std::vector<int>> r) { ribs = r; }

};

