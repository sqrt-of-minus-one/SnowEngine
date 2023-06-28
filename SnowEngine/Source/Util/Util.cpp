    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Util.cpp                    //
////////////////////////////////////////

#include "Util.h"

#include <string>
#include <cwchar>

using namespace snow;

String util::to_string(double var, int precision)
{
	// #CPP20
	// I hope one day SnowEngine will use C++20 and I'll be able to use std::format instead of std::swprintf:
	// 
	// int abs_precision = std::abs(precision);
	// std::wstring str = std::format((L"{:." + to_string(abs_precision) + L"f}").to_std_string(), var);
	// if (precision < 0) // Discard zeros in the end
	// {
	//	while (str.back() == L'0')
	//	{
	//		str.pop_back();
	//	}
	//	if (str.back() == L'.') // If the last characteer is the point, discard it
	//	{
	//		str.pop_back();
	//	}
	// }
	// return String(str);

	int abs_precision = std::abs(precision);
	int str_len = abs_precision + 3; // How many characters we need to store the number as string
	double tmp = std::abs(var);
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
	String result = str;
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
