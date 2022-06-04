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
	TimeInterval() noexcept;
	TimeInterval(const TimeInterval& interval) noexcept;

	virtual String to_string() const noexcept override;
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

	bool operator==(const TimeInterval& interval);
	bool operator!=(const TimeInterval& interval);
	bool operator<(const TimeInterval& interval);
	bool operator>(const TimeInterval& interval);
	bool operator<=(const TimeInterval& interval);
	bool operator>=(const TimeInterval& interval);

	friend TimeInterval operator""_ns(long double ns) noexcept;
	friend TimeInterval operator""_ns(unsigned long long ns) noexcept;
	friend TimeInterval operator""_us(long double us) noexcept;
	friend TimeInterval operator""_us(unsigned long long us) noexcept;
	friend TimeInterval operator""_ms(long double ms) noexcept;
	friend TimeInterval operator""_ms(unsigned long long ms) noexcept;
	friend TimeInterval operator""_s(long double s) noexcept;
	friend TimeInterval operator""_s(unsigned long long s) noexcept;
	friend TimeInterval operator""_min(long double min) noexcept;
	friend TimeInterval operator""_min(unsigned long long min) noexcept;
	friend TimeInterval operator""_h(long double h) noexcept;
	friend TimeInterval operator""_h(unsigned long long h) noexcept;

	static const TimeInterval ZERO;
	
private:
	std::chrono::duration<
		std::chrono::steady_clock::rep,
		std::chrono::steady_clock::period> duration_;
};

TimeInterval operator""_ns(long double ns) noexcept;
TimeInterval operator""_ns(unsigned long long ns) noexcept;
TimeInterval operator""_us(long double us) noexcept;
TimeInterval operator""_us(unsigned long long us) noexcept;
TimeInterval operator""_ms(long double ms) noexcept;
TimeInterval operator""_ms(unsigned long long ms) noexcept;
TimeInterval operator""_s(long double s) noexcept;
TimeInterval operator""_s(unsigned long long s) noexcept;
TimeInterval operator""_min(long double min) noexcept;
TimeInterval operator""_min(unsigned long long min) noexcept;
TimeInterval operator""_h(long double h) noexcept;
TimeInterval operator""_h(unsigned long long h) noexcept;

}

using snow::operator""_ns;
using snow::operator""_us;
using snow::operator""_ms;
using snow::operator""_s;
using snow::operator""_min;
using snow::operator""_h;
