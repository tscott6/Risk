#include "AI.h"
#include "CalculationFunctions.h"
#include <random>

//Initial AI selection of territories
void AI::setupSelectProvince(std::vector<Player>& players, Board& board) {

	for (int i = 1; i < players.size(); i++) {
		std::cout << "Start of Player " << i << " setup turn" << std::endl;

		for (int j = 0; j < board.getProvinceGrid().size(); j++) {

			if (board.getFreeProvinces() == 0) { break; }

			if (board.getProvinceGrid()[j].getOwner() == -1) {
				board.getProvinceGrid()[j].setOwner(i);
				board.changeArmyTokenColour(players[i].getPlayerColour(), j);
				board.getProvinceGrid()[j].setArmyCount(1);
				board.getArmyCounts()[j].setString("1");
				board.setFreeProvinces(board.getFreeProvinces() - 1);

				players[i].setAvailableArmies(players[i].getAvailableArmies() - 1);

				std::cout << "Free Provinces: " << board.getFreeProvinces() << std::endl;

				break;
			}
		}

		std::cout << "End of Player " << i << " setup turn" << std::endl;
	}
}

void AI::placeArmies(Player& player, int playerID, Board& board) {

	//std::cout << "In placeArmies function" << std::endl;
	//std::cout << "Player army count: " << player.getAvailableArmies() << std::endl;

	//Vector encodes the perceived threat to each territory controlled by the player
	//sumBorderArmyThreat is used to normalize the vector
	std::vector<std::pair<float, int>> borderArmyThreat;
	float sumBorderArmyThreat = 0;

	for (int i = 0; i < board.getProvinceGrid().size(); i++) {

		//If territory not controlled by player, set to 0 and ignore
		if (board.getProvinceGrid()[i].getOwner() == playerID) {
			std::vector<int> provinceAdjacencies = board.getProvinceGrid()[i].getAdjacencies();

			int temp = 0;

			//Add together all enemy armies in territories bordering the player controlled territory.
			for (int j = 0; j < provinceAdjacencies.size(); j++) {
				temp += board.getProvinceGrid()[provinceAdjacencies[j] - 1].getArmyCount();
			}

			borderArmyThreat.push_back(std::make_pair(temp, i));

			//Take enemy army count and divide by player armies in player controlled territory to measure threat to territory
			borderArmyThreat[borderArmyThreat.size() - 1].first /= board.getProvinceGrid()[i].getArmyCount();
			sumBorderArmyThreat += borderArmyThreat[borderArmyThreat.size() - 1].first;
		}
		else if (board.getProvinceGrid()[i].getOwner() != playerID) {
			borderArmyThreat.push_back(std::make_pair(0, i));
		}

		//std::cout << "borderArmyThreat first: " << borderArmyThreat[i].first << ", " 
			//<< "borderArmyThreat second: " << borderArmyThreat[i].second << std::endl;
	}

	//Normalize threat values according to total enemy armies bordering player controlled territory
	for (int i = 0; i < borderArmyThreat.size(); i++) {
		borderArmyThreat[i].first /= sumBorderArmyThreat;
	}

	auto remove = std::remove_if(borderArmyThreat.begin(), borderArmyThreat.end(), [](const std::pair<float, int>& pair) {
		return pair.first == 0;
		});

	borderArmyThreat.erase(remove, borderArmyThreat.end());
	std::sort(borderArmyThreat.rbegin(), borderArmyThreat.rend());

	//std::cout << "Player army count: " << player.getAvailableArmies() << std::endl;
	//std::cout << "borderArmyThreat size: " << borderArmyThreat.size() << std::endl;

	/*for (int i = 0; i < borderArmyThreat.size(); i++) {
		std::cout << "borderArmyThreat first: " << borderArmyThreat[i].first << ", " 
			<< "borderArmyThreat second: " << borderArmyThreat[i].second << std::endl;
	}*/

	bool isPlacingArmies = true;

	while (isPlacingArmies) {
		for (int i = 0; i < borderArmyThreat.size(); i++) {
			if (player.getAvailableArmies() > 0) {

				int newArmy = board.getProvinceGrid()[borderArmyThreat[i].second].getArmyCount() + 1;

				board.getProvinceGrid()[borderArmyThreat[i].second].setArmyCount(newArmy);
				board.setArmyCount(std::to_string(newArmy), borderArmyThreat[i].second);

				player.setAvailableArmies(player.getAvailableArmies() - 1);
				//std::cout << "Placed armies in " << board.getProvinceGrid()[borderArmyThreat[i].second].getName() << std::endl;
			}

			if (player.getAvailableArmies() == 0) {
				isPlacingArmies = false;
				break;
			}
		}
	}

	//std::cout << "Player army count: " << player.getAvailableArmies() << std::endl;
}
