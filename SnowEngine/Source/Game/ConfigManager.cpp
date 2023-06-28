    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ConfigManager.cpp           //
////////////////////////////////////////

#include "ConfigManager.h"

#include "../Util/Json/JsonObject.h"
#include "../Util/Json/Value.h"
#include "Game.h"

using namespace snow;

		/* ConfigManager: public */

ConfigManager& ConfigManager::get_instance()
{
	static ConfigManager config_manager;
	return config_manager;
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
		Game::get_instance().create_window_();
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
	path_(DEFAULT_PATH_),
	current_(Config::DEFAULT)
{
	std::shared_ptr<json::JsonObject> init_json =
		std::dynamic_pointer_cast<json::JsonObject>(json::Element::load(INIT_FILE_));
	if (!init_json)
	{
		// Error
	}

	std::shared_ptr<json::StringValue> path_json =
		std::dynamic_pointer_cast<json::StringValue>(init_json->get_content().at(L"path"_s));
	if (path_json)
	{
		path_ = path_json->get();
	}
	else
	{
		// Todo
	}

	std::shared_ptr<json::StringValue> default_json =
		std::dynamic_pointer_cast<json::StringValue>(init_json->get_content().at(L"default"_s));
	if (default_json)
	{
		set_current(Config(default_json->get()), true);
	}
	else
	{
		// Todo
	}
}

const String ConfigManager::INIT_FILE_ = L"config_init.json";

const String ConfigManager::DEFAULT_PATH_ = L"Config";
