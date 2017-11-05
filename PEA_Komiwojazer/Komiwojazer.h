#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <algorithm> //temporary
#include "BruteForce.h"
#include "DynamiczneProgramowanie.h"

using namespace std;

class Komiwojazer
{
private:
	BruteForce* bf;
	DynamiczneProgramowanie* dp;
	int ilosc_miast;
	int** odleglosci;
	int* droga;
	time_t start, stop;
	double czas;
	int koszt;

public:
	Komiwojazer();
	~Komiwojazer();

	int getIloscMiast();
	int getOdleglosc(int, int);
	void setIloscMiast(int);
	void setOdleglosc(int, int, int);

	void wyswietl();
	void wygeneruj(int);
	void wczytaj(string);
	void greedy();
	void algorytmZachlanny();
	void bruteForce();
	void dynamicProgramming();
	void testuj(int);
};

