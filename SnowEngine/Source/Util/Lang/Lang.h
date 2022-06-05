    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Lang.h                      //
////////////////////////////////////////

//   \_____/     ***     SnowFlake            *****  *           *                               //
//   /\___/\    *   *                         *      *           *                               //
//  / /\ /\ \   *      ****    ***   *     *  *      *    ****   *  *   ***                      //
// =====X=====   ***   *   *  *   *  *     *  *****  *   *   *   * *   *   *    /**************\ //
//  \ \/_\/ /       *  *   *  *   *  *  *  *  *      *   *   *   **    *****   |*  SnowEngine  *|//
//   \/___\/    *   *  *   *  *   *  * * * *  *      *   *   *   * *   *       |* localization *|//
//   /     \     ***   *   *   ***    *   *   *       *   *** *  *  *   ****   |*    system    *|//

#pragma once

/**
 *	\file
 *	\brief The file of SnowFlake's Lang class
 *	
 *	This file contains the definition of the Lang class
 */

#include "../Log/Log.h"
#include "../Container/Map.h"

namespace snow
{

/**
 *	\brief The class of the SnowEngine language manager
 *	
 *	This class allows to use languages. Its main instance is contained in Game class as a static
 *	member. You shouldn't create other instances yourself. Use `config.ini` file to set languages
 *	directory and default language.
 */
class Lang : public Object
{
public:
	/**
	 *	\brief The default constructor
	 *	
	 *	Creates an object of the Lang class. Is used by the Game class.
	 *	\warning You shouldn't create instances of the Lang class yourself.
	 */
	Lang();

	/**
	 *	\brief Convert to string
	 *	
	 *	Converts the Lang object to string.
	 *	\return The code of the current language.
	 */
	virtual String to_string() const noexcept override;

	/**
	 *	\brief Get the hash code
	 *	
	 *	The hash code of the Lang object is the hash code of the current language:
	 *	\code
	 *		lang.hash_code() == lang.get_current_lang().hash_code();
	 *	\endcode
	 *	\return The hash code.
	 */
	virtual int hash_code() const noexcept override;

	/**
	 *	\brief Get the current language
	 *	
	 *	Allows to get the language that is active now.
	 *	\return The text code of the current language.
	 */
	const String& get_current_lang();

	/**
	 *	\brief Set the language
	 *	
	 *	Sets the passed language as active.
	 *	\param lang The text code of the required language.
	 *	\return `false` if an error has occurred (and the language hasn't been changed), `true`
	 *	otherwise.
	 */
	bool set_lang(const String& lang);

	/**
	 *	\brief Get a string in the current language
	 *	
	 *	Allows to get a string in the language that is active now. 
	 *	\param key The key of the required string.
	 *	\return The required string in the current language. If there is no string with the passed
	 *	key, returns the key.
	 */
	String get_string(const String& key);

	/**
	 *	\brief Whether the passed key is valid
	 *	
	 *	Checks if the passed key is contained in the list of strings of the current language.
	 *	\param key The key to check.
	 *	\return	`true` if the key is valid, `false` otherwise.
	 */
	bool is_valid(const String& key);

private:
	String current_lang_;
	Map<String, String> strings_;
	Log lang_log_;

};

}
