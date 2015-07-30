#include <sstream>

#include "GUIMenu.h"


GUIMenu::GUIMenu(GameData &data)
	: data(data),
	  text(),
	  items()
{
	initialize();
	loadContent();
}


GUIMenu::~GUIMenu()
{
}


void GUIMenu::initialize()
{
	fontName = "arial";
	fontSize = 48;
	fontColor = sf::Color::White;

	items.push_back("Play");
	items.push_back("Settings");
	items.push_back("Exit");
	
	selectedItemIdx = 0;
	needUpdate = true;
}


void GUIMenu::loadContent()
{
	std::string fontPath = "data/fonts/" + fontName + ".ttf";

	if (!font.loadFromFile(fontPath))
	{
		// Error
	}
}


void GUIMenu::update(sf::Time &elapsedTime)
{
	if (needUpdate)
	{
		sf::Text newText;
		int horizontalMargin = 60;
		int verticalMargin = 6 * newText.getCharacterSize();
		int itemsSpacing = 0;

		text.clear();

		// Make the options evenly spread out and vertically centered around the middle of the screen
		if (items.size() > 1)
			itemsSpacing = (data.settings.windowHeight - verticalMargin * 2 - fontSize * items.size()) / (items.size() - 1);
		
		newText.setFont(font);
		newText.setCharacterSize(fontSize);

		for (int index = 0; index != items.size(); index++)
		{
			sf::Vector2f position = sf::Vector2f(static_cast<float>(horizontalMargin), static_cast<float>(verticalMargin + index * (fontSize + itemsSpacing)));
			std::ostringstream ostr;
			
			ostr << items[index].toAnsiString();
			newText.setString(std::string(ostr.str()));

			// Make the selected option more visible than the others
			if (index == selectedItemIdx)
			{
				newText.setStyle(sf::Text::Bold);
				newText.setColor(sf::Color::White);
				position.x += 25.f;
			}
			else
			{
				newText.setStyle(sf::Text::Regular);
				newText.setColor(sf::Color(125, 135, 155));
			}

			newText.setPosition(position);
			text.push_back(newText);
		}
	}
}


void GUIMenu::draw(sf::RenderWindow &window)
{
	for (std::vector<sf::Text>::iterator it = text.begin(); it != text.end(); it++)
		window.draw(*it);
}


void GUIMenu::handleKeyboardEvent(sf::Event &event, sf::Time &elapsedTime)
{
	switch (event.key.code)
	{
	case sf::Keyboard::Escape:
		data.state = CLOSING;
		break;

	// Go up
	case sf::Keyboard::Up:
	case sf::Keyboard::W:
		if (selectedItemIdx > 0)
			selectedItemIdx--;
		break;

	// Go down
	case sf::Keyboard::Down:
	case sf::Keyboard::S:
		if (selectedItemIdx < static_cast<int>(items.size()) - 1)
			selectedItemIdx++;
		break;

	// Confirm choice
	case sf::Keyboard::Return:
		if (selectedItemIdx == 0)
		{
			data.state = RUNNING;
			//data.music.play();
		}
		else if (selectedItemIdx == 1)
		{

		}
		else if (selectedItemIdx == 2)
		{
			data.state = CLOSING;
		}
		break;

	default:
		break;
	}
}

