#include "Screen.h"

void Screen::initialize() {}

void Screen::addPanel(std::unique_ptr<UIPanel> panel, ScreenManagerControl* screenControlPtr, std::shared_ptr<InputHandler> inputHandler) {
	inputHandler->initializeInputHandler(screenControlPtr, this);

	m_Panels.push_back(std::move(panel));
	m_InputHandlers.push_back(inputHandler);
}

void Screen::handleInput(sf::RenderWindow& window, tgui::Gui& gui) {
	sf::Event event;

	auto start = m_InputHandlers.begin();
	auto end = m_InputHandlers.end();

	while (window.pollEvent(event)) {
		
		gui.handleEvent(event);

		for (start; start != end; ++start) {
			(*start)->handleInput(window, gui, event);
		}
	}
}

void Screen::update() {}

void Screen::draw(sf::RenderWindow& window, tgui::Gui& gui) {
	auto start = m_Panels.begin();
	auto end = m_Panels.end();

	for (start; start != end; ++start) {
		(*start)->draw(window);
	}

	gui.draw();
}

void Screen::activateGUI(tgui::Gui& gui) {}
void Screen::deactivateGUI(tgui::Gui& gui) {}
void Screen::activateButtons(tgui::Gui& gui) {}
void Screen::deactivateButtons(tgui::Gui& gui) {}
void Screen::activateComboBoxes(tgui::Gui& gui) {}
void Screen::deactivateComboBoxes(tgui::Gui& gui) {}

void Screen::initializeGame(int playerNumber, std::string playerColour, std::vector<tgui::String> colourList) {}
