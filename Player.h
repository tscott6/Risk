#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
	sf::Color playerColour;

	//Number of owned provinces. Used to determine if game is won.
	int ownedProvinces;

	//Number of armies available to place at turn start & total armies possessed
	int availableArmies, totalArmies;

	bool isAI;

public:
	Player(bool AI);
	void setPlayerColour(std::string colour);
	sf::Color getPlayerColour();
	void setOwnedProvinces(int number);
	const bool& getIsAI();

	int getAvailableArmies();
	void setAvailableArmies(int number);
};

