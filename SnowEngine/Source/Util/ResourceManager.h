    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ResourceManager.h           //
////////////////////////////////////////

#pragma once

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

class ResourceManager : public Object
{
public:
			/* SINGLETON */

	static ResourceManager& get_instance();

			/* METHODS FROM Object */

	virtual String to_string() const override;

	virtual int hash_code() const noexcept override;

			/* METHODS */

	std::shared_ptr<sf::Texture> get_texture(const String& name);
	std::shared_ptr<sf::Font> get_font(const String& name);
	std::shared_ptr<sf::SoundBuffer> get_sound(const String& name);
	std::shared_ptr<sf::Music> get_music(const String& name);

private:
	ResourceManager();

	void check_resources_();

	std::unordered_map<std::wstring, std::weak_ptr<sf::Texture>> textures_;
	std::unordered_map<std::wstring, std::weak_ptr<sf::Font>> fonts_;
	std::unordered_map<std::wstring, std::weak_ptr<sf::SoundBuffer>> sounds_;
	std::unordered_map<std::wstring, std::weak_ptr<sf::Music>> music_;
};

}
