#include <iostream>

#pragma once
class DynamiczneProgramowanie
{
private:
	int ilosc_miast;
	int n;
	int** odleglosci;
	int** p;
	int** g;

public:
	DynamiczneProgramowanie(int, int**);
	~DynamiczneProgramowanie();
	int tsp(int, int);
	int tsphelper();

};

