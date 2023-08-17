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
#include "../Game/ConfigManager.h"
#include "Time/TimerManager.h"
#include "Time/Timer.h"
#include "Function/Delegate.h"

using namespace snow;

// If res_map contains non-null resource with the specified name, returns it. If the resource is
// null, erases it.
#define GET_RES_(res_map, name)								\
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

// Loads the resource of type t with the specified name from file (res_path) and store it in the res_map
// Returns the loaded resource or nullptr if the resource wasn't loaded
#define LOAD_RES_(t, res_path, res_map, name)															\
	std::shared_ptr<t> res = std::make_shared<t>();														\
	if (res->loadFromFile(sf::String(((res_path) + L'\\' + (name)).to_std_string()).toAnsiString()))	\
	{																									\
		res_log_.d(L"Resource "_s + name + L" has been loaded");										\
		(res_map).insert(std::make_pair((name).to_std_string(), res));									\
		return res;																						\
	}																									\
	res_log_.w(L"Couldn't load resource "_s + name);													\
	return nullptr;

// Checks the map and removes unused resources
#define CHECK_RES_(res_map)									\
for (auto i = (res_map).begin(); i != (res_map).end(); )	\
{															\
	if (!i->second.lock())									\
	{														\
		(res_map).erase(i);									\
		resources_erased++;									\
	}														\
	else													\
	{														\
		i++;												\
	}														\
}

// Reloads every resource from res_map. Removes it if reloading failed
#define RELOAD_RES_(res_map, res_path)
for (auto i = (res_map).begin(); i != (res_map).end(); )
	{
		auto p = i->second.lock();
		if (p && p->loadFromFile(sf::String(((res_path) + L'\\' + i->first).to_std_string()).toAnsiString()))
		{
			resources_reloaded++;
			i++;
		}
		else
		{
			textures_.erase(i);
			resources_erased++;
		}
	}

		/* ResourceManager: public */

ResourceManager& ResourceManager::get_instance()
{
	static ResourceManager resource_manager;
	return resource_manager;
}

String ResourceManager::to_string() const
{
	return String::format(L"ResourceManager, loaded textures: %d, fonts: %d, sounds: %d"_s,
		textures_.size(), fonts_.size(), sounds_.size());
}

std::shared_ptr<json::Element> ResourceManager::to_json() const
{
	std::shared_ptr<json::JsonObject> object = std::make_shared<json::JsonObject>();
	object->get_content().insert({ L"textures"_s, util::to_json(textures_.size()) });
	object->get_content().insert({ L"fonts"_s, util::to_json(fonts_.size()) });
	object->get_content().insert({ L"sounds"_s, util::to_json(sounds_.size()) });
	return object;
}

std::shared_ptr<sf::Texture> ResourceManager::get_texture(const String& name)
{
	GET_RES_(textures_, name);
	LOAD_RES_(sf::Texture, CURRENT_CONFIG.res_textures_path, textures_, name);
}

std::shared_ptr<sf::Font> ResourceManager::get_font(const String& name)
{
	GET_RES_(fonts_, name);
	LOAD_RES_(sf::Font, CURRENT_CONFIG.res_fonts_path, fonts_, name);
}

std::shared_ptr<sf::SoundBuffer> ResourceManager::get_sound(const String& name)
{
	GET_RES_(sounds_, name);
	LOAD_RES_(sf::SoundBuffer, CURRENT_CONFIG.res_sounds_path, sounds_, name);
}

		/* ResourceManager: private */

ResourceManager::ResourceManager() :
	textures_(),
	fonts_(),
	sounds_(),
	check_timer_(),
	res_log_(L"SnowMan"_s)
{
	res_log_.i(L"The resource manager is created"_s);

	ConfigManager::get_instance().on_changed_res_check_period_sec.bind<ResourceManager>(*this, &ResourceManager::update_check_timer_);
	ConfigManager::get_instance().on_changed_res_path<ResourceManager>(*this, &ResourceManager::update_res_path_);

	// Set timer to call check_resources_ method
	Delegate<void> check_delegate;
	check_delegate.bind<ResourceManager>(*this, &ResourceManager::check_resources_);
	check_timer_ = TimerManager::get_instance().create_timer(check_delegate, ConfigManager::get_instance().get_current(), Game::config.res_check_period_sec);
}

void ResourceManager::update_check_timer_(const Config& new_config)
{
	check_timer_->set_period_sec(new_config.res_check_period_sec);
}

void ResourceManager::update_res_path_(const Config& new_config)
{
	int resources_erased = 0, resources_reloaded = 0;

	std::lock_guard<std::mutex> res_grd(res_mtx_());
	RELOAD_RES_(textures_, new_config.res_textures_path);
	RELOAD_RES_(fonts_, new_config.res_fonts_path);
	RELOAD_RES_(sounds_, new_config.res_sounds_path);

	res_log_.d(L"Resources were reloaded ("_s + util::to_string(resources_reloaded) + L" reloaded, " + util::to_string(resourced_erased) + L" erased)");
}

void ResourceManager::check_resources_()
{
	int resources_erased = 0;

	// #CPP20
	// Maybe one day SnowEngine will use C++20:
	// 
	// resources_erased += std::erase_if(textures_, [](const auto& item) { return !item.second.lock(); });
	// resources_erased += std::erase_if(fonts_, [](const auto& item) { return !item.second.lock(); });
	// resources_erased += std::erase_if(sounds_, [](const auto& item) { return !item.second.lock(); });
	// 
	// But in C++17 instead of three lines we need a lot of them:

	std::lock_guard<std::mutex> res_grd(res_mtx_());
	CHECK_RES_(textures_);
	CHECK_RES_(fonts_);
	CHECK_RES_(sounds_);

	if (resources_erased > 0)
	{
		res_log_.d(util::to_string(resources_erased) + L" unloaded resource(s) have been erased");
	}
}

std::mutex& ResourceManager::res_mtx_() noexcept
{
	static std::mutex res_mtx;
	return res_mtx;
}
