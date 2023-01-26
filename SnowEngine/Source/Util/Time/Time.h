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
	JAN = 1,	/// \~english January \~russian ������
	FEB,		/// \~english February \~russian �������
	MAR,		/// \~english March \~russian ����
	APR,		/// \~english April \~russian ������
	MAY,		/// \~english May \~russian ���
	JUN,		/// \~english June \~russian ����
	JUL,		/// \~english July \~russian ����
	AUG,		/// \~english August \~russian ������
	SEP,		/// \~english September \~russian ��������
	OCT,		/// \~english October \~russian �������
	NOV,		/// \~english November \~russian ������
	DEC			/// \~english December \~russian �������
};

enum class EWeekDay
{
	MON = 0,	/// \~english Monday \~russian �����������
	TUE,		/// \~english Tuesday \~russian �������
	WED,		/// \~english Wednesday \~russian �����
	THU,		/// \~english Thursday \~russian �������
	FRI,		/// \~english Friday \~russian �������
	SAT,		/// \~english Saturday \~russian �������
	SUN			/// \~english Sunday \~russian �����������
};

struct STime
{
	int year;			/// \~english The year, e.�g. 2024 \~russian ���, ��������, 2024
	EMonth month;		/// \~english The month \~russian �����
	int day;			/// \~english The day of month, [1, 31] \~russian ���� ������, [1, 31]
	EWeekDay week_day;	/// \~english The day of week \~russian ���� ������
	int year_day;		/// \~english Days since 1st of January, [0, 365] \~russian ���� � 1 ������, [0, 365]
	int hour;			/// \~english Hours, [0, 23] \~russian ����, [0, 23]
	int minute;			/// \~english Minutes, [0, 59] \~russian ������, [0, 59]
	int second;			/// \~english Seconds, [0, 60] (including leap second) \~russian �������, [0, 60] (������� ������� �����������)
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
