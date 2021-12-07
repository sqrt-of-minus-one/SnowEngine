    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Text.h                      //
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
 *	\brief The file of the SnowFlake's Text class
 *	
 *	This file contains the definition of the Text class.
 */

#include "../Types/String.h"

namespace snow
{

/**
 *	\brief The Text class allows to use localizable text
 *	
 *	This class keeps the code of localizable string. You can use `to_string()` method to get the
 *	string in the current language.
 */
class Text : public Object
{
public:

	/**
	 *	\brief The default constructor
	 *	
	 *	Creates the empty string.
	 */
	Text() noexcept;

	/**
	 *	\brief The copy constructor
	 *	
	 *	Creates a new Text object by copying the passed one.
	 *	\param text The text to copy.
	 */
	Text(const Text& text) noexcept;

	/**
	 *	\brief The move constructor
	 *	
	 *	Creates a new Text object by moving the string code value from the passed one.
	 *	\param text The text whose value will be moved.
	 */
	Text(Text&& text) noexcept;

	/**
	 *	\brief Create a new Text object using the passed key
	 *	
	 *	Creates a new Text object with the passed key.
	 *	\param key The key.
	 */
	Text(const String& key) noexcept;

	/**
	 *	\brief Create a new Text object using the passed key
	 *
	 *	Creates a new Text object with the passed key.
	 *	\param key The key.
	 */
	Text(String&& key) noexcept;

	/**
	 *	\brief Get the localized string
	 *	
	 *	Allows to get the localized string in the current language.
	 *	\return The localized string.
	 */
	virtual String to_string() const noexcept override;

	/**
	 *	\brief Get the hash code
	 *	
	 *	The hash code of the Text object is the hash code of its key.
	 *	\return The hash code.
	 */
	virtual int hash_code() const noexcept override;

	/**
	 *	\brief Get the key
	 *	
	 *	Allows to get the key of the text.
	 *	\return The key.
	 */
	const String& get_key() const noexcept;
	
	/**
	 *	\brief Whether the Text object is valid
	 *	
	 *	Checks whether the key of the Text object is contained in the table of the string of the
	 *	current language.
	 *	\return `true` if the key is valid, `false` otherwise.
	 */
	bool is_valid() const noexcept;

	/**
	 *	\brief The copy assignment operator
	 *	
	 *	Replaces the current key with the one of the passed text.
	 *	\param text The text to copy.
	 */
	Text& operator=(const Text& text);

	/**
	 *	\brief The move assignment operator
	 *
	 *	Replaces the current key with the one of the passed text.
	 *	\param text The text whose key will be moved.
	 */
	Text& operator=(Text&& text);

	/**
	 *	\brief Set the key
	 *
	 *	Replaces the current key with the passed one.
	 *	\param text The new key.
	 */
	Text& operator=(const String& key);

	/**
	 *	\brief Set the key
	 *
	 *	Replaces the current key with the passed one.
	 *	\param text The new key.
	 */
	Text& operator=(String&& key);

	/**
	 *	\brief Whether two Text objects are equal
	 *	
	 *	Two objects are equal if their keys are equal.
	 *	\param text The Text object to compare.
	 *	\return `true` if the objects are equal, `false` otherwise.
	 */
	bool operator==(const Text& text) const;

	/**
	 *	\brief Whether the Text objects has the passed key
	 *
	 *	Checks whether the key of the object is equal to the passed one.
	 *	\param key The key to compare.
	 *	\return `true` if the key is equal to the passed one, `false` otherwise.
	 */
	bool operator==(const String& key) const;

	/**
	 *	\brief Whether two Text objects are not equal
	 *
	 *	Two objects are equal if their keys are equal.
	 *	\param text The Text object to compare.
	 *	\return `true` if the objects are not equal, `false` otherwise.
	 */
	bool operator!=(const Text& text) const;

	/**
	 *	\brief Whether the Text objects has not the passed key
	 *
	 *	Checks whether the key of the object differs from the passed one.
	 *	\param key The key to compare.
	 *	\return `true` if the key is not equal to the passed one, `false` otherwise.
	 */
	bool operator!=(const String& key) const;

private:
	String key_;

};

}