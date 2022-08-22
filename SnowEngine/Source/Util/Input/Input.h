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

#include "Keys.h"

namespace snow
{

template<typename... T_Args>
class Event;

template<typename... T_Args>
class EventBinder;

class Point2;
class Vector2;
class CameraComponent;

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

	Point2 get_screen_mouse_position();
	Point2 get_window_mouse_position();
	Vector2 get_level_mouse_position(const CameraComponent& relative_to);
	void set_screen_mouse_position(const Point2& position);
	void set_window_mouse_position(const Point2& position);
	void set_level_mouse_position(const Vector2& position, const CameraComponent& relative_to);

	EventBinder<SystemKeys>& on_pressed(EKey key);
	EventBinder<SystemKeys>& on_released(EKey key);
	EventBinder<>& on_mouse_pressed(EButton button);
	EventBinder<>& on_mouse_released(EButton button);

private:
	Input();

	std::map<EKey, Event<SystemKeys>> on_pressed_;
	std::map<EKey, Event<SystemKeys>> on_released_;
	std::map<EButton, Event<>> on_mouse_pressed_;
	std::map<EButton, Event<>> on_mouse_released_;

	std::map<EKey, EventBinder<SystemKeys>> on_pressed_binder_;
	std::map<EKey, EventBinder<SystemKeys>> on_released_binder_;
	std::map<EButton, EventBinder<>> on_mouse_pressed_binder_;
	std::map<EButton, EventBinder<>> on_mouse_released_binder_;

};

}
