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

const Config& ConfigManager::get_current() const
{
	return current_;
}

void ConfigManager::set_current(const Config& config)
{

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
	current_()
{}
