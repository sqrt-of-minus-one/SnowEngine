    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Log.cpp                     //
////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS

#include "Log.h"

#include <fstream>
#include <iostream>
#include <ctime>

using namespace snow;

Log::Log(const std::string& category_name) :
	name_(category_name)
{
	object_counter_++;
	if (!file_.is_open())
	{
		file_.open("Logs/Log.log", std::ios_base::trunc);
		file_ << "[" << get_time_string_() << "][Logging] Log file is opened" << std::endl;
	}
}

Log::~Log()
{
	if (--object_counter_ <= 0 && file_.is_open())
	{
		file_ << "[" << get_time_string_() << "][Logging] Log file is closed" << std::endl;
		file_.close();
	}
}

std::string Log::to_string() const noexcept
{
	return name_;
}

int Log::hash_code() const noexcept
{
	int hash = 0;
	int one = 1;
	for (char i : name_)
	{
		hash += one * static_cast<int>(i);
		one *= -1;
	}
	return hash;
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

void Log::d(const std::string& message)
{
	if (debug_mode_)
	{
		log_("[Debug  ] ", message);
	}
}

void Log::i(const std::string& message)
{
	log_("[Info   ] ", message);
}

void Log::w(const std::string& message)
{
	log_("[Warning] ", message);
}

void Log::e(const std::string& message)
{
	log_("[ERROR  ] ", message);
}

std::string Log::get_time_string_()
{
	// It's temporary
	std::time_t current_time = std::time(nullptr);
	std::tm time = *std::localtime(&current_time);
	return std::to_string(time.tm_year + 1900) + "." + std::to_string(time.tm_mon + 1) + "." + std::to_string(time.tm_mday) + "-" +
		std::to_string(time.tm_hour) + ":" + std::to_string(time.tm_min) + ":" + std::to_string(time.tm_sec);
}

void Log::log_(const std::string& type, const std::string& message)
{
	std::string time_str = "[" + get_time_string_() + "]";

	file_ << time_str << type << name_ << ": " << message << std::endl;
	std::cout << time_str << type << name_ << ": " << message << std::endl;
}

#ifdef _DEBUG
bool Log::debug_mode_ = true;
#else
bool Log::debug_mode_ = false;
#endif

int Log::object_counter_ = 0;
std::ofstream Log::file_;
