#include "Player.h"

Player::Player(bool AI) {
	isAI = AI;
	ownedProvinces = 0;
	availableArmies = 30;
	totalArmies = 30;
}

void Player::setPlayerColour(std::string colour) {
	if (colour == "Red") {
		playerColour = sf::Color::Red; 
	}
	else if (colour == "Blue") {
		playerColour = sf::Color::Blue;
	}
	else if (colour == "Green") {
		playerColour = sf::Color::Green;
	}
	else if (colour == "Yellow") {
		playerColour = sf::Color::Yellow;
	}
}

sf::Color Player::getPlayerColour() {
	return playerColour;
}

void Player::setOwnedProvinces(int number) {
	ownedProvinces = number;
}

int Player::getOwnedProvinces() {
	return ownedProvinces;
}

const bool& Player::getIsAI() {
	return isAI;
}

int Player::getAvailableArmies() {
	return availableArmies;
}
void Player::setAvailableArmies(int number) {
	availableArmies = number;
}
