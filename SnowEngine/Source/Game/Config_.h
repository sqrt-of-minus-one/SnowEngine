    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Config.h                    //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include "../Math/Vector/Point2.h"
#include "../Util/Types/String.h"

namespace snow
{

/**
 *	\~english
 *	\brief The class with configurations
 *	
 *	This class contains the configurations of the game. Use `config.json` file to set them before
 *	the game starts. The main instance of this class is contained in the `Game` class as a static
 *	member.
 *	
 *	\~russian
 *	\brief Класс с конфигурациями
 *	
 *	Этот класс содержит конфигурации игры. Используйте файл `config.json`, чтобы установить их
 *	перед началом игры. Главный объект этого класса хранится в классе `Game` как статический член.
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
				SECTION: default */

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
	 *	Путь к директории с файлами лога. Если она не существует, то будет создана. Значение по
	 *	умолчанию: `Logs`.
	 */
	String log_path;

	/**
	 *	\~english
	 *	\brief The path to save files
	 *	
	 *	The path to the folder with saves. If it doesn't exist, it will be created. Default value:
	 *	`Saves`.
	 *	
	 *	\~russian
	 *	\brief Путь к файлам сохранений
	 *	
	 *	Путь к директории с файлами сохранений. Если она не существует, то будет создана. Значение
	 *	по умолчанию: `Saves`.
	 */
	String saves_path;

			/* FIELDS
				SECTION: window */

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
				SECTION: resources */

	/**
	 *	\~english
	 *	\brief The period of the resource checks
	 *	
	 *	The time in seconds between the resource checks. While checking the references to unused
	 *	and unloaded resources are deleted. Default value: 300.
	 *	
	 *	\~russian
	 *	\brief Частота проверки ресурсов
	 *	
	 *	Время в секундах между проверками ресурсов. Во время проверки удаляются ссылки на
	 *	неиспользуемые и выгруженные из памяти ресурсы. Значение по умолчанию: 300.
	 */
	double res_check_period_sec;

	/**
	 *	\~english
	 *	\brief The path to textures
	 *
	 *	The path to the folder with texture files. Default value: `Resources\\Textures`.
	 *
	 *	\~russian
	 *	\brief Путь к текстурам
	 *
	 *	Путь к директории с файлами текстур. Значение по умолчанию: `Resources\\Textures`.
	 */
	 String res_textures_path;

	 /**
	  *	\~english
	  *	\brief The path to fonts
	  *
	  *	The path to the folder with font files. Default value: `Resources\\Fonts`.
	  *
	  *	\~russian
	  *	\brief Путь к шрифтам
	  *
	  *	Путь к директории с файлами шрифтов. Значение по умолчанию: `Resources\\Fonts`.
	  */
	 String res_fonts_path;

	 /**
	  *	\~english
	  *	\brief The path to sounds
	  *
	  *	The path to the folder with sound files. Default value: `Resources\\Sounds`.
	  *
	  *	\~russian
	  *	\brief Путь к звукам
	  *
	  *	Путь к директории с файлами звуков. Значение по умолчанию: `Resources\\Sounds`.
	  */
	 String res_sounds_path;

	 /**
	  *	\~english
	  *	\brief The path to music
	  *
	  *	The path to the folder with music files. Default value: `Resources\\Music`.
	  *
	  *	\~russian
	  *	\brief Путь к музыке
	  *
	  *	Путь к директории с файлами музыки. Значение по умолчанию: `Resources\\Music`.
	  */
	 String res_music_path;

			/* FIELDS
				SECTION: chunks */

	/**
	 *	\~english
	 *	\brief Size of a collision chunk
	 *	
	 *	Size of any collision chunk. It is used to handle collisions in the `CollisionComponent`.
	 *	It's recommend that the size of a chunk be bigger than the size of the largest collision.
	 *	Default value: `1500x1500`.
	 *	
	 *	\~russian
	 *	\brief Размер чанка коллизии
	 *	
	 *	Размер одного чанка коллизии. Используется при обработке коллизий в классе
	 *	`CollisionComponent`. Рекомендуется, чтобы размер чанка был больше, чем размер наибольшей
	 *	коллизии. Значение по умолчанию: `1500x1500`
	 */
	Point2 collision_chunk_size;

	/**
	 *	\~english
	 *	\brief Size of a clickable chunk
	 *	
	 *	Size of any clickable chunk. It is used to handle clicks in the `ClickableComponent`. It's
	 *	recommend that the size of a chunk be bigger than the size of the largest clickable
	 *	component. Default value: `500x500`.
	 *	
	 *	\~russian
	 *	\brief Размер чанка кликабельных компонентов
	 *	
	 *	Размер одного чанка кликабельных компонентов. Используется при обработке нажатий в классе
	 *	`CkickableComponent`. Рекомендуется, чтобы размер чанка был больше, чем размер наибольшего
	 *	кликабельного компонента. Значение по умолчанию: `500x500`
	 */
	Point2 clickable_chunk_size;

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
