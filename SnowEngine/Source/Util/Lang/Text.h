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
 
#include "../../Object.h"

#include "../Types/String.h"

namespace snow
{

/**
 *	\~english
 *	\brief The localizable text
 *	
 *	This class keeps the code of a localizable string. You can use `to_string` method to get the
 *	string in the current language. The text object keeps the key of a string, which consists of
 *	the name of the localization table and the key of the string in the table: `<table>.<key>`.
 *	
 *	\~russian
 *	\brief Локализуемый текст
 *	
 *	Этот класс содержит код локализуемой строки. Вы можете использовать метод `to_string`, чтобы
 *	получить строку на соответствуеющем языке. Объект текста хранит ключ строки, состоящий из
 *	названия таблицы локализации и ключа строки в таблице: `<table>.<key>`.
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
	Text();

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
	Text(const Text& text);

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
	Text(Text&& text);

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
	Text(const String& key);

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
	Text(String&& key);

	/**
	 *	\~english
	 *	\brief Creates a new text with the specified key
	 *	
	 *	Creates a new text using the passed JSON. It must be either a JSON string or a JSON object:
	 *	- if the passed JSON is a string, it is used as a translation key of a new text;
	 *	- if the passed JSON is a object, it must only have one element. The key of the element
	 *	will be used as a translation key, the value of the element will be ignored.
	 *	\param json The JSON element with the translation key.
	 *	\throw std::invalid_argument The passed JSON is not correct.
	 *	
	 *	\~russian
	 *	\brief Создаёт новый текст с заданным ключом
	 *	
	 *	Создаёт новый текст, используя переданный JSON. Это должна быть либо строка JSON, либо
	 *	объект JSON:
	 *	- если переданный JSON является строкой, то она будет использована как ключ перевода нового
	 *	текста;
	 *	- если переданный JSON является объектом, то он должен иметь только один элемент. Ключ
	 *	этого элемента будет использован как ключ перевода, а значение будет игнорироваться.
	 *	\param json Элемент JSON с ключом перевода.
	 *	\throw std::invalid_argument Переданный JSON неправильный.
	 */
	Text(std::shared_ptr<const json::Element> json);

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
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Converts the text to JSON
	 *	
	 *	Creates a JSON object with one element. Its key is the translation key, its value is the
	 *	localized string.
	 *	\return The JSON object.
	 *	
	 *	\~russian
	 *	\brief Конвертирует текст в JSON
	 *	
	 *	Создаёт объект JSON с одним элементом. Его ключом является ключ перевода, а значением —
	 *	локализованная строка.
	 *	\return Объект JSON.
	 */
	std::shared_ptr<json::Element> to_json() const override;

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
	const String& get_key() const;
	
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
	bool operator==(const Text& text) const noexcept;

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
	bool operator==(const String& key) const noexcept;

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
	bool operator!=(const Text& text) const noexcept;

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
	bool operator!=(const String& key) const noexcept;

private:
	String key_;

};

}