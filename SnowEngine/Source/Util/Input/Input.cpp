    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Input.cpp                   //
////////////////////////////////////////

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//SnowBall\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
//\\//     \//\\/ ___/\\//\\//\\//\\//\\//\\//\\//\\//  __ \//\\//\\//\\  \\  \\//\\//\\//\\//\\///
//\\         /\\_ \\//\  ___ /\\/ __ /\\  \\/  \//  //  // _//\ __ \//\\  \\  \\//\\//\\//\\//\\///
//\_         _\\/__ //\  /\\  \\  \\  \\  \\/  \//  //  __ \//  //  //\\  \\  \\/| SnowEngine |\///
//\\__     __/\\//\  /\  /\\  \\_ \\ _\\_ \\ __ // _//  // _//_ //  //\\  \\  \\//| input      |///
//\\//_____\//\\____//\__/\\__\\/____/\\/____/\____\//_____\//\____,__\\__\\__\\//\| system     |//
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///

#include "Input.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "../Function/EventBinder.h"
#include "../../Math/Vector/Point2.h"
#include "../../Game/Game.h"
#include "../../Component/Camera/CameraComponent.h"

using namespace snow;

		/* Input: public */

Input& Input::get_instance()
{
	static Input input;
	return input;
}

bool Input::is_key_pressed(EKey key)
{
	return sf::Keyboard::isKeyPressed(key_snow_to_sfml(key));
}

SystemKeys Input::get_system_keys()
{
	SystemKeys ret;
	ret.LeftShift = is_key_pressed(EKey::L_SHIFT);
	ret.LeftCtrl = is_key_pressed(EKey::L_CTRL);
	ret.LeftAlt = is_key_pressed(EKey::L_ALT);
	ret.RightShift = is_key_pressed(EKey::R_SHIFT);
	ret.RightCtrl = is_key_pressed(EKey::R_CTRL);
	ret.RightAlt = is_key_pressed(EKey::R_ALT);
	ret.Win = is_key_pressed(EKey::WIN);
	return ret;
}

Point2 Input::get_screen_mouse_position()
{
	sf::Vector2i position = sf::Mouse::getPosition();
	return Point2(position.x, position.y);
}

Point2 Input::get_window_mouse_position()
{
	auto window = Game::get_window().lock();
	if (window)
	{
		sf::Vector2i position = sf::Mouse::getPosition(*window);
		return Point2(position.x, position.y);
	}
	else
	{
		return Point2::ZERO;
	}
}

Vector2 Input::get_level_mouse_position(const CameraComponent& relative_to)
{
	auto window = Game::get_window().lock();
	if (window)
	{
		sf::Vector2f position = window->mapPixelToCoords(sf::Mouse::getPosition(*window), relative_to.view_);
		return Vector2(position.x, position.y);
	}
	else
	{
		return Vector2::ZERO;
	}
}

void Input::set_screen_mouse_position(const Point2& position)
{
	sf::Mouse::setPosition(sf::Vector2i(position.get_x(), position.get_y()));
}

void Input::set_window_mouse_position(const Point2& position)
{
	auto window = Game::get_window().lock();
	if (window)
	{
		sf::Mouse::setPosition(sf::Vector2i(position.get_x(), position.get_y()), *window);
	}
}

void Input::set_level_mouse_position(const Vector2& position, const CameraComponent& relative_to)
{
	auto window = Game::get_window().lock();
	if (window)
	{
		sf::Mouse::setPosition(window->mapCoordsToPixel(sf::Vector2f(position.get_x(), position.get_y())), *window);
	}
}

EventBinder<SystemKeys>& Input::on_pressed(EKey key)
{
	auto iter = on_pressed_binder_.find(key);
	if (iter == on_pressed_binder_.end())
	{
		return on_pressed_binder_.insert(std::make_pair(key, EventBinder<SystemKeys>(on_pressed_[key]))).first->second;
	}
	else
	{
		return iter->second;
	}
}

EventBinder<SystemKeys>& Input::on_released(EKey key)
{
	auto iter = on_released_binder_.find(key);
	if (iter == on_released_binder_.end())
	{
		return on_released_binder_.insert(std::make_pair(key, EventBinder<SystemKeys>(on_released_[key]))).first->second;
	}
	else
	{
		return iter->second;
	}
}

EventBinder<>& Input::on_mouse_pressed(EButton button)
{
	auto iter = on_mouse_pressed_binder_.find(button);
	if (iter == on_mouse_pressed_binder_.end())
	{
		return on_mouse_pressed_binder_.insert(std::make_pair(button, EventBinder<>(on_mouse_pressed_[button]))).first->second;
	}
	else
	{
		return iter->second;
	}
}

EventBinder<>& Input::on_mouse_released(EButton button)
{
	auto iter = on_mouse_released_binder_.find(button);
	if (iter == on_mouse_released_binder_.end())
	{
		return on_mouse_released_binder_.insert(std::make_pair(button, EventBinder<>(on_mouse_released_[button]))).first->second;
	}
	else
	{
		return iter->second;
	}
}

		/* Input: private */

Input::Input()
{}
