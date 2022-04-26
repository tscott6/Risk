#pragma once
#include "Province.h"
#include <iostream>

class Board
{
private:
	std::vector<Province> provinceGrid;
	std::vector<sf::CircleShape> armyTokens;
	std::vector<sf::Text> armyCounts;

	sf::Font font;

	//Used to track provinces chosen, when 0 all provinces selected by players.
	int freeProvinces = 42;

public:
	Board();

	void populateProvinceGrid();
	void populateArmyTokens();

	std::vector<Province>& getProvinceGrid();
	std::vector<sf::CircleShape> getArmyTokens();
	void clearArmyTokens();
	std::vector<sf::Text>& getArmyCounts();
	void setArmyCount(std::string newCount, int index);
	void clearArmyCounts();
	void clearOwners();

	void setFont();
	void changeArmyTokenColour(sf::Color newColour, int index);

	void setFreeProvinces(int number);
	const int& getFreeProvinces();
};

