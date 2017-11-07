#include <iostream>
#include <list>
#include <algorithm>

#pragma once
class DynamiczneProgramowanie
{
private:
	int ilosc_miast;
	int n;
	std::list <int> droga;
	int** odleglosci;
	int** p;
	int** g;

public:
	DynamiczneProgramowanie(int, int**);
	~DynamiczneProgramowanie();

	int tsp(int, int);
	int tspInit();

	void print();
	void generujDroge(int, int);
};

