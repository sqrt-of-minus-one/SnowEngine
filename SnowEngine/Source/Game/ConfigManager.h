    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ConfigManager.h             //
////////////////////////////////////////

#pragma once

#include "Config.h"
#include "../Util/Function/EventBinder.h"

#define CURRENT_CONFIG snow::ConfigManager::get_instance().get_current()

namespace snow
{

/**
 *	\addtogroup Config
 *	\{
 */

/**
 *	\~english
 *	\brief The configuration manager
 *	
 *	Allows you to manage your configuration profiles (see the `Config` class). The configuration
 *	manager is a singleton, there can only be one instance of it. You can access it via the
 *	`ConfigManager::get_instance()` method. When created, the manager tries to read the
 *	`config_init.json` file (its path is stored in `ConfigManager::INIT_FILE`) (if the file cannot
 *	be found, the manager creates it). The file should contain a JSON object with two strings:
 *	`"path"`, which is the path to the directory where configuration profiles are stored (the
 *	default value is `"Config"`), and `"default"`, which is the name of the configuration profile
 *	which should be loaded when the game starts (the default value is `"default"`).
 *	\sa
 *	- `Config`: configuration profile
 *	
 *	\~russian
 *	\brief Диспетчер конфигураций
 *	
 *	Позволяет управлять профили конфигурации (см. класс `Config`). Диспетчер конфигураций —
 *	одиночка: может существовать только один его экземпляр. Вы можете получить к нему доступ
 *	методом `ConfigManager::get_instance()`. При создании диспетчер пытается прочитать файл
 *	`config_init.json` (путь к нему хранится в `ConfigManager::INIT_FILE`) (если файл не найден,
 *	диспетчер создаёт его). Файл должен содержать объект JSON с двумя строками: `"path"` — путь к
 *	директории, где хранятся профили конфигураций (значение по умолчанию — `"Config"`), и
 *	`"default"` — название профиля конфигураций, который должен быть загружен в начале игры
 *	(значение по умолчанию — `"default"`).
 *	\sa
 *	- `Config`: профиль конфигураций
 */
class ConfigManager
{
public:
			/* SINGLETON */

	/**
	 *	\~english
	 *	\brief The only instance of the configuration manager
	 *	
	 *	Allows to get the only instance of the configuration manager.
	 *	\return The manager.
	 *	
	 *	\~russian
	 *	\brief Единственный экземпляр диспетчера конфигураций
	 *	
	 *	Позволяет получить единственный экземпляр диспетчера конфигураций.
	 *	\return Диспетчер.
	 */
	static ConfigManager& get_instance();

			/* METHODS */

	/**
	 *	\~english
	 *	\brief The path to the directory where profiles are stored
	 *	
	 *	Allows to get the path to the directory where configuration profiles are stored.
	 *	\return The string with the path.
	 *	\sa
	 *	- `set_path()`: sets the path
	 *	
	 *	\~russian
	 *	\brief Путь к директории, где хранятся профили
	 *	
	 *	Позволяет получить путь к директории, где хранятся профили конфигураций.
	 *	\return Строка с путём.
	 *	\sa
	 *	- `set_path()`: устанавливает путь
	 */
	const String& get_path() const;

	/**
	 *	\~english
	 *	\brief Sets the path to the directory where profiles are stored
	 *	
	 *	Allows to change the directory where profiles are stored. It's better to specify the path
	 *	in the `config_init.json` file. The method does not move profiles from the old directory to
	 *	the new one and does not affect the profiles which are already loaded.
	 *	\param path The new path to the directory where profiles are stored.
	 *	\sa
	 *	- `get_path()`: returns the path
	 *	
	 *	\~russian
	 *	\brief Устанавливает путь к директории, где хранятся профили
	 *	
	 *	Позволяет изменить директорию, где хранятся профили. Лучше всего определять этот путь в
	 *	файле `config_init.json`. Метод не перемещает профили из старой директории в новую и никак
	 *	не влияет на уже загруженные профили.
	 *	\param path Новый путь к директории, где хранятся профили.
	 *	\sa
	 *	- `get_path()`: возвращает путь
	 */
	void set_path(const String& path);

	/**
	 *	\~english
	 *	\brief The current profile
	 *	
	 *	Allows to get the configuration profile which is applied at the moment. You may use the
	 *	`CURRENT_CONFIG` macro, which is defined as
	 *	\code
	 *		#define CURRENT_CONFIG snow::ConfigManager::get_instance().get_current()
	 *	\endcode
	 *	\return The current profile.
	 *	\sa
	 *	- `set_current()`: applies the profile
	 *	- `save_current()`: saves the current profile to file
	 *	- `load_current()`: loads the profile from file and applies it
	 *	
	 *	\~russian
	 *	\brief Текущий профиль
	 *	
	 *	Позволяет получить профиль конфигураций, применённый в данный момент. Вы можете
	 *	использовать макрос `CURRENT_CONFIG`, определённый следующим образом:
	 *	\code
	 *		#define CURRENT_CONFIG snow::ConfigManager::get_instance().get_current()
	 *	\endcode
	 *	\return Текущий профиль.
	 *	\sa
	 *	- `set_current()`: применяет профиль
	 *	- `save_current()`: сохраняет текущий профиль в файл
	 *	- `load_current()`: загружает профиль из файла и применяет его
	 */
	const Config& get_current() const;

	/**
	 *	\~english
	 *	\brief Applies the profile
	 *	
	 *	Changes the game settings and properties according to the new profile.
	 *	\param config The new configuration profile. The manager will store its copy, so you don't
	 *	need to ensure its further existance.
	 *	\param reload If `true`, all game settings and properties will be reloaded. If `false`, the
	 *	manager will only reload the properties that are different in the new profile. `false`
	 *	should be preferred.
	 *	\sa
	 *	- `get_current()`: returns the current profile
	 *	- `save_current()`: saves the current profile to file
	 *	- `load_current()`: loads the profile from file and applies it
	 *	
	 *	\~russian
	 *	\brief Применяет профиль
	 *	
	 *	Изменяет игровые настройки и свойства в соответствии с новым профилем.
	 *	\param config Новый профиль конфигураций. Диспетчер будет хранить его копию, поэтому у вас
	 *	нет необходимости обеспечивать его дальнейшее существование.
	 *	\param reload Если `true`, все игровый настройки и свойства будут перезагружены. Если
	 *	`false`, диспетчер перезагрузит только свойства, которые отличаются в новом профиле.
	 *	\sa
	 *	- `get_current()`: возвращает текущий профиль
	 *	- `save_current()`: сохраняет текущий профиль в файл
	 *	- `load_current()`: загружает профиль из файла и применяет его
	 */
	void set_current(const Config& config, bool reload = false);

	/**
	 *	\~english
	 *	\brief Saves the current profile to file
	 *	
	 *	Saves the current configuration profile to file.
	 *	\code
	 *		// These two strings do the same:
	 *		ConfigManager::get_instance().save_current(L"some_name"_s);
	 *		ConfigManager::get_instance().get_current().save(L"some_name"_s);
	 *	\endcode
	 *	\param name The name of the profile.
	 *	\param allow_override Defines what the method should do if the profile with the passed name
	 *	already exists. If `true`, the profile will be overriden; if `false`, an exception will be
	 *	thrown.
	 *	\throw std::runtime_error The file couldn't be created, accessed or overriden.
	 *	\sa
	 *	- `set_current()`: applies the profile
	 *	- `get_current()`: returns the current profile
	 *	- `load_current()`: loads the profile from file and applies it
	 *	
	 *	\~russian
	 *	\brief Сохраняет текущий профиль в файл
	 *	
	 *	Сохраняет текущий профиль конфигураций в файл.
	 *	\code
	 *		// Эти две строки делают одно и то же:
	 *		ConfigManager::get_instance().save_current(L"some_name"_s);
	 *		ConfigManager::get_instance().get_current().save(L"some_name"_s);
	 *	\endcode
	 *	\param name Название профиля.
	 *	\param allow_override Определяет, что должен делать метод, если профиль с переданным
	 *	названием уже существует. Если `true`, профиль будет перезаписан; если `false`, будет
	 *	выброшено исключение.
	 *	\throw std::runtime_error Файл не может быть создан, перезаписан или к нему не удаётся
	 *	получить доступ.
	 *	\sa
	 *	- `set_current()`: применяет профиль
	 *	- `get_current()`: возвращает текущий профиль
	 *	- `load_current()`: загружает профиль из файла и применяет его
	 */
	void save_current(const String& name, bool allow_override = false);

	/**
	 *	\~english
	 *	\brief Loads a new profile and applies it
	 *	
	 *	Loads a profile from file and applies it.
	 *	\code
	 *		// These two strings do the same:
	 *		ConfigManager::get_instance().load_current(L"some_name"_s);
	 *		ConfigManager::get_instance().set_current(Config(L"some_name"_s));
	 *	\endcode
	 *	\param name The name of the saved profile.
	 *	\throw std::runtime_error The file with the profile does not exist or cannot be accessed.
	 *	\throw std::invalid_argument The file does not contain a valid JSON or the JSON doesn't
	 *	represent a configuration profile.
	 *	\sa
	 *	- `set_current()`: applies the profile
	 *	- `get_current()`: returns the current profile
	 *	- `load_current()`: loads the profile from file and applies it
	 *	
	 *	\~russian
	 *	\brief Загружает новый профиль и применяет его
	 *	
	 *	Загружает профиль из файла и применяет его.
	 *	\code
	 *		// Эти две строки делают одно и то же:
	 *		ConfigManager::get_instance().load_current(L"some_name"_s);
	 *		ConfigManager::get_instance().set_current(Config(L"some_name"_s));
	 *	\endcode
	 *	\param name Имя сохранённого профиля.
	 *	\throw std::runtime_error Файл с профилем не существует или к нему не удаётся получить
	 *	доступ.
	 *	\throw std::invalid_argument Файл не содержит корректный JSON или JSON не представляет
	 *	собой профиль конфигураций.
	 *	\sa
	 *	- `set_current()`: применяет профиль
	 *	- `get_current()`: возвращает текущий профиль
	 *	- `save_current()`: сохраняет текущий профиль в файл
	 */
	Config& load_current(const String& name);

			/* EVENTS */
	
	/**
	 *	\~english
	 *	\brief The window properties are changed
	 *	
	 *	This event is called when one of the following properties is changed by `set_current()` or
	 *	`load_current()`:
	 *	- `Config::window_resolution`;
	 *	- `Config::window_fullscreen`;
	 *	- `Config::window_resize`;
	 *	- `Config::window_titlebar`;
	 *	- `Config::window_titlebar_buttons`;
	 *	- `Config::window_title`.
	 *	
	 *	Event parameters:
	 *	- `const Config& new_config`: the new configuration profile.
	 *	
	 *	\~russian
	 *	\brief Свойства окна изменены
	 *	
	 *	Это событие вызывается, когда одно из следующих свойств изменено методом `set_current()`
	 *	или `load_current()`:
	 *	- `Config::window_resolution`;
	 *	- `Config::window_fullscreen`;
	 *	- `Config::window_resize`;
	 *	- `Config::window_titlebar`;
	 *	- `Config::window_titlebar_buttons`;
	 *	- `Config::window_title`.
	 *	
	 *	Параметры события:
	 *	- `const Config& new_config`: новый профиль конфигураций.
	 */
	EventBinder<const Config& /*new_config*/> on_changed_window;
	
	/**
	 *	\~english
	 *	\brief The period of resouce checking is changed
	 *	
	 *	This event is called when the `Config::res_check_period_sec` is changed by `set_current()`
	 *	or `load_current()`.
	 *	
	 *	Event parameters:
	 *	- `const Config& new_config`: the new configuration profile.
	 *	
	 *	\~russian
	 *	\brief Период проверки ресурсов изменён
	 *	
	 *	Это событие вызывается, когда `Config::res_check_period_sec` изменено методом
	 *	`set_current()` или `load_current()`.
	 *	
	 *	Параметры события:
	 *	- `const Config& new_config`: новый профиль конфигураций.
	 */
	EventBinder<const Config& /*new_config*/> on_changed_res_check_period_sec;

	/**
	 *	\~english
	 *	\brief The paths to the resource directories is changed
	 *	
	 *	This event is called when one of the following properties is changed by `set_current()` or
	 *	`load_current()`:
	 *	- `Config::res_textures_path`;
	 *	- `Config::res_fonts_path`;
	 *	- `Config::res_sounds_path`.
	 *	
	 *	Event parameters:
	 *	- `const Config& new_config`: the new configuration profile.
	 *	
	 *	\~russian
	 *	\brief Пути к директориям ресурсов изменены
	 *	
	 *	Это событие вызывается, когда одно из следующих свойств изменено методом `set_current()`
	 *	или `load_current()`:
	 *	- `Config::res_textures_path`;
	 *	- `Config::res_fonts_path`;
	 *	- `Config::res_sounds_path`.
	 *	
	 *	Параметры события:
	 *	- `const Config& new_config`: новый профиль конфигураций.
	 */
	EventBinder<const Config& /*new_config*/> on_changed_res_path;
	
	/**
	 *	\~english
	 *	\brief The size of collision chunks is changed
	 *	
	 *	This event is called when the `Config::chunks_collision_size` is changed by `set_current()`
	 *	or `load_current()`.
	 *	
	 *	Event parameters:
	 *	- `const Config& new_config`: the new configuration profile.
	 *	
	 *	\~russian
	 *	\brief Размер чанков коллизии изменён
	 *	
	 *	Это событие вызывается, когда `Config::chunks_collision_size` изменено методом
	 *	`set_current()` или `load_current()`.
	 *	
	 *	Параметры события:
	 *	- `const Config& new_config`: новый профиль конфигураций.
	 */
	EventBinder<const Config& /*new_config*/> on_changed_chunks_collision_size;
	
	/**
	 *	\~english
	 *	\brief The size of clickable chunks is changed
	 *	
	 *	This event is called when the `Config::chunks_clickable_size` is changed by `set_current()`
	 *	or `load_current()`.
	 *	
	 *	Event parameters:
	 *	- `const Config& new_config`: the new configuration profile.
	 *	
	 *	\~russian
	 *	\brief Размер чанков кликабельных компонентов изменён
	 *	
	 *	Это событие вызывается, когда `Config::chunks_clickable_size` изменено методом
	 *	`set_current()` или `load_current()`.
	 *	
	 *	Параметры события:
	 *	- `const Config& new_config`: новый профиль конфигураций.
	 */
	EventBinder<const Config& /*new_config*/> on_changed_chunks_clickable_size;
	
	/**
	 *	\~english
	 *	\brief The path to the directory with localization files is changed
	 *	
	 *	This event is called when the `Config::lang_path` is changed by `set_current()` or
	 *	`load_current()`.
	 *	
	 *	Event parameters:
	 *	- `const Config& new_config`: the new configuration profile.
	 *	
	 *	\~russian
	 *	\brief Путь к директории с файлами локализации изменён
	 *	
	 *	Это событие вызывается, когда `Config::lang_path` изменено методом `set_current()` или
	 *	`load_current()`.
	 *	
	 *	Параметры события:
	 *	- `const Config& new_config`: новый профиль конфигураций.
	 */
	EventBinder<const Config& /*new_config*/> on_changed_lang_path;
	
	/**
	 *	\~english
	 *	\brief The path to the directory with log files is changed
	 *	
	 *	This event is called when the `Config::log_path` is changed by `set_current()` or
	 *	`load_current()`.
	 *	
	 *	Event parameters:
	 *	- `const Config& new_config`: the new configuration profile.
	 *	
	 *	\~russian
	 *	\brief Путь к директории с файлами лога изменён
	 *	
	 *	Это событие вызывается, когда `Config::log_path` изменено методом `set_current()` или
	 *	`load_current()`.
	 *	
	 *	Параметры события:
	 *	- `const Config& new_config`: новый профиль конфигураций.
	 */
	EventBinder<const Config& /*new_config*/> on_changed_log_path;

	/**
	 *	\~english
	 *	\brief The path to the file with the initial configuration settings
	 *	
	 *	See the documentation of the `ConfigManager` class for more details.
	 *	
	 *	\~russian
	 *	\brief Путь к файлу с начальными настройками конфигураций
	 *	
	 *	Подробности можно найти в документации класса `ConfigManager`.
	 */
	const static String INIT_FILE;

	/**
	 *	\~english
	 *	\brief The default path to the directory where the configuration profile are stored
	 *	
	 *	If the initial configuration settings don't contain the path to the directory with
	 *	profiles, this value will be used.
	 *	
	 *	\~russian
	 *	\brief Путь к директории, где хранятся профили конфигураций
	 *	
	 *	Если начальные настройки конфигураций не содержат пути к директории с профилями, будет
	 *	использовано это значение.
	 */
	const static String DEFAULT_PATH;

	/**
	 *	\~english
	 *	\brief The name of the default configuration profile
	 *	
	 *	If the initial configuration settings don't containt the default profile name, this value
	 *	will be used.
	 *	
	 *	\~russian
	 *	\brief Название профиля конфигураций по умолчанию
	 *	
	 *	Если начальные настройки конфигураций не содержат названия профиля по умолчанию, будет
	 *	использовано это значение.
	 */
	const static String DEFAULT_CONFIG;

private:
	ConfigManager();

	String path_;
	Config current_;

	Event<const Config& /*new_config*/> on_changed_window_;
	Event<const Config& /*new_config*/> on_changed_res_check_period_sec_;
	Event<const Config& /*new_config*/> on_changed_res_path_;
	Event<const Config& /*new_config*/> on_changed_chunks_collision_size_;
	Event<const Config& /*new_config*/> on_changed_chunks_clickable_size_;
	Event<const Config& /*new_config*/> on_changed_lang_path_;
	Event<const Config& /*new_config*/> on_changed_log_path_;

	std::unique_ptr<Log> config_log_;
};

/**
 *	\}
 */

}
