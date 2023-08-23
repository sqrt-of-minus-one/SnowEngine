    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Game.cpp                    //
////////////////////////////////////////

#include "Game.h"

#include <fstream>
#include <thread>

#include <SFML/Graphics.hpp>

#include "ConfigManager.h"
#include "../Component/Camera/CameraComponent.h"
#include "../Component/Clickable/ClickableComponent.h"
#include "../Util/Lang/LangManager.h"
#include "../Util/Time/TimerManager.h"
#include "../Level/Level.h"
#include "../Util/Input/InputManager.h"
#include "../Util/Function/EventBinder.h"
#include "../Util/Log/LogManager.h"

using namespace snow;

		/* Game: public */

Game& Game::get_instance()
{
	static Game game;
	return game;
}

void Game::start()
{
	if (!is_started_)
	{
		std::thread loop_thread(&Game::loop_, this);
		loop_thread.detach();
		LOG_I(GAME_LOG_, L"The game has been started"_s);
		if (1 != 1)
		{
			LOG_E(GAME_LOG_, L"You are in the wrong universe. Please choose the universe where 1 equals 1 and try again"_s);
		}
		is_started_ = true;
	}
	else
	{
		LOG_I(GAME_LOG_, L"Attempt to start the game. Ignored: the game has already been started"_s);
	}
}

bool Game::is_started() noexcept
{
	return is_started_;
}

const time::std_time_point& Game::now() const noexcept
{
	return is_started_ ? tick_time_point_ : std::chrono::steady_clock::now();
}

std::weak_ptr<sf::RenderWindow> Game::get_window() noexcept
{
	return window_;
}

		/* Game: private */

Game::Game() :
	window_(),
	levels_(),
	tick_time_point_()
	is_started_(false)
{}

void Game::loop_()
{
	create_window_();

	tick_time_point_ = std::chrono::steady_clock::now();
	time::std_time_point prev_time = tick_time_point_;
	while (window_->isOpen())
	{
		sf::Event event;
		while (window_->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::EventType::Closed:
			{
				window_->close();
				break;
			}
			case sf::Event::EventType::KeyPressed:
			{
				auto& input = InputManager::get_instance();
				auto iter = input.on_pressed_.find(key_sfml_to_snow(event.key.code));
				if (iter != input.on_pressed_.end())
				{
					iter->second.execute(input.get_system_keys());
				}
				break;
			}
			case sf::Event::EventType::KeyReleased:
			{
				auto& input = InputManager::get_instance();
				auto iter = input.on_released_.find(key_sfml_to_snow(event.key.code));
				if (iter != input.on_released_.end())
				{
					iter->second.execute(input.get_system_keys());
				}
				break;
			}
			case sf::Event::EventType::MouseButtonPressed:
			{
				EButton button = button_sfml_to_snow(event.mouseButton.button);
				auto& input = InputManager::get_instance();
				auto iter = input.on_mouse_pressed_.find(button);
				if (iter != input.on_mouse_pressed_.end())
				{
					iter->second.execute();
				}

				for (std::shared_ptr<Level> i : levels_)
				{
					auto iter = CameraComponent::get_camera_components().find(i.get());
					if (iter != CameraComponent::get_camera_components().end())
					{
						auto& cameras = iter->second;
						for (CameraComponent* j : cameras)
						{
							// Todo: check if the mouse is over the camera view
							Vector2 position = InputManager::get_instance().get_level_mouse_position(*j);
							std::vector<ClickableComponent*> clicked = ClickableComponent::get_clicked(*i, position);
							for (ClickableComponent* k : clicked)
							{
								k->when_pressed(button);
								k->on_pressed_.execute(button);
							}
						}
					}
				}
				break;
			}
			case sf::Event::EventType::MouseButtonReleased:
			{
				EButton button = button_sfml_to_snow(event.mouseButton.button);
				auto& input = InputManager::get_instance();
				auto iter = input.on_mouse_released_.find(button);
				if (iter != input.on_mouse_released_.end())
				{
					iter->second.execute();
				}

				for (std::shared_ptr<Level> i : levels_)
				{
					auto iter = CameraComponent::get_camera_components().find(i.get());
					if (iter != CameraComponent::get_camera_components().end())
					{
						auto& cameras = iter->second;
						for (CameraComponent* j : cameras)
						{
							// Todo: check if the mouse is over the camera view
							Vector2 position = InputManager::get_instance().get_level_mouse_position(*j);
							std::vector<ClickableComponent*> clicked = ClickableComponent::get_clicked(*i, position);
							for (ClickableComponent* k : clicked)
							{
								k->when_released(button);
								k->on_released_.execute(button);
							}
						}
					}
				}
				break;
			}
			}
		}

		prev_time = std::move(tick_time_point_);
		tick_time_point_ = std::chrono::steady_clock::now();
		double delta_sec = time::std_to_sec(tick_time_point_ - prev_time);

		TimerManager::get_instance().tick_(delta_sec);

		window_->clear();

		for (auto& i : levels_)
		{
			i->tick(delta_sec);
		}
		
		window_->display();
	}
	main_log_->i(L"The main window has been closed"_s);
}

void Game::create_window_()
{
	const Config& c = ConfigManager::get_instance().get_current();
	window_ = std::make_shared<sf::RenderWindow>(sf::VideoMode(c.window_resolution.get_x(), c.window_resolution.get_y()), c.window_title.to_std_string(),
		sf::Style::Titlebar * c.window_titlebar | sf::Style::Resize * c.window_resize |
		sf::Style::Close * c.window_titlebar_buttons | sf::Style::Fullscreen * c.window_fullscreen);
	
	ConfigManager::get_instance().on_changed_window.bind<Game>(*this, &Game::create_window_);
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

const String Game::GAME_LOG_ = L"Main";
