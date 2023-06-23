    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ConfigManager.cpp           //
////////////////////////////////////////

#include "ConfigManager.h"

using namespace snow;

		/* ConfigManager: public */

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

	if (config.window_resolution != old.window_resolution ||
		config.window_fullscreen != old.window_fullscreen ||
		config.window_resize != old.window_resize ||
		config.window_titlebar != old.window_titlebar ||
		config.window_titlebar_buttons != old.window_titlebar_buttons ||
		config.window_title != old.window_title ||
		reload)
	{
		// Todo
	}

	// res
	
	if (config.res_check_period_sec != old.res_check_period_sec || reload)
	{
		// Todo
	}
	if (config.res_textures_path != old.res_textures_path || reload)
	{
		// Todo
	}
	if (config.res_fonts_path != old.res_fonts_path || reload)
	{
		// Todo
	}
	if (config.res_sounds_path != old.res_sounds_path || reload)
	{
		// Todo
	}
	if (config.res_music_path != old.res_music_path || reload)
	{
		// Todo
	}

	// chunks

	if (config.chunks_collision_size != old.chunks_collision_size || reload)
	{
		// Todo
	}
	if (config.chunks_clickable_size != old.chunks_clickable_size || reload)
	{
		// Todo
	}

	// lang

	if (config.lang_path != old.lang_path || reload)
	{
		// Todo
	}

	// log
	
	if (config.log_path != old.log_path || reload)
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
	set_current(Config::load(name));
	return current_;
}

		/* ConfigManager: private */

ConfigManager::ConfigManager() :
	path_(DEFAULT_PATH_),
	current_(Config::DEFAULT)
{}

const String ConfigManager::DEFAULT_PATH_ = L"Config";
