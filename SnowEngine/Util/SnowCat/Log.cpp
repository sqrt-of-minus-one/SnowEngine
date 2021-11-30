    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Log.cpp                     //
////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////SnowCat//////////////////
////// \// \////////     ///   ///  ///    //  ///   ///  ///    //   //         ////////////////
/////       ///////  //////    //  //  //  //  //    //  //  /////    /////  //////////////////////
////  o   o  //////    ///  /  /  //  //  ///  /  /  /  //  /////  =  ////  /////////////////////
////    0    ////////  //  //    //  //  ////    //    //  /////      ///  ////   SnowEngine   ////
/////  / \  ////     ///  ///   ///    //////   ///   ///    //  ///  //  //// logging system ///
///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 *	\file
 *	\brief The cpp-file of the SnowCat logger
 *
 *	This file contains the definitions of the Log class methods.
 */

#define _CRT_SECURE_NO_WARNINGS

#include "Log.h"

#include "../Config.h"

#include <fstream>
#include <iostream>
#include <ctime>
#include <filesystem>

using namespace snow;

Log::Log(const String& category_name) noexcept :
	name_(category_name)
{
	object_counter_++;
	if (!file_.is_open())
	{
		if (!std::filesystem::exists(Config::get_log_path().to_std_string()))
		{
			std::filesystem::create_directories(Config::get_log_path().to_std_string());
		}
		file_.open((Config::get_log_path() + L"\\Log.log").to_std_string(), std::ios_base::trunc);
		file_ << String::format(L"[%s][SnowCat] SnowCat log file is opened (meow!)"_s, get_time_string_()) << std::endl;
	}
}

Log::~Log() noexcept
{
	if (--object_counter_ <= 0 && file_.is_open())
	{
		file_ << String::format(L"[%s][SnowCat] SnowCat log file is closed"_s, get_time_string_()) << std::endl;
		file_.close();
	}
}

String Log::to_string() const noexcept
{
	return name_;
}

int Log::hash_code() const noexcept
{
	return name_.hash_code();
}

void Log::enable_debug_mode() noexcept
{
	debug_mode_ = true;
}

void Log::disable_debug_mode() noexcept
{
	debug_mode_ = false;
}

bool Log::is_debug_mode_enabled() noexcept
{
	return debug_mode_;
}

void Log::d(const String& message) noexcept
{
	if (debug_mode_)
	{
		log_(L"[Debug  ] "_s, message);
	}
}

void Log::i(const String& message) noexcept
{
	log_(L"[Info   ] "_s, message);
}

void Log::w(const String& message) noexcept
{
	log_(L"[Warning] "_s, message);
}

void Log::e(const String& message) noexcept
{
	log_(L"[ERROR  ] "_s, message);
}

String Log::get_time_string_() noexcept
{
	std::time_t current_time = std::time(nullptr);
	std::tm time = *std::localtime(&current_time);
	return String::format(L"%04d.%02d.%02d-%02d:%02d:%02d"_s,
		time.tm_year + 1900, time.tm_mon + 1, time.tm_mday,
		time.tm_hour, time.tm_min, time.tm_sec);
}

void Log::log_(const String& type, const String& message) noexcept
{
	String time_str = String::format(L"[%s]"_s, get_time_string_());

	file_ << time_str << type << name_ << ": " << message << std::endl;
	std::wcout << time_str << type << name_ << ": " << message << std::endl;
}

#ifdef _DEBUG
bool Log::debug_mode_ = true;
#else
bool Log::debug_mode_ = false;
#endif

int Log::object_counter_ = 0;
std::wofstream Log::file_;
