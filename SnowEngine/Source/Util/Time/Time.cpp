    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Time.cpp                    //
////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS

#include "Time.h"

#include <ctime>

#include "../Types/String.h"
#include "../Util.h"

using namespace snow;

String month_to_string_(time::EMonth month)
{
	switch (month)
	{
	case time::EMonth::JAN: return L"January"_s;
	case time::EMonth::FEB: return L"February"_s;
	case time::EMonth::MAR: return L"March"_s;
	case time::EMonth::APR: return L"April"_s;
	case time::EMonth::MAY: return L"May"_s;
	case time::EMonth::JUN: return L"June"_s;
	case time::EMonth::JUL: return L"July"_s;
	case time::EMonth::AUG: return L"August"_s;
	case time::EMonth::SEP: return L"September"_s;
	case time::EMonth::OCT: return L"October"_s;
	case time::EMonth::NOV: return L"November"_s;
	default: return L"December"_s;
	}
}

String month_to_str_(time::EMonth month)
{
	switch (month)
	{
	case time::EMonth::JAN: return L"Jan"_s;
	case time::EMonth::FEB: return L"Feb"_s;
	case time::EMonth::MAR: return L"Mar"_s;
	case time::EMonth::APR: return L"Apr"_s;
	case time::EMonth::MAY: return L"May"_s;
	case time::EMonth::JUN: return L"Jun"_s;
	case time::EMonth::JUL: return L"Jul"_s;
	case time::EMonth::AUG: return L"Aug"_s;
	case time::EMonth::SEP: return L"Sep"_s;
	case time::EMonth::OCT: return L"Oct"_s;
	case time::EMonth::NOV: return L"Nov"_s;
	default: return L"Dec"_s;
	}
}

String weekday_to_string_(time::EWeekDay week_day)
{
	switch (week_day)
	{
	case time::EWeekDay::MON: return L"Monday"_s;
	case time::EWeekDay::TUE: return L"Tuesday"_s;
	case time::EWeekDay::WED: return L"Wednesday"_s;
	case time::EWeekDay::THU: return L"Thursday"_s;
	case time::EWeekDay::FRI: return L"Friday"_s;
	case time::EWeekDay::SAT: return L"Saturday"_s;
	default: return L"Sunday"_s;
	}
}

String weekday_to_str_(time::EWeekDay week_day)
{
	switch (week_day)
	{
	case time::EWeekDay::MON: return L"Mon"_s;
	case time::EWeekDay::TUE: return L"Tue"_s;
	case time::EWeekDay::WED: return L"Wed"_s;
	case time::EWeekDay::THU: return L"Thu"_s;
	case time::EWeekDay::FRI: return L"Fri"_s;
	case time::EWeekDay::SAT: return L"Sat"_s;
	default: return L"Sun"_s;
	}
}

time::STime time::to_stime(std::chrono::time_point<std::chrono::steady_clock> point)
{
	std::chrono::time_point<std::chrono::system_clock> system(
		std::chrono::duration_cast<std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period>>(
			point.time_since_epoch() - std::chrono::steady_clock::now().time_since_epoch()) +
		std::chrono::system_clock::now().time_since_epoch());
	std::time_t time = std::chrono::system_clock::to_time_t(system);
	return to_stime(*std::localtime(&time));
}

time::STime time::to_stime(std::tm point)
{
	time::STime ret;
	ret.year = point.tm_year + 1900;
	ret.month = static_cast<time::EMonth>(point.tm_mon + 1);
	ret.day = point.tm_mday;
	ret.week_day = (point.tm_wday == 0 ? time::EWeekDay::SUN : static_cast<time::EWeekDay>(point.tm_wday - 1));
	ret.year_day = point.tm_yday;
	ret.hour = point.tm_hour;
	ret.minute = point.tm_min;
	ret.second = point.tm_sec;
	return ret;
}

String time::to_string(time::STime point, const String& format)
{
	String result;
	for (int i = 0; i < format.size(); i++)
	{
		switch (format[i])
		{
		case L'%':
		{
			if (i < format.size() - 1)
			{
				result += format[i + 1];
				i++;
				continue;
			}
			break;
		}
		case L'y':
		case L'Y': // Year
		{
			// yyyy
			if (i < format.size() - 3 &&
				(format[i + 1] == L'y' || format[i + 1] == L'Y') &&
				(format[i + 2] == L'y' || format[i + 2] == L'Y') &&
				(format[i + 3] == L'y' || format[i + 3] == L'Y'))
			{
				result += util::to_string(point.year);
				i += 3;
				continue;
			}
			// yy
			else if (i < format.size() - 1 &&
				(format[i + 1] == L'y' || format[i + 1] == L'Y'))
			{
				int year = point.year % 100;
				result += year >= 10 ? util::to_string(point.year % 100) : L"0"_s + util::to_string(point.year % 100);
				i++;
				continue;
			}
			break;
		}
		case L'M': // Month
		{
			// MMMM
			if (i < format.size() - 3 &&
				format[i + 1] == L'M' && format[i + 2] == L'M' && format[i + 3] == L'M')
			{
				result += month_to_string_(point.month).to_upper();
				i += 3;
				continue;
			}
			// Mmmm
			else if (i < format.size() - 3 &&
				format[i + 1] == L'm' && format[i + 2] == L'm' && format[i + 3] == L'm')
			{
				result += month_to_string_(point.month);
				i += 3;
				continue;
			}
			// MMM
			else if (i < format.size() - 2 &&
				format[i + 1] == L'M' && format[i + 2] == L'M')
			{
				result += month_to_str_(point.month).to_upper();
				i += 2;
				continue;
			}
			// Mmm
			else if (i < format.size() - 2 &&
				format[i + 1] == L'm' && format[i + 2] == L'm')
			{
				result += month_to_str_(point.month);
				i += 2;
				continue;
			}
			// MM
			else if (i < format.size() - 1 && format[i + 1] == L'M')
			{
				int month = static_cast<int>(point.month);
				result += month >= 10 ? util::to_string(month) : L"0"_s + util::to_string(month);
				i++;
				continue;
			}
			// M
			else
			{
				result += util::to_string(static_cast<int>(point.month));
				continue;
			}
			break;
		}
		case L'd': // Day of month
		{
			// dd
			if (i < format.size() - 1 && format[i + 1] == L'd')
			{
				int day = point.day;
				result += day >= 10 ? util::to_string(day) : L"0"_s + util::to_string(day);
				i++;
				continue;
			}
			// dt
			if (i < format.size() - 1 && format[i + 1] == L't')
			{
				String ending;
				if (point.day == 1 || point.day == 21 || point.day == 31)
				{
					ending = L"st"_s;
				}
				else if (point.day == 2 || point.day == 22)
				{
					ending = L"nd"_s;
				}
				else if (point.day == 3 || point.day == 23)
				{
					ending = L"rd"_s;
				}
				else
				{
					ending = L"th"_s;
				}

				result += util::to_string(point.day) + ending;
				i++;
				continue;
			}
			// d
			else
			{
				result += util::to_string(point.day);
				continue;
			}
			break;
		}
		case L'D': // Day of year
		{
			result += util::to_string(point.year_day);
			continue;
		}
		case L'w': // Day of week
		{
			// ww
			if (i < format.size() - 1 && format[i + 1] == L'w')
			{
				result += weekday_to_string_(point.week_day);
				i++;
				continue;
			}
			// w
			else
			{
				result += weekday_to_str_(point.week_day);
				continue;
			}
			break;
		}
		case L'W': // Day of week
		{
			// WW
			if (i < format.size() - 1 && format[i + 1] == L'W')
			{
				result += weekday_to_string_(point.week_day).to_upper();
				i++;
				continue;
			}
			// W
			else
			{
				result += weekday_to_str_(point.week_day).to_upper();
				continue;
			}
			break;
		}
		case L'h': // Hour (12)
		{
			// hh
			if (i < format.size() - 1 && format[i + 1] == L'h')
			{
				int hour = point.hour % 12 == 0 ? 12 : point.hour % 12;
				result += hour >= 10 ? util::to_string(hour) : L"0"_s + util::to_string(hour);
				i++;
				continue;
			}
			// h
			else
			{
				result += util::to_string(point.hour % 12 == 0 ? 12 : point.hour % 12);
				continue;
			}
			break;
		}
		case L'H': // Hour (24)
		{
			// HH
			if (i < format.size() - 1 && format[i + 1] == L'H')
			{
				result += point.hour >= 10 ? util::to_string(point.hour) : L"0"_s + util::to_string(point.hour);
				i++;
				continue;
			}
			// H
			else
			{
				result += util::to_string(point.hour);
				continue;
			}
			break;
		}
		case L'A': // AM / PM
		{
			if (point.hour <= 12 && point.hour > 0)
			{
				result += L"AM";
			}
			else
			{
				result += L"PM";
			}
			continue;
		}
		case L'a': // am / pm
		{
			if (point.hour < 12)
			{
				result += L"am";
			}
			else
			{
				result += L"pm";
			}
			continue;
		}
		case L'm': // Minute
		{
			// mm
			if (i < format.size() - 1 && format[i + 1] == L'm')
			{
				result += point.minute >= 10 ? util::to_string(point.minute) : L"0"_s + util::to_string(point.minute);
				i++;
				continue;
			}
			// m
			else
			{
				result += util::to_string(point.minute);
				continue;
			}
			break;
		}
		case L's':
		case L'S': // Second
		{
			// ss
			if (i < format.size() - 1 &&
				(format[i + 1] == L's' || format[i + 1] == L'S'))
			{
				result += point.second >= 10 ? util::to_string(point.second) : L"0"_s + util::to_string(point.second);
				i++;
				continue;
			}
			// s
			else
			{
				result += util::to_string(point.second);
				continue;
			}
			break;
		}
		}
		result += format[i];
	}
	return result;
}

String time::to_string(std::chrono::time_point<std::chrono::steady_clock> point, const String& format)
{
	return to_string(to_stime(point), format);
}

String time::to_string(std::tm point, const String& format)
{
	return to_string(to_stime(point), format);
}

String time::to_string(std::chrono::duration<std::chrono::steady_clock::rep, std::chrono::steady_clock::period> duration,
	const String& format)
{
	String result;

	long long nn = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
	long long uu = nn / 1000;
	long long ii = uu / 1000;
	long long ss = ii / 1000;
	long long mm = ss / 60;
	long long hh = mm / 60;

	int n = nn % 1000;
	int u = uu % 1000;
	int i = ii % 1000;
	int s = ss % 60;
	int m = mm % 60;

	for (int j = 0; j < format.size(); j++)
	{
		switch (format[j])
		{
		case L'%':
		{
			if (i < format.size() - 1)
			{
				result += format[j + 1];
				j++;
				continue;
			}
			break;
		}
		case L'h': // Hour
		{
			// hh
			if (j < format.size() - 1 &&
				(format[j + 1] == L'h' || format[j + 1] == L'H'))
			{
				result += hh >= 10 ? util::to_string(hh) : L"0"_s + util::to_string(hh);
				j++;
				continue;
			}
			// h
			else
			{
				result += util::to_string(hh);
				continue;
			}
			break;
		}
		case L'm': // Minute
		{
			// mm
			if (j < format.size() - 1 && format[j + 1] == L'm')
			{
				result += m >= 10 ? util::to_string(m) : L"0"_s + util::to_string(m);
				j++;
				continue;
			}
			// m
			else
			{
				result += util::to_string(m);
				continue;
			}
			break;
		}
		case L'M':
		{
			result += util::to_string(mm);
			continue;
		}
		case L's': // Second
		{
			// ss
			if (j < format.size() - 1 && format[j + 1] == L's')
			{
				result += s >= 10 ? util::to_string(s) : L"0"_s + util::to_string(s);
				j++;
				continue;
			}
			// s
			else
			{
				result += util::to_string(s);
				continue;
			}
			break;
		}
		case L'S':
		{
			result += util::to_string(ss);
			continue;
		}
		case L'i': // Millisecond
		{
			// iii
			if (j < format.size() - 2 &&
				format[j + 1] == L'i' && format[j + 2] == L'i')
			{
				result += j >= 100 ? util::to_string(i) : (j >= 10 ? L"0"_s + util::to_string(i) : L"00"_s + util::to_string(i));
				j++;
				continue;
			}
			// i
			else
			{
				result += util::to_string(i);
				continue;
			}
			break;
		}
		case L'I':
		{
			result += util::to_string(ii);
			continue;
		}
		case L'u': // Microsecond
		{
			// uuu
			if (j < format.size() - 2 &&
				format[j + 1] == L'u' && format[j + 2] == L'u')
			{
				result += u >= 100 ? util::to_string(u) : (u >= 10 ? L"0"_s + util::to_string(u) : L"00"_s + util::to_string(u));
				j++;
				continue;
			}
			// u
			else
			{
				result += util::to_string(u);
				continue;
			}
			break;
		}
		case L'U':
		{
			result += util::to_string(uu);
			continue;
		}
		case L'n': // Nanosecond
		{
			// nnn
			if (j < format.size() - 2 &&
				format[j + 1] == L'n' && format[j + 2] == L'n')
			{
				result += n >= 100 ? util::to_string(n) : (n >= 10 ? L"0"_s + util::to_string(n) : L"00"_s + util::to_string(n));
				j++;
				continue;
			}
			// n
			else
			{
				result += util::to_string(n);
				continue;
			}
			break;
		}
		case L'N':
		{
			result += util::to_string(nn);
			continue;
		}
		}
		result += format[i];
	}
	return result;
}

std::chrono::time_point<std::chrono::steady_clock> time::to_std_point(time::STime point)
{
	std::tm tm;
	tm.tm_year = point.year - 1900;
	tm.tm_mon = static_cast<int>(point.month) - 1;
	tm.tm_mday = point.day;
	tm.tm_hour = point.hour;
	tm.tm_min = point.minute;
	tm.tm_sec = point.second;
	std::time_t time = std::mktime(&tm);
	std::chrono::time_point<std::chrono::system_clock> system = std::chrono::system_clock::from_time_t(time);
	return std::chrono::time_point<std::chrono::steady_clock>() +
		std::chrono::duration_cast<std::chrono::duration<std::chrono::steady_clock::rep, std::chrono::steady_clock::period>>(
		system.time_since_epoch() - std::chrono::system_clock::now().time_since_epoch()) +
		std::chrono::steady_clock::now().time_since_epoch();
}
