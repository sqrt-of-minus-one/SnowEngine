    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: String.cpp                  //
////////////////////////////////////////

#include "String.h"

#include <cstdarg>

#include "Util.h"

using namespace snow;

double string::to_double(const String& string)
{
	return snow_::to_number_<double, 10>(string, true);
}

bool string::to_bool(const String& string)
{
	if (string.empty())
	{
		return false;
	}
	String lower = to_lower(string);
	if (lower == L"true" || lower == L"t" || lower == L"1")
	{
		return true;
	}
	if (lower == L"false" || lower == L"f" || lower == L"0")
	{
		return false;
	}
	try
	{
		return static_cast<bool>(to_double(string));
	}
	catch (std::invalid_argument e)
	{
		return true;
	}
}

String string::reverse(const String& string)
{
	String ret = string;
	for (int i = 0; i < ret.length(); i++)
	{
		ret[i] = ret[ret.length() - 1 - i];
	}
	return ret;
}

std::vector<String> string::split(const String& string, const String& separator, int parts)
{
	std::vector<String> result;
	if (parts <= 0)
	{
		parts = string.length();
	}
	if (parts == 1)
	{
		result.push_back(string);
		return result;
	}

	String str = string;
	for (int i = 0; i < parts; i++)
	{
		std::size_t sep_pos = str.find(separator);
		if (sep_pos == str.npos)
		{
			break;
		}
		else
		{
			result.push_back(str.substr(0, sep_pos));
			str.erase(0, sep_pos + separator.length());
		}
	}
	result.push_back(str);
	return result;
}

wchar_t string::to_lower(wchar_t c)
{
	return std::towlower(c);
}

String string::to_lower(const String& string)
{
	String ret = string;
	for (wchar_t& i : ret)
	{
		i = to_lower(i);
	}
	return ret;
}

wchar_t string::to_upper(wchar_t c)
{
	return std::towupper(c);
}

String string::to_upper(const String& string)
{
	String ret = string;
	for (wchar_t& i : ret)
	{
		i = to_upper(i);
	}
	return ret;
}

String string::escape(const String& string)
{
	String result;
	for (wchar_t i : string)
	{
		switch (i)
		{
		case L'\'':
		{
			result += L"\\\'";
			break;
		}
		case L'\"':
		{
			result += L"\\\"";
			break;
		}
		case L'\\':
		{
			result += L"\\\\";
			break;
		}
		case L'\a':
		{
			result += L"\\\a";
			break;
		}
		case L'\b':
		{
			result += L"\\\b";
			break;
		}
		case L'\f':
		{
			result += L"\\\f";
			break;
		}
		case L'\n':
		{
			result += L"\\\n";
			break;
		}
		case L'\r':
		{
			result += L"\\\r";
			break;
		}
		case L'\t':
		{
			result += L"\\\t";
			break;
		}
		case L'\v':
		{
			result += L"\\\v";
			break;
		}
		default:
		{
			result += i;
		}
		}
	}
	return result;
}

String string::unescape(const String& string)
{
	String result;
	for (int i = 0; i < string.length(); i++)
	{
		if (string[i] == L'\\' && i < string.length() - 1)
		{
			switch (string[++i])
			{
			case L'\'':
			{
				result += L'\'';
				break;
			}
			case L'\"':
			{
				result += L'\"';
				break;
			}
			case L'\\':
			{
				result += L'\\';
				break;
			}
			case L'a':
			{
				result += L'\a';
				break;
			}
			case L'b':
			{
				result += L'\b';
				break;
			}
			case L'f':
			{
				result += L'\f';
				break;
			}
			case L'n':
			{
				result += L'\n';
				break;
			}
			case L'r':
			{
				result += L'\r';
				break;
			}
			case L't':
			{
				result += L'\t';
				break;
			}
			case L'v':
			{
				result += L'\v';
				break;
			}
			default:
			{
				result += L'\\';
				i--;
			}
			}
		}
		else
		{
			result += string[i];
		}
	}
	return result;
}

bool string::is_num(wchar_t c)
{
	return c >= L'0' && c <= L'9';
}

bool string::is_num(const String& string)
{
	for (wchar_t i : string)
	{
		if (!is_num(i))
		{
			return false;
		}
	}
	return true;
}

bool string::is_alpha(wchar_t c)
{
	return c >= L'a' && c <= L'z' ||
		   c >= L'A' && c <= L'Z';
}

bool string::is_alpha(const String& string)
{
	for (wchar_t i : string)
	{
		if (!is_alpha(i))
		{
			return false;
		}
	}
	return true;
}

bool string::is_asbuka(wchar_t c)
{
	return c >= L'а' && c <= L'я' ||
		   c >= L'А' && c <= L'Я' ||
		   c == L'ґ' || c == L'Ґ' ||
		   c == L'є' || c == L'Є' ||
		   c == L'ё' || c == L'Ё' ||
		   c == L'і' || c == L'І' ||
		   c == L'ї' || c == L'Ї' ||
		   c == L'ў' || c == L'Ў';
}

bool string::is_asbuka(const String& string)
{
	for (wchar_t i : string)
	{
		if (!is_asbuka(i))
		{
			return false;
		}
	}
	return true;
}

bool string::is_space(wchar_t c)
{
	return c == L' ' || c == L'\t' || c == L'\n' || c == L'\r' || c == L'\v' || c == L'\f';
}

bool string::is_space(const String& string)
{
	for (wchar_t i : string)
	{
		if (!is_space(i))
		{
			return false;
		}
	}
	return true;
}

String string::format(const String& string, ...)
{
	String result;
	va_list list;

	va_start(list, string);
	for (int i = 0; i < string.size(); i++)
	{
		if (string[i] == L'%')
		{
			String seq = L"%";
			bool finish = false;
			int value = 0;
			wchar_t char_to_fill = L' ';
			// If the number starts with 0, we should put 0's before value
			if (string[i + 1] == L'0')
			{
				char_to_fill = L'0';
				seq += L'0';
				i++;
			}

			for (i++; i < string.size() && !finish; i++)
			{
				seq += string[i];
				switch (string[i])
				{
				case L'0':
				case L'1':
				case L'2':
				case L'3':
				case L'4':
				case L'5':
				case L'6':
				case L'7':
				case L'8':
				case L'9':
				{
					value *= 10;
					value += static_cast<int>(string[i] - L'0');
					break;
				}
				case L'%':
				{
					seq = L'%';
					finish = true;
					break;
				}
				case L'b':
				{
					seq = util::to_string<2>(va_arg(list, int));
					for (int j = seq.size(); j < value; j++)
					{
						seq.insert(0, 1, char_to_fill);
					}
					finish = true;
					break;
				}
				case L'c':
				{
					seq = va_arg(list, wchar_t);
					finish = true;
					break;
				}
				case L'd':
				case L'i':
				{
					seq = util::to_string(va_arg(list, int));
					for (int j = seq.size(); j < value; j++)
					{
						seq.insert(0, 1, char_to_fill);
					}
					finish = true;
					break;
				}
				case L'f':
				{
					seq = util::to_string(va_arg(list, double));
					for (int j = seq.size(); j < value; j++)
					{
						seq.insert(0, 1, char_to_fill);
					}
					finish = true;
					break;
				}
				case L'h':
				{
					seq = util::to_string<16>(va_arg(list, int));
					for (int j = seq.size(); j < value; j++)
					{
						seq.insert(0, 1, char_to_fill);
					}
					finish = true;
					break;
				}
				case L'o':
				{
					seq = util::to_string<8>(va_arg(list, int));
					for (int j = seq.size(); j < value; j++)
					{
						seq.insert(0, 1, char_to_fill);
					}
					finish = true;
					break;
				}
				case L's':
				{
					seq = va_arg(list, String);
					finish = true;
					break;
				}
				default:
				{
					finish = true;
				}
				}
			}
			result += seq;
			i--;
		}
		else
		{
			result += string[i];
		}
	}
	va_end(list);

	return result;
}

String string::operator*(const String& string, int value)
{
	if (value <= 0)
	{
		return L"";
	}

	String result = string;
	int i;
	for (i = 1; 2 * i <= value; i *= 2)
	{
		result += result;
	}
	for (; i < value; i++)
	{
		result += string;
	}
	return result;
}

String string::operator*(int value, const String& string)
{
	return string * value;
}

String& string::operator*=(String& string, int value)
{
	string = string * value;
	return string;
}

bool string::operator==(const String& string, wchar_t ch) noexcept
{
	return string.length() == 1 && string[0] == ch;
}

bool string::operator!=(const String& string, wchar_t ch) noexcept
{
	return !(string == ch);
}
