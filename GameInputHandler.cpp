#include "GameInputHandler.h"
#include "CalculationFunctions.h"
#include "GameFunctions.h"

GameInputHandler::GameInputHandler(GameScreen* screen) {
	gameScreen = screen;
}

void GameInputHandler::handleKeyPressed(sf::RenderWindow& window, tgui::Gui& gui, sf::Event& event) {}

void GameInputHandler::handleLeftClick(sf::RenderWindow& window, tgui::Gui& gui, std::string widgetName) {
	auto name = gui.get(widgetName)->getWidgetName();

	if (name == "Menu") {
		gameScreen->setMenuVisible(true);
		gameScreen->activateMenu(gui);
	}

	if (name == "Main Menu") {
		gameScreen->setMenuVisible(false);
		gameScreen->deactivateMenu(gui);
		gameScreen->clearPlayers();
		gameScreen->clearArmies();
		gameScreen->clearProvinceSelections();
		gameScreen->getGameBoard().setFreeProvinces(42);
		gameScreen->setPhase(gameScreen->getGamePhases()[0]);
		getScreenManagerControl()->switchScreens("Home", gui);
	}

	if (name == "Resume") {
		gameScreen->setMenuVisible(false);
		gameScreen->deactivateMenu(gui);
	}

	if (name == "Exit Game") {
		window.close();
	}

	if (name == "End Attack") {
		if (gameScreen->getPhase() == gameScreen->getGamePhases()[2]) {
			gameScreen->clearProvinceSelections();
			gameScreen->updateNewArmiesText("Attack Phase: Select in order\n1) Territory to attack from\n2) Territory to attack");
			gameScreen->deactivateEndAttackButton(gui);
		}

		else if (gameScreen->getPhase() == gameScreen->getGamePhases()[3]) {
			gameScreen->clearProvinceSelections();
			gameScreen->updateNewArmiesText("Move Phase: Select in order\n1) Territory to move armies from\n2) Territory to move armies into");
			gameScreen->deactivateEndAttackButton(gui);
		}
	}

	if (name == "End Turn") {
		//If in attack phase, change to move phase
		if (gameScreen->getPhase() == gameScreen->getGamePhases()[2]) {
			gameScreen->setPhase(gameScreen->getGamePhases()[3]);
			gameScreen->clearProvinceSelections();
			gui.get<tgui::Button>("End Attack")->setText("End Move");
			gameScreen->updateNewArmiesText("Move Phase: Select in order\n1) Territory to move armies from\n2) Territory to move armies into");
		}

		//If in move phase, change to place armies phase
		else if (gameScreen->getPhase() == gameScreen->getGamePhases()[3]) {
			gameScreen->setPhase(gameScreen->getGamePhases()[1]);
			gameScreen->clearProvinceSelections();

			for (int i = 0; i < gameScreen->getPlayers().size(); i++) {
				int newArmies = GameFunctions::calculateNewArmies(gameScreen->getGameBoard(), i);
				gameScreen->getPlayers()[i].setAvailableArmies(newArmies);
			}

			std::string temp = "Place Your Armies.\nAvailable Armies: ";
			temp += std::to_string(gameScreen->getPlayers()[0].getAvailableArmies());
			gameScreen->updateNewArmiesText(temp);

			std::cout << "Player armies: " << gameScreen->getPlayers()[0].getAvailableArmies() << std::endl;

			gameScreen->deactivateEndTurnButton(gui);
		}
	}
}

//Controls inputs into game loop. Triggered when player clicks on map
//Game phase dictates which commands are triggered when player selects a territory
void GameInputHandler::handleLeftClick(sf::RenderWindow& window, tgui::Gui& gui) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::Color tempColour = gameScreen->getTerritoryImage().getPixel(mousePosition.x, mousePosition.y);

	//Check if territory clicked on when game is active before searching for selected territory
	if (tempColour != sf::Color(255, 255, 255, 255) && gameScreen->getMenuVisible() != true) {
		int province = CalculationFunctions::linearSearch(gameScreen->getProvinceList(), tempColour);

		//When in setup phase and choosing territories
		if (gameScreen->getPhase() == gameScreen->getGamePhases()[0] && province != -1) {

			//Make sure player is only selecting territories not yet claimed
			if (gameScreen->getProvinceList()[province].getOwner() == -1) {
				gameScreen->changeOwnership(gameScreen->getPlayers()[0].getPlayerColour(), province);
				gameScreen->getGameBoard().setFreeProvinces(gameScreen->getGameBoard().getFreeProvinces() - 1);
				std::cout << "Free Provinces: " << gameScreen->getGameBoard().getFreeProvinces() << std::endl;
				gameScreen->AISetup();
				
				//Start army placement phase once no more unclaimed territories remain
				if (gameScreen->getGameBoard().getFreeProvinces() == 0) {
					gameScreen->setPhase(gameScreen->getGamePhases()[1]);

					std::string temp = "Place Your Armies.\nAvailable Armies: ";
					temp += std::to_string(gameScreen->getPlayers()[0].getAvailableArmies());

					gameScreen->updateNewArmiesText(temp);
				}
			}
		}

		//When in place armies phase and choosing territories
		else if (gameScreen->getPhase() == gameScreen->getGamePhases()[1] && province != -1) {

			//Make sure player only placing armies in territories they control
			if (gameScreen->getProvinceList()[province].getOwner() == 0) {
				gameScreen->placeArmies(province);

				std::string temp = "Place Your Armies.\nAvailable Armies: ";
				temp += std::to_string(gameScreen->getPlayers()[0].getAvailableArmies());

				gameScreen->updateNewArmiesText(temp);

				//Start attack phase once all starting armies are placed on the board
				if (gameScreen->getPlayers()[0].getAvailableArmies() == 0) {
					gameScreen->setPhase(gameScreen->getGamePhases()[2]);
					gameScreen->updateNewArmiesText("Attack Phase: Select in order\n1) Territory to attack from\n2) Territory to attack");
					gameScreen->activateEndTurnButton(gui);
					gui.get<tgui::Button>("End Attack")->setText("End Attack");
				}
			}
		}

		//When in attack phase and choosing territories
		else if (gameScreen->getPhase() == gameScreen->getGamePhases()[2] && province != -1) {

			//Is player selecting territory to attack from?
			if (!gameScreen->getIsFirstProvinceSelected() && gameScreen->getProvinceList()[province].getOwner() == 0 &&
				!gameScreen->getIsSecondProvinceSelected()) {

				gameScreen->setFirstProvinceSelected(gameScreen->getProvinceList()[province].getID());
				gameScreen->setIsFirstProvinceSelected(true);

				std::string temp = gameScreen->getProvinceList()[province].getName();
				temp += " Attacking to ";

				gameScreen->updateNewArmiesText(temp);
				gameScreen->activateEndAttackButton(gui);
			}

			//Has player selected attack origin and is selecting territory to attack?
			else if (gameScreen->getIsFirstProvinceSelected() && gameScreen->getProvinceList()[province].getOwner() != 0 && 
				!gameScreen->getIsSecondProvinceSelected()) {

				gameScreen->setSecondProvinceSelected(gameScreen->getProvinceList()[province].getID());

				//Make sure selected territory to attack is adjacent to attack origin
				if (CalculationFunctions::adjacencySearch(gameScreen->getProvinceList()[province], gameScreen->getFirstProvinceSelected())) {

					std::string temp = gameScreen->getNewArmiesText();
					temp += gameScreen->getProvinceList()[province].getName();
					temp += "\nClick on territory again to launch attack";

					gameScreen->updateNewArmiesText(temp);
					gameScreen->setIsSecondProvinceSelected(true);
				}
			}

			//Is player now launching an attack after selecting both attack origin and territory to attack?
			else if (gameScreen->getIsFirstProvinceSelected() && gameScreen->getIsSecondProvinceSelected() &&
				gameScreen->getProvinceList()[province].getOwner() != 0 &&
				gameScreen->getProvinceList()[province].getID() == gameScreen->getSecondProvinceSelected()) {

				int attackingArmies = gameScreen->getProvinceList()[gameScreen->getFirstProvinceSelected() - 1].getArmyCount();
				int defendingArmies = gameScreen->getProvinceList()[gameScreen->getSecondProvinceSelected() - 1].getArmyCount();

				std::cout << "First province armies: " << gameScreen->getProvinceList()[gameScreen->getFirstProvinceSelected() - 1].getArmyCount() << std::endl;
				std::cout << "Second province armies: " << gameScreen->getProvinceList()[gameScreen->getSecondProvinceSelected() - 1].getArmyCount() << std::endl;

				//Player must have more than 1 army in attack origin to launch an attack
				if (attackingArmies > 1) {
					int attackResult = CalculationFunctions::attackResult();

					//Attack successful, destroy a defending army
					if (attackResult == 1) {

						defendingArmies -= 1;
						gameScreen->getProvinceList()[gameScreen->getSecondProvinceSelected() - 1].setArmyCount(defendingArmies);
						gameScreen->getGameBoard().getArmyCounts()[gameScreen->getSecondProvinceSelected() - 1].setString(std::to_string(defendingArmies));

						//Check if no more defending armies, and hand over control of territory to the player if true
						if (defendingArmies == 0) {
							gameScreen->getProvinceList()[gameScreen->getSecondProvinceSelected() - 1].setOwner(0);
							gameScreen->getGameBoard().changeArmyTokenColour(gameScreen->getPlayers()[0].getPlayerColour(), gameScreen->getSecondProvinceSelected() - 1);
							gameScreen->getGameBoard().getArmyCounts()[gameScreen->getSecondProvinceSelected() - 1].setString(std::to_string(0));
						}
					}

					//Attack failed, destroy an attacking army
					else {
						attackingArmies -= 1;
						gameScreen->getProvinceList()[gameScreen->getFirstProvinceSelected() - 1].setArmyCount(attackingArmies);
						gameScreen->getGameBoard().getArmyCounts()[gameScreen->getFirstProvinceSelected() - 1].setString(std::to_string(attackingArmies));
					}
				}
			}

			//Has player conquered territory being attacked? Give ability to move armies into new territory
			else if (gameScreen->getIsFirstProvinceSelected() && gameScreen->getIsSecondProvinceSelected() &&
				gameScreen->getProvinceList()[province].getID() == gameScreen->getSecondProvinceSelected() &&
				gameScreen->getProvinceList()[province].getOwner() == 0) {

				int firstProvinceArmies = gameScreen->getProvinceList()[gameScreen->getFirstProvinceSelected() - 1].getArmyCount();
				int secondProvinceArmies = gameScreen->getProvinceList()[gameScreen->getSecondProvinceSelected() - 1].getArmyCount();

				//Only allow movement if attack origin has more than one army
				if (firstProvinceArmies > 1) {

					firstProvinceArmies -= 1;
					secondProvinceArmies += 1;

					gameScreen->getProvinceList()[gameScreen->getFirstProvinceSelected() - 1].setArmyCount(firstProvinceArmies);
					gameScreen->getProvinceList()[gameScreen->getSecondProvinceSelected() - 1].setArmyCount(secondProvinceArmies);
					gameScreen->getGameBoard().getArmyCounts()[gameScreen->getFirstProvinceSelected() - 1].setString(std::to_string(firstProvinceArmies));
					gameScreen->getGameBoard().getArmyCounts()[gameScreen->getSecondProvinceSelected() - 1].setString(std::to_string(secondProvinceArmies));
				}
			}
		}

		//When in move phase and choosing territories
		else if (gameScreen->getPhase() == gameScreen->getGamePhases()[3] && province != -1) {

			//Is player selecting territory to move armies from?
			if (!gameScreen->getIsFirstProvinceSelected() && gameScreen->getProvinceList()[province].getOwner() == 0 &&
				!gameScreen->getIsSecondProvinceSelected()) {

				gameScreen->setFirstProvinceSelected(gameScreen->getProvinceList()[province].getID());
				gameScreen->setIsFirstProvinceSelected(true);

				std::string temp = "Moving armies from ";
				temp += gameScreen->getProvinceList()[province].getName();
				temp += " to ";

				gameScreen->updateNewArmiesText(temp);
				gameScreen->activateEndAttackButton(gui);
			}

			//Has player selected territory to move armies from and is selecting territory to move armies into?
			else if (gameScreen->getIsFirstProvinceSelected() && gameScreen->getProvinceList()[province].getOwner() == 0 &&
				!gameScreen->getIsSecondProvinceSelected()) {

				gameScreen->setSecondProvinceSelected(gameScreen->getProvinceList()[province].getID());

				//Make sure selected territory to move armies into is adjacent to the territory moving armies out of
				if (CalculationFunctions::adjacencySearch(gameScreen->getProvinceList()[province], gameScreen->getFirstProvinceSelected())) {

					std::string temp = gameScreen->getNewArmiesText();
					temp += gameScreen->getProvinceList()[province].getName();
					temp += "\nClick on territory again to move army";

					gameScreen->updateNewArmiesText(temp);
					gameScreen->setIsSecondProvinceSelected(true);
				}
			}

			//Is player now moving armies into the selected territory?
			else if (gameScreen->getIsFirstProvinceSelected() && gameScreen->getIsSecondProvinceSelected() &&
				gameScreen->getProvinceList()[province].getID() == gameScreen->getSecondProvinceSelected() &&
				gameScreen->getProvinceList()[province].getOwner() == 0) {

				int firstProvinceArmies = gameScreen->getProvinceList()[gameScreen->getFirstProvinceSelected() - 1].getArmyCount();
				int secondProvinceArmies = gameScreen->getProvinceList()[gameScreen->getSecondProvinceSelected() - 1].getArmyCount();

				//Only allow movement if territory moving armies from has more than one army
				if (firstProvinceArmies > 1) {

					firstProvinceArmies -= 1;
					secondProvinceArmies += 1;

					gameScreen->getProvinceList()[gameScreen->getFirstProvinceSelected() - 1].setArmyCount(firstProvinceArmies);
					gameScreen->getProvinceList()[gameScreen->getSecondProvinceSelected() - 1].setArmyCount(secondProvinceArmies);
					gameScreen->getGameBoard().getArmyCounts()[gameScreen->getFirstProvinceSelected() - 1].setString(std::to_string(firstProvinceArmies));
					gameScreen->getGameBoard().getArmyCounts()[gameScreen->getSecondProvinceSelected() - 1].setString(std::to_string(secondProvinceArmies));
				}
			}
		}
	}
 }
