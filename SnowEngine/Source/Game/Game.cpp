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
#include "../Util/Lang/Lang.h"
#include "../Util/Time/TimerManager.h"
#include "../Level/Level.h"
#include "../Util/Function/EventBinder.h"

using namespace snow;

		/* Game: public */

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

bool Game::is_started() noexcept
{
	return is_started_;
}

std::weak_ptr<sf::RenderWindow> Game::get_window() noexcept
{
	return window_;
}

template<typename T_Level>
std::shared_ptr<T_Level> Game::create_level()
{
	static_assert(std::is_base_of<Level, T_Level>::value, L"An argument of create_level method template must be Level");

	std::shared_ptr<T_Level> level(new T_Level);
	level->on_destroyed.bind(&Game::remove_level_, true);

	levels_.push_back(level);
	return level;
}

Config Game::config;
Lang Game::lang;
TimerManager Game::timer_manager;

		/* Game: private */

void Game::loop_()
{
	window_ = std::make_shared<sf::RenderWindow>(sf::VideoMode(config.resolution.get_x(), config.resolution.get_y()), config.title.to_std_string(),
		sf::Style::Titlebar * config.titlebar | sf::Style::Resize * config.resize |
		sf::Style::Close * config.titlebar_buttons | sf::Style::Fullscreen * config.fullscreen);

	auto f_time = std::chrono::steady_clock::now();
	auto s_time = f_time;
	while (window_->isOpen())
	{
		sf::Event event;
		while (window_->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window_->close();
			}
		}

		f_time = std::move(s_time);
		s_time = std::chrono::steady_clock::now();
		float delta_sec = std::chrono::duration_cast<std::chrono::microseconds>(s_time - f_time).count() / 1'000'000.f;

		window_->clear();

		timer_manager.tick_(delta_sec);

//		Todo: draw
		
		window_->display();
	}
	main_log_->i(L"The main window has been closed"_s);
}

void Game::remove_level_(Level& level)
{
	for (auto i = levels_.begin(); i != levels_.end(); i++)
	{
		if (i->get() == &level)
		{
			levels_.erase(i);
			break;
		}
	}
}

std::shared_ptr<sf::RenderWindow> Game::window_;
std::list<std::shared_ptr<Level>> Game::levels_;
bool Game::is_started_ = false;
std::unique_ptr<Log> Game::main_log_(new Log(L"Main"_s));
