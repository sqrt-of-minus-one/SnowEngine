    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Object.h                    //
////////////////////////////////////////

#pragma once

#include <stdexcept>
#include <memory>
#include <unordered_set>
#include <filesystem>
#include <chrono>

namespace snow
{

namespace json
{
class Element;
}

using String = std::wstring;
using Path = std::filesystem::path;
using TimePoint = std::chrono::steady_clock::time_point;
using Duration = std::chrono::steady_clock::duration;

/**
 *	\~english
 *	\brief The base class of all SnowEngine classes
 *	
 *	Every SnowEngine class (except of the singletons) is derived from this one. This class also
 *	keeps a list of all objects, which lets you to check if the pointer to an `Object` is valid
 *	using `is_valid()` method.
 *	
 *	\~russian
 *	\brief Базовый класс для всех классов SnowEngine
 *	
 *	Каждый класс SnowEngine (кроме одиночек) наследуется от этого. Этот класс также хранит список
 *	всех существующих объектов, что позволяет вам проверить, действителен ли указатель на `Object`
 *	с помощью метода `is_valid()`.
 */
class Object
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The default constructor
	 *
	 *	Serves to add a new object into the list of objects.
	 *
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *
	 *	Служит для добавления нового объекта в список объектов.
	 */
	Object();

	/**
	 *	\~english
	 *	\brief The destructor
	 *
	 *	Serves to remove the object from the list of objects.
	 *
	 *	\~russian
	 *	\brief Деструктор
	 *
	 *	Служит для удаления объекта из списка объектов.
	 */
	virtual ~Object();

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Converts the object into a string
	 *	
	 *	The virtual method that creates a string from the object.
	 *	\return The string.
	 *	
	 *	\~russian
	 *	\brief Конвертирует объект в строку
	 *	
	 *	Виртуальный метод, который создаёт строку из объекта.
	 *	\return Строка.
	 */
	virtual String to_string() const = 0;

	/**
	 *	\~english
	 *	\brief Converts the object into a JSON element
	 *	
	 *	The virtual method that creates a JSON element with the information about the object.
	 *	\return The JSON element.
	 *	
	 *	\~russian
	 *	\brief Конвертирует объект в элемент JSON
	 *	
	 *	Виртуальный метод, который создаёт элемент JSON с информацией о данном объекте.
	 *	\return Элемент JSON.
	 */
	virtual std::shared_ptr<json::Element> to_json() const = 0;

	/**
	 *	\~english
	 *	\brief Checks whether the object still exists
	 *	
	 *	Searches the address of the object in the list of existing objects.
	 *	\param object The pointer to the object.
	 *	\return `true` if the object exists, `false` if it was destroyed.
	 *	
	 *	\~russian
	 *	\brief Проверяет, по-прежнему ли существеут объект
	 *	
	 *	Ищет адрес объекта в списке существующих объектов.
	 *	\param object Указатель на объект.
	 *	\return `true`, если объект существует; `false`, если он был уничтожен.
	 */
	static bool is_valid(const Object* object);

private:
	/* lazy */ static std::unordered_set<const Object*>& existing_objects_();
};

}
