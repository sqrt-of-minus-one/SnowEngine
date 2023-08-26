    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SaveManager.h               //
////////////////////////////////////////

//****__ __****   /===\     \SnowFall/           ||===|           /|    /|                      //
//**_/  V  \_**   ||                             ||               ||    ||                      //
//**\__^_^__/**   ||                             ||               ||    ||                      //
//** *  *  * **   \===\ ||==\   /=\   ||     ||  ||===|   /==|    ||    ||       /==============//
//**  *  *   **      || ||  |  || ||  ||     ||  ||      || ||    ||    ||      ||* SnowEngine *//
//**   *  *  **      || ||  |  || ||  \\ /^\ //  ||      || ||    ||    ||      ||*   saving   *//
//**    *  * **   \===/ ||  |   \=/    \V/ \V/   ||       \==\_  _||_  _||_     ||*   system   *//

#pragma once

#include "../../Object.h"

#include <list>
#include <map>

namespace snow
{

/**
 *	\defgroup SnowFall SnowFall
 *	\~english
 *	\brief SnowFall, the SnowEngine saving system
 *	
 *	The `SaveManager` class allows you to create saves and then load them.
 *	
 *	\~russian
 *	\brief SnowFall, система сохранения SnowEngine
 *	
 *	Класс `SaveManager` позволяет вам создавать сохранения и затем загружать их.
 */

/**
 *	\~english
 *	\brief The class for saving and loading
 *	
 *	This class allows to save and load data. The save manager is singleton: only one its instance
 *	may exist. You can access it using `get_instance()` method. The saves are stored as JSON files
 *	in the folder which is determined by the current configuration profile (see
 *	`Config::saves_path`).
 *	
 *	\~russian
 *	\brief Класс для сохранения и загрузки
 *	
 *	Этот класс позволяет сохранять и загружать данные. Диспетчер сохранений является одиночкой:
 *	может существовать только один его экземпляр. Вы можете получить к нему доступ с помощью метода
 *	`get_instance()`. Сохранения хранятся в виде файлов JSON в директории, которая определяется
 *	текущим профилем конфигураций (см. `Config::saves_path`).
 */
class SaveManager : public Object
{
public:
			/* SINGLETON */

	/**
	 *	\~english
	 *	\brief The only instance of the save manager
	 *	
	 *	Allow to access the save manager.
	 *	\return The save manager.
	 *	
	 *	\~russian
	 *	\brief Единственный экземпляр диспетчера сохранений
	 *	
	 *	Позволяет получить доступ к диспетчеру сохранений.
	 *	\return Диспетчер сохранений.	
	 */
	static SaveManager& get_instance();

	/**
	 *	\~english
	 *	\brief Converts the save manager to string
	 *	
	 *	Returns the string `"SaveManager, path: <path>"`, where `<path>` is the path to the
	 *	directory where the saves are stored.
	 *	\return The string.
	 *	
	 *	\~russian
	 *	\brief Конвертирует диспетчер сохранений в строку
	 *	
	 *	Возвращает строку `"SaveManager, path: <path>"`, где `<path>` — путь к директории, где
	 *	хранятся сохранения.
	 *	\return Строка.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Creates a JSON object with the save manager data
	 *	
	 *	Creates a JSON object with the following elements:
	 *	- `path`: the string value with the path to the directory where the saves are stored;
	 *	- `saves`: the array of names of the existing saves.
	 *	\return The JSON object.
	 *	
	 *	\~russian
	 *	\brief Создаёт объект JSON с информацией о диспетчере сохранений
	 *	
	 *	Создаёт объект JSON со следующими элементами:
	 *	- `path`: строковое значение, содержащее путь к директории, где хранятся сохранения;
	 *	- `saves`: массив названий существующих сохранений.
	 *	\return Объект JSON
	*/
	virtual std::shared_ptr<json::Element> to_json() const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Names of all save files
	 *	
	 *	Allows to get the name of all saves (including backups).
	 *	\return The set with names of all saves.
	 *	
	 *	\~russian
	 *	\brief Названия всех файлов сохранений
	 *	
	 *	Позволяет получить названия всех сохранений (включая резервные копии).
	 *	\return Множество с названиями всех сохранений.
	 */
	std::set<String> get_saves() const;

	/**
	 *	\~english
	 *	\brief Remove the save with passed name
	 *	
	 *	Allows to remove the save file with the passed name.
	 *	\param name The name of the save which should be removed.
	 *	\param do_backup If `true`, the save will be replaced from `<name>.json` to `~<name>.json`.
	 *	\return `true` if the save was successfully removed, `false` otherwise (e. g. if the save
	 *	with the passed name doesn't exist).
	 *	
	 *	\~russian
	 *	\brief Удалить сохранение с переданным названием
	 *	
	 *	Позволяет удалить файл сохранения с переданным названием.
	 *	\param name Название сохранения, которое должно быть удалено.
	 *	\param do_backup Если `true`, сохранение будет перемещено из `<name>.json` в
	 *	`~<name>.json`.
	 *	\return `true`, если сохранение было успешно удалено, иначе `false` (например, если
	 *	сохранения с переданным названием не существует).
	 */
	bool remove_save(const String& name, bool do_backup = false);

	/**
	 *	\~english
	 *	\brief Whether the save with the passed name exist
	 *	
	 *	Checks whether the save with the passed name exist.
	 *	\param name The name of the save.
	 *	\return `true` if the save exists, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Существует ли сохранение с переданным названием
	 *	
	 *	Проверяет, существует ли сохранение с переданным названием.
	 *	\param name Название сохранения.
	 *	\return `true`, если сохранение существует, иначе `false`.
	 */
	bool exists(const String& name) const;

	/**
	 *	\~english
	 *	\brief Save a data
	 *	
	 *	Creates a new save file and puts into it the passed data.
	 *	\param name The name of the save. It cannot start with the `~` character.
	 *	\param data The data which will be saved.
	 *	\param do_backup Defines what the method should do if the save with the passed name already
	 *	exists. If `false`, the old data will be discarded. If `true`, the old data will be moved
	 *	from `<name>.json` to `~<name>.json`.
	 *	\return `true` if the data was successfully saved, `false` otherwise (e. g. if the save
	 *	name starts with the `~` character or if data is a null pointer).
	 *	\throw std::runtime_error The save file cannot be created, overriden or accessed.
	 *	
	 *	\~russian
	 *	\brief Сохранить данные
	 *	
	 *	Создаёт новый файл сохранения и помещает в него переданные данные.
	 *	\param name Название сохранения. Оно не должно начинаться с символа `~`.
	 *	\param data Данные, которые будут сохранены.
	 *	\param do_backup Определяет, что должен делать метод, если сохранение с переданным
	 *	названием уже существует. Если `false`, старые данные будут стёрты. Если `true`, старые
	 *	данные будут перемещены из `<name>.json` в `~<name>.json`.
	 *	\return `true`, если данные были успешно сохранены, иначе `false` (например, если название
	 *	сохранения начинается с символа `~` или если вместо данных передан нулевой указатель).
	 *	\throw std::runtime_error Файл сохранения не может быть создан, перезаписан или к нему не
	 *	удаётся получить доступ.
	 */
	bool save(const String& name, std::shared_ptr<const json::Element> data, bool do_backup = true);
	
	/**
	 *	\~english
	 *	\brief Load a data
	 *	
	 *	Loads a data from the specified save and returns it.
	 *	\param name The name of the save.
	 *	\return The loaded data.
	 *	\throw std::runtime_error The save file with the passed name does not exist or cannot be
	 *	accessed.
	 *	\throw std::invalid_argument The JSON in the save file is not valid.
	 *	
	 *	\~russian
	 *	\brief Загрузить данные
	 *	
	 *	Загружает данные из заданного сохранения и возвращает их.
	 *	\param name Название сохранения.
	 *	\return Загруженные данные.
	 *	\throw std::runtime_error Файл сохранения с переданным названием не существует или к нему
	 *	не удалось получить доступ.
	 *	\throw std::invalid_argument Файл сохранения не содержит корректный JSON.
	 */
	std::shared_ptr<json::Element> load(const String& name);

	static const String SAVE_LOG;

private:
	SaveManager();
};

}
