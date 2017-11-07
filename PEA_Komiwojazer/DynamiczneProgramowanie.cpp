#include "stdafx.h"
#include "DynamiczneProgramowanie.h"

using namespace std;

DynamiczneProgramowanie::DynamiczneProgramowanie(int ilosc_miast, int **tablica)
{
	// przypisanie wskaznikow dla zmiennych globalnych
	this->ilosc_miast = ilosc_miast;
	this->odleglosci = tablica;

	// utworzenie stalej pomocniczej zmiennej
	n = static_cast<int>(pow(2, ilosc_miast));
	
	// deklaracja tablic dwuwymiarowych
	g = new int*[ilosc_miast]; 
	p = new int*[ilosc_miast];
	for (int i = 0; i < ilosc_miast; i++) {
		g[i] = new int[n];
		p[i] = new int[n];
	}

}


DynamiczneProgramowanie::~DynamiczneProgramowanie()
{	
	// czyszczenie uzytej pamieci
	for (int i = 0; i < ilosc_miast; i++) {
		delete[] g[i];
		delete[] p[i];
	}
	delete[] g;
	delete[] p;
}


int DynamiczneProgramowanie::tsp(int start, int set) {
	int masked, mask, temp;
	int result = -1;
	if (g[start][set] != -1) {
		return g[start][set];
	}
	else {
		for (int x = 0; x < ilosc_miast; x++) {
			mask = n - 1 - (int)pow(2, x);
			masked = set & mask;
			if (masked != set) { // sprawdzenie czy wierzcholek nie wystapil
				temp = odleglosci[start][x] + tsp(x, masked);
				if (result == -1 || result > temp) {
					p[start][set] = x;
					result = temp;
				}
			}
		}
	}
	
	g[start][set] = result;
	return result;
}

// rozpoczecie algorytmu
int DynamiczneProgramowanie::tspInit()
{
	// wype³nienie obu macierzy wartosciami -1
	for (int i = 0; i < ilosc_miast; i++) {
		for (int j = 0; j < n; j++) {
			g[i][j] = -1;
			p[i][j] = -1;
		}
	}

	// inicjalizacja macierzy g z odleglosciami od punktu startowego
	for (int i = 0; i < ilosc_miast; i++) {
		g[i][0] = odleglosci[i][0];
	}

	return tsp(0, n - 2);
}

// wyswietlenie trasy na ekranie
void DynamiczneProgramowanie::print() {
	droga.push_front(0);
	generujDroge(0, n-2);

	for (int n : droga) {
		cout << n << " -> ";
	}
	cout << "0" << endl;
}

void DynamiczneProgramowanie::generujDroge(int start, int set) {
	if (p[start][set] == -1) { 
		return; // dla wylosowanej wartosci rownej -1, zakoncz funkcje
	}
	int x = p[start][set];
	int mask = n - 1 - (int)pow(2, x);
	int masked = set & mask;

	//cout << x << " -> ";
	droga.push_back(x);
	generujDroge(x, masked);
}