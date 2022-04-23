#include "Province.h"

Province::Province(int id, std::string name, std::string continent) {
	m_ID = id;
	m_Name = name;
	m_Continent = continent;
}

int Province::getID() {
	return m_ID;
}

void Province::setID(int id) {
	m_ID = id;
}

std::string Province::getName() {
	return m_Name;
}

void Province::setName(std::string name) {
	m_Name = name;
}

std::string Province::getContinent() {
	return m_Continent;
}

void Province::setContinent(std::string continent) {
	m_Continent = continent;
}

sf::Color Province::getColour() {
	return m_Colour;
}

void Province::setColour(sf::Color colour) {
	m_Colour = colour;
}

std::vector<int> Province::getAdjacencies() {
	return m_Adjacencies;
}

void Province::setAdjacencies(std::vector<int> adjacencies) {
	m_Adjacencies = adjacencies;
}

int Province::getOwner() {
	return m_Owner;
}

void Province::setOwner(int owner) {
	m_Owner = owner;
}

int Province::getArmyCount() {
	return m_ArmyCount;
}

void Province::setArmyCount(int armyCount) {
	m_ArmyCount = armyCount;
}

std::vector<int> Province::getCentroid() {
	return m_Centroid;
}

void Province::setCentroid(std::vector<int> centroid) {
	m_Centroid = centroid;
}
