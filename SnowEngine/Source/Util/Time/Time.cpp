    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Time.cpp                    //
////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS

#include "Time.h"

#include "TimeInterval.h"
#include "../Types/String.h"

#include <ctime>

using namespace snow;

Time::Time() noexcept :
	point_(),
	cache_tm_(),
	cache_state_(false)
{}

Time::Time(const Time& time) noexcept :
	point_(time.point_),
	cache_tm_(time.cache_tm_),
	cache_state_(time.cache_state_)
{}

String Time::to_string() const noexcept
{
	return String::format(L"%02d.%02d.%04d, %02d:%02d:%02d"_s,
		month_day(), static_cast<int>(month()), year(), hour(), minute(), second());
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

Time& Time::operator=(const Time& time)
{
	point_ = time.point_;
	cache_tm_ = time.cache_tm_;
	cache_state_ = time.cache_state_;
	return *this;
}

Time Time::operator+(const TimeInterval& interval) const
{
	Time ret;
	ret.point_ = point_ + interval.duration_;
	return ret;
}

TimeInterval Time::operator-(const Time& time) const
{
	TimeInterval ret;
	ret.duration_ = point_ - time.point_;
	return ret;
}

Time Time::operator-(const TimeInterval& interval) const
{
	Time ret;
	ret.point_ = point_ + interval.duration_;
	return ret;
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

bool Time::operator==(const Time& interval) const
{
	return point_ == interval.point_;
}

bool Time::operator!=(const Time& interval) const
{
	return !operator==(interval);
}

bool Time::operator<(const Time& interval) const
{
	return point_ < interval.point_;
}

bool Time::operator>(const Time& interval) const
{
	return point_ > interval.point_;
}

bool Time::operator<=(const Time& interval) const
{
	return point_ <= interval.point_;
}

bool Time::operator>=(const Time& interval) const
{
	return point_ >= interval.point_;
}

void Time::update_cache_() const
{
	std::chrono::time_point<std::chrono::system_clock> system(
		std::chrono::duration_cast<std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period>>(
			point_.time_since_epoch() + std::chrono::steady_clock::now().time_since_epoch()) +
		std::chrono::system_clock::now().time_since_epoch());
	std::time_t time = std::chrono::system_clock::to_time_t(system);
	cache_tm_ = *std::gmtime(&time);
	cache_state_ = true;
}
