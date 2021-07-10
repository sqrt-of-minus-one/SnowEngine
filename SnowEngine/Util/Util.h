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

}


		/* DEFINITIONS */

template<typename T>
const std::string util::to_string(T* var)
{
	return var->to_string();
}

template<typename T>
const std::string util::to_string(T var)
{
	return var.to_string();
}

}
