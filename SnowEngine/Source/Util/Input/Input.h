    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Input.h                     //
////////////////////////////////////////

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//SnowBall\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\
//\\//     \//\\/ ___/\\//\\//\\//\\//\\//\\//\\//\\//  __ \//\\//\\//\\  \\  \\//\\//\\//\\//\\//\
//\\         /\\_ \\//\  ___ /\\/ __ /\\  \\/  \//  //  // _//\ __ \//\\  \\  \\//\\//\\//\\//\\//\
//\_         _\\/__ //\  /\\  \\  \\  \\  \\/  \//  //  __ \//  //  //\\  \\  \\/| SnowEngine |\//\
//\\__     __/\\//\  /\  /\\  \\_ \\ _\\_ \\ __ // _//  // _//_ //  //\\  \\  \\//| input      |//\
//\\//_____\//\\____//\__/\\__\\/____/\\/____/\____\//_____\//\_______\\__\\__\\//\| system     |/\
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\

#pragma once

#include "../../Object.h"

#include <map>

#include <SFML/Window/Keyboard.hpp>

namespace snow
{

template<typename... T_Args>
class Event;

template<typename... T_Args>
class EventBinder;

enum class EKey
{
	UNKNOWN = -1,
	A = 0,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	SPACE,
	BACKSPACE,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	ZERO,
	MINUS,
	EQUAL,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	TILDE,
	ESC,
	TAB,
	L_SHIFT,
	R_SHIFT,
	L_CTRL,
	R_CTRL,
	L_ALT,
	R_ALT,
	WIN,
	ENTER,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	L_BRACKET,
	R_BRACKET,
	SEMICOLON,
	QUOTE,
	BACKSLASH,
	COMMA,
	PERIOD,
	SLASH,
	HOME,
	END,
	PAGE_UP,
	PAGE_DOWN,
	DELETE,
	INSERT,
	PAUSE,
	MENU,
	NUM_ADD,
	NUM_SUBTRACT,
	NUM_MULTIPLY,
	NUM_DIVIDE,
	NUM_0,
	NUM_1,
	NUM_2,
	NUM_3,
	NUM_4,
	NUM_5,
	NUM_6,
	NUM_7,
	NUM_8,
	NUM_9
};

struct SystemKeys
{
	bool LeftShift : 1;
	bool LeftCtrl : 1;
	bool LeftAlt : 1;
	bool RightShift : 1;
	bool RightCtrl : 1;
	bool RightAlt : 1;
	bool Win : 1;
};

sf::Keyboard::Key key_snow_to_sfml(EKey key);
EKey key_sfml_to_snow(sf::Keyboard::Key key);

class Input : public Object
{
	friend class Game;

public:
			/* SINGLETON */
	static Input& get_instance();

			/* METHODS FROM Object */

	virtual String to_string() const override;
	
	virtual int hash_code() const noexcept override;

			/* METHODS */

	bool is_key_pressed(EKey key);

	SystemKeys get_system_keys();

	EventBinder<SystemKeys>& on_pressed(EKey key);
	EventBinder<SystemKeys>& on_released(EKey key);

private:
	Input();

	std::map<EKey, Event<SystemKeys>> on_pressed_;
	std::map<EKey, Event<SystemKeys>> on_released_;

	std::map<EKey, EventBinder<SystemKeys>> on_pressed_binder_;
	std::map<EKey, EventBinder<SystemKeys>> on_released_binder_;

};

}
