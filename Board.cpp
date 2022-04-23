#include "Board.h"
#include <sstream>
#include <fstream>

Board::Board() {
	populateProvinceGrid();
}

//Load territory data from csv file
//Note that csv should be UTF-8 encoded or similar to ensure it can be properly read
void Board::populateProvinceGrid() {
	std::ifstream provinceFile("data/TerritoryData.csv");

	std::vector<std::string> row;
	std::vector<int> tempAdj, tempCentroid;
	std::string line, word, temp, adj, centroid;

	while (std::getline(provinceFile, line)) {
		//clear vectors storing line, territory adjacency, and centroid data before reading new line
		row.clear();
		tempAdj.clear();
		tempCentroid.clear();

		std::stringstream ss(line);

		//Separate each data type by splitting on ',' delimiter and store in row vector
		while (std::getline(ss, word, ',')) {
			row.push_back(word);
		}

		std::stringstream ss2(row[6]);

		//Separate adjacencies by splitting on ';' delimiter and store in tempAdj vector
		while (std::getline(ss2, adj, ';')) {
			tempAdj.push_back(std::stoi(adj));
		}

		std::stringstream ss3(row[7]);

		//Separate centroid coordinates by splitting on ';' delimiter and store in tempCentroid vector
		while (std::getline(ss3, centroid, ';')) {
			tempCentroid.push_back(std::stoi(centroid));
		}

		//Create new territory and populate all relevant data (owner and army count initialized during game setup)
		provinceGrid.push_back(Province(std::stoi(row[0]), row[1], row[5]));
		provinceGrid[provinceGrid.size() - 1].setColour(
			sf::Color(std::stoi(row[2]), std::stoi(row[3]), std::stoi(row[4]), 255));
		provinceGrid[provinceGrid.size() - 1].setAdjacencies(tempAdj);
		provinceGrid[provinceGrid.size() - 1].setCentroid(tempCentroid);
	}
}

//Initializes army numbers displayed on board for each territory
//Must be called after font is loaded to ensure text is properly drawn
void Board::populateArmyTokens() {
	sf::Text text;
	float x, y;

	for (int i = 0; i < provinceGrid.size(); i++) {
		x = provinceGrid[i].getCentroid()[0];
		y = provinceGrid[i].getCentroid()[1];

		armyTokens.push_back(sf::CircleShape(15.f));
		armyTokens[armyTokens.size() - 1].setFillColor(sf::Color::White);
		armyTokens[armyTokens.size() - 1].setOutlineColor(sf::Color::Black);
		armyTokens[armyTokens.size() - 1].setOutlineThickness(2.f);
		armyTokens[armyTokens.size() - 1].setPosition(sf::Vector2f(x - 15, y - 15));

		text.setString(std::to_string(provinceGrid[i].getArmyCount()));

		armyCounts.push_back(text);
		armyCounts[armyCounts.size() - 1].setFillColor(sf::Color::Black);
		armyCounts[armyCounts.size() - 1].setCharacterSize(20);
		armyCounts[armyCounts.size() - 1].setPosition(sf::Vector2f(x - 6, y - 12));
		armyCounts[armyCounts.size() - 1].setFont(font);
	}
}

void Board::clearArmyTokens() {
	for (int i = 0; i < armyTokens.size(); i++) {
		armyTokens[i].setFillColor(sf::Color::White);
	}
}

std::vector<Province>& Board::getProvinceGrid() {
	return provinceGrid;
}

std::vector<sf::CircleShape> Board::getArmyTokens() {
	return armyTokens;
}

std::vector<sf::Text>& Board::getArmyCounts() {
	return armyCounts;
}

void Board::clearArmyCounts() {
	for (int i = 0; i < armyCounts.size(); i++) {
		armyCounts[i].setString("0");
		provinceGrid[i].setArmyCount(0);
	}
}

void Board::clearOwners() {
	for (int i = 0; i < provinceGrid.size(); i++) {
		provinceGrid[i].setOwner(-1);
	}
}

void Board::setFont() {
	font.loadFromFile("fonts/Roboto-Bold.ttf");
}

void Board::changeArmyTokenColour(sf::Color newColour, int index) {
	armyTokens[index].setFillColor(newColour);
}

void Board::setFreeProvinces(int number) {
	freeProvinces = number;
}

const int& Board::getFreeProvinces() {
	return freeProvinces;
}
