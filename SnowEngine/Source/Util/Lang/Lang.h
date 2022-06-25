    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Lang.h                      //
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
 *	\brief The file with `Lang` class
 *
 *	This file contains the definition of the `Lang` class of the SnowFlake system.
 *
 *	\~russian
 *	\brief Файл с классом `Lang`
 *
 *	Этот файл содержит определение класса `Lang` системы SnowFlake.
 */

#include "../Log/Log.h"
#include "../Container/Map.h"

namespace snow
{

/**
 *	\~english
 *	\brief The class of the SnowFlake language manager
 *	
 *	This class is used to manage languages. Its main instance is contained in the `Game` class as a
 *	static member. You shouldn't create other instances. Use `config.ini` file to set default
 *	language and the directory of localization files.
 *	
 *	\~russian
 *	\brief Класс диспетчера языков SnowFlake
 *	
 *	Этот класс используется для управления языками. Его главный объект хранится в классе `Game` как
 *	статический член. Вы не должны создавать другие объекты. Используйте файл `config.ini`, чтобы
 *	установить язык по умолчанию, а также директорию для файлов локализации.
 */
class Lang : public Object
{
	friend class Game;

public:
			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the language manager to string
	 *	
	 *	Converts the language manager to string.
	 *	\return The code of the current language.
	 *
	 *	\~russian
	 *	\brief Конвертирует диспетчер языков в строку
	 *	
	 *	Конвертирует диспетчер языков в строку.
	 *	\return Код текущего языка.
	 */
	virtual String to_string() const noexcept override;
	
	/**
	 *	\~english
	 *	\brief Hash code of the language manager
	 *
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes.
	 *	\return Hash code of the object.
	 *
	 *	\~russian
	 *	\brief Хеш-код диспетчера языков
	 *
	 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
	 *	также могут иметь одинаковые хеш-коды.
	 *	\return Хеш-код объекта.
	 */
	virtual int hash_code() const noexcept override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief The current language
	 *	
	 *	Allows to get the language that is active now.
	 *	\return The text code of the current language.
	 *	
	 *	\~russian
	 *	\brief Текущий язык
	 *	
	 *	Позволяет получить язык, который в данный момент активен.
	 *	\return Текстовый код текущего языка.
	 */
	const String& get_current_lang();

	/**
	 *	\~english
	 *	\brief Sets the language
	 *	
	 *	Sets the passed language as active. Tries to load for the new language all localization
	 *	tables that were loaded for the previous language.
	 *	\param lang The text code of the required language.
	 *	\return `false` if an error has occurred (and the language hasn't been changed), `true`
	 *	otherwise.
	 *	
	 *	\~russian
	 *	\brief Устанавливает язык
	 *	
	 *	Устанавливает переданный язык в качестве активного. Пытается загрузить для нового языка все
	 *	таблицы локализации, которые были загружены для старого.
	 *	\param lang Текстовый код требуемого языка.
	 *	\return `false`, если произошла ошибка (и язык не был изменён), иначе `true`.
	 */
	bool set_lang(const String& lang);

	/**
	 *	\~english
	 *	\brief Loads the localization table
	 *	
	 *	Loads the localization table for the current language.
	 *	\param table The name of the table.
	 *	\return `false` if an error has occurred (and the localization table hasn't been loaded),
	 *	`true` otherwise.
	 *	
	 *	\~russian
	 *	\brief Загружает таблицу локализации
	 *	
	 *	Загружает таблицу локализации для текущего языка.
	 *	\param table Название таблицы.
	 *	\return `false`, если произошла ошибка (и таблица локализации не была загружена), иначе
	 *	`true`.
	 */
	bool load_table(const String& table);

	/**
	 *	\~english
	 *	\brief Unloads the localization table
	 *
	 *	Unloads the localization table. The default table cannot be unloaded.
	 *	\param table The name of the table.
	 *	\return `true` if the table has been successfully unloaded, `false` otherwise (e. g. if
	 *	it hadn't been loaded).
	 *
	 *	\~russian
	 *	\brief Выгружает таблицу локализации
	 *
	 *	Удаляет из памяти таблицу локализации. Таблица по умолчанию не может быть удалена.
	 *	\param table Название таблицы.
	 *	\return `true`, если таблица была успешно выгружена, иначе `false` (например, если она не
	 *	была предварительно загружена).
	 */
	bool unload_table(const String& table);

	/**
	 *	\~english
	 *	\brief Checks whether the localization table is loaded
	 *	
	 *	Checks whether the localization table with the passed name is loaded.
	 *	\param table The name of the table.
	 *	\return `true` if the table is loaded, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, загружена ли таблица локализации
	 *	
	 *	Проверяет, загружена ли таблица локализации с переданным названием.
	 *	\param table Название таблицы.
	 *	\return `true`, если таблица загружена, иначе `false`.
	 */
	bool is_table_loaded(const String& table);

	/**
	 *	\~english
	 *	\brief A localized string
	 *	
	 *	Allows to get a string in the language that is active now.
	 *	\param key The key of the required string: `<table>.<key>`. For the default localization
	 *	table it's allowed to use the string `.<key>`.
	 *	\return The required string in the current language. If there is no string with the passed
	 *	key, returns the key.
	 *	
	 *	\~russian
	 *	\brief Локализованный текст
	 *	
	 *	Позволяет получить строку на активном в данный момент языке.
	 *	\param key Ключ требуемой строки: `<таблица>.<ключ>`. Для таблицы локализации по умолчанию
	 *	допускается использовать строку `.<ключ>`.
	 *	\return Требуемая строка на текущем языке. Если строка с переданным ключом не найдена,
	 *	возвращает ключ.
	 */
	String get_string(const String& key);

	/**
	 *	\~english
	 *	\brief Checks whether the passed key is valid
	 *	
	 *	Checks if the passed key is contained in the list of strings of the current language.
	 *	\param key The key to check: `<table>.<key>`. For the default localization table it's
	 *	allowed to use the string `.<key>`.
	 *	\return	`true` if there is a string with the passed key, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, действителен ли переданный ключ
	 *	
	 *	Проверяет, содержится ли переданный ключ в списке строк текущего языка.
	 *	\param key Ключ для проверки: `<таблица>.<ключ>`. Для таблицы локализации по умолчанию
	 *	допускается использовать строку `.<ключ>`.
	 *	\return `true`, если существует строка с переданным ключом, иначе `false`.
	 */
	bool is_valid(const String& key);

private:
	using Table_ = Map<String, std::unique_ptr<String>>;

	Lang();

	bool load_table_(const String& table, const String& lang);
	static Pair<String, String> split_to_table_key_(const String& key);

	String current_lang_;
	Map<String, Table_> strings_;
	Log lang_log_;

};

}
