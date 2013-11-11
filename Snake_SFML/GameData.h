#pragma once

#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "GameSettings.h"


enum GameState
{
	UNINITIALIZED,
	INITIALIZED,
	MAIN_MENU,
	RUNNING,
	PAUSED,
	CLOSING
};


struct GameData
{
	GameSettings settings;
	GameState state;
	sf::Clock clock;

	sf::Music music;
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
};

