#pragma once
#include "Button.h"
#include "ComboBox.h"

class UIPanel
{
private:
	sf::RectangleShape m_UIPanel;

	bool m_IsHidden = false;

protected:
	float m_ButtonWidth = 0;
	float m_ButtonHeight = 0;
	float m_ButtonPadding = 0;

	sf::Font m_Font;
	sf::Text m_Text;

	void addButton(sf::Vector2f position, float width, float height, std::string text, tgui::Gui& gui);
	void addComboBox(sf::Vector2f position, sf::Vector2f dimensions, std::string name, std::vector<std::string> items, tgui::Gui& gui);

public:
	//sf::View m_View;

	UIPanel(sf::Vector2i res, int x, int y, float w, float h);

	virtual void draw(sf::RenderWindow& window);
	void show();
	void hide();
};

