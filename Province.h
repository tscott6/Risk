#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Province
{
private:
	int m_ID;
	std::string m_Name;
	std::string m_Continent;
	sf::Color m_Colour;
	std::vector<int> m_Adjacencies, m_Centroid;

	int m_Owner = -1;
	int m_ArmyCount = 0;

public:
	Province(int id, std::string name, std::string continent);

	int getID();
	void setID(int id);

	std::string getName();
	void setName(std::string name);

	std::string getContinent();
	void setContinent(std::string continent);

	sf::Color getColour();
	void setColour(sf::Color colour);

	std::vector<int> getAdjacencies();
	void setAdjacencies(std::vector<int> adjacencies);

	int getOwner();
	void setOwner(int owner);

	int getArmyCount();
	void setArmyCount(int armyCount);

	std::vector<int> getCentroid();
	void setCentroid(std::vector<int> centroid);
};

