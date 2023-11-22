    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ResourceManager.h           //
////////////////////////////////////////

//      _         /====  -  -  -  -  -  -  -  - ==     ==  -  -  -  -  -  -  -  -  -  -  -  -    //
//     /_\  \|/   |                             | \   / |                   /=/==============\   //
//    (`v`)  W    |      \===    ===   |     |  |  \ /  |   ===/   \===    | |=  SnowEngine  =|  //
//     >-<   |    \===\  |   |  |   |  |     |  |   V   |  |   |   |   |   | |=   resource   =|  //
// ---/ * \--|        |  |   |  |   |  |  ^  |  |SnowMan|  |   |   |   |   | |=  management  =|  //
//   |  *  | |        |  |   |  |   |  | / \ |  |       |  |   |   |   |   | |=    system    =|  //
//    \___/  |    ====/  |   |   ===   ==   ==  |       |   ===\=  |   |    \=\==============/   //

#pragma once

#include "../Object.h"

#include <unordered_map>
#include <mutex>

namespace sf
{
class Texture;
class Font;
class SoundBuffer;
class Music;
}

namespace snow
{

/**
 *	\~english
 *	\brief The class of the SnowMan resource manager
 *
 *	This class is used to manage resourced such as textures, fonts and sounds. It is singleton,
 *	only one resource manager may exist. You can get it using `get_instance` static method. The
 *	directories of resource files are defined by the current configuration (see `Config`).
 *	\warning This class is designed for internal use. Do not use it in your project directly.
 *
 *	\~russian
 *	\brief Класс диспетчера ресурсов SnowMan
 *
 *	Этот класс используется для управления ресурсами: текстурами, шрифтами и звуками. Он является
 *	одиночкой: может существовать только один диспетчер ресурсов. Вы можете получить его, используя
 *	статический метод `get_instance`. Директории файлов ресурсов определяются текущей конфигурацией
 *	(см. `Config`).
 *	\warning Этот класс предназначен для внутреннего использования. Не используйте его
 *	непосредственно в своём проекте.
 */
class ResourceManager : public Object
{
public:
			/* SINGLETON */
			
	/**
	 *	\~english
	 *	\brief The only instance of the resource manager
	 *	
	 *	Allows to get the only instance of the resource manager.
	 *	\return The resource manager.
	 *	
	 *	\~russian
	 *	\brief Единственный экземпляр диспетчера ресурсов
	 *	
	 *	Позволяет получить единственный экземпляр диспетчера ресурсов.
	 *	\return Диспетчер ресурсов.
	 */
	static ResourceManager& get_instance();

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the resource manager to string
	 *	
	 *	Returns the string `"ResourceManager, loaded textures: <t>, fonts: <f>, sounds: <s>"`,
	 *	where `<t>`, `<f>`, and `<s>` is the amount of texture, font, and sound resources
	 *	respectively which are currently loaded (why on Earth would anyone need this?).
	 *	\return The string with the information about the resource manager.
	 *	
	 *	\~russian
	 *	\brief Конвертирует диспетчер ресурсов в строку
	 *	
	 *	Возвращает строку `"ResourceManager, loaded textures: <t>, fonts: <f>, sounds: <s>"`, где
	 *	`<t>`, `<f>` и `<s>` — соответственно количество текстур, шрифтов и звуков, загруженных в
	 *	данный момент (кому вообще это может понадобиться?).
	 *	\return Строка с информацией о диспетчере ресурсов.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Creates a JSON object with the resouce manager data
	 *	
	 *	Creates a JSON object containing three integer values:
	 *	- `textures`: the amount of currently loaded texture resources;
	 *	- `fonts`: the amount of currently loaded font resources;
	 *	- `sounds`: the anount of currently loaded sound resources.
	 *	\return The JSON object.
	 *	
	 *	\~russian
	 *	\brief Создаёт объект JSON с информацией о диспетчере ресурсов
	 *	
	 *	Создаёт объект JSON, содержащий три целочисленных значения:
	 *	- `textures`: количество загруженных в данный момент текстур;
	 *	- `fonts`: количество загруженных в данный момент шрифтов;
	 *	- `sounds`: количество загруженных в данный момент звуков.
	 *	\return Объект JSON.
	*/
	virtual std::shared_ptr<json::Element> to_json() const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Get the texture
	 *	
	 *	Allows to get the texture. Loads it if necessary. The directory with texture files is
	 *	defined by the current configuration.
	 *	\param name The name of the texture (the path to the file relative to textures directory).
	 *	\return The pointer to the SFML texture.
	 *	
	 *	\~russian
	 *	\brief Получить текстуру
	 *	
	 *	Позволяет получить текстуру. Загружает её при необходимости. Директория с файлами текстур
	 *	определяется текущей конфигурацией.
	 *	\param name Имя текстуры (путь к файлу относительно директории текстур).
	 *	\return Указатель на текстуру SFML.
	 */
	std::shared_ptr<sf::Texture> get_texture(const String& name);

	/**
	 *	\~english
	 *	\brief Get the font
	 *
	 *	Allows to get the font. Loads it if necessary. The directory with font files is defined by
	 *	the current configuration.
	 *	\param name The name of the font (the path to the file relative to fonts directory).
	 *	\return The pointer to the SFML font.
	 *
	 *	\~russian
	 *	\brief Получить шрифт
	 *
	 *	Позволяет получить шрифт. Загружает его при необходимости. Директория с файлами шрифтов
	 *	определяется текущей конфигурацией.
	 *	\param name Имя шрифта (путь к файлу относительно директории шрифтов).
	 *	\return Указатель на шрифт SFML.
	 */
	std::shared_ptr<sf::Font> get_font(const String& name);

	/**
	 *	\~english
	 *	\brief Get the sound
	 *
	 *	Allows to get the sound. Loads it if necessary. The directory with sound files is defined
	 *	by the current configuration.
	 *	\param name The name of the sound (the path to the file relative to sounds directory).
	 *	\return The pointer to the SFML sound.
	 *
	 *	\~russian
	 *	\brief Получить звук
	 *
	 *	Позволяет получить звук. Загружает его при необходимости. Директория с файлами звуков
	 *	определяется текущей конфигурацией.
	 *	\param name Имя звука (путь к файлу относительно директории звуков).
	 *	\return Указатель на звук SFML.
	 */
	std::shared_ptr<sf::SoundBuffer> get_sound(const String& name);

private:
	ResourceManager();

	void check_resources_();
	void update_check_timer_(const Config& new_config);
	void update_res_path_(const Config& new_config);

	std::unordered_map<String, std::weak_ptr<sf::Texture>> textures_;
	std::unordered_map<String, std::weak_ptr<sf::Font>> fonts_;
	std::unordered_map<String, std::weak_ptr<sf::SoundBuffer>> sounds_;
	// Music is loaded from file directly, without resource manager

	std::shared_ptr<Timer> check_timer_;

	std::mutex res_mtx_;
	static const String RESOURCE_LOG_;
};

}
