    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Game.h                      //
////////////////////////////////////////

#pragma once

#include <memory>
#include <list>

namespace sf
{
class RenderWindow;
}

namespace snow
{

class Log;
class Level;

/**
 *	\addtogroup Config
 *	\{
 */

/**
 *	\~english
 *	\brief The class that contains global game properties
 *
 *	This class controls the game process and contains the game properties. Is is a singleton, only
 *	one its instance can exist.
 *
 *	\~russian
 *	\brief Класс, содержащий глобальные игровые свойства
 *
 *	Этот класс контролирует процесс игры и содержит игровые свойства. Он является одиночкой: может
 *	существовать только один его экземпляр.
 */
class Game
{
public:
			/* SINGLETON */

	/**
	 *	\~english
	 *	\brief The only instance of the class
	 *	
	 *	Allows to get the instance of the `Game` class.
	 *	\return The instance of the class.
	 *	
	 *	\~russian
	 *	\brief Единственный экземпляр класса
	 *	
	 *	Позволяет получить экземпляр класса `Game`.
	 *	\return Экземпляр класса.
	*/
	static Game& get_instance();

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Starts the game
	 *	
	 *	This methods launches the game. It can only be called once, subsequent calls will be
	 *	ignored. The game starts in a new thread.
	 *	\sa `is_started()`: checks if the game is started.
	 *	
	 *	\~russian
	 *	\brief Начинает игру
	 *	
	 *	Этот метод запускает игру. Он может быть вызван только один раз, последующие вызовы будут
	 *	проигнорированы. Игра начинается в новом потоке.
	 *	\sa `is_started()`: проверяет, начата ли игра.
	 */
	void start();

	/**
	 *	\~english
	 *	\brief Checks whether the game is started
	 *	
	 *	Checks if the game has been started by the `start()` method.
	 *	\return `true` if the game is started, `false` otherwise.
	 *	\sa `start()`: launches the game.
	 *	
	 *	\~russian
	 *	\brief Проверяет, начата ли игра
	 *	
	 *	Проверяет, была ли игра начата методом `start()`.
	 *	\return `true`, если игра начата; иначе `false`.
	 *	\sa `start()`: запускает игру.
	 */
	bool is_started() noexcept;

	/**
	 *	\~english
	 *	\brief The SFML window
	 *	
	 *	Allows to get the SFML window where the game is running.
	 *	\warning This method is designed for internal use. You shouldn't use it directly.
	 *	\return The pointer to the current game window. Null pointer if the game hasn't been
	 *	started.
	 *	
	 *	\~russian
	 *	\brief Окно SFML
	 *	
	 *	Позволяет получить окно SFML, где запущена игра.
	 *	\warning Этот метод предназначен для внутреннего использования. Вы не должны вызывать его
	 *	напрямую.
	 *	\return Указатель на текущее игровое окно. Нулевой указатель, если игра не была начата.
	 */
	std::weak_ptr<sf::RenderWindow> get_window() noexcept;

	/**
	 *	\~english
	 *	\brief Creates a new level
	 *	
	 *	Allows to create a new level. You should use this method instead of the constructor of the
	 *	level.
	 *	\tparam T_Level The class of the level that will be created.
	 *	\return The pointer to the created level.
	 *	
	 *	\~russian
	 *	\brief Создаёт новый уровень
	 *	
	 *	Позволяет создать новый уровень. Этот метод следует использовать вместо конструктора
	 *	уровня.
	 *	\tparam T_Level Класс уровня, который будет создан.
	 *	\return Указатель на созданный уровень.
	 */
	template<typename T_Level>
	std::shared_ptr<T_Level> create_level();

private:
	Game();
	
	void loop_();

	void create_window_();

	void remove_level_(Level& level);

	std::shared_ptr<sf::RenderWindow> window_;
	std::list<std::shared_ptr<Level>> levels_;

	bool is_started_;
	std::unique_ptr<Log> main_log_;
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
