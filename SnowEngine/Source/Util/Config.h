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
#include "../Math/Vector/Point2.h"

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

	void save();
	void load();

	String log_path;
	String lang_path;
	String default_lang;

	Point2 resolution;
	bool fullscreen;
	bool resize;
	bool titlebar;
	bool titlebar_buttons;
	String title;
};

}
