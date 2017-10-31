#include <iostream>
#include <string.h>

#pragma once
class BruteForce
{
private:
	int* wierzcholki; // tablica wierzcholkow {0,...,n-1}
	int ilosc_miast;
	int** odleglosci;
	int minKoszt;
	int* droga; // najszybsza trasa

public:
	BruteForce(int, int**);
	~BruteForce();

	void print();
	void swap(int*, int*);
	void obliczKoszt(int*, int);
	void licz(int*, int, int);
	void execute();
};

