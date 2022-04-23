#include "CalculationFunctions.h"
#include <random>

//Basic linear search of all game territories. Returns index of territory if found
//Can brute force for the standard Risk map as list size is small
int CalculationFunctions::linearSearch(std::vector<Province> gameMap, sf::Color colour) {
	for (int i = 0; i < gameMap.size(); i++) {
		if (gameMap[i].getColour() == colour) {
			return i;
		}
	}

	return -1;
}

//Basic linear search of all adjacencies for a specific territory
//Can brute force as each territory on the standard Risk map has no more than 6 adjacencies
bool CalculationFunctions::adjacencySearch(Province& province, int id) {
	for (int i = 0; i < province.getAdjacencies().size(); i++) {
		if (province.getAdjacencies()[i] == id) {
			return true;
		}
	}

	return false;
}

//Dice roll to determine victor during an attack
int CalculationFunctions::attackResult() {
	int attackerRoll = std::rand() % 6 + 1;
	int defenderRoll = std::rand() % 6 + 1;

	if (attackerRoll > defenderRoll) {
		return 1;
	}

	return -1;
}
