#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "ScreenManager.h"

class GameEngine
{
private:
	sf::RenderWindow m_Window;
	tgui::Gui m_GUI{m_Window};

	sf::Vector2f m_Resolution;

	std::unique_ptr<ScreenManager> m_ScreenManager;

	void handleInput();
	void update();
	void draw();

public:
	GameEngine();
	void run();
};

