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

	std::unordered_map<int, Pipe> pipes;
	std::unordered_map<int, Station> stations;
public:
	std::unordered_map<int, int> GetVerticesIndex();

};

