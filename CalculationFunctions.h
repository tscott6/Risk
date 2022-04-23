#pragma once
#include "Province.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class CalculationFunctions
{
public:
	static int linearSearch(std::vector<Province> gameMap, sf::Color colour);
	static bool adjacencySearch(Province& province, int id);
	static int attackResult();
};

