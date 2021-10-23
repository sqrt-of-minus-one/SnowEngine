    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Config.h                    //
////////////////////////////////////////

#pragma once

#include "Types/String.h"

namespace snow
{

class Config
{
public:
	Config() = delete;

	static void init();

	static const String& get_log_path();
	static const String& get_lang_path();
	static const String& get_default_lang();

private:
	static bool was_init_;

	static String log_path_;
	static String lang_path_;
	static String default_lang_;

};

}
