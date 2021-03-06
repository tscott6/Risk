#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Board.h"

class AI
{
public:
	static void setupSelectProvince(std::vector<Player>& players, Board& board);

	static void placeArmies(Player& player, int playerID, Board& board);
};

