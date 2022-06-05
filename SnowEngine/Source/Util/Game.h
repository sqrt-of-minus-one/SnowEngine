    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Game.h                      //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\brief The file with the Game class
 *	
 *	This file contains the definition of the Game class.
 */

#include <mutex>

namespace snow
{

class Config;
class Lang;

/**
 *	\brief The class that contains global game properties
 *	
 *	This class contains static fields with global game properties, such as Config or Lang objects.
 */
class Game
{
	friend class Log;

public:
	Game() = delete;

	static void start();

	/**
	 *	\brief The configurations of the game
	 *	
	 *	This field is the main instance of the Config class, that contains game configurations. You
	 *	can set them using `config.ini` file.
	 */
	static Config config;

	/**
	 *	\brief The instance of the language manager
	 *	
	 *	This field is the main instance of the Lang class, that is used to manage the game
	 *	localization.
	 */
	static Lang lang;

private:
	static void loop_();

	static bool debug_mode_;
	static std::mutex log_file_mtx_;
	static std::wofstream log_file_;
	static std::unique_ptr<Log> main_log_;
};

}
