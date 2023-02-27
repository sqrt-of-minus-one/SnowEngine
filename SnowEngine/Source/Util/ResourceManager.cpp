    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ResourceManager.cpp         //
////////////////////////////////////////

//      _         /====  -  -  -  -  -  -  -  - ==     ==  -  -  -  -  -  -  -  -  -  -  -  -    //
//     /_\  \|/   |                             | \   / |                   /=/==============\   //
//    (`v`)  W    |      \===    ===   |     |  |  \ /  |   ===/   \===    | |=  SnowEngine  =|  //
//     >-<   |    \===\  |   |  |   |  |     |  |   V   |  |   |   |   |   | |=   resource   =|  //
// ---/ * \--|        |  |   |  |   |  |  ^  |  |SnowMan|  |   |   |   |   | |=  management  =|  //
//   |  *  | |        |  |   |  |   |  | / \ |  |       |  |   |   |   |   | |=    system    =|  //
//    \___/  |    ====/  |   |   ===   ==   ==  |       |   ===\=  |   |    \=\==============/   //

#include "ResourceManager.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/String.hpp>

#include <algorithm>

#include "Types/String.h"
#include "Util.h"
#include "../Game/Game.h"
#include "../Game/Config.h"
#include "Time/TimerManager.h"
#include "Function/Delegate.h"

using namespace snow;

// If res_map contains non-null resource with the specified name, returns it. If the resource is
// null, erases it.
#define GET_RES(res_map, name)								\
	std::lock_guard<std::mutex> res_grd(res_mtx_());		\
	auto iter = (res_map).find((name).to_std_string());		\
	if (iter != (res_map).end())							\
	{														\
		auto ret = iter->second.lock();						\
		if (ret)											\
		{													\
			return ret;										\
		}													\
		(res_map).erase(iter);								\
	}

// Load the resource of type t with the specified name from file (res_path) and store it in the res_map
// Returns the loaded resource of nullptr if the resource wasn't loaded
#define LOAD_RES(t, res_path, res_map, name)															\
	res_log_.d(L"Resource "_s + name + L" has been loaded");											\
	std::shared_ptr<t> res = std::make_shared<t>();														\
	if (res->loadFromFile(sf::String(((res_path) + L'\\' + (name)).to_std_string()).toAnsiString()))	\
	{																									\
		(res_map).insert(std::make_pair((name).to_std_string(), res));									\
		return res;																						\
	}																									\
	return nullptr;

		/* ResourceManager: public */

ResourceManager& ResourceManager::get_instance()
{
	static ResourceManager resource_manager;
	return resource_manager;
}

String ResourceManager::to_string() const
{
	std::lock_guard<std::mutex> res_grd(res_mtx_());
	return String::format(L"{ textures: %d, fonts: %d, sounds: %d }"_s,
			textures_.size(), fonts_.size(), sounds_.size());
}

int ResourceManager::hash_code() const noexcept
{
	int ret = 0;
	int sign = 1;
	std::lock_guard<std::mutex> res_grd(res_mtx_());
	for (const auto& i : textures_)
	{
		ret += sign * reinterpret_cast<int>(i.second.lock().get());
		sign = -sign;
	}
	for (const auto& i : fonts_)
	{
		ret += sign * reinterpret_cast<int>(i.second.lock().get());
		sign = -sign;
	}
	for (const auto& i : sounds_)
	{
		ret += sign * reinterpret_cast<int>(i.second.lock().get());
		sign = -sign;
	}
	return ret;
}

std::shared_ptr<sf::Texture> ResourceManager::get_texture(const String& name)
{
	GET_RES(textures_, name);
	LOAD_RES(sf::Texture, Game::config.res_textures_path, textures_, name);
}

std::shared_ptr<sf::Font> ResourceManager::get_font(const String& name)
{
	GET_RES(fonts_, name);
	LOAD_RES(sf::Font, Game::config.res_fonts_path, fonts_, name);
}

std::shared_ptr<sf::SoundBuffer> ResourceManager::get_sound(const String& name)
{
	GET_RES(sounds_, name);
	LOAD_RES(sf::SoundBuffer, Game::config.res_sounds_path, sounds_, name);
}

		/* ResourceManager: private */

ResourceManager::ResourceManager() :
	textures_(),
	fonts_(),
	sounds_(),
	res_log_(L"SnowMan"_s)
{
	res_log_.i(L"The resource manager is created"_s);

	// Set timer to call check_resources_ method
	Delegate<void> check_delegate;
	check_delegate.bind<ResourceManager>(*this, &ResourceManager::check_resources_);
	TimerManager::get_instance().create_timer(check_delegate, Game::config.res_check_period_sec, Game::config.res_check_period_sec);
}

void ResourceManager::check_resources_()
{
	int resources_erased = 0;

	// Maybe one day SnowEngine will use C++20:
	// 
	// resources_erased += std::erase_if(textures_, [](const auto& item) { return !item.second.lock(); });
	// resources_erased += std::erase_if(fonts_, [](const auto& item) { return !item.second.lock(); });
	// resources_erased += std::erase_if(sounds_, [](const auto& item) { return !item.second.lock(); });
	// 
	// But in C++17 instead of three lines we need a lot of them:

	std::lock_guard<std::mutex> res_grd(res_mtx_());
	for (auto i = textures_.begin(); i != textures_.end(); )
	{
		if (!i->second.lock())
		{
			textures_.erase(i);
			resources_erased++;
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
			resources_erased++;
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
			resources_erased++;
		}
		else
		{
			i++;
		}
	}

	// We don't have to check if debug mode is enabled, but it should work a little faster with this check
	if (Log::is_debug_mode_enabled() && resources_erased > 0)
	{
		res_log_.d(String::format(L"%d unloaded resource(s) have been erased"_s, resources_erased));
	}
}

std::mutex& ResourceManager::res_mtx_() noexcept
{
	static std::mutex res_mtx;
	return res_mtx;
}
