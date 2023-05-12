    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ConfigManager.h             //
////////////////////////////////////////

#pragma once

#include "Config.h"

namespace snow
{

class ConfigManager : public Object
{
public:
			/* SINGLETON */

	static ConfigManager& get_instance();

			/* METHODS FROM Object */
	
	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;

			/* METHODS */

	const String& get_path() const;

	const Config& get_current() const;
	void set_current(const Config& config);

	void save_current(const String& name, bool allow_override = false);
	Config& load_current(const String& name);

private:
	ConfigManager();

	String path_;
	Config current_;
};

}
