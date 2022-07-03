    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: TimeInterval.h              //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include <chrono>

namespace snow
{

class TimeInterval : public Object
{
	friend class Time;

public:
	TimeInterval();
	TimeInterval(const TimeInterval& interval);

	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;

	long long h() const noexcept;
	long long min() const noexcept;
	long long s() const noexcept;
	long long ms() const noexcept;
	long long us() const noexcept;
	long long ns() const noexcept;

	TimeInterval& operator=(const TimeInterval& interval);

	const TimeInterval operator+() const;
	const TimeInterval operator-() const;

	const TimeInterval operator+(const TimeInterval& interval) const;
	const TimeInterval operator-(const TimeInterval& interval) const;
	const TimeInterval operator*(float value) const;
	friend const TimeInterval operator*(float value, const TimeInterval& interval);
	const TimeInterval operator/(float value) const;

	TimeInterval& operator+=(const TimeInterval& interval);
	TimeInterval& operator-=(const TimeInterval& interval);
	TimeInterval& operator*=(float value);
	TimeInterval& operator/=(float value);

	bool operator==(const TimeInterval& interval) noexcept;
	bool operator!=(const TimeInterval& interval) noexcept;
	bool operator<(const TimeInterval& interval) noexcept;
	bool operator>(const TimeInterval& interval) noexcept;
	bool operator<=(const TimeInterval& interval) noexcept;
	bool operator>=(const TimeInterval& interval) noexcept;

	friend TimeInterval operator""_ns(long double ns);
	friend TimeInterval operator""_ns(unsigned long long ns);
	friend TimeInterval operator""_us(long double us);
	friend TimeInterval operator""_us(unsigned long long us);
	friend TimeInterval operator""_ms(long double ms);
	friend TimeInterval operator""_ms(unsigned long long ms);
	friend TimeInterval operator""_s(long double s);
	friend TimeInterval operator""_s(unsigned long long s);
	friend TimeInterval operator""_min(long double min);
	friend TimeInterval operator""_min(unsigned long long min);
	friend TimeInterval operator""_h(long double h);
	friend TimeInterval operator""_h(unsigned long long h);

	static const TimeInterval ZERO;
	
private:
	using Duration_ = std::chrono::duration<
		std::chrono::steady_clock::rep,
		std::chrono::steady_clock::period>;

	TimeInterval(const Duration_& duration);

	Duration_ duration_;
};

TimeInterval operator""_ns(long double ns);
TimeInterval operator""_ns(unsigned long long ns);
TimeInterval operator""_us(long double us);
TimeInterval operator""_us(unsigned long long us);
TimeInterval operator""_ms(long double ms);
TimeInterval operator""_ms(unsigned long long ms);
TimeInterval operator""_s(long double s);
TimeInterval operator""_s(unsigned long long s);
TimeInterval operator""_min(long double min);
TimeInterval operator""_min(unsigned long long min);
TimeInterval operator""_h(long double h);
TimeInterval operator""_h(unsigned long long h);

}

using snow::operator""_ns;
using snow::operator""_us;
using snow::operator""_ms;
using snow::operator""_s;
using snow::operator""_min;
using snow::operator""_h;
