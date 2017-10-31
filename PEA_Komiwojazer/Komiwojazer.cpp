#include "stdafx.h"
#include "Komiwojazer.h"

using namespace std;

#pragma region basic
Komiwojazer::Komiwojazer()
{
	ilosc_miast = 0;
}


Komiwojazer::~Komiwojazer()
{
	for (int i = 0; i < ilosc_miast; i++) delete[] odleglosci[i];
	delete[] odleglosci;
}

// deklaracje funkcji podstawowych
int Komiwojazer::getIloscMiast() { return ilosc_miast; }
int Komiwojazer::getOdleglosc(int i, int j) { return odleglosci[i][j]; }
void Komiwojazer::setIloscMiast(int ilosc_miast) {
	this -> ilosc_miast = ilosc_miast; 
}
void Komiwojazer::setOdleglosc(int i, int j, int odleglosc) {
	this->odleglosci[i][j] = odleglosc;
}


void Komiwojazer::wyswietl() {
	cout << "\nIlosc miast: " << ilosc_miast << endl << endl;
	for (int i = 0; i < ilosc_miast; i++) {
		for (int j = 0; j < ilosc_miast; j++) {
			cout << setw(4) << odleglosci[i][j] << " ";
		}
		cout << endl << endl;
	}
}

// generator losowych danych dla testow
void Komiwojazer::wygeneruj(int ilosc) {
	if (ilosc <= 0) {
		cout << "Blad! Ilosc miast musi byc dodatnia" << endl;
		return;
	}

	if (ilosc_miast != 0) {
		for (int i = 0; i < ilosc_miast; i++) delete[] odleglosci[i];
		delete[] odleglosci;
	}

	setIloscMiast(ilosc);
	odleglosci = new int*[ilosc];
	for (int i = 0; i < ilosc; i++) odleglosci[i] = new int[ilosc];
	for (int i = 0; i < ilosc; i++) {
		for (int j = 0; j < ilosc; j++) odleglosci[i][j] = 0;
	}

	srand(time(NULL));
	for (int i = 0; i < ilosc; i++) {
		for (int j = 0; j < ilosc; j++) {
			if (i != j) odleglosci[i][j] = (rand() % 19) + 1;
		}
	}
}

// funkcja czyta z pliku o danej nazwie
void Komiwojazer::wczytaj(string nazwa) {
	fstream plik;
	nazwa += ".txt";
	plik.open(nazwa, ios::in);

	if (plik.good()) {
		int n;

		plik >> n;
		ilosc_miast = n;

		odleglosci = new int*[n];
		for (int i = 0; i < n; i++) odleglosci[i] = new int[n];

		for (int i = 0; i < ilosc_miast; i++) {
			for (int j = 0; j < ilosc_miast; j++) {
				plik >> n;
				odleglosci[i][j] = n;
			}
		}
	}

	plik.close();
}
#pragma endregion


// ALGORYTM ZACHLANNY
void Komiwojazer::algorytmZachlanny() {
	// ______________________STOPER_________________________
	start = clock();

	int koszt = 0;
	droga = new int[ilosc_miast];
	int * visited = new int[ilosc_miast];
	for (int i = 1; i < ilosc_miast; i++) {
		visited[i] = 0; // 0 - nieodwiedzone, 1 - odwiedzone
	}

	int curVertex = 0; // aktualny wierzcholek
	int lastIteration = 0; // ostatnia pomyslna iteracja

	for (int i=1; i < ilosc_miast; i++) {
		int minValue = INT_MAX;
		for (int j = 1; j < ilosc_miast; j++) {
			if (odleglosci[curVertex][j] < minValue && odleglosci[curVertex][j] != 0 && visited[j] == 0) {
				minValue = odleglosci[curVertex][j];
				lastIteration = j;
			}
		}
		curVertex = lastIteration;
		visited[curVertex] = 1; // odwiedzone
		droga[i] = curVertex;
		koszt += minValue;
	}
	koszt += odleglosci[curVertex][0];

	stop = clock();
	// ______________________STOPER_________________________

	// przebieg drogi
	droga[0] = 0;
	cout << "Droga: ";
	for (int i = 0; i < ilosc_miast; i++) {
		cout << droga[i] << " -> ";
	}
	cout << "0" << endl;

	// Koszt
	cout << "Koszt: " << koszt << endl;

	// czas wykonania
	czas = (static_cast <double> (stop - start)) / CLOCKS_PER_SEC;
	cout << "Czas wykonania algorytmu: " << czas << endl;
}

// ALGORYTM BRUTE FORCE
void Komiwojazer::bruteForce() {
	start = clock();
	bf = new BruteForce(ilosc_miast, odleglosci);
	bf->execute();
	stop = clock();
	bf->print();
	czas = (static_cast <double> (stop - start)) / CLOCKS_PER_SEC;
	cout << "Czas wykonania algorytmu: " << czas << endl;
}

// ALGORYTM PROGRAMOWANIE DYNAMICZNE
void Komiwojazer::dynamicProgramming() {
	start = clock();
	dp = new DynamiczneProgramowanie(ilosc_miast, odleglosci);
	cout << dp->tsphelper() << endl;
	stop = clock();
	czas = (static_cast <double> (stop - start)) / CLOCKS_PER_SEC;
	cout << "Czas wykonania algorytmu: " << czas << endl;
}