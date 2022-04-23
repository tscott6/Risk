#include "GameScreen.h"
#include "GameUIPanel.h"
#include "GameInputHandler.h"
#include "AI.h"

GameScreen::GameScreen(ScreenManagerControl* screenControl, sf::Vector2i res, tgui::Gui& gui) {
	auto gameUI = std::make_unique<GameUIPanel>(res, gui);
	auto gameInput = std::make_shared<GameInputHandler>(this);

	addPanel(std::move(gameUI), screenControl, gameInput);

	m_ScreenManagerControl = screenControl;

	m_TerritoryImage.loadFromFile("graphics/Territory_Map.png");

	m_GameMap.loadFromFile("graphics/Game_Map.png");
	m_GameMapSprite.setTexture(m_GameMap);
	m_GameMapSprite.setPosition(sf::Vector2f(0, 0));

	gameBoard = Board();
	gameBoard.populateArmyTokens();
	//Font loaded outside Board as destructor to ensure Font object remains instantiated
	gameBoard.setFont();

	menuVisible = false;
	m_MenuPanel.setPosition(sf::Vector2f(539, 286));
	m_MenuPanel.setSize(sf::Vector2f(160, 210));

	m_MenuOverlay.setPosition(sf::Vector2f(0, 0));
	m_MenuOverlay.setSize(sf::Vector2f(res));
	m_MenuOverlay.setFillColor(sf::Color(191, 191, 191, 100));

	m_Dashboard.setPosition(sf::Vector2f(600, 700));
	m_Dashboard.setSize(sf::Vector2f(600, 200));
	m_Dashboard.setOutlineColor(sf::Color::Black);
	m_Dashboard.setOutlineThickness(2.f);

	font.loadFromFile("fonts/Roboto-Bold.ttf");
	m_NewArmies.setFont(font);
	m_NewArmies.setString("Game Start: Pick Your Territories");
	m_NewArmies.setPosition(sf::Vector2f(605, 705));
	m_NewArmies.setCharacterSize(20);
	m_NewArmies.setFillColor(sf::Color::Black);

	//Prevent gui widgets from displaying upon screen instantiation (TGUI stores all widgets in common container)
	deactivateGUI(gui);
}

void GameScreen::setMenuVisible(bool visible) {
	menuVisible = visible;
}

bool GameScreen::getMenuVisible() {
	return menuVisible;
}

void GameScreen::draw(sf::RenderWindow& window, tgui::Gui& gui) {
	window.draw(m_GameMapSprite);
	window.draw(m_Dashboard);
	window.draw(m_NewArmies);

	for (int i = 0; i < gameBoard.getArmyTokens().size(); i++) {
		window.draw(gameBoard.getArmyTokens()[i]);
		window.draw(gameBoard.getArmyCounts()[i]);
	}

	if (menuVisible) {
		window.draw(m_MenuOverlay);
		window.draw(m_MenuPanel);
	}

	Screen::draw(window, gui);
}

void GameScreen::activateGUI(tgui::Gui& gui) {
	activateButtons(gui);
}

void GameScreen::deactivateGUI(tgui::Gui& gui) {
	deactivateButtons(gui);
	deactivateMenu(gui);
	deactivateEndTurnButton(gui);
	deactivateEndAttackButton(gui);
}

void GameScreen::activateButtons(tgui::Gui& gui) {
	gui.get<tgui::Button>("Menu")->setVisible(true);
}

void GameScreen::deactivateButtons(tgui::Gui& gui) {
	gui.get<tgui::Button>("Menu")->setVisible(false);
}

void GameScreen::activateMenu(tgui::Gui& gui) {
	gui.get<tgui::Button>("Menu")->setEnabled(false);
	gui.get<tgui::Button>("Main Menu")->setVisible(true);
	gui.get<tgui::Button>("Exit Game")->setVisible(true);
	gui.get<tgui::Button>("Resume")->setVisible(true);
}
void GameScreen::deactivateMenu(tgui::Gui& gui) {
	gui.get<tgui::Button>("Menu")->setEnabled(true);
	gui.get<tgui::Button>("Main Menu")->setVisible(false);
	gui.get<tgui::Button>("Exit Game")->setVisible(false);
	gui.get<tgui::Button>("Resume")->setVisible(false);
}

void GameScreen::activateEndTurnButton(tgui::Gui& gui) {
	gui.get<tgui::Button>("End Turn")->setVisible(true);
}
void GameScreen::deactivateEndTurnButton(tgui::Gui& gui) {
	gui.get<tgui::Button>("End Turn")->setVisible(false);
}

void GameScreen::activateEndAttackButton(tgui::Gui& gui) {
	gui.get<tgui::Button>("End Attack")->setVisible(true);
}
void GameScreen::deactivateEndAttackButton(tgui::Gui& gui) {
	gui.get<tgui::Button>("End Attack")->setVisible(false);
}

sf::Image& GameScreen::getTerritoryImage() {
	return m_TerritoryImage;
}

std::vector<Province>& GameScreen::getProvinceList() {
	return gameBoard.getProvinceGrid();
}

const std::vector<std::string>& GameScreen::getGamePhases() {
	return m_GamePhases;
}

const std::string& GameScreen::getPhase() {
	return m_Phase;
}

void GameScreen::setPhase(std::string newPhase) {
	m_Phase = newPhase;
}

void GameScreen::changeOwnership(sf::Color newColor, int index) {
	gameBoard.changeArmyTokenColour(newColor, index);
	gameBoard.getProvinceGrid()[index].setOwner(0);
	gameBoard.getProvinceGrid()[index].setArmyCount(1);
	gameBoard.getArmyCounts()[index].setString("1");
	players[0].setAvailableArmies(players[0].getAvailableArmies() - 1);
}

std::vector<Player> GameScreen::getPlayers() {
	return players;
}

void GameScreen::initializeGame(int playerNumber, std::string playerColour, std::vector<tgui::String> colourList) {
	for (int i = 0; i < playerNumber; i++) {
		if (i == 0) {
			players.push_back(Player(false));
			players[players.size() - 1].setPlayerColour(playerColour);

			for (int j = 0; j < colourList.size(); j++) {
				if (colourList[j] == playerColour) {
					colourList.erase(colourList.begin() + j);
				}
			}
		}
		else {
			players.push_back(Player(true));
			players[players.size() - 1].setPlayerColour(colourList[0].toStdString());

			std::cout << colourList[0].toStdString() << std::endl;

			colourList.erase(colourList.begin());
		}
	}

	std::cout << "Player number initialized: " << players.size() << std::endl;
}

void GameScreen::clearPlayers() {
	players.clear();
	gameBoard.clearOwners();
}

void GameScreen::clearArmies() {
	gameBoard.clearArmyTokens();
	gameBoard.clearArmyCounts();

	for (int i = 0; i < players.size(); i++) {
		players[i].setAvailableArmies(30);
	}
}

void GameScreen::placeArmies(int index) {
	gameBoard.getProvinceGrid()[index].setArmyCount(gameBoard.getProvinceGrid()[index].getArmyCount() + 1);
	gameBoard.getArmyCounts()[index].setString(std::to_string(gameBoard.getProvinceGrid()[index].getArmyCount()));
	players[0].setAvailableArmies(players[0].getAvailableArmies() - 1);
}

void GameScreen::updateNewArmiesText(std::string newText) {
	m_NewArmies.setString(newText);
}

std::string GameScreen::getNewArmiesText() {
	return m_NewArmies.getString();
}

Board& GameScreen::getGameBoard() {
	return gameBoard;
}

void GameScreen::setFirstProvinceSelected(int id) {
	firstProvinceSelected = id;
}

int GameScreen::getFirstProvinceSelected() {
	return firstProvinceSelected;
}

void GameScreen::setSecondProvinceSelected(int id) {
	secondProvinceSelected = id;
}

int GameScreen::getSecondProvinceSelected() {
	return secondProvinceSelected;
}

void GameScreen::setIsFirstProvinceSelected(bool selected) {
	isFirstProvinceSelected = selected;
}

bool GameScreen::getIsFirstProvinceSelected() {
	return isFirstProvinceSelected;
}

void GameScreen::setIsSecondProvinceSelected(bool selected) {
	isSecondProvinceSelected = selected;
}

bool GameScreen::getIsSecondProvinceSelected() {
	return isSecondProvinceSelected;
}

void GameScreen::clearProvinceSelections() {
	firstProvinceSelected = 0;
	secondProvinceSelected = 0;
	isFirstProvinceSelected = false;
	isSecondProvinceSelected = false;
}

void GameScreen::AISetup() {
	AI::setupSelectProvince(players, gameBoard);
}


