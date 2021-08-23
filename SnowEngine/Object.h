    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Object.h                    //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\brief Definition of Object class
 *	
 *	This file contains the definition of the Object class.
 */

#include <string>
#include <stdexcept>

namespace snow
{

/**
 *	\brief The base class of all SnowEngine classes
 *	
 *	Every SnowEngine class is derived from this one.
 */
class Object
{
public:
			/* METHODS */

	/**
	 *	\brief Converts the object into a string
	 *	
	 *	The virtual method that creates a string from the object.
	 *	\return A string.
	 */
	virtual const std::string to_string() const noexcept = 0;

	/**
	 *	\brief Allows to get hash code of the object
	 *	
	 *	Hash code is an integer number. If two objects are equal, their hash codes are equal too,
	 *	but two different objects can also have the same hash.
	 *	\return Hash code of the object.
	 */
	virtual int hash_code() const noexcept = 0;
};

}
