    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ConfigManager.cpp           //
////////////////////////////////////////

#include "ConfigManager.h"

#include "../Util/Json/JsonObject.h"
#include "../Util/Json/Value.h"
#include "../Util/ResourceManager.h"
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

	// log

	// log category is the most important because it may be used by others	
	if (reload || config.log_path != old.log_path)
	{
		on_changed_log_path_.execute(config);
	}

	// window

	if (reload ||
		config.window_resolution != old.window_resolution ||
		config.window_fullscreen != old.window_fullscreen ||
		config.window_resize != old.window_resize ||
		config.window_titlebar != old.window_titlebar ||
		config.window_titlebar_buttons != old.window_titlebar_buttons ||
		config.window_title != old.window_title)
	{
		on_changed_window_.execute(config);
	}

	// res
	
	if (reload || config.res_check_period_sec != old.res_check_period_sec)
	{
		on_changed_res_check_period_sec_.execute(config);
	}
	if (reload || config.res_textures_path != old.res_textures_path ||
		reload || config.res_fonts_path != old.res_fonts_path ||
		reload || config.res_sounds_path != old.res_sounds_path)
	{
		on_changed_res_path_.execute(config);
	}

	// chunks

	if (reload || config.chunks_collision_size != old.chunks_collision_size)
	{
		on_changed_chunks_collision_size_.execute(config);
	}
	if (reload || config.chunks_clickable_size != old.chunks_clickable_size)
	{
		on_changed_chunks_clickable_size_.execute(config);
	}

	// lang

	if (reload || config.lang_path != old.lang_path)
	{
		on_changed_lang_path_.execute(config);
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

const String ConfigManager::INIT_FILE = L"config_init.json";
const String ConfigManager::DEFAULT_PATH = L"Config";
const String ConfigManager::DEFAULT_CONFIG = L"default";

		/* ConfigManager: private */

ConfigManager::ConfigManager() :
	path_(DEFAULT_PATH_),
	current_(Config::DEFAULT),
	on_changed_window_(),
	on_changed_window(on_changed_window_),
	on_changed_res_check_period_sec_(),
	on_changed_res_check_period_sec(on_changed_res_check_period_sec_),
	on_changed_res_path_(),
	on_changed_res_path(on_changed_res_path_),
	on_changed_chunks_collision_size_(),
	on_changed_chunks_collision_size(on_changed_chunks_collision_size_),
	on_changed_chunks_clickable_size_(),
	on_changed_chunks_clickable_size(on_changed_chunks_clickable_size_),
	on_changed_lang_path_(),
	on_changed_lang_path(on_changed_lang_path_),
	on_changed_log_path_(),
	on_changed_log_path(on_changed_log_path_)
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
