    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ConfigManager.h             //
////////////////////////////////////////

#pragma once

#include "Config.h"

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

private:
	ConfigManager();

	String path_;
	Config current_;

	const static String INIT_FILE_;
	const static String DEFAULT_PATH_;
};

}
