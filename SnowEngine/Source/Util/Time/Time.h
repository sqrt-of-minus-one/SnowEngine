    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Time.h                      //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include <chrono>

#include "../Types/String.h"

namespace snow
{

enum class EMonth
{
	JAN = 1,	/// \~english January \~russian Январь
	FEB,		/// \~english February \~russian Февраль
	MAR,		/// \~english March \~russian Март
	APR,		/// \~english April \~russian Апрель
	MAY,		/// \~english May \~russian Май
	JUN,		/// \~english June \~russian Июнь
	JUL,		/// \~english July \~russian Июль
	AUG,		/// \~english August \~russian Август
	SEP,		/// \~english September \~russian Сентябрь
	OCT,		/// \~english October \~russian Октябрь
	NOV,		/// \~english November \~russian Ноябрь
	DEC			/// \~english December \~russian Декабрь
};

enum class EWeekDay
{
	MON = 0,	/// \~english Monday \~russian Понедельник
	TUE,		/// \~english Tuesday \~russian Вторник
	WED,		/// \~english Wednesday \~russian Среда
	THU,		/// \~english Thursday \~russian Четверг
	FRI,		/// \~english Friday \~russian Пятница
	SAT,		/// \~english Saturday \~russian Суббота
	SUN			/// \~english Sunday \~russian Воскресенье
};

struct STime
{
	int year;			/// \~english The year, e. g. 2024 \~russian Год, например, 2024
	EMonth month;		/// \~english The month \~russian Месяц
	int day;			/// \~english The day of month, [1, 31] \~russian День месяца, [1, 31]
	EWeekDay week_day;	/// \~english The day of week \~russian День недели
	int year_day;		/// \~english Days since 1st of January, [0, 365] \~russian Дней с 1 января, [0, 365]
	int hour;			/// \~english Hours, [0, 23] \~russian Часы, [0, 23]
	int minute;			/// \~english Minutes, [0, 59] \~russian Минуты, [0, 59]
	int second;			/// \~english Seconds, [0, 60] (including leap second) \~russian Секунды, [0, 60] (включая секунду координации)
};

class Time : public Object
{
public:
	static STime to_stime(std::chrono::time_point<std::chrono::steady_clock> point);
	static STime to_stime(std::tm point);
	static String to_string(STime point, const String& format = L"yyyy.MM.dd-HH:mm:ss"_s);
	static String to_string(std::chrono::time_point<std::chrono::steady_clock> point,
							const String& format = L"yyyy.MM.dd-HH:mm:ss"_s);
	static String to_string(std::tm point, const String& format = L"yyyy.MM.dd-HH:mm:ss"_s);
	static String to_string(std::chrono::duration<std::chrono::steady_clock::rep, std::chrono::steady_clock::period> duration,
							const String& format = L"hh:mm:ss.iii.uuu.nnn"_s);
	static std::chrono::time_point<std::chrono::steady_clock> to_std_point(STime point);
};

}
