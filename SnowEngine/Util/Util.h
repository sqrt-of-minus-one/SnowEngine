    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Util.h                      //
////////////////////////////////////////

#pragma once

#include "../Object.h"

namespace snow
{

namespace util
{

const std::string to_string(int var);

const std::string to_string(float var);

const std::string to_string(char var);

const std::string to_string(bool var);

template<typename T>
const std::string to_string(T* var);

template<typename T>
const std::string to_string(T var);


int hash_code(int var);

int hash_code(float var);

int hash_code(char var);

int hash_code(bool var);

template<typename T>
int hash_code(T* var);

template<typename T>
int hash_code(T var);

}


		/* DEFINITIONS */

template<typename T>
const std::string util::to_string(T* var)
{
	if (var)
	{
		return var->to_string();
	}
	else
	{
		return "NULL";
	}
}

template<typename T>
const std::string util::to_string(T var)
{
	return var.to_string();
}

template<typename T>
int util::hash_code(T* var)
{
	if (var)
	{
		return var->hash_code();
	}
	else
	{
		return 0;
	}
}

template<typename T>
int util::hash_code(T var)
{
	return var.hash_code();
}

}
