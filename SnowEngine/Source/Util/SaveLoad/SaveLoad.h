    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SaveLoad.h                  //
////////////////////////////////////////

//****__ __*****/===\******\SnowFall/***********||===|********** /| ** /| ***********************//
//**_/  V  \_***||   ***************************||    ********** || ** || ***********************//
//**\__^_^__/***||   ***************************||    ********** || ** || ***********************//
//** *  *  * ***\===\**||==\***/=\***||     ||**||===|***/==| ** || ** || ********/==============//
//**  *  *   ***   ||**||  |**|| ||**||     ||**||    **|| || ** || ** || *******||* SnowEngine *//
//**   *  *  ***   ||**||  |**|| ||**\\ /^\ //**||    **|| || ** || ** || *******||*   saving   *//
//**    *  * ***\===/**||  |***\=/****\V/ \V/***||    ***\==\_**_||_**_||_*******||*   system   *//

#pragma once

#include <list>
#include <map>

namespace snow
{

class String;

/**
 *	\~english
 *	\brief The class for saving and loading
 *	
 *	This class allows to save and load data.
 *	
 *	\~russian
 *	\brief Класс для сохранения и загрузки
 *	
 *	Этот класс позволяет сохранять и загружать данные.
 */
class SaveLoad
{
public:
			/* SINGLETON */

	static SaveLoad& get_instance();

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Names of all save files
	 *	
	 *	Allows to get the name of all saves.
	 *	\return The vector with names of all saves.
	 *	
	 *	\~russian
	 *	\brief Названия всех файлов сохранений
	 *	
	 *	Позволяет получить названия всех сохранений.
	 *	\return Вектор с названиями всех сохранений.
	 */
	static std::list<String> get_saves();

	/**
	 *	\~english
	 *	\brief Remove the save with passed name
	 *	
	 *	Allows to remove the save file with the passed name.
	 *	\param name The name of the save which should be removed.
	 *	\param do_backup If `true`, the save will be replaced to a `.tmp` file.
	 *	\return `true` if the save was successfully removed, `false` otherwise (e. g. if the save
	 *	with the passed name doesn't exist).
	 *	
	 *	\~russian
	 *	\brief Удалить сохранение с переданным названием
	 *	
	 *	Позволяет удалить файл сохранения с переданным названием.
	 *	\param name Название сохранения, которое должно быть удалено.
	 *	\param do_backup Если `true`, сохранени будет перемещено в файл `.tmp`.
	 *	\return `true`, если сохранение было успешно удалено, иначе `false` (например, если
	 *	сохранения с переданным названием не существует).
	 */
	static bool remove_save(const String& name, bool do_backup = false);

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
	static bool exist(const String& name);

	/**
	 *	\~english
	 *	\brief Save a data
	 *	
	 *	Creates a new save file and puts into it the passed data.
	 *	\param save_name The name of the save.
	 *	\param data The map with data being saved.
	 *	\param do_backup If the save with the passed name already exists, and `do_backup` is
	 *	`true`, the old data will be saved in a `.tmp` file. If `false`, the old data will be
	 *	removed.
	 *	\return `true` if the data was successfully saved, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Сохранить данные
	 *	
	 *	Создаёт новый файл сохранения и помещает в него переданные данные.
	 *	\param save_name Название сохранения.
	 *	\param data Словарь с сохраняемыми данными.
	 *	\param do_backup Если сохранение с переданным названием уже существует и `do_backup` равно
	 *	`true`, старые данные будут сохранены в файл `.tmp`. Если `false`, старые данные будут
	 *	удалены.
	 *	\return `true`, если данные были успешно сохранены, иначе `false`.
	 */
	static bool save(const String& save_name, const std::map<String, String>& data, bool do_backup = true);
	
	/**
	 *	\~english
	 *	\brief Load a data
	 *	
	 *	Loads a data from the specified save and returns it as the map.
	 *	\param save_name The name of the save.
	 *	\return The loaded data.
	 *	\throw std::runtime_error The save file with the passed name does not exist or cannot be
	 *	accessed.
	 *	
	 *	\~russian
	 *	\brief Загрузить данные
	 *	
	 *	Загружает данные из заданного сохранения и возвращает их в виде словаря.
	 *	\param save_name Название сохранения.
	 *	\return Загруженные данные.
	 *	\throw std::runtime_error Файл сохранения с переданным названием не существует или к нему
	 *	не удалось получить доступ.
	 */
	static std::map<String, String> load(const String& save_name);

private:
	SaveLoad();
};

}
