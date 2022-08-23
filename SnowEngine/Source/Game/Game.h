    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Game.h                      //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `Game` class
 *
 *	This file contains the definition of the `Game` class.
 *
 *	\~russian
 *	\brief Файл с классом `Game`
 *
 *	Этот файл содержит определение класса `Game`.
 */

#include <memory>
#include <list>

namespace sf
{
class RenderWindow;
}

namespace snow
{

class Config;
class Log;
class Level;

/**
 *	\~english
 *	\brief The class that contains global game properties
 *
 *	This static class class controls the game process and contains static field with game
 *	properties. Unlike other SnowEngine classes, it isn't inherited from the `Object`.
 *
 *	\~russian
 *	\brief Класс, содержащий глобальные игровые свойства
 *
 *	Этот статический класс контролирует процесс игры и содержит статические поля с игровыми
 *	свойствами. В отличие от остальных классов SnowEngine, он не является наследником `Object`.
 */
class Game
{
public:
			/* CONSTRUCTORS */

	Game() = delete;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Starts the game
	 *	
	 *	This methods launches the game. It can only be called once, subsequent calls will be
	 *	ignored. The game starts in a new thread.
	 *	
	 *	\~russian
	 *	\brief Начинает игру
	 *	
	 *	Этот метод запускает игру. Он может быть вызван только один раз, последующие вызовы будут
	 *	проигнорированы. Игра начинается в новом потоке.
	 */
	static void start();

	/**
	 *	\~english
	 *	\brief Checks whether the game is started
	 *	
	 *	Checks if the game is started by `start` method.
	 *	\return `true` if the game is started, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, начата ли игра
	 *	
	 *	Проверяет, была ли игра начата методом `start`.
	 *	\return `true`, если игра начата; иначе `false`.
	 */
	static bool is_started() noexcept;

	static std::weak_ptr<sf::RenderWindow> get_window() noexcept;

	template<typename T_Level>
	static std::shared_ptr<T_Level> create_level();

			/* FIELDS */

	/**
	 *	\~english
	 *	\brief The configurations of the game
	 *	
	 *	This field is the main instance of the `Config` class, which contains game configurations.
	 *	You can set them by `config.ini` file before the game starts.
	 *	
	 *	\~russian
	 *	\brief Конфигурации игры
	 *	
	 *	Это поле — главный объект класса `Config`, содержащий конфигурации игры. Вы можете
	 *	установить их с помощью файла `config.ini` перед запуском игры.
	 */
	static Config config;

private:
	static void loop_();

	static void remove_level_(Level& level);

	static std::shared_ptr<sf::RenderWindow> window_;
	static std::list<std::shared_ptr<Level>> levels_;

	static bool is_started_;
	static std::unique_ptr<Log> main_log_;
};


		/* DEFINITIONS */

		/* Game: public */

template<typename T_Level>
std::shared_ptr<T_Level> Game::create_level()
{
	static_assert(std::is_base_of<Level, T_Level>::value, L"An argument of create_level method template must be Level");

	std::shared_ptr<T_Level> level(new T_Level);
	level->on_destroyed.bind(&Game::remove_level_, true);

	levels_.push_back(level);
	return level;
}

}
