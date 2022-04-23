#pragma once
#include <string>
#include <TGUI/TGUI.hpp>

class ScreenManagerControl
{
public:
	virtual void switchScreens(std::string switchToScreen, tgui::Gui& gui) = 0;
	virtual void initializeGameScreen(int playerNumber, std::string playerColour, std::vector<tgui::String> colourList) = 0;
};

