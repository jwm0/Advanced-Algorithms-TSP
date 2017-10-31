#include "stdafx.h"
#include "Menu.h"


Menu::Menu()
{
	komiwojazer = new Komiwojazer();
	okno_startowe();
	menu_glowne();
}


Menu::~Menu()
{
}

void Menu::okno_startowe() {
	cout << "|******************************************************|" << endl;
	cout << "|                      PEA PROJEKT                     |" << endl;
	cout << "|                                                      |" << endl;
	cout << "| Autor: Jakub Majorek 218322                          |" << endl;
	cout << "| Prowadzacy: dr inz. Tomasz Kaplon                    |" << endl;
	cout << "|                                                      |" << endl;
	cout << "|******************************************************|" << endl;
}

void Menu::menu_glowne() {
	cout << "________________________" << endl;
	cout << "Menu:" << endl;
	cout << "1. Wczytaj z pliku" << endl;
	cout << "2. Wygeneruj" << endl;
	cout << "3. Wyswietl" << endl;
	cout << "4. Algorytm zachlanny" << endl;
	cout << "5. Algorytm Brute Force" << endl;
	cout << "6. Algorytm programowania dynamicznego" << endl;
	cout << "7. //Projekt 3" << endl;
	cout << "8. Zakoncz" << endl;
	cout << endl << "---> ";

	cin >> wybor_operacji;

	switch (wybor_operacji) {
	case 1: /* Wczytaj z pliku */
		{
			cout << "Podaj nazwe pliku: ";
			cin >> nazwa_pliku;
			komiwojazer->wczytaj(nazwa_pliku);
			menu_glowne();
		}
		break;
	case 2: /* Wygeneruj */
		{
			cout << "Ile miast mam wygenerowac: ";
			cin >> ilosc;
			komiwojazer->wygeneruj(ilosc);
			menu_glowne();
		}
		break;
	case 3: /* Wyswietl */
		{
			komiwojazer->wyswietl();
			menu_glowne();
		}
		break;
	case 4:	/* Algorytm Zachlanny */
		{
			start = clock();
			komiwojazer->algorytmZachlanny();
			stop = clock();
			wynik = (static_cast <double> (stop - start)) / CLOCKS_PER_SEC;
			cout << "Czas wykonania: " << wynik << endl;
			menu_glowne();
		}
		break;
	case 5: /* Algorytm Brute Force */
		{
			komiwojazer->bruteForce();
			menu_glowne();
		}
		break;
	case 6: /* Algorytm DP */
		{
			komiwojazer->dynamicProgramming();
			menu_glowne();
		}
		break;
	case 7: /* Algorytm mrowkowy */
		{
			//komiwojazer->algorytmMrowkowy();
			menu_glowne();
		}
		break;
	case 8: /* Zakoncz */
		{
			cout << "Koniec!" << endl;
			exit(0);
		}
		break;
	default:
		{
			cout << endl << "Nie ma takiej opcji" << endl;
			menu_glowne();
		}
		break;
	}
}