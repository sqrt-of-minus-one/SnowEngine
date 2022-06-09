    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Game.cpp                    //
////////////////////////////////////////

#include "Game.h"

#include <fstream>
#include <thread>

#include <SFML/Graphics.hpp>

#include "Config.h"
#include "Lang/Lang.h"
#include "Time/Time.h"

using namespace snow;

void Game::start()
{
	if (!is_started_)
	{
		std::thread loop_thread(loop_);
		loop_thread.detach();
		main_log_->i(L"The game has been started"_s);
		is_started_ = true;
	}
}

Config Game::config;
Lang Game::lang;

bool Game::is_started() noexcept
{
	return is_started_;
}

void Game::loop_()
{
	sf::RenderWindow window(sf::VideoMode(config.resolution.get_x(), config.resolution.get_y()), config.title.to_std_string(),
		sf::Style::Titlebar * config.titlebar | sf::Style::Resize * config.resize |
		sf::Style::Close * config.titlebar_buttons | sf::Style::Fullscreen * config.fullscreen);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();

//		Todo: draw		
		
		window.display();
	}
	main_log_->i(L"The main window has been closed"_s);
}

bool Game::is_started_ = false;
std::unique_ptr<Log> Game::main_log_(new Log(L"Main"_s));
