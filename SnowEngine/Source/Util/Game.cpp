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
	std::thread loop_thread(loop_);
	loop_thread.detach();
	main_log_->i(L"The game has been started"_s);
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

std::mutex Game::log_file_mtx_;
std::wofstream Game::log_file_;

#ifdef _DEBUG
bool Game::debug_mode_ = true;
#else
bool Game::debug_mode_ = false;
#endif

Config Game::config;
Lang Game::lang;
std::unique_ptr<Log> Game::main_log_(new Log(L"Main"_s));
