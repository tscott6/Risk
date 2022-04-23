#include "GameEngine.h"

GameEngine::GameEngine() {
	m_Resolution.x = sf::VideoMode::getDesktopMode().width;
	m_Resolution.y = sf::VideoMode::getDesktopMode().height;

	m_Window.create(sf::VideoMode(1800, 1000), "Risk");

	m_ScreenManager = std::unique_ptr<ScreenManager>(new ScreenManager(sf::Vector2i(m_Resolution.x, m_Resolution.y), m_GUI));

	m_GUI.setTarget(m_Window);
}

void GameEngine::run() {
	m_Window.setMouseCursorVisible(true);

	while (m_Window.isOpen()) {
		handleInput();
		update();
		draw();
	}
}

void GameEngine::handleInput() {
	m_ScreenManager->handleInput(m_Window, m_GUI);
}

void GameEngine::update() {

}

void GameEngine::draw() {
	m_Window.clear(sf::Color::White);
	m_ScreenManager->draw(m_Window, m_GUI);
	m_Window.display();
}
