    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ResourceManager.cpp         //
////////////////////////////////////////

//      _         /====  -  -  -  -  -  -  -  - ==     ==  -  -  -  -  -  -  -  -  -  -  -  -    //
//     /_\        |                             | \   / |                   /=/==============\   //
//    (`v`)  W    |      \===    ===   |     |  |  \ /  |   ===/   \===    | |=  SnowEngine  =|  //
//     >-<   |    \===\  |   |  |   |  |     |  |   V   |  |   |   |   |   | |=   resource   =|  //
// ---/ * \--|        |  |   |  |   |  |  ^  |  |SnowMan|  |   |   |   |   | |=  management  =|  //
//   |  *  | |        |  |   |  |   |  | / \ |  |       |  |   |   |   |   | |=    system    =|  //
//    \___/  |    ====/  |   |   ===   ==   ==  |       |   ===\=  |   |    \=\==============/   //

#include "ResourceManager.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/System/String.hpp>

#include "Types/String.h"
#include "../Game/Game.h"
#include "../Game/Config.h"
#include "Time/TimerManager.h"
#include "Function/Delegate.h"

using namespace snow;

#define GET_RES(res_map, name)								\
	auto iter = (res_map).find((name).to_std_string());		\
	if (iter != (res_map).end())							\
	{														\
		auto ret = iter->second.lock();						\
		if (ret)											\
		{													\
			return ret;										\
		}													\
		else												\
		{													\
			(res_map).erase(iter);							\
		}													\
	}

		/* ResourceManager: public */

ResourceManager& ResourceManager::get_instance()
{
	static ResourceManager resource_manager;
	return resource_manager;
}

String ResourceManager::to_string() const
{
	return String::format(L"{ textures: %d, fonts: %d, sounds: %d }"_s,
			textures_.size(), fonts_.size(), sounds_.size());
}

int ResourceManager::hash_code() const noexcept
{
	int ret = 0;
	int sign = 1;
	for (const auto& i : textures_)
	{
		ret += sign * reinterpret_cast<int>(i.second.lock().get());
		sign = -sign;
	}
	return ret;
}

std::shared_ptr<sf::Texture> ResourceManager::get_texture(const String& name)
{
	GET_RES(textures_, name);
	std::shared_ptr<sf::Texture> res = std::make_shared<sf::Texture>();
	if (res->loadFromFile(sf::String((Game::config.res_textures_path + L'\\' + name).to_std_string()).toAnsiString()))
	{
		textures_.insert(std::make_pair(name.to_std_string(), res));
		return res;
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<sf::Font> ResourceManager::get_font(const String& name)
{
	GET_RES(fonts_, name);
	std::shared_ptr<sf::Font> res = std::make_shared<sf::Font>();
	if (res->loadFromFile(sf::String((Game::config.res_fonts_path + L'\\' + name).to_std_string()).toAnsiString()))
	{
		fonts_.insert(std::make_pair(name.to_std_string(), res));
		return res;
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<sf::SoundBuffer> ResourceManager::get_sound(const String& name)
{
	GET_RES(sounds_, name);
	std::shared_ptr<sf::SoundBuffer> res = std::make_shared<sf::SoundBuffer>();
	if (res->loadFromFile(sf::String((Game::config.res_sounds_path + L'\\' + name).to_std_string()).toAnsiString()))
	{
		sounds_.insert(std::make_pair(name.to_std_string(), res));
		return res;
	}
	else
	{
		return nullptr;
	}
}

		/* ResourceManager: private */

ResourceManager::ResourceManager() :
	textures_(),
	fonts_(),
	sounds_()
{
	Delegate<void> check_delegate;
	check_delegate.bind<ResourceManager>(*this, &ResourceManager::check_resources_);
	TimerManager::get_instance().create_timer(check_delegate, 300.f, 300.f);
}

void ResourceManager::check_resources_()
{
	for (auto i = textures_.begin(); i != textures_.end(); )
	{
		if (!i->second.lock())
		{
			textures_.erase(i);
		}
		else
		{
			i++;
		}
	}
	for (auto i = fonts_.begin(); i != fonts_.end(); )
	{
		if (!i->second.lock())
		{
			fonts_.erase(i);
		}
		else
		{
			i++;
		}
	}
	for (auto i = sounds_.begin(); i != sounds_.end(); )
	{
		if (!i->second.lock())
		{
			sounds_.erase(i);
		}
		else
		{
			i++;
		}
	}
}
