    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ConfigManager.cpp           //
////////////////////////////////////////

#include "ConfigManager.h"

#include <filesystem>

#include "../Util/Log/LogManager.h"
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

String ConfigManager::to_string() const
{
	std::lock_guard<std::mutex> current_grd(current_mtx_);
	return current_.to_string();
}

std::shared_ptr<json::Element> ConfigManager::to_json() const
{
	std::shared_ptr<json::JsonObject> result = std::make_shared<json::JsonObject>();
	std::lock_guard<std::mutex> path_grd(path_mtx_);
	result->get_content().insert({ L"path", util::to_json(path_) });
	std::lock_guard<std::mutex> current_grd(current_mtx_);
	result->get_content().insert({ L"current", current_.to_json() });
	return result;
}

const Path& ConfigManager::get_path() const
{
	std::lock_guard<std::mutex> path_grd(path_mtx_);
	return path_;
}

void ConfigManager::set_path(const Path& path)
{
	std::lock_guard<std::mutex> path_grd(path_mtx_);
	path_ = path;
	std::filesystem::create_directories(path_);
}

const Config& ConfigManager::get_current() const
{
	std::lock_guard<std::mutex> current_grd(current_mtx_);
	return current_;
}

void ConfigManager::set_current(const Config& config, bool reload)
{
	Config old = current_;

	std::lock_guard<std::mutex> current_grd(current_mtx_);

	current_ = config;
	LOG_I(CONFIG_LOG_, L"A new configuration profile is being applied");

	// log category is the most important because it may be used by others	
	if (reload || !std::filesystem::equivalent(config.log_path, old.log_path))
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
	if (reload || !std::filesystem::equivalent(config.res_textures_path, old.res_textures_path) ||
		reload || !std::filesystem::equivalent(config.res_fonts_path, old.res_fonts_path) ||
		reload || !std::filesystem::equivalent(config.res_sounds_path, old.res_sounds_path))
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

	if (reload || !std::filesystem::equivalent(config.lang_path, old.lang_path))
	{
		on_changed_lang_path_.execute(config);
	}
	if (reload || config.lang_default_table != old.lang_default_table)
	{
		on_changed_lang_default_table_.execute(config);
	}
}

void ConfigManager::save_current(const String& name, bool allow_override) const
{
	std::lock_guard<std::mutex> current_grd(current_mtx_);
	current_.save(name, allow_override);
}

Config& ConfigManager::load_current(const String& name)
{
	std::lock_guard<std::mutex> current_grd(current_mtx_);
	set_current(Config(name));
	return current_;
}

const Path ConfigManager::INIT_FILE = L"config_init.json";
const Path ConfigManager::DEFAULT_PATH = L"Config";
const String ConfigManager::DEFAULT_CONFIG = L"default";

		/* ConfigManager: private */

ConfigManager::ConfigManager() :
	path_(DEFAULT_PATH),
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
	on_changed_lang_default_table_(),
	on_changed_lang_default_table(on_changed_lang_default_table_),
	on_changed_log_path_(),
	on_changed_log_path(on_changed_log_path_),
	path_mtx_(),
	current_mtx_()
{
	LogManager::get_instance(); // We just need to create a log manager

	std::shared_ptr<json::JsonObject> init_json;
	Path path = DEFAULT_PATH;
	String default_config = DEFAULT_CONFIG;
	bool recreate_file_flag = false;
	
	try
	{
		init_json = std::dynamic_pointer_cast<json::JsonObject>(json::Element::load(INIT_FILE));
	}
	catch (const std::runtime_error& e)
	{
		LOG_E(CONFIG_LOG_, L"Couldn't open the initial configuration file. The file will be created with default values");
		recreate_file_flag = true;
	}
	catch (const std::invalid_argument& e)
	{
		LOG_E(CONFIG_LOG_, L"The initial configuration file does not contain a valid JSON. The file will be recreated with default values");
		recreate_file_flag = true;
	}

	if (init_json)
	{
		try
		{
			path = util::json_to_path(init_json->get_content().at(L"path"));
		}
		catch (const std::out_of_range& e)
		{
			LOG_E(CONFIG_LOG_, L"The initial configuration file does not contain a \"path\" field. The file will be recreated with the default path value");
			recreate_file_flag = true;
		}
		catch (const std::invalid_argument& e)
		{
			LOG_E(CONFIG_LOG_, L"The \"path\" field in the initial configuration file is not a string. The file will be recreated with the default path value");
			recreate_file_flag = true;
		}

		try
		{
			default_config = util::json_to_string(init_json->get_content().at(L"default"));
		}
		catch (const std::out_of_range& e)
		{
			LOG_E(CONFIG_LOG_, L"The initial configuration file does not contain a \"default\" field. The file will be recreated with the default value");
			recreate_file_flag = true;
		}
		catch (const std::invalid_argument& e)
		{
			LOG_E(CONFIG_LOG_, L"The \"default\" field in the initial configuration file is not a string. The file will be recreated with the default value");
			recreate_file_flag = true;
		}
	}

	set_path(path);
	set_current(Config(default_config));

	if (recreate_file_flag)
	{
		init_json = std::make_shared<json::JsonObject>();
		init_json->get_content().insert({ L"path", std::make_shared<json::StringValue>(get_path()) });
		init_json->get_content().insert({ L"default", std::make_shared<json::StringValue>(default_config) });
		try
		{
			init_json->save(INIT_FILE);
			LOG_I(CONFIG_LOG_, L"The initial configuration has been created or recreated");
		}
		catch (const std::runtime_error& e)
		{
			LOG_E(CONFIG_LOG_, L"Couldn't create or recreate the initial configuration file");
		}
	}
}

const String ConfigManager::CONFIG_LOG_ = L"Config";
