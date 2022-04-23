#include "GameFunctions.h"
#include "CalculationFunctions.h"

//Calculates the number of new armies the select player receives at beginning of their turn
int GameFunctions::calculateNewArmies(Board& gameBoard, int player) {
	int newArmies = 0;

	//Armies rewarded for owning each continent. Order follows the list in the data/TerritoryData.csv file.
	std::vector<int> continentArmies = { 5, 2, 5, 3, 7, 2 };

	for (int i = 0; i < gameBoard.getProvinceGrid().size(); i++) {

		//Add one army if territory owned by player
		if (gameBoard.getProvinceGrid()[i].getOwner() == player) {
			newArmies += 1;
		}

		//Check for continent ownership. If any territory not owned by player, they do not receive armies for that continent
		if (gameBoard.getProvinceGrid()[i].getOwner() != player && gameBoard.getProvinceGrid()[i].getContinent() == "North America") {
			continentArmies[0] = 0;
		}
		if (gameBoard.getProvinceGrid()[i].getOwner() != player && gameBoard.getProvinceGrid()[i].getContinent() == "South America") {
			continentArmies[1] = 0;
		}
		if (gameBoard.getProvinceGrid()[i].getOwner() != player && gameBoard.getProvinceGrid()[i].getContinent() == "Europe") {
			continentArmies[2] = 0;
		}
		if (gameBoard.getProvinceGrid()[i].getOwner() != player && gameBoard.getProvinceGrid()[i].getContinent() == "Africa") {
			continentArmies[3] = 0;
		}
		if (gameBoard.getProvinceGrid()[i].getOwner() != player && gameBoard.getProvinceGrid()[i].getContinent() == "Asia") {
			continentArmies[4] = 0;
		}
		if (gameBoard.getProvinceGrid()[i].getOwner() != player && gameBoard.getProvinceGrid()[i].getContinent() == "Oceania") {
			continentArmies[5] = 0;
		}
	}

	//Finalize armies based on territory number according to Risk rules
	//If player has fewer than 9 territories, they receive 3 armies
	if (newArmies < 9) { newArmies = 3; }
	else { newArmies = newArmies / 3; }

	for (int i = 0; i < continentArmies.size(); i++) {
		newArmies += continentArmies[i];
	}

	return newArmies;
}
