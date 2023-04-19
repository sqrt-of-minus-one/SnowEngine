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

/**
 *	\file
 *	\~english
 *	\brief The file with `SaveLoad` class
 *
 *	This file contains the definition of the `SaveLoad` class of the SnowFall system.
 *
 *	\~russian
 *	\brief ‘айл с классом `SaveLoad`
 *
 *	Ётот файл содержит определение класса `SaveLoad` системы SnowFall.
 */

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
 *	\brief  ласс дл€ сохранени€ и загрузки
 *	
 *	Ётот класс позвол€ет сохран€ть и загружать данные.
 */
class SaveLoad
{
public:
			/* CONSTRUCTORS */

	SaveLoad() = delete;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Names of all save files
	 *	
	 *	Allows to get the name of all saves.
	 *	\return The vector with names of all saves.
	 *	
	 *	\~russian
	 *	\brief Ќазвани€ всех файлов сохранений
	 *	
	 *	ѕозвол€ет получить названи€ всех сохранений.
	 *	\return ¬ектор с названи€ми всех сохранений.
	 */
	static std::list<String> get_saves();

	/**
	 *	\~english
	 *	\brief Remove the save with passed name
	 *	
	 *	Allows to remove the save file with the passed name.
	 *	\param name The name of the save which should be removed.
	 *	\param do_backup If `true`, the save will be replaced to a `.tmp` file.
	 *	\return `true` if the save was successfully removed, `false` otherwise (e.†g. if the save
	 *	with the passed name doesn't exist).
	 *	
	 *	\~russian
	 *	\brief ”далить сохранение с переданным названием
	 *	
	 *	ѕозвол€ет удалить файл сохранени€ с переданным названием.
	 *	\param name Ќазвание сохранени€, которое должно быть удалено.
	 *	\param do_backup ≈сли `true`, сохранени будет перемещено в файл `.tmp`.
	 *	\return `true`, если сохранение было успешно удалено, иначе `false` (например, если
	 *	сохранени€ с переданным названием не существует).
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
	 *	\brief —уществует ли сохранение с переданным названием
	 *	
	 *	ѕровер€ет, существует ли сохранение с переданным названием.
	 *	\param name Ќазвание сохранени€.
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
	 *	\brief —охранить данные
	 *	
	 *	—оздаЄт новый файл сохранени€ и помещает в него переданные данные.
	 *	\param save_name Ќазвание сохранени€.
	 *	\param data —ловарь с сохран€емыми данными.
	 *	\param do_backup ≈сли сохранение с переданным названием уже существует и `do_backup` равно
	 *	`true`, старые данные будут сохранены в файл `.tmp`. ≈сли `false`, старые данные будут
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
	 *	\brief «агрузить данные
	 *	
	 *	«агружает данные из заданного сохранени€ и возвращает их в виде словар€.
	 *	\param save_name Ќазвание сохранени€.
	 *	\return «агруженные данные.
	 *	\throw std::runtime_error ‘айл сохранени€ с переданным названием не существует или к нему
	 *	не удалось получить доступ.
	 */
	static std::map<String, String> load(const String& save_name);
};

}
