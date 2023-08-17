    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: InputManager.cpp            //
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

		/* InputManager: public */

InputManager& InputManager::get_instance()
{
	static InputManager input;
	return input;
}

String InputManager::to_string() const
{
	return L"InputManager"_s;
}

std::shared_ptr<json::Element> InputManager::to_json() const
{
	return util::to_json(L"InputManager"_s);
}

bool InputManager::is_key_pressed(EKey key)
{
	return sf::Keyboard::isKeyPressed(key_snow_to_sfml(key));
}

SystemKeys InputManager::get_system_keys()
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

Point2 InputManager::get_screen_mouse_position()
{
	sf::Vector2i position = sf::Mouse::getPosition();
	return Point2(position.x, position.y);
}

Point2 InputManager::get_window_mouse_position()
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

Vector2 InputManager::get_level_mouse_position(const CameraComponent& relative_to)
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

void InputManager::set_screen_mouse_position(const Point2& position)
{
	sf::Mouse::setPosition(sf::Vector2i(position.get_x(), position.get_y()));
}

void InputManager::set_window_mouse_position(const Point2& position)
{
	auto window = Game::get_window().lock();
	if (window)
	{
		sf::Mouse::setPosition(sf::Vector2i(position.get_x(), position.get_y()), *window);
	}
}

void InputManager::set_level_mouse_position(const Vector2& position, const CameraComponent& relative_to)
{
	auto window = Game::get_window().lock();
	if (window)
	{
		sf::Mouse::setPosition(window->mapCoordsToPixel(sf::Vector2f(position.get_x(), position.get_y())), *window);
	}
}

EventBinder<SystemKeys>& InputManager::on_pressed(EKey key)
{
	auto iter = on_pressed_binder_.find(key);
	if (iter == on_pressed_binder_.end())
	{
		return on_pressed_binder_.insert({ key, EventBinder<SystemKeys>(on_pressed_[key]) }).first->second;
	}
	else
	{
		return iter->second;
	}
}

EventBinder<SystemKeys>& InputManager::on_released(EKey key)
{
	auto iter = on_released_binder_.find(key);
	if (iter == on_released_binder_.end())
	{
		return on_released_binder_.insert({ key, EventBinder<SystemKeys>(on_released_[key]) }).first->second;
	}
	else
	{
		return iter->second;
	}
}

EventBinder<>& InputManager::on_mouse_pressed(EButton button)
{
	auto iter = on_mouse_pressed_binder_.find(button);
	if (iter == on_mouse_pressed_binder_.end())
	{
		return on_mouse_pressed_binder_.insert({ button, EventBinder<>(on_mouse_pressed_[button]) }).first->second;
	}
	else
	{
		return iter->second;
	}
}

EventBinder<>& InputManager::on_mouse_released(EButton button)
{
	auto iter = on_mouse_released_binder_.find(button);
	if (iter == on_mouse_released_binder_.end())
	{
		return on_mouse_released_binder_.insert({ button, EventBinder<>(on_mouse_released_[button]) }).first->second;
	}
	else
	{
		return iter->second;
	}
}

		/* InputManager: private */

InputManager::InputManager()
{}
