    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ResourceManager.h           //
////////////////////////////////////////

//      _         /====  -  -  -  -  -  -  -  - ==     ==  -  -  -  -  -  -  -  -  -  -  -  -    //
//     /_\        |                             | \   / |                   /=/==============\   //
//    (`v`)  W    |      \===    ===   |     |  |  \ /  |   ===/   \===    | |=  SnowEngine  =|  //
//     >-<   |    \===\  |   |  |   |  |     |  |   V   |  |   |   |   |   | |=   resource   =|  //
// ---/ * \--|        |  |   |  |   |  |  ^  |  |SnowMan|  |   |   |   |   | |=  management  =|  //
//   |  *  | |        |  |   |  |   |  | / \ |  |       |  |   |   |   |   | |=    system    =|  //
//    \___/  |    ====/  |   |   ===   ==   ==  |       |   ===\=  |   |    \=\==============/   //

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `ResourceManager` class
 *
 *	This file contains the definition of the `ResourceManager` class.
 *
 *	\~russian
 *	\brief Файл с классом `ResourceManager`
 *
 *	Этот файл содержит определение класса `ResourceManager`.
 */

#include "../Object.h"

#include <unordered_map>

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
 *	only one resource manager may exist. You can get it using `get_instance` static method. Use
 *	`config.ini` file to set directories of resource files. This class is designed for internal
 *	use.
 *
 *	\~russian
 *	\brief Класс диспетчера ресурсов SnowMan
 *
 *	Этот класс используется для управления ресурсами: текстурами, шрифтами и звуками. Он является
 *	одиночкой: может существовать только один диспетчер ресурсов. Вы можете получить его, используя
 *	статический метод `get_instance`. Используйте файл `config.ini`, чтобы установить директории
 *	файлов ресурсов. Этот класс предназначен для внутреннего использования.
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
	 *	Returns the string `{ textures: <n>, fonts: <n>, sounds: <n> }`, where `<n>` is the number
	 *	of resources being loaded at the moment.
	 *	\return The resultant string.
	 *
	 *	\~russian
	 *	\brief Конвертирует диспетчер ресурсов в строку
	 *
	 *	Возвращает строку `{ textures: <n>, fonts: <n>, sounds: <n> }`, где `<n>` — количество
	 *	ресурсов, загруженных в данный момент.
	 *	\return Полученная строка.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Hash code of the resource manager
	 *
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes.
	 *	\return Hash code of the object.
	 *
	 *	\~russian
	 *	\brief Хеш-код диспетчера ресурсов
	 *
	 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
	 *	также могут иметь одинаковые хеш-коды.
	 *	\return Хеш-код объекта.
	 */
	virtual int hash_code() const noexcept override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Get the texture
	 *	
	 *	Allows to get the texture. Loads it if necessary. The directory with texture files is
	 *	defined by config.ini file.
	 *	\param name The name of the texture (the path to the file relative to textures directory).
	 *	\return The pointer to the SFML texture.
	 *	
	 *	\~russian
	 *	\brief Получить текстуру
	 *	
	 *	Позволяет получить текстуру. Загружает её при необходимости. Директория с файлами текстур
	 *	определяется файлом config.ini.
	 *	\param name Имя текстуры (путь к файлу относительно директории текстур).
	 *	\return Указатель на текстуру SFML.
	 */
	std::shared_ptr<sf::Texture> get_texture(const String& name);

	/**
	 *	\~english
	 *	\brief Get the font
	 *
	 *	Allows to get the font. Loads it if necessary. The directory with font files is defined by
	 *	config.ini file.
	 *	\param name The name of the font (the path to the file relative to fonts directory).
	 *	\return The pointer to the SFML font.
	 *
	 *	\~russian
	 *	\brief Получить шрифт
	 *
	 *	Позволяет получить шрифт. Загружает его при необходимости. Директория с файлами шрифтов
	 *	определяется файлом config.ini.
	 *	\param name Имя шрифта (путь к файлу относительно директории шрифтов).
	 *	\return Указатель на шрифт SFML.
	 */
	std::shared_ptr<sf::Font> get_font(const String& name);

	/**
	 *	\~english
	 *	\brief Get the sound
	 *
	 *	Allows to get the sound. Loads it if necessary. The directory with sound files is defined
	 *	by config.ini file.
	 *	\param name The name of the sound (the path to the file relative to sounds directory).
	 *	\return The pointer to the SFML sound.
	 *
	 *	\~russian
	 *	\brief Получить звук
	 *
	 *	Позволяет получить звук. Загружает его при необходимости. Директория с файлами звуков
	 *	определяется файлом config.ini.
	 *	\param name Имя звука (путь к файлу относительно директории звуков).
	 *	\return Указатель на звук SFML.
	 */
	std::shared_ptr<sf::SoundBuffer> get_sound(const String& name);

private:
	ResourceManager();

	void check_resources_();

	std::unordered_map<std::wstring, std::weak_ptr<sf::Texture>> textures_;
	std::unordered_map<std::wstring, std::weak_ptr<sf::Font>> fonts_;
	std::unordered_map<std::wstring, std::weak_ptr<sf::SoundBuffer>> sounds_;
};

}
