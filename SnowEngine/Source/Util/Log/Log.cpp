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

#include "../../Game/Game.h"
#include "../../Game/ConfigManager.h"
#include "../Time/Time.h"
#include "../Json/Value.h"

using namespace snow;

		/* Log: public */

Log::Log(const String& category_name) :
	name_(category_name)
{
	open_();
}

Log::Log(const std::shared_ptr<json::Element> json) :
	name_()
{
	if (!json)
	{
		throw std::invalid_argument("Couldn't create a logger: the JSON cannot be nullptr");
	}

	std::shared_ptr<json::StringValue> string = std::dynamic_pointer_cast<json::StringValue>(json);
	if (!string)
	{
		throw std::invalid_argument("Couldn't create a logger: the JSON must be a string value");
	}
	name_ = string->get();

	open_();
}

Log::~Log()
{
	if (--object_counter_ <= 0 && log_file_().is_open())
	{
		std::lock_guard<std::mutex> log_grd(log_file_mtx_());
		log_file_() << String::format(L"[%s][SnowCat] SnowCat log file is closed"_s,
			time::to_string(std::chrono::steady_clock::now())) << std::endl;
		log_file_().close();
	}
}

String Log::to_string() const
{
	return name_;
}

std::shared_ptr<json::Element> Log::to_json() const
{
	return name_.to_json();
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

void Log::d(const String& message)
{
	if (debug_mode_())
	{
		log_(L"[Debug  ] "_s, message);
	}
}

void Log::i(const String& message)
{
	log_(L"[Info   ] "_s, message);
}

void Log::w(const String& message)
{
	log_(L"[Warning] "_s, message);
}

void Log::e(const String& message)
{
	log_(L"[ERROR  ] "_s, message);
}

		/* Log: private */

bool& Log::debug_mode_() noexcept
{
#ifdef _DEBUG
	static bool debug_mode = true;
#else
	static bool debug_mode = false;
#endif
	return debug_mode;
}

std::mutex& Log::log_file_mtx_() noexcept
{
	static std::mutex log_file_mtx;
	return log_file_mtx;
}

std::wofstream& Log::log_file_()
{
	static std::wofstream log_file;
	return log_file;
}

void Log::log_(const String& type, const String& message)
{
	std::lock_guard<std::mutex> log_grd(log_file_mtx_());
	String time_str = time::to_string(std::chrono::steady_clock::now());

	log_file_() << L'[' << time_str << L']' << type << name_ << L": " << message << std::endl;
	std::wcout << L'[' << time_str << L']' << type << name_ << L": " << message << std::endl;
}

void Log::open_()
{
	object_counter_++;
	if (!log_file_().is_open())
	{
		std::lock_guard<std::mutex> log_grd(log_file_mtx_());
		Config config = ConfigManager::get_instance().get_current();
		if (!std::filesystem::exists(config.log_path.to_std_string()))
		{
			std::filesystem::create_directories(config.log_path.to_std_string());
		}
		std::wstring file_path = (config.log_path + L"\\Log.log").to_std_string();
		log_file_().open(file_path);
		log_file_() << L'[' << time::to_string(std::chrono::steady_clock::now()) << L"][Info   ] SnowCat: SnowCat log file is opened (meow!)" << std::endl;
	}
}

int Log::object_counter_ = 0;
