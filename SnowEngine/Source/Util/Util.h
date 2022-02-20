    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Util.h                      //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\brief File with auxiliary functions
 *	
 *	This file contains declarations of members of util namespace.
 */

#include "../Object.h"

namespace snow
{

class String;

namespace util
{

/**
 *	\brief `int` to string
 *	
 *	Converts the passed integer to string.
 *	\param var Integer that will be converted to string.
 *	\return A string that represents the passed integer.
 */
String to_string(int var) noexcept;

/**
 *	\brief `int` to string in binary system
 *	
 *	Converts the passed integer to string as binary number.
 *	\param var Integer that will be converted to string.
 *	\return A string that represents the passed binary integer.
 */
String to_string_bin(int var) noexcept;

/**
 *	\brief `int` to string in octal system
 *	
 *	Converts the passed integer to string as octal number.
 *	\param var Integer that will be converted to string.
 *	\return A string that represents the passed octal integer.
 */
String to_string_oct(int var) noexcept;

/**
 *	\brief `int` to string in hexadecimal system
 *	
 *	Converts the passed integer to string as hexadecimal number.
 *	\param var Integer that will be converted to string.
 *	\return A string that represents the passed hexadecimal integer.
 */
String to_string_hex(int var) noexcept;

/**
 *	\brief `float` to string
 *
 *	Converts the passed float to string.
 *	\param var Float that will be converted to string.
 *	\return A string that contains the passed float.
 */
String to_string(float var) noexcept;

/**
 *	\brief `char` to string
 *
 *	Creates a string that contains the passed character.
 *	\param var Character that will be converted to string.
 *	\return A string that contains the passed character.
 */
String to_string(wchar_t var) noexcept;

/**
 *	\brief `bool` to string
 *
 *	Converts the passed boolean to string.
 *	\param var Boolean that will be converted to string.
 *	\return `"true"` if the passed value is true, `"false"` otherwise.
 */
String to_string(bool var) noexcept;

/**
 *	\brief Pointer to string
 *
 *	Converts the value of the passed pointer to string.
 *	\param var Pointer to the value that will be converted to string.
 *	\return `"NULL"` if the pointer is null, `util::to_string(*var)` otherwise.
 */
template<typename T>
String to_string(T* var) noexcept;

/**
 *	\brief Unique pointer to string
 *
 *	Converts the value of the passed pointer to string.
 *	\param var Pointer to the value that will be converted to string.
 *	\return `"NULL"` if the pointer is null, `util::to_string(*var)` otherwise.
 */
template<typename T>
String to_string(const std::unique_ptr<T>& var) noexcept;

/**
 *	\brief Shared pointer to string
 *
 *	Converts the value of the passed pointer to string.
 *	\param var Pointer to the value that will be converted to string.
 *	\return `"NULL"` if the pointer is null, `util::to_string(*var)` otherwise.
 */
template<typename T>
String to_string(const std::shared_ptr<T>& var) noexcept;

/**
 *	\brief Weak pointer to string
 *
 *	Converts the value of the passed pointer to string.
 *	\param var Pointer to the value that will be converted to string.
 *	\return `"NULL"` if the pointer is null, `util::to_string(*var)` otherwise.
 */
template<typename T>
String to_string(const std::weak_ptr<T>& var) noexcept;

/**
 *	\brief Object to string
 *
 *	Converts the passed object to string. The object must have `to_string()` method (any
 *	`snow::Object` has it).
 *	\param var The object that will be converted to string.
 *	\return Result of object's `to_string()` method.
 */
template<typename T>
String to_string(const T& var) noexcept;

/**
 *	\brief Hash code of `int`
 *
 *	Hash code of an integer is equal to the value of the integer.
 *	\param var Integer whose hash code will be calculated.
 *	\return A hash code of the passed integer.
 */
int hash_code(int var) noexcept;

/**
 *	\brief Hash code of `float`
 *
 *	Hash code of a float number is equal to the value of the float rounded down.
 *	\param var Float whose hash code will be calculated.
 *	\return A hash code of the passed float.
 */
int hash_code(float var) noexcept;

/**
 *	\brief Hash code of `char`
 *
 *	Hash code of a character is the character's ASCII code.
 *	\param var Character whose hash code will be calculated.
 *	\return A hash code of the passed character.
 */
int hash_code(wchar_t var) noexcept;

/**
 *	\brief Hash code of `bool`
 *
 *	Hash code of a boolean value is 1 if the boolean is true, 0 otherwise.
 *	\param var Boolean whose hash code will be calculated.
 *	\return A hash code of the passed boolean.
 */
int hash_code(bool var) noexcept;

/**
 *	\brief Hash code of pointer
 *
 *	Calculates a hash code of the passed pointer. To do it the function converts the pointer to
 *	integer.
 *	\param var The pointer whose hash code will be calculated.
 *	\return A hash code of the passed pointer.
 */
template<typename T>
int hash_code(T* var) noexcept;

/**
 *	\brief Hash code of unique pointer
 *
 *	Calculates a hash code of the passed pointer. To do it the function converts the pointer to
 *	integer.
 *	\param var The pointer whose hash code will be calculated.
 *	\return A hash code of the passed pointer.
 */
template<typename T>
int hash_code(const std::unique_ptr<T>& var) noexcept;

/**
 *	\brief Hash code of shared pointer
 *
 *	Calculates a hash code of the passed pointer. To do it the function converts the pointer to
 *	integer.
 *	\param var The pointer whose hash code will be calculated.
 *	\return A hash code of the passed pointer.
 */
template<typename T>
int hash_code(const std::shared_ptr<T>& var) noexcept;

/**
 *	\brief Hash code of weak pointer
 *
 *	Calculates a hash code of the passed pointer. To do it the function converts the pointer to
 *	integer.
 *	\param var The pointer whose hash code will be calculated.
 *	\return A hash code of the passed pointer.
 */
template<typename T>
int hash_code(const std::weak_ptr<T>& var) noexcept;

/**
 *	\brief Hash code of object
 *
 *	Calculates a hash code of the passed object. The object must have `hash_code()` method (any
 *	`snow::Object` has it).
 *	\param var Object whose hash code will be calculated.
 *	\return A hash code of the passed object.
 */
template<typename T>
int hash_code(const T& var) noexcept;

}


		/* DEFINITIONS */

template<typename T>
String util::to_string(T* var) noexcept
{
	if (var)
	{
		return to_string(*var);
	}
	else
	{
		return L"NULL";
	}
}

template<typename T>
String util::to_string(const std::unique_ptr<T>& var) noexcept
{
	return to_string(var.get());
}

template<typename T>
String util::to_string(const std::shared_ptr<T>& var) noexcept
{
	return to_string(var.get());
}

template<typename T>
String util::to_string(const std::weak_ptr<T>& var) noexcept
{
	return to_string(var.lock().get());
}

template<typename T>
String util::to_string(const T& var) noexcept
{
	return var.to_string();
}

template<typename T>
int util::hash_code(T* var) noexcept
{
	return reinterpret_cast<int>(var);
}

template<typename T>
int util::hash_code(const std::unique_ptr<T>& var) noexcept
{
	return hash_code(var.get());
}

template<typename T>
int util::hash_code(const std::shared_ptr<T>& var) noexcept
{
	return hash_code(var.get());
}

template<typename T>
int util::hash_code(const std::weak_ptr<T>& var) noexcept
{
	return hash_code(var.lock().get());
}

template<typename T>
int util::hash_code(const T& var) noexcept
{
	return var.hash_code();
}

}
