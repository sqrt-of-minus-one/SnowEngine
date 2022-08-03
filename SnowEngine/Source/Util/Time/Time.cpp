    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Time.cpp                    //
////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS

#include "Time.h"

#include <ctime>

#include "TimeInterval.h"
#include "../Types/String.h"

using namespace snow;

Time::Time() :
	point_(),
	cache_tm_(),
	cache_state_(false)
{}

Time::Time(const Time& time) :
	point_(time.point_),
	cache_tm_(time.cache_tm_),
	cache_state_(time.cache_state_)
{}

Time::Time(int year, EMonth month, int day, int hour, int minute, int second,
	int millisecond, int microsecond, int nanosecond) :
	point_(),
	cache_tm_(),
	cache_state_(false)
{
	cache_tm_.tm_year = year - 1900;
	cache_tm_.tm_mon = static_cast<int>(month) - 1;
	cache_tm_.tm_mday = day;
	cache_tm_.tm_hour = hour;
	cache_tm_.tm_min = minute;
	cache_tm_.tm_sec = second;
	std::time_t time = std::mktime(&cache_tm_);
	std::chrono::time_point<std::chrono::system_clock> system = std::chrono::system_clock::from_time_t(time);
	point_ += std::chrono::duration_cast<std::chrono::duration<std::chrono::steady_clock::rep, std::chrono::steady_clock::period>>(
			system.time_since_epoch() - std::chrono::system_clock::now().time_since_epoch()) +
		std::chrono::steady_clock::now().time_since_epoch();
	point_ += std::chrono::nanoseconds(nanosecond) + std::chrono::microseconds(microsecond) + std::chrono::milliseconds(millisecond);
}

String Time::to_string() const
{
	return String::format(L"%04d.%02d.%02d-%02d:%02d:%02d"_s,
		year(), static_cast<int>(month()), month_day(), hour(), minute(), second());
}

int Time::hash_code() const noexcept
{
	return static_cast<int>(point_.time_since_epoch().count());
}

int Time::second() const
{
	if (!cache_state_)
	{
		update_cache_();
	}
	return cache_tm_.tm_sec;
}

int Time::minute() const
{
	if (!cache_state_)
	{
		update_cache_();
	}
	return cache_tm_.tm_min;
}

int Time::hour() const
{
	if (!cache_state_)
	{
		update_cache_();
	}
	return cache_tm_.tm_hour;
}

int Time::month_day() const
{
	if (!cache_state_)
	{
		update_cache_();
	}
	return cache_tm_.tm_mday;
}

EMonth Time::month() const
{
	if (!cache_state_)
	{
		update_cache_();
	}
	return static_cast<EMonth>(cache_tm_.tm_mon + 1);
}

int Time::year() const
{
	if (!cache_state_)
	{
		update_cache_();
	}
	return cache_tm_.tm_year + 1900;
}

EWeekDay Time::week_day() const
{
	if (!cache_state_)
	{
		update_cache_();
	}
	if (cache_tm_.tm_wday == 0)
	{
		return EWeekDay::SUN;
	}
	else
	{
		return static_cast<EWeekDay>(cache_tm_.tm_wday - 1);
	}
}

int Time::year_day() const
{
	if (!cache_state_)
	{
		update_cache_();
	}
	return cache_tm_.tm_yday;
}

Time Time::now()
{
	return Time(std::chrono::steady_clock::now());
}

Time& Time::operator=(const Time& time)
{
	point_ = time.point_;
	cache_tm_ = time.cache_tm_;
	cache_state_ = time.cache_state_;
	return *this;
}

Time Time::operator+(const TimeInterval& interval) const
{
	return Time(point_ + interval.duration_);
}

TimeInterval Time::operator-(const Time& time) const
{
	return TimeInterval(point_ - time.point_);
}

Time Time::operator-(const TimeInterval& interval) const
{
	return Time(point_ - interval.duration_);
}

Time& Time::operator+=(const TimeInterval& interval)
{
	point_ += interval.duration_;
	cache_state_ = false;
	return *this;
}

Time& Time::operator-=(const TimeInterval& interval)
{
	point_ -= interval.duration_;
	cache_state_ = false;
	return *this;
}

bool Time::operator==(const Time& interval) const noexcept
{
	return point_ == interval.point_;
}

bool Time::operator!=(const Time& interval) const noexcept
{
	return !operator==(interval);
}

bool Time::operator<(const Time& interval) const noexcept
{
	return point_ < interval.point_;
}

bool Time::operator>(const Time& interval) const noexcept
{
	return point_ > interval.point_;
}

bool Time::operator<=(const Time& interval) const noexcept
{
	return point_ <= interval.point_;
}

bool Time::operator>=(const Time& interval) const noexcept
{
	return point_ >= interval.point_;
}

Time::Time(const std::chrono::time_point<std::chrono::steady_clock>& point) :
	point_(point),
	cache_tm_(),
	cache_state_(false)
{}

void Time::update_cache_() const
{
	std::chrono::time_point<std::chrono::system_clock> system(
		std::chrono::duration_cast<std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period>>(
			point_.time_since_epoch() - std::chrono::steady_clock::now().time_since_epoch()) +
		std::chrono::system_clock::now().time_since_epoch());
	std::time_t time = std::chrono::system_clock::to_time_t(system);
	cache_tm_ = *std::localtime(&time);
	cache_state_ = true;
}
