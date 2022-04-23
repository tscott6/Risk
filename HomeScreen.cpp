#include "HomeScreen.h"
#include "HomeUIPanel.h"
#include "HomeInputHandler.h"

HomeScreen::HomeScreen(ScreenManagerControl* screenControl, sf::Vector2i res, tgui::Gui& gui)
{
	auto homeUI = std::make_unique<HomeUIPanel>(res, gui);
	auto homeInput = std::make_shared<HomeInputHandler>();

	addPanel(std::move(homeUI), screenControl, homeInput);

	m_ScreenManagerControl = screenControl;

	m_BackgroundTexture.loadFromFile("graphics/background.png");

	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	deactivateGUI(gui);

	//auto textureSize = m_BackgroundSprite.getTexture()->getSize();

	//m_BackgroundSprite.setScale(float(m_View.getSize().x) / textureSize.x, float(m_View.getSize().y) / textureSize.y);
}

void HomeScreen::draw(sf::RenderWindow& window, tgui::Gui& gui) {
	//window.setView(m_View);
	window.draw(m_BackgroundSprite);

	Screen::draw(window, gui);
}

void HomeScreen::activateButtons(tgui::Gui& gui) {
	gui.get<tgui::Button>("Quit")->setVisible(true);
	gui.get<tgui::Button>("New Game")->setVisible(true);
}

void HomeScreen::deactivateButtons(tgui::Gui& gui) {
	gui.get<tgui::Button>("Quit")->setVisible(false);
	gui.get<tgui::Button>("New Game")->setVisible(false);
}

void HomeScreen::activateGUI(tgui::Gui& gui) {
	activateButtons(gui); 
}
void HomeScreen::deactivateGUI(tgui::Gui& gui) {
	deactivateButtons(gui);
}

