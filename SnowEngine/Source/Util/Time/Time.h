    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Time.h                      //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include <chrono>

namespace snow
{

class TimeInterval;

enum class EMonth
{
	JAN = 1,
	FEB,
	MAR,
	APR,
	MAY,
	JUN,
	JUL,
	AUG,
	SEP,
	OCT,
	NOV,
	DEC
};

enum class EWeekDay
{
	MON = 0,
	TUE,
	WED,
	THU,
	FRI,
	SAT,
	SUN
};

class Time : public Object
{
public:
	Time() noexcept;
	Time(const Time& time) noexcept;

	virtual String to_string() const noexcept override;
	virtual int hash_code() const noexcept override;

	int second() const;
	int minute() const;
	int hour() const;
	int month_day() const;
	EMonth month() const;
	int year() const;
	EWeekDay week_day() const;
	int year_day() const;

	Time& operator=(const Time& time);

	Time operator+(const TimeInterval& interval) const;
	TimeInterval operator-(const Time& time) const;
	Time operator-(const TimeInterval& interval) const;

	Time& operator+=(const TimeInterval& interval);
	Time& operator-=(const TimeInterval& interval);

	bool operator==(const Time& interval) const;
	bool operator!=(const Time& interval) const;
	bool operator<(const Time& interval) const;
	bool operator>(const Time& interval) const;
	bool operator<=(const Time& interval) const;
	bool operator>=(const Time& interval) const;

private:
	std::chrono::time_point<std::chrono::steady_clock> point_;
	mutable std::tm cache_tm_;
	mutable bool cache_state_;

	void update_cache_() const;

};

}
