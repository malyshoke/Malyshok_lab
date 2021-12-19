#pragma once
#include "pch.h"
#include "Malyshok_lab.h"
#include "Pipe.h"
#include "Station.h"
#include "Utils.h"
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
	void AddPipe();
	void AddStation();
	void EditStation();
	void EditPipe();
	void ShowInfo();
	void DeletePipe();
	void DeleteStation();
	void TopologicalSort(const std::unordered_map<int, int>&);
};

