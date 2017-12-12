#pragma once
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <limits>

class Tabu
{
private:
	std::list<std::pair<int, int> > tabu_list;
	int obliczKoszt(std::vector<int> path);
	int** odleglosci;
	int ilosc_miast;
public:
	Tabu(int, int**);
	~Tabu();

	std::string getSolutionToString(std::vector<int> path, int cost);
	std::pair<int, int> swapTwoRandomCities(std::vector<int>& path);
	std::vector <int> generujLosoweRozwiazanie();
	void startAlgorithm(int tabu_list_size = 10, int neighbours_count = 400, int steps_without_change = 200, int steps_with_random_neighbourhood = 20);
	std::vector<int> generujStartoweUstawienie();
	bool checkTabu(std::pair<int, int>&, std::vector<int>& path, int neighbour_cost);

	std::vector< int > najlepszeRozwiazanie;
	int minKoszt;
};