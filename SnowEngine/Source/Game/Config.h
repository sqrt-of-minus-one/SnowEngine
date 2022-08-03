    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Config.h                    //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `Config` class
 *
 *	This file contains the definition of the `Config` class.
 *
 *	\~russian
 *	\brief Файл с классом `Config`
 *
 *	Этот файл содержит определение класса `Config`.
 */

#include "../Math/Vector/Point2.h"
		// + Object

#include "../Util/Types/String.h"

namespace snow
{

/**
 *	\~english
 *	\brief The class with configurations
 *	
 *	This class contains the configurations of the game. Use `config.ini` file to set them before
 *	the game starts. The main instance of this class is contained in the `Game` class as a static
 *	member. You shouldn't create other instances.
 *	
 *	\~russian
 *	\brief Класс с конфигурациями
 *	
 *	Этот класс содержит конфигурации игры. Используйте файл `config.ini`, чтобы установить их перед
 *	началом игры. Главный объект этого класса хранится в классе `Game` как статический член. Вы не
 *	должны создавать других объектов.
 */
class Config : public Object
{
	friend class Game;

public:
			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the configurations to the string
	 *	
	 *	The resultant string contains all configurations in the format of `config.ini` file.
	 *	\return The string with configurations.
	 *	
	 *	\~russian
	 *	\brief Конвертирует конфигурации в строку
	 *	
	 *	Итоговая строка содержит все конфигурации в формате файла `config.ini`.
	 *	\return Строка с конфигурациями.
	 */
	virtual String to_string() const override;
	
	/**
	 *	\~english
	 *	\brief Hash code of the configurations
	 *
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes.
	 *	\return Hash code of the object.
	 *
	 *	\~russian
	 *	\brief Хеш-код конфиураций
	 *
	 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
	 *	также могут иметь одинаковые хеш-коды.
	 *	\return Хеш-код объекта.
	 */
	virtual int hash_code() const noexcept override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Saves configrations
	 *	
	 *	Saves current configurations to `config.ini` file.
	 *	
	 *	\~russian
	 *	\brief Сохраняет конфигурации
	 *	
	 *	Сохраняет конфигурации в файл `config.ini`.
	 */
	void save();

	/**
	 *	\~english
	 *	\brief Loads configrations
	 *
	 *	Loads current configurations from `config.ini` file.
	 *
	 *	\~russian
	 *	\brief Загружает конфигурации
	 *
	 *	Загружает конфигурации из файла `config.ini`.
	 */
	void load();

			/* FIELDS
				SECTION: Default */

	/**
	 *	\~english
	 *	\brief The path to log files
	 *	
	 *	The path to the folder with log files. If it doesn't exist, it will be created. Default
	 *	value: `Logs`.
	 *
	 *	\~russian
	 *	\brief Путь к файлам лога
	 *
	 *	Путь к директории с файлами лога. Если он не существует, то будет создан. Значение по
	 *	умолчанию: `Logs`.
	 */
	String log_path;

			/* FIELDS
				SECTION: Window */

	/**
	 *	\~english
	 *	\brief The resolution
	 *
	 *	The default resolution. Default value: `800x600`.
	 *
	 *	\~russian
	 *	\brief Разрешение экрана
	 *
	 *	Разрешение экрана по умолчанию. Значение по умолчанию: `800x600`.
	 */
	Point2 resolution;

	/**
	 *	\~english
	 *	\brief Is fullscreen
	 *
	 *	If true, the game will be launched in fullscreen. Default value: `false`.
	 *
	 *	\~russian
	 *	\brief Полноэкранный режим
	 *
	 *	Если истинно, игра будет запускаться в полноэкранном режиме. Значение по умолчанию:
	 *	`false`.
	 */
	bool fullscreen;

	/**
	 *	\~english
	 *	\brief Can the window be resized
	 *
	 *	If true, the game window can be resized unless fullscreen mode is active. Default value:
	 *	`true`.
	 *
	 *	\~russian
	 *	\brief Может ли размер окна быть изменён
	 *
	 *	Если истинно, размер окна может быть изменён (не работает в полноэкранном режиме). Значение
	 *	по умолчанию: `true`.
	 */
	bool resize;

	/**
	 *	\~english
	 *	\brief Does the window have a titlebar
	 *
	 *	If true, the game window has a titlebar unless fullscreen mode is active. This property is
	 *	ignored if `resize` or `titlebar_buttons` is `true`. Default value: `true`.
	 *
	 *	\~russian
	 *	\brief Есть ли у окна заголовок
	 *
	 *	Если истинно, у игрового окна есть строка с заголовком (не работает в полноэкранном
	 *	режиме). Это свойство игнорируется, если `resize` или `titlebar_buttons` имеет значение
	 *	`true`.Значение по умолчанию: `true`.
	 */
	bool titlebar;

	/**
	 *	\~english
	 *	\brief Does the window have titlebar buttons
	 *
	 *	If true, the game window has titlebar buttons (such as close) unless fullscreen mode is
	 *	active. Default value: `true`.
	 *
	 *	\~russian
	 *	\brief Есть ли у окна кнопки в заголовке
	 *
	 *	Если истинно, у игрового окна есть кнопки в заголовке (такие как кнопка закрытия) (не
	 *	работает в полноэкранном режиме). Значение по умолчанию: `true`.
	 */
	bool titlebar_buttons;

	/**
	 *	\~english
	 *	\brief The title of the window
	 *	
	 *	The string with the title of the game window. Default value: `The Game (powered by
	 *	SnowEngine)`.
	 *	
	 *	\~russian
	 *	\brief Заоловок окна
	 *	
	 *	Строка с заголовком игрового окна. Значение по умолчанию: `The Game (powered by
	 *	SnowEngine)`.
	 */
	String title;

			/* FIELDS
				SECTION: localization */

	/**
	 *	\~english
	 *	\brief The path to localization files
	 *
	 *	The path to the folder with localization files. If it doesn't exist, it will be created.
	 *	Default value: `Localization`.
	 *
	 *	\~russian
	 *	\brief Путь к файлам локализации
	 *
	 *	Путь к директории с файлами локализации. Если он не существует, то будет создан. Значение
	 *	по умолчанию: `Localization`.
	 */
	String lang_path;

	/**
	 *	\~english
	 *	\brief The code of the default language
	 *
	 *	The code of the language that will be used in the game by default. Default value: `en_UK`.
	 *
	 *	\~russian
	 *	\brief Код языка по умолчанию
	 *
	 *	Код языка, который будет использоваться в игре по умолчанию. Значение по умолчанию:
	 *	`en_UK`.
	 */
	String default_lang;

	/**
	 *	\~english
	 *	\brief The default localization table
	 *	
	 *	The name of the localization table that will be used as default. Default value: `default`.
	 *	
	 *	\~russian
	 *	\brief Таблица локализации по умолчанию
	 *	
	 *	Название таблицы локализации, которая будет использоваться по умолчанию. Значение по
	 *	умолчанию: `default`.
	 */
	String default_table;

private:
	Config();
};

}
