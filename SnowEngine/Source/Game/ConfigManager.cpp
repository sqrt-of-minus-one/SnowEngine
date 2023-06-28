    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ConfigManager.cpp           //
////////////////////////////////////////

#include "ConfigManager.h"

#include "../Util/Json/JsonObject.h"

using namespace snow;

		/* ConfigManager: public */

void ConfigManager::initialize()
{
	if (is_initialized_)
	{
		// Log
		return;
	}

	std::shared_ptr<json::JsonObject> init_json =
		std::dynamic_pointer_cast<json::JsonObject>(json::Element::load(INIT_FILE_));
	if (!init_json)
	{
		// Error
	}

}

ConfigManager& ConfigManager::get_instance()
{
	static ConfigManager config_manager;
	return config_manager;
}

String ConfigManager::to_string() const
{
	return current_.to_string();
}

int ConfigManager::hash_code() const noexcept
{
	return current_.hash_code();
}

const String& ConfigManager::get_path() const
{
	return path_;
}

void ConfigManager::set_path(const String& path)
{
	path_ = path;
}

const Config& ConfigManager::get_current() const
{
	return current_;
}

void ConfigManager::set_current(const Config& config, bool reload)
{
	Config old = current_;
	current_ = config;

	// window

	if (reload ||
		config.window_resolution != old.window_resolution ||
		config.window_fullscreen != old.window_fullscreen ||
		config.window_resize != old.window_resize ||
		config.window_titlebar != old.window_titlebar ||
		config.window_titlebar_buttons != old.window_titlebar_buttons ||
		config.window_title != old.window_title)
	{
		// Todo
	}

	// res
	
	if (reload || config.res_check_period_sec != old.res_check_period_sec)
	{
		// Todo
	}
	if (reload || config.res_textures_path != old.res_textures_path)
	{
		// Todo
	}
	if (reload || config.res_fonts_path != old.res_fonts_path)
	{
		// Todo
	}
	if (reload || config.res_sounds_path != old.res_sounds_path)
	{
		// Todo
	}
	if (reload || config.res_music_path != old.res_music_path)
	{
		// Todo
	}

	// chunks

	if (reload || config.chunks_collision_size != old.chunks_collision_size)
	{
		// Todo
	}
	if (reload || config.chunks_clickable_size != old.chunks_clickable_size)
	{
		// Todo
	}

	// lang

	if (reload || config.lang_path != old.lang_path)
	{
		// Todo
	}

	// log
	
	if (reload || config.log_path != old.log_path)
	{
		// Todo
	}
}

void ConfigManager::save_current(const String& name, bool allow_override)
{
	current_.save(name, allow_override);
}

Config& ConfigManager::load_current(const String& name)
{
	set_current(Config(name));
	return current_;
}

		/* ConfigManager: private */

ConfigManager::ConfigManager() :
	is_initialized_(false),
	path_(DEFAULT_PATH_),
	current_(Config::DEFAULT)
{}

const String ConfigManager::INIT_FILE_ = L"config_init.json";

const String ConfigManager::DEFAULT_PATH_ = L"Config";
