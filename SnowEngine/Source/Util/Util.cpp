    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Util.cpp                    //
////////////////////////////////////////

#include "Util.h"

#include <string>

#include "../Math/Math.h"

using namespace snow;

String util::to_string(long long var)
{
	if (var == 0)
	{
		return String(L"0");
	}

	String res;
	long long a = math::abs(var);
	while (a > 0)
	{
		res += static_cast<wchar_t>(static_cast<int>(L'0') + a % 10);
		a /= 10;
	}
	if (var < 0)
	{
		res += L'-';
	}
	return res.reverse();
}

String util::to_string_bin(long long var)
{
	if (var == 0)
	{
		return String(L"0");
	}

	String res;
	long long a = math::abs(var);
	while (a > 0)
	{
		res += static_cast<wchar_t>(static_cast<int>(L'0') + a % 2);
		a /= 2;
	}
	if (var < 0)
	{
		res += L'-';
	}
	return res.reverse();
}

String util::to_string_oct(long long var)
{
	if (var == 0)
	{
		return String(L"0");
	}

	String res;
	long long a = math::abs(var);
	while (a > 0)
	{
		res += static_cast<wchar_t>(static_cast<int>(L'0') + a % 8);
		a /= 8;
	}
	if (var < 0)
	{
		res += L'-';
	}
	return res.reverse();
}

String util::to_string_hex(long long var)
{
	if (var == 0)
	{
		return String(L"0");
	}

	String res;
	long long a = math::abs(var);
	while (a > 0)
	{
		int t = a % 16;
		if (t < 10)
		{
			res += static_cast<wchar_t>(static_cast<int>(L'0') + t);
		}
		else
		{
			res += static_cast<wchar_t>(static_cast<int>(L'A') + t - 10);
		}
		a /= 16;
	}
	if (var < 0)
	{
		res += L'-';
	}
	return res.reverse();
}

String util::to_string(int var)
{
	return to_string(static_cast<long long>(var));
}

String util::to_string_bin(int var)
{
	return to_string_bin(static_cast<long long>(var));
}

String util::to_string_oct(int var)
{
	return to_string_oct(static_cast<long long>(var));
}

String util::to_string_hex(int var)
{
	return to_string_hex(static_cast<long long>(var));
}

String util::to_string(float var)
{
	return std::to_wstring(var);
}

String util::to_string(wchar_t var)
{
	return String(var);
}

String util::to_string(bool var)
{
	return var ? L"true"_s : L"false"_s;
}

int util::hash_code(int var) noexcept
{
	return var;
}

int util::hash_code(float var) noexcept
{
	// Often values of float variables are between 0 and 1. Their hash codes would be the same unless we multiplied them by 1000
	return static_cast<int>(var * 1000);
}

int util::hash_code(wchar_t var) noexcept
{
	return static_cast<int>(var);
}

int util::hash_code(bool var) noexcept
{
	return static_cast<int>(var);
}
