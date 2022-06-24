    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Text.h                      //
////////////////////////////////////////

//   \_____/     ***     SnowFlake            *****  *           *                               //
//   /\___/\    *   *                         *      *           *                               //
//  / /\ /\ \   *      ****    ***   *     *  *      *    ****   *  *   ***                      //
// =====X=====   ***   *   *  *   *  *     *  *****  *   *   *   * *   *   *    /**************\ //
//  \ \/_\/ /       *  *   *  *   *  *  *  *  *      *   *   *   **    *****   |*  SnowEngine  *|//
//   \/___\/    *   *  *   *  *   *  * * * *  *      *   *   *   * *   *       |* localization *|//
//   /     \     ***   *   *   ***    *   *   *       *   *** *  *  *   ****   |*    system    *|//

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `Text` class
 *
 *	This file contains the definition of the `Text` class of the SnowFlake System.
 *
 *	\~russian
 *	\brief Файл с классом `Text`
 *
 *	Этот файл содержит определение класса `Text` системы SnowFlake.
 */

#include "../Types/String.h"
		// + Object

namespace snow
{

/**
 *	\~english
 *	\brief The localizable text
 *	
 *	This class keeps the code of a localizable string. You can use `to_string` method to get the
 *	string in the current language.
 *	
 *	\~russian
 *	\brief Локализуемый текст
 *	
 *	Этот класс содержит код локализуемой строки. Вы можете использовать метод `to_string`, чтобы
 *	получить строку на соответствуеющем языке.
 */
class Text : public Object
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates an empty text.
	 *	
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *	
	 *	Создаёт пустой текст.
	 */
	Text() noexcept;

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *
	 *	Copies the text.
	 *	\param text The text that will be copied.
	 *
	 *	\~russian
	 *	\brief Конструктор копирования
	 *
	 *	Копирует текст.
	 *	\param text Текст, который будет скопирован.
	 */
	Text(const Text& text) noexcept;

	/**
	 *	\~english
	 *	\brief The move constructor
	 *
	 *	Creates a new text by moving the code from the passed one.
	 *	\param text The text whose code will be moved.
	 *
	 *	\~russian
	 *	\brief Конструктор перемещения
	 *
	 *	Создаёт новый текст путём перемещения кода из переданного.
	 *	\param text Текст, чей код будет перемещён.
	 */
	Text(Text&& text) noexcept;

	/**
	 *	\~english
	 *	\brief Creates a new text with the passed key
	 *
	 *	Creates a new text with the passed key.
	 *	\param key The key.
	 *	
	 *	\~russian
	 *	\brief Создаёт новый текст с переданным ключом
	 *	
	 *	Создаёт новый текст с переданным ключом.
	 *	\param key Ключ.
	 */
	Text(const String& key) noexcept;

	/**
	 *	\~english
	 *	\brief Creates a new text with the passed key
	 *
	 *	Creates a new text with the passed key.
	 *	\param key The key.
	 *
	 *	\~russian
	 *	\brief Создаёт новый текст с переданным ключом
	 *
	 *	Создаёт новый текст с переданным ключом.
	 *	\param key Ключ.
	 */
	Text(String&& key) noexcept;

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief The localized string
	 *	
	 *	Allows to get the localized string in the current language.
	 *	\return The localized string.
	 *	
	 *	\~russian
	 *	\brief Локализованный текст
	 *	
	 *	Позволяет получить локализованный текст на текущем языке.
	 *	\return Локализованный текст.
	 */
	virtual String to_string() const noexcept override;

	/**
	 *	\~english
	 *	\brief Hash code of the text
	 *
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes. Hash code of a text with empty key is zero.
	 *	\return Hash code of the object.
	 *
	 *	\~russian
	 *	\brief Хеш-код текста
	 *
	 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
	 *	также могут иметь одинаковые хеш-коды. Хеш-код текста с пустым ключом — ноль.
	 *	\return Хеш-код объекта.
	 */
	virtual int hash_code() const noexcept override;

			/* METHODS */

	/**
	 *	~english
	 *	\brief The key
	 *	
	 *	Allows to get the key of the text.
	 *	\return The key.
	 *	
	 *	\~russian
	 *	\brief Ключ
	 *	
	 *	Позволяет получить ключ текста.
	 *	\return Ключ.
	 */
	const String& get_key() const noexcept;
	
	/**
	 *	\~english
	 *	\brief Checks whether the text is valid
	 *	
	 *	Checks whether the key of the text is contained in the table of strings of the current
	 *	language.
	 *	\return `true` if the key is valid, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, действителен ли текст
	 *	
	 *	Проверяет, содержится ли ключ текста в таблице строк текущего языка.
	 *	\return `true`, если ключ действителен, иначе `false`.
	 */
	bool is_valid() const noexcept;

			/* OPERATORS */

	/**
	 *	\~english
	 *	\brief The copy assignment operator
	 *	
	 *	Replaces the current key with the one of the passed text.
	 *	\param text The text to copy.
	 *	\return A reference to itself.
	 *	
	 *	\~russian
	 *	\brief Оператор присваивания копированием
	 *	
	 *	Заменяет текущий ключ на ключ переданного текста.
	 *	\param text Текст для копирования.
	 *	\return Ссылка на себя.
	 */
	Text& operator=(const Text& text);

	/**
	 *	\~english
	 *	\brief The move assignment operator
	 *
	 *	Replaces the current key with the one of the passed text.
	 *	\param text The text to move.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Оператор присваивания перемещением
	 *
	 *	Заменяет текущий ключ на ключ переданного текста.
	 *	\param text Текст для перемещения.
	 *	\return Ссылка на себя.
	 */
	Text& operator=(Text&& text);

	/**
	 *	\~english
	 *	\brief Sets the key
	 *
	 *	Replaces the current key with the passed one.
	 *	\param key The new key.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Устанавливает ключ
	 *
	 *	Заменяет текущий ключ на переданный.
	 *	\param key Новый ключ.
	 *	\return Ссылка на себя.
	 */
	Text& operator=(const String& key);

	/**
	 *	\~english
	 *	\brief Sets the key
	 *
	 *	Replaces the current key with the passed one.
	 *	\param key The new key.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Устанавливает ключ
	 *
	 *	Заменяет текущий ключ на переданный.
	 *	\param key Новый ключ.
	 *	\return Ссылка на себя.
	 */
	Text& operator=(String&& key);

	/**
	 *	\~english
	 *	\brief Checks whether two texts are equal
	 *	
	 *	Two texts are equal if their keys are equal.
	 *	\param text The text to compare.
	 *	\return `true` if two texts are equal, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, равны ли два текста
	 *	
	 *	Два текста равны, если равны их ключи.
	 *	\param text Текст для сравнения.
	 *	\return `true`, если два текста равны, иначе `false`.
	 */
	bool operator==(const Text& text) const;

	/**
	 *	\~english
	 *	\brief Checks whether the text has the passed key
	 *
	 *	Checks whether the key of the text is equal to the passed string.
	 *	\param key The key to compare.
	 *	\return `true` if the key of the text is equal to the passed string, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, имеет ли текст переданный ключ
	 *
	 *	Проверяет, равен ли ключ текста переданной строке.
	 *	\param key Ключ для сравнения.
	 *	\return `true`, если ключ текста равен переданной строке, иначе `false`.
	 */
	bool operator==(const String& key) const;

	/**
	 *	\~english
	 *	\brief Checks whether two texts are not equal
	 *
	 *	Two texts are equal if their keys are equal.
	 *	\param text The text to compare.
	 *	\return `true` if two texts are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, различаются ли два текста
	 *
	 *	Два текста равны, если равны их ключи.
	 *	\param text Текст для сравнения.
	 *	\return `true`, если два текста не равны, иначе `false`.
	 */
	bool operator!=(const Text& text) const;

	/**
	 *	\~english
	 *	\brief Checks whether the text has the key that is not equal to the passed one
	 *
	 *	Checks whether the key of the text is not equal to the passed string.
	 *	\param key The key to compare.
	 *	\return `true` if the key of the text is not equal to the passed string, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, имеет ли текст ключ, отличный от переданного
	 *
	 *	Проверяет, отличается ли ключ текста от переданной строки.
	 *	\param key Ключ для сравнения.
	 *	\return `true`, если ключ текста не равен переданной строке, иначе `false`.
	 */
	bool operator!=(const String& key) const;

private:
	String key_;

};

}