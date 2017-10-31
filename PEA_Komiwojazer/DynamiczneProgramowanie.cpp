#include "stdafx.h"
#include "DynamiczneProgramowanie.h"

using namespace std;

DynamiczneProgramowanie::DynamiczneProgramowanie(int ilosc_miast, int **tablica)
{
	this->ilosc_miast = ilosc_miast;
	this->odleglosci = tablica;

	n = static_cast<int>(pow(2, ilosc_miast));

	g = new int*[this->ilosc_miast]; // TO FIX, KTORE SZYBSZE global czy argument
	p = new int*[this->ilosc_miast];
	for (int i = 0; i < ilosc_miast; i++) {
		g[i] = new int[n];
		p[i] = new int[n];
	}

}


DynamiczneProgramowanie::~DynamiczneProgramowanie()
{
	
	for (int i = 0; i < ilosc_miast; i++) {
		delete[] odleglosci[i];
		delete[] g[i];
		delete[] p[i];
	}
	delete[] odleglosci;
	delete[] g;
	delete[] p;
}


int DynamiczneProgramowanie::tsp(int start, int set) {
	int masked, mask, result = -1, temp;
	if (g[start][set] != -1)
	{
		return g[start][set];
	}
	else
	{
		for (int x = 0; x < ilosc_miast; x++)
		{
			mask = n - 1 - (int)pow(2, x);
			masked = set & mask;
			if (masked != set)
			{
				temp = odleglosci[start][x] + tsp(x, masked);
				if (result == -1 || result > temp)
					result = temp;
				p[start][set] = x;
			}
		}
	}
	g[start][set] = result;
	return result;
}

int DynamiczneProgramowanie::tsphelper()
{
	for (int i = 0; i < ilosc_miast; i++)
	{
		for (int j = 0; j < n; j++)
		{
			g[i][j] = -1;
			p[i][j] = -1;
		}
	}

	// init matrix g ,from distance matrix graph
	for (int i = 0; i < ilosc_miast; i++)
	{
		g[i][0] = odleglosci[i][0];
	}

	return tsp(0, n - 2);
}
