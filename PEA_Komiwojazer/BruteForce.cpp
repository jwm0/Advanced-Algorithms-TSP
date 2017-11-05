#include "stdafx.h"
#include "BruteForce.h"

using namespace std;


BruteForce::BruteForce(int ilosc_miast, int **tablica)
{
	this->ilosc_miast = ilosc_miast;
	this->odleglosci = tablica;

	minKoszt = INT_MAX;
	droga = new int[this->ilosc_miast];
	wierzcholki = new int[this->ilosc_miast]; // tablica wierzcholkow
	for (int i = 0; i < ilosc_miast; i++) {
		wierzcholki[i] = i;
	}
}


BruteForce::~BruteForce()
{
	delete[] droga;
	delete[] wierzcholki;
}

int BruteForce::getKoszt() { return minKoszt; }

void BruteForce::print() {
	cout << "KOSZT: " << minKoszt << endl;
	for (int i = 0; i < ilosc_miast; i++) {
		cout << droga[i] << " -> ";
	};
	cout << "0" << endl;
}

void BruteForce::execute() {
	licz(wierzcholki, 1, ilosc_miast-1); // (tablica_wierzcholkow, miejsce od ktorego zaczac brute force, ilosc iteracji)
}


void BruteForce::swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void BruteForce::obliczKoszt(int *vertex, int n)
{
	int suma = 0;
	for (int i = 0; i <= n; i++) {
		suma += odleglosci[vertex[i % ilosc_miast]][vertex[(i + 1) % ilosc_miast]];
	}
	if (minKoszt > suma) {
		minKoszt = suma;
		for (int i = 0; i <= n; i++) {
			droga[i] = vertex[i];
		}
	}
}

void BruteForce::licz(int *vertex, int i, int n)
{
	if (i == n) {
		obliczKoszt(vertex, n);
	}
	else {
		for (int j = i; j <= n; j++) {
			swap((vertex + i), (vertex + j));
			licz(vertex, i + 1, n);
			swap((vertex + i), (vertex + j)); // przywroc tablice
		}
	}
}