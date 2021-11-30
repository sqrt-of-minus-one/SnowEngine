    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Config.h                    //
////////////////////////////////////////

#pragma once

#include "Types/String.h"

namespace snow
{

class Config : public Object
{
public:
	Config();

	virtual String to_string() const noexcept override;
	virtual int hash_code() const noexcept override;

	const String& get_log_path();
	const String& get_lang_path();
	const String& get_default_lang();

private:
	String log_path_;
	String lang_path_;
	String default_lang_;

};

}
