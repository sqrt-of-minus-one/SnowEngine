    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Game.cpp                    //
////////////////////////////////////////

#include "Game.h"

#include <fstream>

using namespace snow;

void Game::start()
{

}

std::wofstream Game::log_file_;
#ifdef _DEBUG
bool Game::debug_mode_ = true;
#else
bool Game::debug_mode_ = false;
#endif

Config Game::config;
Lang Game::lang;
