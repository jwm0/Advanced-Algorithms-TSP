#include "stdafx.h"
#include "Komiwojazer.h"



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


void Komiwojazer::greedy() {
	koszt = 0;
	droga = new int[ilosc_miast];
	int * visited = new int[ilosc_miast];
	for (int i = 1; i < ilosc_miast; i++) {
		visited[i] = 0; // 0 - nieodwiedzone, 1 - odwiedzone
	}

	int curVertex = 0; // aktualny wierzcholek
	int lastIteration = 0; // ostatnia pomyslna iteracja

	for (int i = 1; i < ilosc_miast; i++) {
		int minValue = INT_MAX;
		for (int j = 1; j < ilosc_miast; j++) {
			if (odleglosci[curVertex][j] < minValue && visited[j] == 0) {
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
}

// ALGORYTM ZACHLANNY
void Komiwojazer::algorytmZachlanny() {
	// ______________________STOPER_________________________
	start = clock();
	greedy();
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
	delete bf;
}

// ALGORYTM PROGRAMOWANIE DYNAMICZNE
void Komiwojazer::dynamicProgramming() {
	start = clock();
	dp = new DynamiczneProgramowanie(ilosc_miast, odleglosci);
	cout << "Koszt: " << dp->tspInit() << endl;
	stop = clock();
	dp->print();
	czas = (static_cast <double> (stop - start)) / CLOCKS_PER_SEC;
	cout << "Czas wykonania algorytmu: " << czas << endl;
	delete dp;
}

// ALGORYTM TABU SEARCH
void Komiwojazer::tabuSearch() {
	int wybor_operacji;
	cout << "1. Domyslne parametry" << endl;
	cout << "2. Wlasne parametry z losowym rozmiarem tabu" << endl;
	cout << endl << "---> ";

	cin >> wybor_operacji;

	switch (wybor_operacji) {
	case 1:
		{
			start = clock();
			ts = new Tabu(ilosc_miast, odleglosci);
			ts->startAlgorithm(10, 400, 200, 20);
			stop = clock();
			cout << ts->getSolutionToString(ts->najlepszeRozwiazanie, ts->minKoszt) << endl;
			czas = (static_cast <double> (stop - start)) / CLOCKS_PER_SEC;
			cout << "Czas wykonania algorytmu: " << czas << endl;
			delete ts;
		}
		break;
	case 2:
		{
			int defaultParams[] = { 10, 400, 200, 20 };
			int wybor;
			cout << "Podaj liczbe sasiadow: ";
			cin >> wybor;
			if (wybor > 0) defaultParams[1] = wybor;
			cout << "\nPodaj liczbe iteracji bez poprawy wyniku: ";
			cin >> wybor;
			if (wybor > 0) defaultParams[2] = wybor;
			cout << "\nPodaj liczbe losowo wygenerowanych drog: ";
			cin >> wybor;
			if (wybor > 0) defaultParams[3] = wybor;

			start = clock();
			int tabuSize[] = { 5, 10, 15, 20, 50 };
			int bestCost = INT_MAX;
			vector<int> bestRoute;
			
			for (int i = 0; i < 5; i++) {
				ts = new Tabu(ilosc_miast, odleglosci);
				ts->startAlgorithm(tabuSize[i], defaultParams[1], defaultParams[2], defaultParams[3]);
				if (ts->minKoszt < bestCost) {
					bestCost = ts->minKoszt;
					bestRoute = ts->najlepszeRozwiazanie;
				}
			}

			stop = clock();
			cout << ts->getSolutionToString(bestRoute, bestCost) << endl;
			czas = (static_cast <double> (stop - start)) / CLOCKS_PER_SEC;
			cout << "Czas wykonania algorytmu: " << czas << endl;
			delete ts;
		}
	default:
		{
			return;
		}
		break;
	}

}

void Komiwojazer::testuj(int ile_testow) {
	string instancje[] = { "gr21", "gr48", "eil76", "br17", "kro124", "rbg443" }; // 3 tsp, 3 atsp
	int tabuSize[] = { 1, 2, 5, 10, 20, 50, 100 };
	int neighbourSize[] = { 5, 10, 20, 40, 100, 200, 400, 800 };
	double sumaCzasu;
	double sumaKosztu;

	int ile_pomiarow = 5;

	for (int i = 0; i < 6; i++) {
		cout << "==== " << instancje[i] << " ====" << endl;
		string file_name = "./Testy/" + instancje[i] + "_wyniki.txt";
		ofstream file;
		file.open(file_name, std::ios_base::app);
		wczytaj(instancje[i]);

		// ROZMIAR TABU
		file << "Rozmiar tabu" << " ; " << "Sredni koszt" << " ; " << "Sredni czas" << endl;
		for (int j = 0; j < 7; j++) {
			cout << "== Rozmiar tabu: " << tabuSize[j] << " ==" << endl;
			sumaCzasu = 0;
			sumaKosztu = 0;
			for (int k = 0; k < ile_pomiarow; k++) {
				start = clock();
				ts = new Tabu(ilosc_miast, odleglosci);
				ts->startAlgorithm(tabuSize[j]);
				stop = clock();
				czas = (static_cast <double> (stop - start)) / CLOCKS_PER_SEC;
				sumaCzasu += czas;
				sumaKosztu += ts->minKoszt;
				//cout << k << ". Koszt: " << ts->minKoszt << "	Czas: " << czas << endl;
				delete ts;
			}
			file << tabuSize[j] << " ; " << sumaKosztu / ile_pomiarow << " ; " << sumaCzasu / ile_pomiarow << std::endl; //zapisujemy wyniki do plik
		}

		// ILOSC SASIADOW
		file << "Ilosc sasiadow" << " ; " << "Sredni koszt" << " ; " << "Sredni czas" << endl;
		for (int j = 0; j < 8; j++) {
			cout << "== Ilosc sasiadow: " << neighbourSize[j] << " ==" << endl;
			sumaCzasu = 0;
			sumaKosztu = 0;
			for (int k = 0; k < ile_pomiarow; k++) {
				start = clock();
				ts = new Tabu(ilosc_miast, odleglosci);
				ts->startAlgorithm(10,neighbourSize[j]);
				stop = clock();
				czas = (static_cast <double> (stop - start)) / CLOCKS_PER_SEC;
				sumaCzasu += czas;
				sumaKosztu += ts->minKoszt;
				//cout << k << ". Koszt: " << ts->minKoszt << "	Czas: " << czas << endl;
				delete ts;
			}
			file << neighbourSize[j] << " ; " << sumaKosztu / ile_pomiarow << " ; " << sumaCzasu / ile_pomiarow << std::endl; //zapisujemy wyniki do plik
		}

		// ILOSC ITERACJI
		file << "Ilosc iteracji" << " ; " << "Sredni koszt" << " ; " << "Sredni czas" << endl;
		for (int j = 0; j < 8; j++) {
			cout << "== Ilosc iteracji: " << neighbourSize[j] << " ==" << endl;
			sumaCzasu = 0;
			sumaKosztu = 0;
			for (int k = 0; k < ile_pomiarow; k++) {
				start = clock();
				ts = new Tabu(ilosc_miast, odleglosci);
				ts->startAlgorithm(10, 200, neighbourSize[j]);
				stop = clock();
				czas = (static_cast <double> (stop - start)) / CLOCKS_PER_SEC;
				sumaCzasu += czas;
				sumaKosztu += ts->minKoszt;
				//cout << k << ". Koszt: " << ts->minKoszt << "	Czas: " << czas << endl;
				delete ts;
			}
			file << neighbourSize[j] << " ; " << sumaKosztu / ile_pomiarow << " ; " << sumaCzasu / ile_pomiarow << std::endl; //zapisujemy wyniki do plik
		}

		// ILOSC ITERACJI DLA LOSOWYCH SASIADOW
		file << "Ilosc iteracji dla losowych sasiadow" << " ; " << "Sredni koszt" << " ; " << "Sredni czas" << endl;
		for (int j = 0; j < 8; j++) {
			cout << "== Ilosc iteracji dla losowych sasiadow: " << neighbourSize[j] << " ==" << endl;
			sumaCzasu = 0;
			sumaKosztu = 0;
			for (int k = 0; k < ile_pomiarow; k++) {
				start = clock();
				ts = new Tabu(ilosc_miast, odleglosci);
				ts->startAlgorithm(10, 200, 100, neighbourSize[j]);
				stop = clock();
				czas = (static_cast <double> (stop - start)) / CLOCKS_PER_SEC;
				sumaCzasu += czas;
				sumaKosztu += ts->minKoszt;
				//cout << k << ". Koszt: " << ts->minKoszt << "	Czas: " << czas << endl;
				delete ts;
			}
			file << neighbourSize[j] << " ; " << sumaKosztu / ile_pomiarow << " ; " << sumaCzasu / ile_pomiarow << std::endl; //zapisujemy wyniki do plik
		}

		file.close();
	}
	/*
		int miasta[3] = {10, 11, 12}; // instancje
	cout << "Ilosc probek: " << ile_testow << endl;
	for (int i = 0; i < 3; i++) {
		wygeneruj(miasta[i]);
		double czasBF = 0;
		double czasDP = 0;
		double czasGreedy = 0;
		cout << "--- Tabela wynikow dla " << miasta[i] << " instancji ---" << endl;
		for (int j = 0; j < ile_testow; j++) {
			// brute force
			start = clock();
			bf = new BruteForce(ilosc_miast, odleglosci);
			bf->execute();
			stop = clock();
			czas = (static_cast <double> (stop - start)) / CLOCKS_PER_SEC;
			cout << "BF: " << czas << endl;
			czasBF += czas;
			delete bf;

			// greedy
			start = clock();
			greedy();
			stop = clock();
			czas = (static_cast <double> (stop - start)) / CLOCKS_PER_SEC;
			cout << "Greedy: " << czas << endl;
			czasBF += czas;

			// dynamic programming
			start = clock();
			dp = new DynamiczneProgramowanie(ilosc_miast, odleglosci);
			dp->tspInit();
			stop = clock();
			czas = (static_cast <double> (stop - start)) / CLOCKS_PER_SEC;
			cout << "DP: " << czas << endl;
			czasDP += czas;
			delete dp;
		}
		czasBF = czasBF / ile_testow;
		czasGreedy = czasGreedy / ile_testow;
		czasDP = czasDP / ile_testow;
		cout << "\nSrednia:" << endl;
		cout << "Algorytm BF: " << czasBF << endl;
		cout << "Algorytm Greedy: "  << czasGreedy << endl;
		cout << "Algorytm DP: " << czasDP << endl;
	}
	*/

}