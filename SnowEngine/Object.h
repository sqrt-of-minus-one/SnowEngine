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
	virtual const std::string to_string() const = 0;
};

}
