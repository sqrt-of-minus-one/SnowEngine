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

#define _CRT_SECURE_NO_WARNINGS

#include "Log.h"

#include <fstream>
#include <iostream>
#include <ctime>
#include <filesystem>

#include "../Game.h"
#include "../Config.h"
#include "../Time/Time.h"

using namespace snow;

		/* Log: public */

Log::Log(const String& category_name) noexcept :
	name_(category_name)
{
	object_counter_++;
	if (!log_file_().is_open())
	{
		std::lock_guard<std::mutex> log_grd(log_file_mtx_());
		if (!std::filesystem::exists(Game::config.log_path.to_std_string()))
		{
			std::filesystem::create_directories(Game::config.log_path.to_std_string());
		}
		std::wstring tmp = (Game::config.log_path + L"\\Log.log").to_std_string();
		log_file_().open(tmp);
		tmp = String::format(L"[%s][SnowCat] SnowCat log file is opened (meow!)"_s, Time::now().to_string()).to_std_string();
		log_file_() << tmp << std::endl;
	}
}

Log::~Log() noexcept
{
	if (--object_counter_ <= 0 && log_file_().is_open())
	{
		std::lock_guard<std::mutex> log_grd(log_file_mtx_());
		log_file_() << String::format(L"[%s][SnowCat] SnowCat log file is closed"_s, Time::now().to_string()) << std::endl;
		log_file_().close();
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
	debug_mode_() = true;
}

void Log::disable_debug_mode() noexcept
{
	debug_mode_() = false;
}

bool Log::is_debug_mode_enabled() noexcept
{
	return debug_mode_();
}

void Log::d(const String& message) noexcept
{
	if (debug_mode_())
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

		/* Log: private */

void Log::log_(const String& type, const String& message) noexcept
{
	std::lock_guard<std::mutex> log_grd(log_file_mtx_());
	String time_str = Time::now().to_string();

	log_file_ ()<< L"[" << time_str << L"]" << type << name_ << ": " << message << std::endl;
	std::wcout << L"[" << time_str << L"]" << type << name_ << ": " << message << std::endl;
}

bool& Log::debug_mode_()
{
#ifdef _DEBUG
	static bool debug_mode = true;
#else
	static bool debug_mode = false;
#endif
	return debug_mode;
}

std::mutex& Log::log_file_mtx_()
{
	static std::mutex log_file_mtx;
	return log_file_mtx;
}

std::wofstream& Log::log_file_()
{
	static std::wofstream log_file;
	return log_file;
}

int Log::object_counter_ = 0;
