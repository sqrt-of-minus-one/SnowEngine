    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: LangManager.h               //
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

#include <mutex>
#include <unordered_map>

namespace snow
{

/**
 *	\defgroup SnowFlake SnowFlake
 *	\~english
 *	\brief SnowFlake, the SnowEngine localization system
 *	
 *	The `LangManager` allows you to switch the current language. The `Text` class represents a
 *	localizable string. Every localizable string has its unique key, which consists of two parts:
 *	the name of the localization table and the identifier. These two parts are divided by the dot,
 *	e. g. the key `messages.hello_world` defines a string whose id is `hello_world` and which is
 *	contained in the localization table named `messages`. The name of the table in the key may be
 *	omitted if the default table is used, e. g. the keys `.hello` and `hello` define a string whose
 *	id is `hello` and which is contained in the default localization table. The name of the default
 *	table is defined by the configuration profile (see the `Config::lang_default_table`). The
 *	profile also defines the directory where the localization files are stored (see the
 *	`Config::lang_path`). Each language has its own folder in that directory, the names of the
 *	folders are the language codes (e. g. `en_UK`, `en_US`, `ru_RU` etc.). Every folder contains
 *	JSON files, each of which corresponds to its localization table, e. g. the
 *	`en_UK/messages.json` file contains strings of the table named `messages` in British English.
 *	Every file contains a JSON object with string values. Every value is the translation of the
 *	localizable string, the key of the value is the id of the string. The name of the localization
 *	table is allowed to contain the `/` character. If it does, the localization file of the table
 *	should be places it the subfolder of the language folder.
 *	
 *	\~russian
 *	\brief SnowFlake, система локализации SnowEngine
 *	
 *	`LangManager` позволяет вам переключать языки. Класс `Text` представляет собой локализуемую
 *	строку. Каждая локализуемая строка имеет свой уникальный ключ, состоящий из двух частей:
 *	названия таблицы локализации и идентификатора (ID). Эти две части разделяются точкой, например,
 *	ключ `messages.hello_world` определяет строку с идентификатором `hello_world`, которая
 *	содержится в таблице локализации `messages`. Название таблицы в ключе может быть опущено, если
 *	используется таблица по умолчанию, например, ключи `.hello` и `hello` определяют строку с
 *	идентификатором `hello`, содержащуюся в таблице локализации по умолчанию. Название таблицы по
 *	умолчанию определяется профилем конфигураций (см. `Config::lang_default_table`). Профиль также
 *	определяет директорию, где хранятся файлы локализации (см. `Config::lang_path`). Каждый язык
 *	имеет в этой директории свою папку, в качестве названий папок используются коды языков
 *	(например, `ru_RU`, `en_UK`, `en_US` и т. д.). Каждая папка содержит файлы JSON, каждый из
 *	которых соответствует своей таблице локализации, например, в файле `en_UK/messages.json`
 *	содержатся строки таблицы `messages` на британском английском. Каждый файл содержит объект JSON
 *	со строковыми значениями. Каждое такое значение — перевод локализуемой строки, ключ этого
 *	значения — идентификатор строки. Название таблицы локализации может содержать символ `/`. В
 *	таком случае файл локализации для этой таблицы должен находиться в подпапке, вложенной в папку
 *	языка.
 */

/**
 *	\addtogroup SnowFlake
 *	\{
 */

/**
 *	\~english
 *	\brief The class of the SnowFlake language manager
 *	
 *	This class is used to manage languages. The language manager is singleton, only one its
 *	instance may exist. You can get it using the `get_instance()` method.
 *	
 *	\~russian
 *	\brief Класс диспетчера языков SnowFlake
 *	
 *	Этот класс используется для управления языками. Диспетчер языков является одиночкой: может
 *	существовать только один его экземпляр. Вы можете получить его, используя метод
 *	`get_instance()`.
 */
class LangManager
{
public:
			/* SINGLETON */

	/**
	 *	\~english
	 *	\brief The only instance of the language manager
	 *	
	 *	Allows to get the instance of the language manager.
	 *	\return The language manager.
	 *	
	 *	\~russian
	 *	\brief Единственный экземпляр диспетчера языков
	 *	
	 *	Позволяет получить экземпляр диспетчера языков.
	 *	\return Диспетчер языков.
	 */
	static LangManager& get_instance();

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
	const String& get_current_lang() noexcept;

	/**
	 *	\~english
	 *	\brief Sets the language
	 *	
	 *	Sets the passed language as active. Tries to load for the new language all localization
	 *	tables that were loaded for the previous language.
	 *	\param lang The text code of the required language.
	 *	\throw std::runtime_error The file of the default localization table does not exist or
	 *	cannot be accessed.
	 *	\throw std::invalid_argument The JSON containing in the file of the default localization
	 *	table is not correct.
	 *	
	 *	\~russian
	 *	\brief Устанавливает язык
	 *	
	 *	Устанавливает переданный язык в качестве активного. Пытается загрузить для нового языка все
	 *	таблицы локализации, которые были загружены для старого.
	 *	\param lang Текстовый код требуемого языка.
	 *	\throw std::runtime_error Файл таблицы локализации по умолчанию не существует или к нему не
	 *	удаётся получить доступ.
	 *	\throw std::invalid_argument JSON, содержащийся в файле таблицы локализации по умолчанию,
	 *	неверный.
	 */
	void set_lang(const String& lang);

	/**
	 *	\~english
	 *	\brief Loads the localization table
	 *	
	 *	Loads the localization table for the current language.
	 *	\param table The name of the table.
	 *	\param reload Defines whether the method should reload the table if it has already been
	 *	loaded.
	 *	\throw std::runtime_error The file of the localization table does not exist or cannot be
	 *	accessed.
	 *	\throw std::invalid_argument The JSON containing in the file of the localization table is
	 *	correct.
	 *	
	 *	\~russian
	 *	\brief Загружает таблицу локализации
	 *	
	 *	Загружает таблицу локализации для текущего языка. Если таблица уже была загружена,
	 *	загружает её заново.
	 *	\param table Название таблицы.
	 *	\param reload Определяет, должен ли метод загрузить таблицу заново, если она уже была
	 *	загружена.
	 *	\throw std::runtime_error Файл таблицы локализации не существует или к нему не удаётся
	 *	получить доступ.
	 *	\throw std::invalid_argument JSON, содержащийся в файле таблицы локализации, неверный.
	 */
	void load_table(const String& table, bool reload = false);

	/**
	 *	\~english
	 *	\brief Unloads the localization table
	 *
	 *	Unloads the localization table. The default table cannot be unloaded.
	 *	\param table The name of the table.
	 *	\return `true` if the table has been successfully unloaded, `false` otherwise (e. g. if
	 *	it hasn't been loaded).
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
	 *	\brief Unloads all tables except of the default table
	 *	
	 *	Unloads all loaded localization tables except of the default table.
	 *	\return The amound of tables which have been unloaded.
	 *	
	 *	\~russian
	 *	\brief Выгружает все таблицы, кроме таблицы по умолчанию
	 *	
	 *	Выгружает из памяти все загруженные таблицы локализации, кроме таблицы по умолчанию.
	 *	\return Количество таблиц, которые были выгружены.
	*/
	int unload_all_tables();

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
	 *	\brief The set of all loaded tables
	 *	
	 *	Allows to get the set of all loaded localization tables.
	 *	\return The set of loaded tables.
	 *	
	 *	\~russian
	 *	\brief Множество всех загруженных таблиц
	 *	
	 *	Позволяет получить множество из всех загруженных таблиц локализации.
	 *	\return Множество загруженных таблиц.
	 */
	std::set<String> get_loaded_tables() const;

	/**
	 *	\~english
	 *	\brief A localized string
	 *	
	 *	Allows to get a string in the language that is active now.
	 *	\param key The key of the required string: `<table>.<id>`. For the default localization
	 *	table it's allowed to use the string `.<id>` or just `<id>`.
	 *	\param allow_loading Defines whether the method should load the required localization table
	 *	if it hasn't been loaded.
	 *	\return The required string in the current language. The key itself if there is no string
	 *	with the passed key.
	 *	
	 *	\~russian
	 *	\brief Локализованный текст
	 *	
	 *	Позволяет получить строку на активном в данный момент языке.
	 *	\param key Ключ требуемой строки: `<таблица>.<id>`. Для таблицы локализации по умолчанию
	 *	допускается использовать строку `.<id>` или просто `<id>`.
	 *	\param allow_loading Определяет, должен ли метод загрузить требуемую таблицу локализации,
	 *	если она не загружена.
	 *	\return Требуемая строка на текущем языке. Сам ключ, если строка с переданным ключом не
	 *	найдена.
	 */
	String get_string(const String& key, bool allow_loading = true);

	/**
	 *	\~english
	 *	\brief A localized string
	 *	
	 *	Allows to get a string in the language that is active now.
	 *	\param table The localization table. If the string is empty, the default table will be
	 *	used.
	 *	\param id The id of the required string.
	 *	\param allow_loading Defines whether the method should load the required localization table
	 *	if it hasn't been loaded.
	 *	\return The required string in the current language. The key itself if there is no string
	 *	with the passed key.
	 *	
	 *	\~russian
	 *	\brief Локализованный текст
	 *	
	 *	Позволяет получить строку на активном в данный момент языке.
	 *	\param table Таблица локализации. Если строка пуста, будет использоваться таблица по
	 *	умолчанию.
	 *	\param id Идентификатор требуемой строки.
	 *	\param allow_loading Определяет, должен ли метод загрузить требуемую таблицу локализации,
	 *	если она не загружена.
	 *	\return Требуемая строка на текущем языке. Сам ключ, если строка с переданным ключом не
	 *	найдена.
	 */
	String get_string(const String& table, const String& id, bool allow_loading = true);

	/**
	 *	\~english
	 *	\brief Checks whether the passed key is valid
	 *	
	 *	Checks if the passed key is contained in the list of strings of the current language.
	 *	\param key The key to check: `<table>.<id>`. For the default localization table it's
	 *	allowed to use the string `.<id>` or just `<id>`.
	 *	\param allow_loading Defines whether the method should load the required localization table
	 *	if it hasn't been loaded.
	 *	\return	`true` if there is a string with the passed key, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, действителен ли переданный ключ
	 *	
	 *	Проверяет, содержится ли переданный ключ в списке строк текущего языка.
	 *	\param key Ключ для проверки: `<таблица>.<id>`. Для таблицы локализации по умолчанию
	 *	допускается использовать строку `.<id>` или `<id>`.
	 *	\param allow_loading Определяет, должен ли метод загрузить требуемую таблицу локализации,
	 *	если она не загружена.
	 *	\return `true`, если существует строка с переданным ключом, иначе `false`.
	 */
	bool is_valid(const String& key, bool allow_loading = false);

	/**
	 *	\~english
	 *	\brief Checks whether the passed key is valid
	 *	
	 *	Checks if the passed key is contained in the list of strings of the current language.
	 *	\param table The localization table. If the string is empty, the default table will be
	 *	used.
	 *	\param id The id to check.
	 *	\param allow_loading Defines whether the method should load the required localization table
	 *	if it hasn't been loaded.
	 *	\return	`true` if there is a string with the passed key, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, действителен ли переданный ключ
	 *	
	 *	Проверяет, содержится ли переданный ключ в списке строк текущего языка.
	 *	\param table Таблица локализации. Если строка пуста, будет использоваться таблица по
	 *	умолчанию.
	 *	\param id Идентификатор для проверки.
	 *	\param allow_loading Определяет, должен ли метод загрузить требуемую таблицу локализации,
	 *	если она не загружена.
	 *	\return `true`, если существует строка с переданным ключом, иначе `false`.
	 */
	bool is_valid(const String& table, const String& id, bool allow_loading = false);

			/* STATIC METHODS */

	/**
	 *	\~english
	 *	\brief Splits the key into the table name and id
	 *	
	 *	The key consists of the name of the localization table and the id separated by dot. This
	 *	method splits the key into these two parts.
	 *	\param key The key: `<table>.<id>`. For the default localization table it's allowed to use
	 *	the string `.<id>` or just `<id>`.
	 *	\return The pair of the table name and the id.
	 *	
	 *	\~russian
	 *	\brief Делит ключ на название таблицы и идентификатор
	 *	
	 *	Ключ состоит из названия таблицы локализации и идентификатора, разделённых точкой. Этот
	 *	метод разделяет ключ на эти две части.
	 *	\param key Ключ: `<таблица>.<id>`. Для таблицы локализации по умолчанию допускается
	 *	использовать строку `.<id>` или просто `<id>`.
	 */
	static std::pair<String, String> key_to_table_and_id(const String& key);

private:
	using Table_ = std::unordered_map<std::wstring, String>;

	LangManager();

	void load_table_(const String& table, const String& lang, const Path& path);
	int reload_(const Path& path);

	void change_path_(const Config& new_config);
	void change_default_table_(const Config& new_config);

	String current_lang_;
	std::unordered_map<std::wstring, Table_> strings_;

	std::mutex lang_mtx_;
	static const String LANG_LOG_;

};

}
