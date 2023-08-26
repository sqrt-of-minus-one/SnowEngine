    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Level.h                     //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include <list>

#include "../Util/Function/EventBinder.h"
#include "../Actor/Actor.h"

namespace snow
{

class Transform;

/**
 *	\~english
 *	\brief The class of SnowEngine level
 *	
 *	The level is the place where there are actors and where the game takes place. You may create
 *	your own levels as classes derived from this one.
 *	
 *	\~russian
 *	\brief Класс уровня SnowEngine
 *	
 *	Уровень — это пространство, где существуют актёры и где происходит игра. Вы можете создавать
 *	свои собственные уровни как классы, наследованные от этого.
 */
class Level : public Object
{
	friend class Game;

public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates a new level.
	 *	\warning The constructor is designed for internal use only, don't use it directly. To
	 *	create a level use the `create_level` method of the `Game` class.
	 *	
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *	
	 *	Создаёт новый уровень.
	 *	\warning Конструктор предназначен только для внутреннего использования, не используйте его
	 *	напрямую. Чтобы создать уровень, воспользуйтесь методом `create_level` класса `Game`.
	 */
	Level();

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the level to string
	 *	
	 *	Creates the string `Level #<n> (actors: <a>)`, where `<n>` is a unique number of the level,
	 *	`<a>` is the number of actors on the level.
	 *	\return The created string.
	 *	
	 *	\~russian
	 *	\brief Конвертирует уровень в строку
	 *	
	 *	Создаёт строку `Level #<n> (actors: <a>)`, где `<n>` — уникальный номер уровня, `<a>` —
	 *	количество актёров на уровне.
	 *	\return Созданная строка.
	 */
	virtual String to_string() const override;
	
	/**
	 *	\~english
	 *	\brief Creates a JSON with the level data
	 *	
	 *	Creates a JSON object containing the following fields:
	 *	- `"id"`: the ID of the level (integer value).
	 *	- `"actors"`: the array of actors on the level, each element is an object created by
	 *	`Actor::to_json()`.
	 *	\return The JSON object describing the level.
	 *	\warning This method produces the JSON which describes every component of every actor on
	 *	the level. Sometimes it's a lot.
	 *	
	 *	\~russian
	 *	\brief Создаёт JSON с информацией об уровне
	 *	
	 *	Создаёт объект JSON, содержащий следующие поля:
	 *	- `"id"`: ID уровня (целочисленное значение);
	 *	- `"actors"`: массив актёров на уровне, каждый элемент является объектом, создаваемым
	 *	методом `Actor::to_json()`.
	 *	\return Объект JSON, описывающий уровень.
	 *	\warning Этот метод производит JSON, который описывает каждый компонент каждого актёра на
	 *	уровне. Иногда это много.
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Spawns a new actor
	 *	
	 *	Creates a new actor on the level.
	 *	\tparam T_Actor The class of a new actor, which must be derived from the `Actor` class.
	 *	\param transform The transform of a new actor.
	 *	\return The pointer to the created actor.
	 *	
	 *	\~russian
	 *	\brief Создаёт нового актёра
	 *	
	 *	Создаёт нового актёра на уровне.
	 *	\tparam T_Actor Класс нового актёра, который должен быть наследником класса `Actor`.
	 *	\param transform Преобразование нового актёра.
	 *	\return Указатель на созданный актёр.
	 */
	template<typename T_Actor>
	std::shared_ptr<T_Actor> spawn_actor(const Transform& transform);

	/**
	 *	\~english
	 *	\brief Destroys the level
	 *	
	 *	Destroys the level and all actors on it. The level cannot be recovered after the
	 *	destroying.
	 *	
	 *	\~russian
	 *	\brief Уничтожает уровень
	 *	
	 *	Уничтожает уровень и все актёры на нём. Уровень не может быть восстановлен после
	 *	уничтожения.
	 */
	void destroy();
	
	/**
	 *	\~english
	 *	\brief Checks whether the level is destroyed
	 *	
	 *	Checks whether the level has been destroyed by the `destroy` method.
	 *	\return `true` if the level is destroyed, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, уничтожен ли уровень
	 *	
	 *	Проверяет, был ли уровень уничтожен методом `destroy`.
	 *	\return `true`, если уровень уничтожен, иначе `false`.
	 */
	bool is_destroyed() const noexcept;

			/* EVENTS */

	/**
	 *	\~english
	 *	\brief The level is destroyed
	 *	
	 *	This event is called when the level is destroyed by the `destroy` method.
	 *	
	 *	Event parameters:
	 *	- `Level& level`: the level which was destroyed.
	 *	
	 *	\~russian
	 *	\brief Уровень уничтожен
	 *	
	 *	Это событие вызывается, когда уровень уничтожается методом `destroy`.
	 *	
	 *	Параметры события:
	 *	- `Level& level`: уровень, который был уничтожен.
	 */
	EventBinder<Level& /*level*/> on_destroyed;

protected:
			/* METHODS */
		
	/**
	 *	\~english
	 *	\brief Tick
	 *	
	 *	This method is called every tick. If you override this method, don't forget to call
	 *	parent's `tick`.
	 *	\param delta_sec The length of the tick in seconds.
	 *	
	 *	\~russian
	 *	\brief Тик
	 *	
	 *	Этот метод вызывается каждый тик. Если вы переопределяете этот метод, не забудьте вызвать
	 *	родительский `tick`.
	 *	\param delta_sec Длительность тика в секундах.
	 */
	virtual void tick(double delta_sec);

private:
	static int levels_counter_;
	int number_;

	bool is_destroyed_;

	void remove_actor_(Actor& actor);

	std::list<std::shared_ptr<Actor>> actors_;

	Event<Level& /*level*/> on_destroyed_;
};

		
		/* DEFINITIONS */

		/* Level: public */

template<typename T_Actor>
std::shared_ptr<T_Actor> Level::spawn_actor(const Transform& transform)
{
	static_assert(std::is_base_of_v<Actor, T_Actor>, "An argument of spawn_actor method template must be Actor");

	std::shared_ptr<T_Actor> actor = std::make_shared<T_Actor>(*this, transform);
	actor->on_destroyed.bind<Level>(*this, &Level::remove_actor_, true);

	actors_.push_back(actor);
	dynamic_cast<Actor*>(actor.get())->when_begin_play();
	return actor;
}

}
