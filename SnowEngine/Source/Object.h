    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Object.h                    //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `Object` class
 *	
 *	This file contains the definition of the `Object` class.
 *
 *	\~russian
 *	\brief Файл с классом `Object`
 *
 *	Этот файл содержит определение класса `Object`.
 */

#include <stdexcept>
#include <memory>
#include <unordered_set>

namespace snow
{

class String;

/**
 *	\~english
 *	\brief The base class of all SnowEngine classes
 *	
 *	Every SnowEngine class (except of the singletons) is derived from this one. This class has also
 *	a list with all objects, so you can check if the pointer to an `Object` is valid using
 *	`is_valid` method.
 *	
 *	\~russian
 *	\brief Базовый класс для всех классов SnowEngine
 *	
 *	Каждый класс SnowEngine (кроме одиночек) наследуется от этого. Этот класс также имеет список
 *	всех существующих объектов, и вы можете проверить, действителен ли указатель на `Object` с
 *	помощью метода `is_valid`.
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
	 *	\brief Hash code of the object
	 *	
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes.
	 *	\return Hash code of the object.
	 *	
	 *	\~russian
	 *	\brief Хеш-код объекта
	 *	
	 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
	 *	также могут иметь одинаковые хеш-коды.
	 *	\return Хеш-код объекта.
	 */
	virtual int hash_code() const noexcept = 0;

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
