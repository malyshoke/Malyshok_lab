#pragma once
#include "pch.h"
#include "Malyshok_lab.h"
#include "Pipe.h"
#include "Station.h"
#include "Utils.h"
#include "Filters.h"
#include <fstream>
#include <set>
#include <vector>
#include <unordered_map>
#include <queue>

class GTS
{
	std::vector<std::vector<int>> ribs;
	std::unordered_map<int, Pipe> pipes;
	std::unordered_map<int, Station> stations;
	vector<vector<double>> weights_matrix;
	vector<vector<int>> throughput_matrix;
	std::vector<std::vector<int>> AddGraph();
	std::unordered_map<int, int> GetIndexVertices();
	std::unordered_map<int, int> GetIndexVerticesBack();
	void TopologicalSort(const std::unordered_map<int, int>&);
	std::vector<std::vector<double>> MatrixWeights();
	vector<vector<int>> MatrixCapacity();
	void Stream(int, int, const unordered_map<int, int>&);
	void Way(int, int, const unordered_map<int, int>&);

public:
	void AddPipe();
	void AddStation();
	void EditStation();
	void EditPipe();
	void ShowInfo();
	void DeletePipe();
	void DeleteStation();
	void SaveInfo();
	void LoadInfo();
	void ConnectionWork();
	void DoSort();
	void FindStream();
	void FindWay();
	void BatchEditing();
};

