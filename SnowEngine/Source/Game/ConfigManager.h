    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ConfigManager.h             //
////////////////////////////////////////

#pragma once

#include "Config.h"
#include "../Util/Function/EventBinder.h"

#define CURRENT_CONFIG snow::ConfigManager::get_instance().get_current()

namespace snow
{

class ConfigManager
{
public:
			/* SINGLETON */

	static ConfigManager& get_instance();

			/* METHODS */

	const String& get_path() const;
	void set_path(const String& path);

	const Config& get_current() const;
	void set_current(const Config& config, bool reload = false);

	void save_current(const String& name, bool allow_override = false);
	Config& load_current(const String& name);

			/* EVENTS */
	
	EventBinder<const Config& /*new_config*/> on_changed_window;
	EventBinder<const Config& /*new_config*/> on_changed_res_check_period_sec;
	EventBinder<const Config& /*new_config*/> on_changed_res_path;
	EventBinder<const Config& /*new_config*/> on_changed_chunks_collision_size;
	EventBinder<const Config& /*new_config*/> on_changed_chunks_clickable_size;
	EventBinder<const Config& /*new_config*/> on_changed_lang_path;
	EventBinder<const Config& /*new_config*/> on_changed_log_path;

private:
	ConfigManager();

	String path_;
	Config current_;

	Event<const Config& /*new_config*/> on_changed_window_;
	Event<const Config& /*new_config*/> on_changed_res_check_period_sec_;
	Event<const Config& /*new_config*/> on_changed_res_path_;
	Event<const Config& /*new_config*/> on_changed_chunks_collision_size_;
	Event<const Config& /*new_config*/> on_changed_chunks_clickable_size_;
	Event<const Config& /*new_config*/> on_changed_lang_path_;
	Event<const Config& /*new_config*/> on_changed_log_path_;

	const static String INIT_FILE_;
	const static String DEFAULT_PATH_;
};

}
