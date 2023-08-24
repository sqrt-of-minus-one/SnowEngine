    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Game.h                      //
////////////////////////////////////////

#pragma once

#include <memory>
#include <list>

#include "../Util/Time/Time.h"

namespace sf
{
class RenderWindow;
}

namespace snow
{

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
class Game : public Object
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

			/* METHODS FROM Object */
	
	/**
	 *	\~english
	 *	\brief Converts the game object to string
	 *	
	 *	If the game is not started, creates a string `"The game is not started"`. If the game is
	 *	started, creates a string `"The game is started, there are <l> levels"`, where `<l>` is the
	 *	number of levels.
	 *	\return The string describing the game object.
	 *	
	 *	\~russian
	 *	\brief Конвертирует объект `Game` в строку
	 *	
	 *	Если игра не начата, создаёт строку `"The game is not started"`. Если игра начата, создаёт
	 *	строку `"The game is started, there are <l> levels"`, где `<l>` — количество уровней.
	 *	\return Строка, описывающая объект `Game`.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Creates a JSON object describing the game object
	 *	
	 *	Creates a JSON object. Its only element (`levels`) is an array with JSON objects describing
	 *	all levels (see `Level::to_json()`).
	 *	\return The JSON object. A null JSON value if the game has not been started.
	 *	\warning This method produces the JSON which describes every component of every actor on
	 *	the level. Sometimes it's a lot.
	 *	
	 *	\~russian
	 *	\brief Создаёт объект JSON, описывающий объект `Game`
	 *	
	 *	Создаёт объект JSON. Его единственный элемент (`levels`) представляет собой массив с
	 *	объектами JSON, описывающими все уровни (см. `Level::to_json()`).
	 *	\return Объект JSON. Нулевое значение JSON, если игра не была начата.
	 *	\warning Этот метод производит JSON, который описывает каждый компонент каждого актёра на
	 *	уровне. Иногда это много.
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Starts the game
	 *	
	 *	This methods launches the game. It can only be called once, subsequent calls will be
	 *	ignored. The game starts in a new thread.
	 *	\sa
	 *	- `is_started()`: checks if the game is started.
	 *	
	 *	\~russian
	 *	\brief Начинает игру
	 *	
	 *	Этот метод запускает игру. Он может быть вызван только один раз, последующие вызовы будут
	 *	проигнорированы. Игра начинается в новом потоке.
	 *	\sa
	 *	- `is_started()`: проверяет, начата ли игра.
	 */
	void start();

	/**
	 *	\~english
	 *	\brief Checks whether the game is started
	 *	
	 *	Checks if the game has been started by the `start()` method.
	 *	\return `true` if the game is started, `false` otherwise.
	 *	\sa
	 *	- `start()`: launches the game.
	 *	
	 *	\~russian
	 *	\brief Проверяет, начата ли игра
	 *	
	 *	Проверяет, была ли игра начата методом `start()`.
	 *	\return `true`, если игра начата; иначе `false`.
	 *	\sa
	 *	- `start()`: запускает игру.
	 */
	bool is_started() noexcept;

	/**
	 *	\~english
	 *	\brief The time point when the current tick has begun
	 *	
	 *	Allows to get the time point when the current tick has begin.
	 *	\return The time point of the current tick. The current time if the game has not been
	 *	started.
	 *	
	 *	\~russian
	 *	\brief Временная точка, когда начался текущий тик
	 *	
	 *	Позволяет получить временную точку, когда начался текущий тик.
	 *	\return Временная точка текущего тика. Текущее время, если игра не была начата.
	*/
	const time::std_time_point& now() const noexcept;

	/**
	 *	\~english
	 *	\brief The SFML window
	 *	
	 *	Allows to get the SFML window where the game is running.
	 *	\warning This method is designed for internal use. You shouldn't use it directly.
	 *	\return The pointer to the current game window. Null pointer if the game hasn't been
	 *	started or the window hasn't been created yet.
	 *	
	 *	\~russian
	 *	\brief Окно SFML
	 *	
	 *	Позволяет получить окно SFML, где запущена игра.
	 *	\warning Этот метод предназначен для внутреннего использования. Вы не должны вызывать его
	 *	напрямую.
	 *	\return Указатель на текущее игровое окно. Нулевой указатель, если игра не была начата или
	 *	окно ещё не было создано.
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

	void create_window_(); // Create or recreate the game window

	void remove_level_(Level& level);

	std::shared_ptr<sf::RenderWindow> window_; // The game window (if it has been created)
	std::list<std::shared_ptr<Level>> levels_;

	time::std_time_point tick_time_point_;
	bool is_started_;

	std::mutex window_mtx_;
	std::mutex levels_mtx_;

	static const String GAME_LOG_;
};


		/* DEFINITIONS */

		/* Game: public */

template<typename T_Level>
std::shared_ptr<T_Level> Game::create_level()
{
	static_assert(std::is_base_of<Level, T_Level>::value, L"An argument of create_level method template must be Level");

	std::shared_ptr<T_Level> level(new T_Level);
	level->on_destroyed.bind(&Game::remove_level_, true);

	std::lock_guard<std::mutex> levels_grd(levels_mtx_);
	levels_.push_back(level);
	return level;
}

}
