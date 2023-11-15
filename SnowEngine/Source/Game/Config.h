    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Config.h                    //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include <filesystem>

#include "../Math/Vector/Point2.h"
#include "../Util/String.h"

namespace snow
{

namespace json
{
class JsonObject;
}

class Log;

/**
 *	\defgroup Config Config
 *	\~english
 *	\brief Classes which control the game
 *	
 *	- `Game` is the main class of the game. It is singleton: only one instance of it can exist. You
 *	can access it via `Game::get_instance()`. Use the `Game::start()` method to launch the game.
 *	- `ConfigManager` is also singleton, you can access it via `ConfigManager::get_instance()`. The
 *	`ConfigManager` class allows you to control configuration profiles.
 *	- `Config` represents a configuration profile. It contains game settings and properties and can
 *	be applied via `ConfigManager::set_current()`.
 *	
 *	\~russian
 *	\brief Классы, контролирующие игру
 *	
 *	- `Game` — главный класс игры. Он является одиночкой: может существовать только один его
 *	экземпляр. Вы можете получить к нему доступ с помощью `Game::get_instance()`. Используйте метод
 *	`Game::start()`, чтобы запустить игру.
 *	- `ConfigManager` также является одиночкой, вы можете получить к нему доступ с помощью
 *	`ConfigManager::get_instance()`. Класс `ConfigManager` позволяет вам управлять профилями
 *	кофигураций.
 *	- `Config` представляет профиль конфигураций. Он содержит настройки и свойства игры и может
 *	быть применён с помощью `ConfigManager::set_current()`.
 */

/**
 *	\addtogroup Config
 *	\{
 */

/**
 *	\~english
 *	\brief The configuration profile
 *	
 *	The configuration profile contains the game settings and properties. Use the
 *	`ConfigManager::set_current()` method to apply the profile. This class allows to save
 *	(`Config::save()`) the profile to file and load (`Config::Config(const String&)`) it from file.
 *	The directory where the profiles are stored is defined by the `ConfigManager` class, see its
 *	documentation for more details. The path to the saved profile is `<config_path>/<name>.json`,
 *	where `<name>` is the name of the profile. It can contain `/` characters (then the file will
 *	be stored in the subdirectory). The file of the profile is a text file with JSON object, which
 *	contains JSON objects of configuration categories. Categories and their fields are listed in
 *	the table below. For more detailed descriptions see the documentation of the fields of the
 *	`Config` class.
 *	
 *	| Category | Field              | Type                  | Description                                                 | Default value                        | Field of the class                |
 *	| -------- | ------------------ | --------------------- | ----------------------------------------------------------- | ------------------------------------ | --------------------------------- |
 *	| `window` | `resolution`       | `Point2` (JSON array) | The game window resolution                                  | [800, 600]                           | `Config::window_resolution`       |
 *	| `window` | `fullscreen`       | Boolean               | Is the game window fullscreen                               | `false`                              | `Config::window_fullscreen`       |
 *	| `window` | `resize`           | Boolean               | Can the game window be resized                              | `true`                               | `Config::window_resize`           |
 *	| `window` | `titlebar`         | Boolean               | Does the game window have a titlebar                        | `true`                               | `Config::window_titlebar`         |
 *	| `window` | `titlebar_buttons` | Boolean               | Does the game window have a buttons on its titlebar         | `true`                               | `Config::window_titlebar_buttons` |
 *	| `window` | `title`            | String                | The title of the game window                                | `"The game (powered by SnowEngine)"` | `Config::window_title`            |
 *	| `res`    | `check_period_sec` | Double                | How often the resource manager will remove unused resources | 300.0                                | `Config::res_check_period_sec`    |
 *	| `res`    | `textures_path`    | String (path)         | The path to the directory with textures                     | `"Resources/Textures"`               | `Config::res_textures_path`       |
 *	| `res`    | `fonts_path`       | String (path)         | The path to the directory with fonts                        | `"Resources/Fonts"`                  | `Config::res_fonts_path`          |
 *	| `res`    | `sounds_path`      | String (path)         | The path to the directory with sounds                       | `"Resources/Sounds"`                 | `Config::res_sounds_path`         |
 *	| `res`    | `music_path`       | String (path)         | The path to the directory with music                        | `"Resources/Music"`                  | `Config::res_music_path`          |
 *	| `chunks` | `collision_size`   | `Point2` (JSON array) | The size of a collision chunk                               | [1500, 1500]                         | `Config::chunks_collision_size`   |
 *	| `chunks` | `clickable_size`   | `Point2` (JSON array) | The size of a clickable chunk                               | [500, 500]                           | `Config::chunks_clickable_size`   |
 *	| `lang`   | `path`             | String (path)         | The path to the directory with localization files           | `"Localization"`                     | `Config::lang_path`               |
 *	| `lang`   | `default_lang`     | String                | The code of the default language                            | `"en_UK"`                            | `Config::lang_default_lang`       |
 *	| `lang`   | `default_table`    | String                | The name of the default localization table                  | `"default"`                          | `Config::lang_default_table`      |
 *	| `log`    | `path`             | String (path)         | The path to the directory with log files                    | `"Logs"`                             | `Config::log_path`                |
 *	| `saves`  | `path`             | String (path)         | The path to the directory with game saves                   | `"Saves"`                            | `Config::saves_path`              |
 *	\sa
 *	- `ConfigManager`: allows to control and apply configuration profile
 *	
 *	\~russian
 *	\brief Профиль конфигураций
 *	
 *	Профиль конфигураций содержит настройки и свойства игры. Чтобы применить профиль, используйте
 *	метод `ConfigManager::set_current()`. Этот класс позволяет сохранять (`Config::save()`) профиль
 *	в файл и загружать (`Config::Config(const String&)`) его из файла. Директория, где хранятся
 *	профили, определяется классом `ConfigManager`, подробности можно найти в его документации. Путь
 *	к сохранённому профилю: `<config_path>/<name>.json`, где `<name>` — название профиля. Оно
 *	может содержать символы `/` (тогда файл будет сохранён в подпапке). Файл профиля — это
 *	текстовый файл с объектом JSON, содержащим JSON-объекты категорий конфигураций. В таблице ниже
 *	перечислены категории и содержащиеся в них поля. Более детальные описания можно найти в
 *	документации к полям класса `Config`.
 *	
 *	| Категория | Поле               | Тип                    | Описание                                                          | Значение по умолчанию                | Поле класса                       |
 *	| --------- | ------------------ | ---------------------- | ----------------------------------------------------------------- | ------------------------------------ | --------------------------------- |
 *	| `window`  | `resolution`       | `Point2` (массив JSON) | Разрешение окна игры                                              | [800, 600]                           | `Config::window_resolution`       |
 *	| `window`  | `fullscreen`       | Булев                  | Находится ли окно игры в полноэкранном режиме                     | `false`                              | `Config::window_fullscreen`       |
 *	| `window`  | `resize`           | Булев                  | Может ли у окна игры быть изменён размер                          | `true`                               | `Config::window_resize`           |
 *	| `window`  | `titlebar`         | Булев                  | Имеет ли окно игры строку с заголовком                            | `true`                               | `Config::window_titlebar`         |
 *	| `window`  | `titlebar_buttons` | Булев                  | Имеются ли у окна игры кнопки на строке с заголовком              | `true`                               | `Config::window_titlebar_buttons` |
 *	| `window`  | `title`            | Строка                 | Заголовок окна игры                                               | `"The game (powered by SnowEngine)"` | `Config::window_title`            |
 *	| `res`     | `check_period_sec` | Вещественный           | Как часто диспетчер ресурсов будет удалять неиспользуемые ресурсы | 300.0                                | `Config::res_check_period_sec`    |
 *	| `res`     | `textures_path`    | Строка (путь)          | Путь к директории с текстурами                                    | `"Resources/Textures"`               | `Config::res_textures_path`       |
 *	| `res`     | `fonts_path`       | Строка (путь)          | Путь к директории со шрифтами                                     | `"Resources/Fonts"`                  | `Config::res_fonts_path`          |
 *	| `res`     | `sounds_path`      | Строка (путь)          | Путь к директории со звуками                                      | `"Resources/Sounds"`                 | `Config::res_sounds_path`         |
 *	| `res`     | `music_path`       | String                 | Путь к директории с музыкой                                       | `"Resources/Music"`                  | `Config::res_music_path`          |
 *	| `chunks`  | `collision_size`   | `Point2` (массив JSON) | Размер чанка коллизии                                             | [1500, 1500]                         | `Config::chunks_collision_size`   |
 *	| `chunks`  | `clickable_size`   | `Point2` (массив JSON) | Размер чанка кликабельных компонентов                             | [500, 500]                           | `Config::chunks_clickable_size`   |
 *	| `lang`    | `path`             | Строка (путь)          | Путь к директории с файлами локализации                           | `"Localization"`                     | `Config::lang_path`               |
 *	| `lang`    | `default_lang`     | Строка                 | Код языка по умолчанию                                            | `"en_UK"`                            | `Config::lang_default_lang`       |
 *	| `lang`    | `default_table`    | Строка                 | Название таблицы локализации по умолчанию                         | `"default"`                          | `Config::lang_default_table`      |
 *	| `log`     | `path`             | Строка (путь)          | Путь к директории с файлами лога                                  | `"Logs"`                             | `Config::log_path`                |
 *	| `saves`   | `path`             | Строка (путь)          | Путь к директории с игровыми сохранениями                         | `"Saves"`                            | `Config::saves_path`              |
 *	\sa
 *	- `ConfigManager`: позволяет управлять профилями конфигураций и применять их
 */
class Config : public Object
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates a new profile with default values.
	 *	
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *	
	 *	Создаёт новый профиль со значениями по умолчанию.
	 */
	Config();

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *	
	 *	Creates a copy of the passed profile.
	 *	\param config The profile which will be copied.
	 *	
	 *	\~russian
	 *	\brief Конструктор копирования
	 *	
	 *	Создаёт копию переданного профиля.
	 *	\param config Профиль, который будет скопирован.
	 */
	Config(const Config& config);

	/**
	 *	\~english
	 *	\brief The move constructor
	 *	
	 *	Creates a new profile and moves into it the values from the passed one.
	 *	\param config The profile whose values will be moved.
	 *	
	 *	\~russian
	 *	\brief Конструктор перемещения
	 *	
	 *	Создаёт новый профиль и перемещает в него значения из переданного.
	 *	\param config Профиль, чьи значения будут перемещены.
	 */
	Config(Config&& config);

	/**
	 *	\~english
	 *	\brief Loads the profile from file
	 *	
	 *	Creates a new profile by loading its values from the file.
	 *	\param name The name of the saved profile.
	 *	\throw std::runtime_error The file with the profile does not exist or cannot be accessed.
	 *	\throw std::invalid_argument The file does not contain a valid JSON or the JSON doesn't
	 *	represent a configuration profile.
	 *	\sa
	 *	- `save()`: saves the profile to file
	 *	
	 *	\~russian
	 *	\brief Загружает профиль из файла
	 *	
	 *	Создаёт новый профиль, загружая его значения из файла.
	 *	\param name Имя сохранённого профиля.
	 *	\throw std::runtime_error Файл с профилем не существует или к нему не удаётся получить
	 *	доступ.
	 *	\throw std::invalid_argument Файл не содержит корректный JSON или JSON не представляет
	 *	собой профиль конфигураций.
	 *	\sa
	 *	- `save()`: сохраняет профиль в файл
	 */
	Config(const String& name);

	/**
	 *	\~english
	 *	\brief Creates a profile using JSON.
	 *	
	 *	Creates a new profile using the passed JSON.
	 *	\param json The JSON element with the profile values. It must be an object containing
	 *	other objects (see the documentation of `Config`).
	 *	\throw std::invalid_argument The passed JSON is not correct.
	 *	\sa
	 *	- `to_json()`: converts the profile to JSON
	 *	
	 *	\~russian
	 *	\brief Создаёт профиль с помощью JSON
	 *	
	 *	Создаёт новый профиль, используя переданный JSON.
	 *	\param json Элемент JSON со значениями профиля. Это должен быть объект, содержащий другие
	 *	объекты (см. документацию `Config`).
	 *	\throw std::invalid_argument Переданный JSON неправильный.
	 *	\sa
	 *	- `to_json()`: конвертирует профиль в JSON
	 */
	Config(std::shared_ptr<const json::Element> json);
	
			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the profile to string
	 *	
	 *	Creates a string with the JSON containing all values of the profile.
	 *	\return The string in JSON format.
	 *	
	 *	\~russian
	 *	\brief Конвертирует профиль в строку
	 *	
	 *	Создаёт строку с JSON, содержащим все значения профиля.
	 *	\return Строка в формате JSON.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Converts the profile to JSON
	 *	
	 *	Creates a JSON object containing all values of the profile. See the documentation of
	 *	`Config` for more details about what the JSON includes.
	 *	\return The JSON object.
	 *	\sa
	 *	- `Config(std::shared_ptr<const json::Element>)`: creates a profile from JSON
	 *	
	 *	\~russian
	 *	\brief Конвертирует профиль в JSON
	 *	
	 *	Создаёт объект JSON, содержащий все значения профиля. Подробности о том, что включает в
	 *	себя этот JSON, можно найти в документации класса `Config`.
	 *	\return Объект JSON.
	 *	\sa
	 *	- `Config(std::shared_ptr<const json::Element>)`: создаёт профиль из JSON
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;

			/* METHODS */
	
	/**
	 *	\~english
	 *	\brief Saves the profile to file
	 *	
	 *	Saves the profile values to the file in JSON format. See the documentation of `Config` for
	 *	more details about how the JSON looks.
	 *	\param name The name of the profile.
	 *	\param allow_override Defines what the method should do if the profile with the passed name
	 *	already exists. If `true`, the profile will be overriden; if `false`, an exception will be
	 *	thrown.
	 *	\throw std::runtime_error The file couldn't be created, accessed or overriden.
	 *	\sa
	 *	- `Config(const String&)`: loads the profile from file
	 *	
	 *	\~russian
	 *	\brief Сохраняет профиль в файл
	 *	
	 *	Сохраняет значения профиля в файл в формате JSON. Подробности о том, как выглядит этот
	 *	JSON, можно найти в документации класса `Config`.
	 *	\param name Название профиля.
	 *	\param allow_override Определяет, что должен делать метод, если профиль с переданным
	 *	названием уже существует. Если `true`, профиль будет перезаписан; если `false`, будет
	 *	выброшено исключение.
	 *	\throw std::runtime_error Файл не может быть создан, перезаписан или к нему не удаётся
	 *	получить доступ.
	 *	\sa
	 *	- `Config(const String&)`: загружает профиль из файла
	 */
	void save(const String& name, bool allow_override = false) const;

			/* FIELDS
				SECTION: window */
	
	/**
	 *	\~english
	 *	\brief The game window resolution
	 *	
	 *	The resolution of the game window. The default value is [800, 600].
	 *	
	 *	\~russian
	 *	\brief Разрешение окна игры
	 *	
	 *	Разрешение игрового окна. Значение по умолчанию — [800, 600].
	 */
	Point2 window_resolution;

	/**
	 *	\~english
	 *	\brief Is the game window fullscreen
	 *	
	 *	Is the game window in the fullscreen mode. The default value is `false`.
	 *	
	 *	\~russian
	 *	\brief Находится ли окно игры в полноэкранном режиме
	 *	
	 *	Находится ли игровое окно в полноэкранном режиме. Значение по умолчанию — `false`.
	 */
	bool window_fullscreen;

	/**
	 *	\~english
	 *	\brief Can the game window be resized
	 *	
	 *	If `true`, a user can resize the game window. Affects nothing in fullscreen mode. The
	 *	default value is `true`.
	 *	
	 *	\~russian
	 *	\brief Может ли у окна быть изменён размер
	 *	
	 *	Если `true`, пользователь может изменять размер игрового окна. Ни на что не влияет в
	 *	полноэкранном режиме. Значение по умолчанию — `true`.
	 */
	bool window_resize;

	/**
	 *	\~english
	 *	\brief Does the game window have a titlebar
	 *	
	 *	If `true`, the game window has a titlebar. Affects nothig in fullscreen mode. The value is
	 *	ignored if either `window_resize` or `window_titlebar_buttons` is `true`. The default value
	 *	is `true`.
	 *	
	 *	\~russian
	 *	\brief Имеет ли окно игры строку с заголовком
	 *	
	 *	Если `true`, игровое окно имеет строку с заголовком. Ни на что не влияет в полноэкранном
	 *	режиме. Значение игнорируется, если `window_resize` или `window_titlebar_buttons` имеет
	 *	значение `true`. Значение по умолчанию — `true`.
	 */
	bool window_titlebar;

	/**
	 *	\~english
	 *	\brief Does the game window have buttons on its titlebar
	 *	
	 *	If `true`, the game window has buttons on the titlebar (such as close button). Affects
	 *	nothing in fullscreen mode. The default value is `true`.
	 *	
	 *	\~russian
	 *	\brief Имеются ли у окна игры кнопки на строке с заголовком
	 *	
	 *	Если `true`, игровое окно имеет кнопки на строке с заголовком (такие как кнопка закрытия).
	 *	Ни на что не влияет в полноэкранном режиме. Значение по умолчанию — `true`.
	 */
	bool window_titlebar_buttons;

	/**
	 *	\~english
	 *	\brief The title of the game window
	 *	
	 *	The string which will be diplayed as a title of the game window. The default value is
	 *	`"The game (powered by SnowEngine)"`.
	 *	
	 *	\~russian
	 *	\brief Заголовок окна игры
	 *	
	 *	Строка, которая будет отображаться как заголовок игрового окна. Значение по умолчанию —
	 *	`"The game (powered by SnowEngine)"`.
	 */
	String window_title;

			/* FIELDS
				SECTION: res */

	/**
	 *	\~english
	 *	\brief How often the resource manager will remove unused resources
	 *	
	 *	The resource manager keeps pointers to all loaded resources in its maps. Sometimes the
	 *	manager checks the maps. If a pointer to an unused resource is found, the resource manager
	 *	removes it from the map. This field defines the time between these checks in seconds. The
	 *	default value is 300.
	 *	
	 *	\~russian
	 *	\brief Как часто диспетчер ресурсов будет удалять неиспользуемые ресурсы
	 *	
	 *	Диспетчер ресурсов хранит указатели на все загруженные ресурсы в своих словарях. Иногда
	 *	диспетчер проверяет эти словари. Если будет обнаружен указатель на неиспользуемый ресурс,
	 *	диспетчер ресурсов удалит его из словаря. Это поле определяет время между такими проверками
	 *	в секундах. Значение по умолчанию — 300.
	 */
	double res_check_period_sec;

	/**
	 *	\~english
	 *	\brief The path to the directory with textures
	 *	
	 *	The relative path to the directory where textures are stored. The default value is
	 *	`"Resources/Textures"`.
	 *	
	 *	\~russian
	 *	\brief Путь к директории с текстурами
	 *	
	 *	Относительный путь к директории, где хранятся текстуры. Значение по умолчанию —
	 *	`"Resources/Textures"`.
	 */
	Path res_textures_path;

	/**
	 *	\~english
	 *	\brief The path to the directory with fonts
	 *	
	 *	The relative path to the directory where fonts are stored. The default value is
	 *	`"Resources/Fonts"`.
	 *	
	 *	\~russian
	 *	\brief Путь к директории со шрифтами
	 *	
	 *	Относительный путь к директории, где хранятся шрифты. Значение по умолчанию —
	 *	`"Resources/Fonts"`.
	 */
	Path res_fonts_path;

	/**
	 *	\~english
	 *	\brief The path to the directory with sounds
	 *	
	 *	The relative path to the directory where sounds are stored. The default value is
	 *	`"Resources/Sounds"`.
	 *	
	 *	\~russian
	 *	\brief Путь к директории со звуками
	 *	
	 *	Относительный путь к директории, где хранятся звуки. Значение по умолчанию —
	 *	`"Resources/Sounds"`.
	 */
	Path res_sounds_path;

	/**
	 *	\~english
	 *	\brief The path to the directory with music
	 *	
	 *	The relative path to the directory where music is stored. The default value is
	 *	`"Resources/Music"`.
	 *	
	 *	\~russian
	 *	\brief Путь к директории с музыкой
	 *	
	 *	Относительный путь к директории, где хранится музыка. Значение по умолчанию —
	 *	`"Resources/Music"`.
	 */
	Path res_music_path;

			/* FIELDS
				SECTION: chunks */
	
	/**
	 *	\~english
	 *	\brief The size of a collision chunk
	 *	
	 *	To handle collisions the `CollisionComponent` uses collision chunks. This field defines
	 *	their size. For better performance the collision chunks should be bigger than any collision
	 *	component. But the bigger collision chunk is, the more components can be inside it and the
	 *	slower collision handling is performed. The default value is [1500, 1500].
	 *	\sa
	 *	- `CollisionComponent`
	 *	
	 *	\~russian
	 *	\brief Размер чанка коллизии
	 *	
	 *	Для обработки коллизий `CollisionComponent` использует чанки коллизии. Это поле определяет
	 *	их размеры. Для лучшей производительности чанк коллизии должен быть больше, чем любой
	 *	компонент-коллизия. Но чем больше размер чанка коллизии, тем больше компонентов может
	 *	находиться внутри него и тем медленнее происходит обработка коллизий. Значение по
	 *	умолчанию — [1500, 1500].
	 *	\sa
	 *	- `CollisionComponent`
	 */
	Point2 chunks_collision_size;
	
	/**
	 *	\~english
	 *	\brief The size of a clickable chunk
	 *	
	 *	To handle clicks the `ClickableComponent` uses clickable chunks. This field defines their
	 *	size. For better performance the clickable chunks should be bigger than any clickable
	 *	component. But the bigger clickable chunk is, the more components can be inside it and the
	 *	slower clicks handling is performed. The default value is [500, 500].
	 *	\sa
	 *	- `ClickableComponent`
	 *	
	 *	\~russian
	 *	\brief Размер чанка кликабельных компонентов
	 *	
	 *	Для обработки кликов `ClickableComponent` использует чанки. Это поле определяет их размеры.
	 *	Для лучшей производительности чанк кликабельных компонентов должен быть больше, чем любой
	 *	кликабельный компонент. Но чем больше размер чанка, тем больше компонентов может находиться
	 *	внутри него и тем медленнее происходит обработка кликов. Значение по умолчанию — [500,
	 *	500].
	 *	\sa
	 *	- `ClickableComponent`
	 */
	Point2 chunks_clickable_size;

			/* FIELDS
				SECTION: lang */
	
	/**
	 *	\~english
	 *	\brief The path to the directory with localization files
	 *	
	 *	The relative path to the directory where localization files are stored. The default value
	 *	is `"Localization"`.
	 *	\sa
	 *	- `LangManager`
	 *	
	 *	\~russian
	 *	\brief Путь к директории с файлами локализации
	 *	
	 *	Относительный путь к директории, где хранятся файлы локализации. Значение по умолчанию —
	 *	`"Localization"`.
	 *	\sa
	 *	- `LangManager`
	 */
	Path lang_path;

	/**
	 *	\~english
	 *	\brief The code of the default language
	 *	
	 *	The code of the language that should be loaded when the game is launched. The default value
	 *	is `"en_UK"`.
	 *	\sa
	 *	- `LangManager`
	 *	
	 *	\~russian
	 *	\brief Код языка по умолчанию
	 *	
	 *	Код языка, который должен быть загружен при запуске игры. Значение по умолчанию —
	 *	`"en_UK"`.
	 *	\sa
	 *	- `LangManager`
	 */
	String lang_default_lang;

	/**
	 *	\~english
	 *	\brief The name of the default localization table
	 *	
	 *	The name of the localization table that will be used as default. E. g. the default table is
	 *	used when no table is specified. The default value is `"default"`.
	 *	\sa
	 *	- `LangManager`
	 *	
	 *	\~russian
	 *	\brief Название таблицы локализации по умолчанию
	 *	
	 *	Название таблицы локализации, которая будет использоваться по умолчанию. Например, таблица
	 *	по умолчанию используется, когда не указана никакая таблица. Значени по умолчанию —
	 *	`"default"`.
	 *	\sa
	 *	- `LangManager`
	 */
	String lang_default_table;

			/* FIELDS
				SECTION: log */
	
	/**
	 *	\~english
	 *	\brief The path to the directory with log files
	 *	
	 *	The relative path to the directory where log files are stored. The default value is
	 *	`"Logs"`.
	 *	\sa
	 *	- `Log`
	 *	
	 *	\~russian
	 *	\brief Путь к директории с файлами лога
	 *	
	 *	Относительный путь к директории, где хранятся файлы лога. Значение по умолчанию — `"Logs"`.
	 *	\sa
	 *	- `Log`
	 */
	Path log_path;

			/* FIELDS
				SECTION: saves */

	
	/**
	 *	\~english
	 *	\brief The path to the directory with game saves
	 *	
	 *	The relative path to the directory where game save files are stored. The default value is
	 *	`"Logs"`.
	 *	
	 *	\~russian
	 *	\brief Путь к директории с игровыми сохранениями
	 *	
	 *	Относительный путь к директории, где хранятся файлы игровых сохранений. Значение по
	 *	умолчанию — `"Logs"`.
	 */
	Path saves_path;
	
			/* OPERATORS */

	/**
	 *	\~english
	 *	\brief The copy assignment operator
	 *	
	 *	Assigns the values of the passed profile to this one.
	 *	\param config The profile whose values will be copied.
	 *	
	 *	\~russian
	 *	\brief Оператор присваивания копированием
	 *	
	 *	Присваивает значения переданного профиля этому.
	 *	\param config Профиль, чьи значения будут скопированы.
	 */
	Config& operator=(const Config& config) = default;

	/**
	 *	\~english
	 *	\brief The move assignment operator
	 *	
	 *	Moves the values of the passed profile to this one.
	 *	\param config The profile whose values will be moved.
	 *	
	 *	\~russian
	 *	\brief Оператор присваивания перемещением
	 *	
	 *	Перемещает значения переданного профиля в этот.
	 *	\param config Профиль, чьи значения будут перемещены.
	 */
	Config& operator=(Config&& config) = default;

			/* CONSTANTS */

	/**
	 *	\~english
	 *	\brief The default profile
	 *	
	 *	The configuration profile with default values.
	 *	
	 *	\~russian
	 *	\brief Профиль по умолчанию
	 *	
	 *	Профиль конфигураций со значениями по умолчанию.
	*/
	static const Config DEFAULT;

private:
	std::mutex config_mtx_;
	static const String CONFIG_LOG_;
};

/**
 *	\}
 */

}
