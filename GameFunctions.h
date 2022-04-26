#pragma once
#include <iostream>
#include "Board.h"
#include "Player.h"

class GameFunctions
{
public:
	static int calculateNewArmies(Board& gameboard, int player);
	static int isGameWon(std::vector<Player>& players);
};

