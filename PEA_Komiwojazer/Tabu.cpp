#include "stdafx.h"
#include "Tabu.h"

Tabu::Tabu(int ilosc_miast, int **tablica)
{
	// przypisanie wskaznikow dla zmiennych globalnych
	this->ilosc_miast = ilosc_miast;
	this->odleglosci = tablica;
}


Tabu::~Tabu()
{
}

void Tabu::startAlgorithm(int tabu_list_size, int neighbours_count, int steps_without_change, int steps_with_random_neighbourhood)
{
	//std::cout << "parametry:" << "rozmiar tabu: " << tabu_list_size << ", ilosc sasiadow: " << neighbours_count << ", ilosc krokow bez zmian: " << steps_without_change << ", ilosc krokow z losowym sasiadem: " << steps_with_random_neighbourhood << "\n";
	if (ilosc_miast == 0) return;
	srand(static_cast<unsigned int>(time(NULL)));

	int curKoszt;
	std::vector <int> aktualneRozwiazanie(generujStartoweUstawienie());
	curKoszt = obliczKoszt(aktualneRozwiazanie);

	najlepszeRozwiazanie = aktualneRozwiazanie;
	minKoszt = curKoszt;

	std::pair<int, int> swaped_cities;
	std::pair<int, int> saved_swap;

	std::vector <int> the_best_neighbour;
	std::vector <int> neighbour;
	int neighbour_cost;
	int the_best_neighbour_cost;
	int steps = 0;
	int neighbourhood_count = 0;
	do {
		the_best_neighbour_cost = INT_MAX;
		for (int i = 0; i < neighbours_count; i++)
		{
			neighbour = aktualneRozwiazanie;
			swaped_cities = swapTwoRandomCities(neighbour);
			neighbour_cost = obliczKoszt(neighbour);
			if (neighbour_cost < the_best_neighbour_cost && checkTabu(swaped_cities, neighbour, neighbour_cost))
			{
				the_best_neighbour_cost = neighbour_cost;
				the_best_neighbour = neighbour;
				saved_swap = swaped_cities;
			}
		}
		aktualneRozwiazanie = the_best_neighbour;
		curKoszt = the_best_neighbour_cost;


		if (curKoszt < minKoszt)
		{
			najlepszeRozwiazanie = aktualneRozwiazanie;
			minKoszt = curKoszt;
			steps = 0;
		}

		if (tabu_list.size() > tabu_list_size)
		{
			tabu_list.pop_front();
		}
		tabu_list.push_back(saved_swap);
		steps++;
		if (steps > steps_without_change)
		{
			aktualneRozwiazanie = generujLosoweRozwiazanie();
			curKoszt = obliczKoszt(aktualneRozwiazanie);
			neighbourhood_count++;
			steps = 0;
		}


	} while (neighbourhood_count < steps_with_random_neighbourhood);
}

std::vector <int> Tabu::generujStartoweUstawienie() {
	std::vector <int> solution; //droga
	solution.push_back(0);

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
		solution.push_back(curVertex);
	}
	return solution;
}

std::vector <int> Tabu::generujLosoweRozwiazanie()
{

	std::vector <int> solution;
	for (int i = 0; i < ilosc_miast; i++)
	{
		solution.push_back(i);
	}
	std::random_shuffle(solution.begin()+1, solution.end());
	return solution;
}

int Tabu::obliczKoszt(std::vector<int> path)
{
	int cost = 0;
	for (std::size_t i = 0; i < path.size() - 1; i++)
	{
		cost += odleglosci[path[i]][path[i + 1]];
	}
	cost += odleglosci[path[path.size() - 1]][path[0]];

	return cost;
}

std::pair<int, int> Tabu::swapTwoRandomCities(std::vector<int>& path)
{
	int firstPosition = (rand() % (path.size() - 1)) + 1;

	int secondPosition;
	do {
		secondPosition = (rand() % (path.size() - 1)) + 1;
	} while (firstPosition == secondPosition);

	std::pair<int, int> swaped_cities;

	if (firstPosition > secondPosition)
	{
		swaped_cities.first = path.at(secondPosition);
		swaped_cities.second = path.at(firstPosition);
	}
	else
	{
		swaped_cities.first = path.at(firstPosition);
		swaped_cities.second = path.at(secondPosition);
	}

	int buffor = path.at(firstPosition);
	path.at(firstPosition) = path.at(secondPosition);
	path.at(secondPosition) = buffor;

	return swaped_cities;
}

bool Tabu::checkTabu(std::pair<int, int>& swaped_cities, std::vector<int>& path, int neighbour_cost)
{
	std::list<std::pair<int, int> >::iterator list_iterator = tabu_list.begin();
	while (list_iterator != tabu_list.end())
	{
		if (swaped_cities.first == list_iterator->second || swaped_cities.second == list_iterator->first)
		{
			int first_element_index = std::find(path.begin(), path.end(), list_iterator->first) - path.begin();
			int second_element_index = std::find(path.begin(), path.end(), list_iterator->second) - path.begin();
			if (first_element_index < second_element_index && neighbour_cost > minKoszt)
				return false;
		}
		list_iterator++;
	}
	return true;
}

std::string Tabu::getSolutionToString(std::vector<int> path, int cost)
{
	std::string str = "";
	str.append("Droga: ");
	for (std::size_t i = 0; i < path.size(); i++)
	{
		str.append(std::to_string(path[i]));
		str.append(" -> ");
	}
	str.append(std::to_string(path[0]));
	str.append("\nKoszt: ");
	str.append(std::to_string(cost));
	return str;
}