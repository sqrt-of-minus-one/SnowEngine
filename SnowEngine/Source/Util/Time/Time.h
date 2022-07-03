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
	Time();
	Time(const Time& time);
	Time(int year, EMonth month, int day, int hour = 0, int minute = 0, int second = 0,
		int millisecond = 0, int microsecond = 0, int nanosecond = 0);

	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;

	int second() const;
	int minute() const;
	int hour() const;
	int month_day() const;
	EMonth month() const;
	int year() const;
	EWeekDay week_day() const;
	int year_day() const;

	static Time now();

	Time& operator=(const Time& time);

	Time operator+(const TimeInterval& interval) const;
	TimeInterval operator-(const Time& time) const;
	Time operator-(const TimeInterval& interval) const;

	Time& operator+=(const TimeInterval& interval);
	Time& operator-=(const TimeInterval& interval);

	bool operator==(const Time& interval) const noexcept;
	bool operator!=(const Time& interval) const noexcept;
	bool operator<(const Time& interval) const noexcept;
	bool operator>(const Time& interval) const noexcept;
	bool operator<=(const Time& interval) const noexcept;
	bool operator>=(const Time& interval) const noexcept;

private:
	using Point_ = std::chrono::time_point<std::chrono::steady_clock>;

	Time(const Point_& point);

	Point_ point_;
	mutable std::tm cache_tm_;
	mutable bool cache_state_;

	void update_cache_() const;

};

}
