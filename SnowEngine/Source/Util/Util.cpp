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

String util::to_string(const std::wstring& var)
{
	return String(var);
}

String util::to_string(const Path& var)
{
	return String(var.wstring());
}

std::shared_ptr<json::Element> util::to_json(int var)
{
	return std::make_shared<json::IntValue>(var);
}

std::shared_ptr<json::Element> util::to_json(double var)
{
	return std::make_shared<json::DoubleValue>(var);
}

std::shared_ptr<json::Element> util::to_json(wchar_t var)
{
	return std::make_shared<json::StringValue>(String(var));
}

std::shared_ptr<json::Element> util::to_json(bool var)
{
	return std::make_shared<json::BoolValue>(var);
}

std::shared_ptr<json::Element> util::to_json(const std::wstring& var)
{
	return std::make_shared<json::StringValue>(String(var));
}

std::shared_ptr<json::Element> util::to_json(const Path& var)
{
	return std::make_shared<json::StringValue>(String(var.wstring()));
}

int util::json_to_int(std::shared_ptr<const json::Element> json)
{
	std::shared_ptr<const json::IntValue> value = std::dynamic_pointer_cast<const json::IntValue>(json);
	if (!value)
	{
		throw std::invalid_argument("Couldn't create an integer: the JSON must be an integer value");
	}
	return value->get();
}

double util::json_to_double(std::shared_ptr<const json::Element> json, bool allow_int)
{
	std::shared_ptr<const json::DoubleValue> d_value = std::dynamic_pointer_cast<const json::DoubleValue>(json);
	if (!d_value)
	{
		if (!allow_int)
		{
			throw std::invalid_argument("Couldn't create a double: the JSON must be a double value");
		}
		std::shared_ptr<const json::IntValue> i_value = std::dynamic_pointer_cast<const json::IntValue>(json);
		if (!i_value)
		{
			throw std::invalid_argument("Couldn't create a double: the JSON must be either a double or an integer value");
		}
		return static_cast<double>(i_value->get());
	}
	return d_value->get();
}

wchar_t util::json_to_char(std::shared_ptr<const json::Element> json)
{
	std::shared_ptr<const json::StringValue> value = std::dynamic_pointer_cast<const json::StringValue>(json);
	if (!value)
	{
		throw std::invalid_argument("Couldn't create a character: the JSON must be a string value");
	}
	const String& str = value->get();
	if (str.size() != 1)
	{
		throw std::invalid_argument("Couldn't create a character: the JSON string must only have 1 character");
	}
	return str[0];
}

bool util::json_to_bool(std::shared_ptr<const json::Element> json)
{
	std::shared_ptr<const json::BoolValue> value = std::dynamic_pointer_cast<const json::BoolValue>(json);
	if (!value)
	{
		throw std::invalid_argument("Couldn't create a boolean: the JSON must be a boolean value");
	}
	return value->get();
}

String util::json_to_string(std::shared_ptr<const json::Element> json)
{
	std::shared_ptr<const json::StringValue> value = std::dynamic_pointer_cast<const json::StringValue>(json);
	if (!value)
	{
		throw std::invalid_argument("Couldn't create a string: the JSON must be a string value");
	}
	return value->get();
}

Path util::json_to_path(std::shared_ptr<const json::Element> json)
{
	return Path(json_to_string(json).to_std_string());
}
