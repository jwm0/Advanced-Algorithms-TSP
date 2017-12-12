#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include "Komiwojazer.h"
#include "Tabu.h"
using namespace std;

class Menu {
private:
	int wybor_operacji, ilosc;											// Zmienne pomocne podczas nawigacji po menu
	string nazwa_pliku;													// Nazwa pliku .txt zawieraj�cego dane 
	Komiwojazer* komiwojazer;											// Obiekt wykonuj�cy algorytmy
	time_t start, stop;													// Pocz�tek oraz koniec wykonywania algorytmu
	double wynik;														// Czas potrzebny do wykonania algorytmu
	int iteracje;
	float temperatura;

	void okno_startowe();												// Metody do uporzadkowania menu
	void menu_glowne();													//

public:
	Menu();
	~Menu();
};