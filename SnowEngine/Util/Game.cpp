    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Game.cpp                    //
////////////////////////////////////////

#include "Game.h"

#include <fstream>
#include <thread>

#include <SFML/Graphics.hpp>

using namespace snow;

void Game::start()
{
	std::thread loop_thread(loop);
	loop_thread.detach();
	game_log_->i(L"The game has been started"_s);
}

void Game::loop()
{
	sf::RenderWindow window(sf::VideoMode(config.resolution.get_x(), config.resolution.get_y()), config.title.to_std_string(),
		sf::Style::Titlebar * config.titlebar | sf::Style::Resize * config.resize |
		sf::Style::Close * config.titlebar_buttons | sf::Style::Fullscreen * config.fullscreen);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
	game_log_->i(L"The main window has been closed"_s);
}

std::wofstream Game::log_file_;
#ifdef _DEBUG
bool Game::debug_mode_ = true;
#else
bool Game::debug_mode_ = false;
#endif

Config Game::config;
Lang Game::lang;
std::unique_ptr<Log> Game::game_log_ = std::make_unique<Log>(L"Main"_s);
