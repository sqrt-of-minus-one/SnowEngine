    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Array.h                     //
////////////////////////////////////////

#include "Util.h"

using namespace snow;

const std::string util::to_string(int var) noexcept
{
	return std::to_string(var);
}

const std::string util::to_string(float var) noexcept
{
	return std::to_string(var);
}

const std::string util::to_string(char var) noexcept
{
	return { var };
}

const std::string util::to_string(bool var) noexcept
{
	return var ? "true" : "false";
}


int util::hash_code(int var) noexcept
{
	return var;
}

int util::hash_code(float var) noexcept
{
	return static_cast<int>(var);
}

int util::hash_code(char var) noexcept
{
	return static_cast<int>(var);
}

int util::hash_code(bool var) noexcept
{
	return static_cast<int>(var);
}
