#include "AI.h"
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

void AI::placeArmies(std::vector<Player>& players, Board& board) {

}
