    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Config.h                    //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\brief The file of the Config class
 *	
 *	This file contains the definition of the Config class.
 */

#include "Types/String.h"

namespace snow
{

/**
 *	\brief The class with configurations
 *	
 *	This class contains the configurations of the program. Use `config.ini` to set them. The main
 *	instance of this class is contained in the Game class as a static member. You shouldn't create
 *	other instances yourself.
 */
class Config : public Object
{
public:

	/**
	 *	\brief The default constructor
	 *	
	 *	This constructor creates a new Config object and is used by the Game class.
	 *	\warning You shouldn't create instances of the Config class yourself.
	 */
	Config();

	/**
	 *	\brief Convert the configurations to the string
	 *	
	 *	The resultant string contains all configurations in the format of `config.ini` class.
	 *	\return The string with configurations.
	 */
	virtual String to_string() const noexcept override;

	/**
	 *	\brief Get the hash code
	 *	
	 *	The hash code of the Config object is the sum of hash codes of its members with different
	 *	size (`log_path` - `lang_path` + `default_lang` - …).
	 *	\return The hash code.
	 */
	virtual int hash_code() const noexcept override;

	/**
	 *	\brief Get the log path
	 *	
	 *	Allows to get the path to the directory where logs are saved.
	 *	\return The path to the log directory.
	 */
	const String& get_log_path();

	/**
	 *	\brief Get the languages path
	 *	
	 *	Allows to get the path to the directory where localization files are stored.
	 *	\return The path to the languages directory.
	 */
	const String& get_lang_path();

	/**
	 *	\brief Get the default language
	 *	
	 *	Allows to get the code of the default language.
	 *	\return The default language.
	 */
	const String& get_default_lang();

private:
	String log_path_;
	String lang_path_;
	String default_lang_;

};

}
