    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Input.cpp                   //
////////////////////////////////////////

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//SnowBall\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\
//\\//     \//\\/ ___/\\//\\//\\//\\//\\//\\//\\//\\//  __ \//\\//\\//\\  \\  \\//\\//\\//\\//\\//\
//\\         /\\_ \\//\  ___ /\\/ __ /\\  \\/  \//  //  // _//\ __ \//\\  \\  \\//\\//\\//\\//\\//\
//\_         _\\/__ //\  /\\  \\  \\  \\  \\/  \//  //  __ \//  //  //\\  \\  \\/| SnowEngine |\//\
//\\__     __/\\//\  /\  /\\  \\_ \\ _\\_ \\ __ // _//  // _//_ //  //\\  \\  \\//| input      |//\
//\\//_____\//\\____//\__/\\__\\/____/\\/____/\____\//_____\//\_______\\__\\__\\//\| system     |/\
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\

#include "Input.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "../Function/EventBinder.h"
#include "../../Math/Vector/Point2.h"
#include "../../Game/Game.h"

using namespace snow;

sf::Keyboard::Key snow::key_snow_to_sfml(EKey key)
{
	switch (key)
	{
	case EKey::A:
		return sf::Keyboard::Key::A;
	case EKey::B:
		return sf::Keyboard::Key::B;
	case EKey::C:
		return sf::Keyboard::Key::C;
	case EKey::D:
		return sf::Keyboard::Key::D;
	case EKey::E:
		return sf::Keyboard::Key::E;
	case EKey::F:
		return sf::Keyboard::Key::F;
	case EKey::G:
		return sf::Keyboard::Key::G;
	case EKey::H:
		return sf::Keyboard::Key::H;
	case EKey::I:
		return sf::Keyboard::Key::I;
	case EKey::J:
		return sf::Keyboard::Key::J;
	case EKey::K:
		return sf::Keyboard::Key::K;
	case EKey::L:
		return sf::Keyboard::Key::L;
	case EKey::M:
		return sf::Keyboard::Key::M;
	case EKey::N:
		return sf::Keyboard::Key::N;
	case EKey::O:
		return sf::Keyboard::Key::O;
	case EKey::P:
		return sf::Keyboard::Key::P;
	case EKey::Q:
		return sf::Keyboard::Key::Q;
	case EKey::R:
		return sf::Keyboard::Key::R;
	case EKey::S:
		return sf::Keyboard::Key::S;
	case EKey::T:
		return sf::Keyboard::Key::T;
	case EKey::U:
		return sf::Keyboard::Key::U;
	case EKey::V:
		return sf::Keyboard::Key::V;
	case EKey::W:
		return sf::Keyboard::Key::W;
	case EKey::X:
		return sf::Keyboard::Key::X;
	case EKey::Y:
		return sf::Keyboard::Key::Y;
	case EKey::Z:
		return sf::Keyboard::Key::Z;
	case EKey::SPACE:
		return sf::Keyboard::Key::Space;
	case EKey::BACKSPACE:
		return sf::Keyboard::Key::Backspace;
	case EKey::ONE:
		return sf::Keyboard::Key::Num1;
	case EKey::TWO:
		return sf::Keyboard::Key::Num2;
	case EKey::THREE:
		return sf::Keyboard::Key::Num3;
	case EKey::FOUR:
		return sf::Keyboard::Key::Num4;
	case EKey::FIVE:
		return sf::Keyboard::Key::Num5;
	case EKey::SIX:
		return sf::Keyboard::Key::Num6;
	case EKey::SEVEN:
		return sf::Keyboard::Key::Num7;
	case EKey::EIGHT:
		return sf::Keyboard::Key::Num8;
	case EKey::NINE:
		return sf::Keyboard::Key::Num9;
	case EKey::ZERO:
		return sf::Keyboard::Key::Num0;
	case EKey::MINUS:
		return sf::Keyboard::Key::Hyphen;
	case EKey::EQUAL:
		return sf::Keyboard::Key::Equal;
	case EKey::F1:
		return sf::Keyboard::Key::F1;
	case EKey::F2:
		return sf::Keyboard::Key::F2;
	case EKey::F3:
		return sf::Keyboard::Key::F3;
	case EKey::F4:
		return sf::Keyboard::Key::F4;
	case EKey::F5:
		return sf::Keyboard::Key::F5;
	case EKey::F6:
		return sf::Keyboard::Key::F6;
	case EKey::F7:
		return sf::Keyboard::Key::F7;
	case EKey::F8:
		return sf::Keyboard::Key::F8;
	case EKey::F9:
		return sf::Keyboard::Key::F9;
	case EKey::F10:
		return sf::Keyboard::Key::F10;
	case EKey::F11:
		return sf::Keyboard::Key::F11;
	case EKey::F12:
		return sf::Keyboard::Key::F12;
	case EKey::TILDE:
		return sf::Keyboard::Key::Tilde;
	case EKey::ESC:
		return sf::Keyboard::Key::Escape;
	case EKey::TAB:
		return sf::Keyboard::Key::Tab;
	case EKey::L_SHIFT:
		return sf::Keyboard::Key::LShift;
	case EKey::R_SHIFT:
		return sf::Keyboard::Key::RShift;
	case EKey::L_CTRL:
		return sf::Keyboard::Key::LControl;
	case EKey::R_CTRL:
		return sf::Keyboard::Key::RControl;
	case EKey::L_ALT:
		return sf::Keyboard::Key::LAlt;
	case EKey::R_ALT:
		return sf::Keyboard::Key::RAlt;
	case EKey::WIN:
		return sf::Keyboard::Key::LSystem;
	case EKey::ENTER:
		return sf::Keyboard::Key::Enter;
	case EKey::LEFT:
		return sf::Keyboard::Key::Left;
	case EKey::RIGHT:
		return sf::Keyboard::Key::Right;
	case EKey::UP:
		return sf::Keyboard::Key::Up;
	case EKey::DOWN:
		return sf::Keyboard::Key::Down;
	case EKey::L_BRACKET:
		return sf::Keyboard::Key::LBracket;
	case EKey::R_BRACKET:
		return sf::Keyboard::Key::RBracket;
	case EKey::SEMICOLON:
		return sf::Keyboard::Key::Semicolon;
	case EKey::QUOTE:
		return sf::Keyboard::Key::Quote;
	case EKey::BACKSLASH:
		return sf::Keyboard::Key::Backslash;
	case EKey::COMMA:
		return sf::Keyboard::Key::Comma;
	case EKey::PERIOD:
		return sf::Keyboard::Key::Period;
	case EKey::SLASH:
		return sf::Keyboard::Key::Slash;
	case EKey::HOME:
		return sf::Keyboard::Key::Home;
	case EKey::END:
		return sf::Keyboard::Key::End;
	case EKey::PAGE_UP:
		return sf::Keyboard::Key::PageUp;
	case EKey::PAGE_DOWN:
		return sf::Keyboard::Key::PageDown;
	case EKey::DELETE:
		return sf::Keyboard::Key::Delete;
	case EKey::INSERT:
		return sf::Keyboard::Key::Insert;
	case EKey::PAUSE:
		return sf::Keyboard::Key::Pause;
	case EKey::MENU:
		return sf::Keyboard::Key::Menu;
	case EKey::NUM_ADD:
		return sf::Keyboard::Key::Add;
	case EKey::NUM_SUBTRACT:
		return sf::Keyboard::Key::Subtract;
	case EKey::NUM_MULTIPLY:
		return sf::Keyboard::Key::Multiply;
	case EKey::NUM_DIVIDE:
		return sf::Keyboard::Key::Divide;
	case EKey::NUM_0:
		return sf::Keyboard::Key::Numpad0;
	case EKey::NUM_1:
		return sf::Keyboard::Key::Numpad1;
	case EKey::NUM_2:
		return sf::Keyboard::Key::Numpad2;
	case EKey::NUM_3:
		return sf::Keyboard::Key::Numpad3;
	case EKey::NUM_4:
		return sf::Keyboard::Key::Numpad4;
	case EKey::NUM_5:
		return sf::Keyboard::Key::Numpad5;
	case EKey::NUM_6:
		return sf::Keyboard::Key::Numpad6;
	case EKey::NUM_7:
		return sf::Keyboard::Key::Numpad7;
	case EKey::NUM_8:
		return sf::Keyboard::Key::Numpad8;
	case EKey::NUM_9:
		return sf::Keyboard::Key::Numpad9;
	default:
		return sf::Keyboard::Key::Unknown;
	}
}

EKey snow::key_sfml_to_snow(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Key::A:
		return EKey::A;
	case sf::Keyboard::Key::B:
		return EKey::B;
	case sf::Keyboard::Key::C:
		return EKey::C;
	case sf::Keyboard::Key::D:
		return EKey::D;
	case sf::Keyboard::Key::E:
		return EKey::E;
	case sf::Keyboard::Key::F:
		return EKey::F;
	case sf::Keyboard::Key::G:
		return EKey::G;
	case sf::Keyboard::Key::H:
		return EKey::H;
	case sf::Keyboard::Key::I:
		return EKey::I;
	case sf::Keyboard::Key::J:
		return EKey::J;
	case sf::Keyboard::Key::K:
		return EKey::K;
	case sf::Keyboard::Key::L:
		return EKey::L;
	case sf::Keyboard::Key::M:
		return EKey::M;
	case sf::Keyboard::Key::N:
		return EKey::N;
	case sf::Keyboard::Key::O:
		return EKey::O;
	case sf::Keyboard::Key::P:
		return EKey::P;
	case sf::Keyboard::Key::Q:
		return EKey::Q;
	case sf::Keyboard::Key::R:
		return EKey::R;
	case sf::Keyboard::Key::S:
		return EKey::S;
	case sf::Keyboard::Key::T:
		return EKey::T;
	case sf::Keyboard::Key::U:
		return EKey::U;
	case sf::Keyboard::Key::V:
		return EKey::V;
	case sf::Keyboard::Key::W:
		return EKey::W;
	case sf::Keyboard::Key::X:
		return EKey::X;
	case sf::Keyboard::Key::Y:
		return EKey::Y;
	case sf::Keyboard::Key::Z:
		return EKey::Z;
	case sf::Keyboard::Key::Space:
		return EKey::SPACE;
	case sf::Keyboard::Key::Backspace:
		return EKey::BACKSPACE;
	case sf::Keyboard::Key::Num1:
		return EKey::ONE;
	case sf::Keyboard::Key::Num2:
		return EKey::TWO;
	case sf::Keyboard::Key::Num3:
		return EKey::THREE;
	case sf::Keyboard::Key::Num4:
		return EKey::FOUR;
	case sf::Keyboard::Key::Num5:
		return EKey::FIVE;
	case sf::Keyboard::Key::Num6:
		return EKey::SIX;
	case sf::Keyboard::Key::Num7:
		return EKey::SEVEN;
	case sf::Keyboard::Key::Num8:
		return EKey::EIGHT;
	case sf::Keyboard::Key::Num9:
		return EKey::NINE;
	case sf::Keyboard::Key::Num0:
		return EKey::ZERO;
	case sf::Keyboard::Key::Hyphen:
		return EKey::MINUS;
	case sf::Keyboard::Key::Equal:
		return EKey::EQUAL;
	case sf::Keyboard::Key::F1:
		return EKey::F1;
	case sf::Keyboard::Key::F2:
		return EKey::F2;
	case sf::Keyboard::Key::F3:
		return EKey::F3;
	case sf::Keyboard::Key::F4:
		return EKey::F4;
	case sf::Keyboard::Key::F5:
		return EKey::F5;
	case sf::Keyboard::Key::F6:
		return EKey::F6;
	case sf::Keyboard::Key::F7:
		return EKey::F7;
	case sf::Keyboard::Key::F8:
		return EKey::F8;
	case sf::Keyboard::Key::F9:
		return EKey::F9;
	case sf::Keyboard::Key::F10:
		return EKey::F10;
	case sf::Keyboard::Key::F11:
		return EKey::F11;
	case sf::Keyboard::Key::F12:
		return EKey::F12;
	case sf::Keyboard::Key::Tilde:
		return EKey::TILDE;
	case sf::Keyboard::Key::Escape:
		return EKey::ESC;
	case sf::Keyboard::Key::Tab:
		return EKey::TAB;
	case sf::Keyboard::Key::LShift:
		return EKey::L_SHIFT;
	case sf::Keyboard::Key::RShift:
		return EKey::R_SHIFT;
	case sf::Keyboard::Key::LControl:
		return EKey::L_CTRL;
	case sf::Keyboard::Key::RControl:
		return EKey::R_CTRL;
	case sf::Keyboard::Key::LAlt:
		return EKey::L_ALT;
	case sf::Keyboard::Key::RAlt:
		return EKey::R_ALT;
	case sf::Keyboard::Key::LSystem:
		return EKey::WIN;
	case sf::Keyboard::Key::Enter:
		return EKey::ENTER;
	case sf::Keyboard::Key::Left:
		return EKey::LEFT;
	case sf::Keyboard::Key::Right:
		return EKey::RIGHT;
	case sf::Keyboard::Key::Up:
		return EKey::UP;
	case sf::Keyboard::Key::Down:
		return EKey::DOWN;
	case sf::Keyboard::Key::LBracket:
		return EKey::L_BRACKET;
	case sf::Keyboard::Key::RBracket:
		return EKey::R_BRACKET;
	case sf::Keyboard::Key::Semicolon:
		return EKey::SEMICOLON;
	case sf::Keyboard::Key::Quote:
		return EKey::QUOTE;
	case sf::Keyboard::Key::Backslash:
		return EKey::BACKSLASH;
	case sf::Keyboard::Key::Comma:
		return EKey::COMMA;
	case sf::Keyboard::Key::Period:
		return EKey::PERIOD;
	case sf::Keyboard::Key::Slash:
		return EKey::SLASH;
	case sf::Keyboard::Key::Home:
		return EKey::HOME;
	case sf::Keyboard::Key::End:
		return EKey::END;
	case sf::Keyboard::Key::PageUp:
		return EKey::PAGE_UP;
	case sf::Keyboard::Key::PageDown:
		return EKey::PAGE_DOWN;
	case sf::Keyboard::Key::Delete:
		return EKey::DELETE;
	case sf::Keyboard::Key::Insert:
		return EKey::INSERT;
	case sf::Keyboard::Key::Pause:
		return EKey::PAUSE;
	case sf::Keyboard::Key::Menu:
		return EKey::MENU;
	case sf::Keyboard::Key::Add:
		return EKey::NUM_ADD;
	case sf::Keyboard::Key::Subtract:
		return EKey::NUM_SUBTRACT;
	case sf::Keyboard::Key::Multiply:
		return EKey::NUM_MULTIPLY;
	case sf::Keyboard::Key::Divide:
		return EKey::NUM_DIVIDE;
	case sf::Keyboard::Key::Numpad0:
		return EKey::NUM_0;
	case sf::Keyboard::Key::Numpad1:
		return EKey::NUM_1;
	case sf::Keyboard::Key::Numpad2:
		return EKey::NUM_2;
	case sf::Keyboard::Key::Numpad3:
		return EKey::NUM_3;
	case sf::Keyboard::Key::Numpad4:
		return EKey::NUM_4;
	case sf::Keyboard::Key::Numpad5:
		return EKey::NUM_5;
	case sf::Keyboard::Key::Numpad6:
		return EKey::NUM_6;
	case sf::Keyboard::Key::Numpad7:
		return EKey::NUM_7;
	case sf::Keyboard::Key::Numpad8:
		return EKey::NUM_8;
	case sf::Keyboard::Key::Numpad9:
		return EKey::NUM_9;
	default:
		return EKey::UNKNOWN;
	}
}

sf::Mouse::Button snow::button_snow_to_sfml(EButton button)
{
	switch (button)
	{
	case EButton::LEFT:
		return sf::Mouse::Button::Left;
	case EButton::RIGHT:
		return sf::Mouse::Button::Right;
	case EButton::MIDDLE:
		return sf::Mouse::Button::Middle;
	case EButton::EXTRA_1:
		return sf::Mouse::Button::XButton1;
	default:
		return sf::Mouse::Button::XButton2;
	}
}

EButton snow::button_sfml_to_snow(sf::Mouse::Button button)
{
	switch (button)
	{
	case sf::Mouse::Button::Left:
		return EButton::LEFT;
	case sf::Mouse::Button::Right:
		return EButton::RIGHT;
	case sf::Mouse::Button::Middle:
		return EButton::MIDDLE;
	case sf::Mouse::Button::XButton1:
		return EButton::EXTRA_1;
	default:
		return EButton::EXTRA_2;
	}
}

		/* Input: public */

Input& Input::get_instance()
{
	static Input input;
	return input;
}

String Input::to_string() const
{
	return L"Input object";
}

int Input::hash_code() const noexcept
{
	return 0;
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
