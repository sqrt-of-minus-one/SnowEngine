    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: TimeInterval.cpp            //
////////////////////////////////////////

#include "TimeInterval.h"

#include "../Types/String.h"

using namespace snow;
using namespace std::chrono_literals;

TimeInterval::TimeInterval() :
	duration_()
{}

TimeInterval::TimeInterval(const TimeInterval& interval) :
	duration_(interval.duration_)
{}

String TimeInterval::to_string() const
{
	long long t = ns();
	bool is_negative = false;
	if (t < 0)
	{
		is_negative = true;
		t = -t;
	}

	int ns = static_cast<int>(t % 1000000);
	t /= 1000000;

	int ms = static_cast<int>(t % 1000);
	t /= 1000;

	int s = static_cast<int>(t % 60);
	t /= 60;

	int min = static_cast<int>(t % 60);
	t /= 60;

	int h = static_cast<int>(t);
	
	return (is_negative ? L"-"_s : L""_s) + String::format(L"%dh%02dm%02ds%03d.%06dms"_s, h, min, s, ms, ns);
}

int TimeInterval::hash_code() const noexcept
	// count() is not noexcept, but I have no idea how may it throw any exception
{
	return static_cast<int>(duration_.count());
}

long long TimeInterval::h() const noexcept
{
	return ns() / 3'600'000'000'000LL;
}

long long TimeInterval::min() const noexcept
{
	return ns() / 60'000'000'000LL;
}

long long TimeInterval::s() const noexcept
{
	return ns() / 1'000'000'000LL;
}

long long TimeInterval::ms() const noexcept
{
	return ns() / 1'000'000LL;
}

long long TimeInterval::us() const noexcept
{
	return ns() / 1000LL;
}

long long TimeInterval::ns() const noexcept
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(duration_).count();
}

TimeInterval& TimeInterval::operator=(const TimeInterval& interval)
{
	duration_ = interval.duration_;
	return *this;
}

const TimeInterval TimeInterval::operator+() const
{
	return *this;
}

const TimeInterval TimeInterval::operator-() const
{
	return TimeInterval(-duration_);
}

const TimeInterval TimeInterval::operator+(const TimeInterval& interval) const
{
	return TimeInterval(duration_ + interval.duration_);
}

const TimeInterval TimeInterval::operator-(const TimeInterval& interval) const
{
	return TimeInterval(duration_ - interval.duration_);
}

const TimeInterval TimeInterval::operator*(float value) const
{
	return TimeInterval(std::chrono::duration_cast<std::chrono::duration<
		std::chrono::steady_clock::rep,
		std::chrono::steady_clock::period>>(duration_ * value));
}

const TimeInterval snow::operator*(float value, const TimeInterval& interval)
{
	return interval * value;
}

const TimeInterval TimeInterval::operator/(float value) const
{
	return TimeInterval(std::chrono::duration_cast<std::chrono::duration<
		std::chrono::steady_clock::rep,
		std::chrono::steady_clock::period>>(duration_ / value));
}

TimeInterval& TimeInterval::operator+=(const TimeInterval& interval)
{
	duration_ += interval.duration_;
	return *this;
}

TimeInterval& TimeInterval::operator-=(const TimeInterval& interval)
{
	duration_ -= interval.duration_;
	return *this;
}

TimeInterval& TimeInterval::operator*=(float value)
{
	duration_ = std::chrono::duration_cast<std::chrono::duration<
		std::chrono::steady_clock::rep,
		std::chrono::steady_clock::period>>(duration_ * value);
	return *this;
}

TimeInterval& TimeInterval::operator/=(float value)
{
	duration_ = std::chrono::duration_cast<std::chrono::duration<
		std::chrono::steady_clock::rep,
		std::chrono::steady_clock::period>>(duration_ / value);
	return *this;
}

bool TimeInterval::operator==(const TimeInterval& interval) noexcept
{
	return duration_ == interval.duration_;
}

bool TimeInterval::operator!=(const TimeInterval& interval) noexcept
{
	return !operator==(interval);
}

bool TimeInterval::operator<(const TimeInterval& interval) noexcept
{
	return duration_ < interval.duration_;
}

bool TimeInterval::operator>(const TimeInterval& interval) noexcept
{
	return duration_ > interval.duration_;
}

bool TimeInterval::operator<=(const TimeInterval& interval) noexcept
{
	return duration_ <= interval.duration_;
}

bool TimeInterval::operator>=(const TimeInterval& interval) noexcept
{
	return duration_ >= interval.duration_;
}

TimeInterval snow::operator""_ns(long double ns)
{
	return TimeInterval(std::chrono::duration_cast<std::chrono::duration<
		std::chrono::steady_clock::rep,
		std::chrono::steady_clock::period>>(std::chrono_literals::operator""ns(ns)));
}

TimeInterval snow::operator""_ns(unsigned long long ns)
{
	return TimeInterval(std::chrono_literals::operator""ns(ns));
}

TimeInterval snow::operator""_us(long double us)
{
	return TimeInterval(std::chrono::duration_cast<std::chrono::duration<
		std::chrono::steady_clock::rep,
		std::chrono::steady_clock::period>>(std::chrono_literals::operator""us(us)));
}

TimeInterval snow::operator""_us(unsigned long long us)
{
	return TimeInterval(std::chrono_literals::operator""us(us));
}

TimeInterval snow::operator""_ms(long double ms)
{
	return TimeInterval(std::chrono::duration_cast<std::chrono::duration<
		std::chrono::steady_clock::rep,
		std::chrono::steady_clock::period>>(std::chrono_literals::operator""ms(ms)));
}

TimeInterval snow::operator""_ms(unsigned long long ms)
{
	return TimeInterval(std::chrono_literals::operator""ms(ms));
}

TimeInterval snow::operator""_s(long double s)
{
	return TimeInterval(std::chrono::duration_cast<std::chrono::duration<
		std::chrono::steady_clock::rep,
		std::chrono::steady_clock::period>>(std::chrono_literals::operator""s(s)));
}

TimeInterval snow::operator""_s(unsigned long long s)
{
	return TimeInterval(std::chrono_literals::operator""s(s));
}

TimeInterval snow::operator""_min(long double min)
{
	return TimeInterval(std::chrono::duration_cast<std::chrono::duration<
		std::chrono::steady_clock::rep,
		std::chrono::steady_clock::period>>(std::chrono_literals::operator""min(min)));
}

TimeInterval snow::operator""_min(unsigned long long min)
{
	return TimeInterval(std::chrono_literals::operator""min(min));
}

TimeInterval snow::operator""_h(long double h)
{
	return TimeInterval(std::chrono::duration_cast<std::chrono::duration<
		std::chrono::steady_clock::rep,
		std::chrono::steady_clock::period>>(std::chrono_literals::operator""h(h)));
}

TimeInterval snow::operator""_h(unsigned long long h)
{
	return TimeInterval(std::chrono_literals::operator""h(h));
}

TimeInterval::TimeInterval(const std::chrono::duration<std::chrono::steady_clock::rep, std::chrono::steady_clock::period>& duration) :
	duration_(duration)
{}
