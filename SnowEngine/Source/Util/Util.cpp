    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Util.cpp                    //
////////////////////////////////////////

#include "Util.h"

#include <string>
#include <cwchar>

using namespace snow;

String util::to_string(float var, int precision)
{
	int abs_precision = math::abs(precision);
	int str_len = abs_precision + 3; // How many characters we need to store the number as string
	float tmp = math::abs(var);
	while (tmp > 1.)
	{
		str_len++;
		tmp /= 10;
	}
	wchar_t* str = new wchar_t[str_len]; // Using std::swprintf to convert the number into the string
	str_len = std::swprintf(str, str_len, (L"%." + to_string(abs_precision) + L"f").to_std_string().c_str(), var);
	if (precision < 0) // Discard zeros in the end 
	{
		while (str[str_len - 1] == L'0')
		{
			str_len--;
		}
		if (str[str_len - 1] == L'.') // If the last character is the point, discard it
		{
			str_len--;
		}
	}
	str[str_len] = L'\0'; // Set the new end of the string
	String result= str;
	delete[] str;
	return result;
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
