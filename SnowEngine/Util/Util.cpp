    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Array.h                     //
////////////////////////////////////////

#include "Util.h"

using namespace snow;

const std::string util::to_string(int var)
{
	return std::to_string(var);
}

const std::string util::to_string(float var)
{
	return std::to_string(var);
}

const std::string util::to_string(char var)
{
	return "" + var;
}

const std::string util::to_string(bool var)
{
	return var ? "true" : "false";
}


int util::hash_code(int var)
{
	return var;
}

int util::hash_code(float var)
{
	return static_cast<int>(var);
}

int util::hash_code(char var)
{
	return static_cast<int>(var);
}

int util::hash_code(bool var)
{
	return static_cast<int>(var);
}
