#pragma once
#include "Screen.h"
#include "Board.h"
#include "Player.h"

class GameScreen : public Screen
{
private:
	ScreenManagerControl* m_ScreenManagerControl;

	sf::Image m_TerritoryImage;
	sf::Texture m_GameMap;
	sf::Sprite m_GameMapSprite;

	//Game phase controls. Identifies what the player can do at a given point in the game
	std::vector<std::string> m_GamePhases = { "setup", "place armies", "attack", "move" };
	std::string m_Phase = "setup";

	//Attack phase controls and visual cues
	int firstProvinceSelected, secondProvinceSelected;
	bool isFirstProvinceSelected = false;
	bool isSecondProvinceSelected = false;
	int attackRound = 0;

	Board gameBoard;
	std::vector<Player> players;

	sf::Font font;

	sf::RectangleShape m_MenuPanel;
	sf::RectangleShape m_MenuOverlay;
	bool menuVisible;

	sf::RectangleShape m_Dashboard;
	sf::RectangleShape m_Statboard;
	sf::Text m_NewArmies;
	sf::Text m_AttackOrMovePath;

public:
	GameScreen(ScreenManagerControl* screenControl, sf::Vector2i res, tgui::Gui& gui);

	void setMenuVisible(bool visible);
	bool getMenuVisible();

	virtual void draw(sf::RenderWindow& window, tgui::Gui& gui);

	virtual void activateGUI(tgui::Gui& gui);
	virtual void deactivateGUI(tgui::Gui& gui);
	virtual void activateButtons(tgui::Gui& gui);
	virtual void deactivateButtons(tgui::Gui& gui);

	void activateMenu(tgui::Gui& gui);
	void deactivateMenu(tgui::Gui& gui);
	void activateEndAttackButton(tgui::Gui& gui);
	void deactivateEndAttackButton(tgui::Gui& gui);
	void activateEndTurnButton(tgui::Gui& gui);
	void deactivateEndTurnButton(tgui::Gui& gui);

	sf::Image& getTerritoryImage();

	std::vector<Province>& getProvinceList();

	const std::vector<std::string>& getGamePhases();
	const std::string& getPhase();
	void setPhase(std::string newPhase);

	std::vector<Player>& getPlayers();
	void initializeGame(int playerNumber, std::string playerColour, std::vector<tgui::String> colourList);
	void clearPlayers();
	void clearArmies();

	void updateNewArmiesText(std::string newText);
	std::string getNewArmiesText();

	Board& getGameBoard();

	void changeOwnership(sf::Color newColor, int index);
	void placeArmies(int index);

	void setFirstProvinceSelected(int id);
	int getFirstProvinceSelected();
	void setSecondProvinceSelected(int id);
	int getSecondProvinceSelected();
	void setIsFirstProvinceSelected(bool selected);
	bool getIsFirstProvinceSelected();
	void setIsSecondProvinceSelected(bool selected);
	bool getIsSecondProvinceSelected();

	int getAttackRound();
	void setAttackRound(int number);

	void clearProvinceSelections();

	void AISetup();
	void AIPlaceArmies(Player& player, int playerID);
};

