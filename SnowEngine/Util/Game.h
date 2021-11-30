    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Game.h                      //
////////////////////////////////////////

#pragma once

#include "Config.h"
#include "SnowFlake/Lang.h"

namespace snow
{

class Game
{
public:
	Game() = delete;

	static Config config;
	static Lang lang;

private:
	// Special static fields
	friend class Log;
	static bool debug_mode_;
	static std::wofstream log_file_;
};

}
