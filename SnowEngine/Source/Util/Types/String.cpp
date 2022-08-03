    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: String.cpp                  //
////////////////////////////////////////

#include "String.h"

#include <iostream>
#include <cwctype>
#include <cstdarg>

#include "../Util.h"

using namespace snow;

		/* String: public */

String::String() :
	string_()
{}

String::String(const String& string) :
	string_(string.string_)
{}

String::String(String&& string) :
	string_(std::move(string.string_))
{}

String::String(wchar_t ch) :
	string_()
{
	string_.push_back(ch);
}

String::String(const wchar_t* string) :
	string_(string)
{}

String::String(const std::wstring& string) :
	string_(string)
{}

String::String(std::wstring&& string) :
	string_(std::move(string))
{}

String String::to_string() const
{
	return *this;
}

int String::hash_code() const noexcept
{
	return static_cast<int>(std::hash<std::wstring>().operator()(string_));
}

const std::wstring& String::to_std_string() const noexcept
{
	return string_;
}

int String::size() const noexcept
{
	return static_cast<int>(string_.length());
}

bool String::is_empty() const noexcept
{
	return size() == 0;
}

void String::clear() noexcept
{
	string_.clear();
}

void String::shrink_to_fit()
{
	string_.shrink_to_fit();
}

bool String::add(wchar_t ch)
{
	string_.push_back(ch);
	return true;
}

int String::add(const String& string)
{
	string_.append(string.string_);
	return string.size();
}

bool String::add(wchar_t ch, int pos)
{
	return add(String(ch), pos);
}

int String::add(const String& string, int pos)
{
	string_.insert(pos, string.string_);
	return string.size();
}

bool String::remove(int pos)
{
	if (pos >= 0 && pos < size())
	{
		string_.erase(pos, 1);
		return true;
	}
	else
	{
		return false;
	}
}

int String::remove(int from, int to)
{
	if (from >= 0 && to <= size() && from < to)
	{
		string_.erase(from, to - from);
		return to - from;
	}
	else
	{
		return 0;
	}
}

int String::to_int() const
{
	if (!is_empty())
	{
		int res = 0;
		bool is_first = true;
		bool is_negative = false;
		bool was_dot = false;
		for (wchar_t i : string_)
		{
			switch (i)
			{
			case L'-':
			case L'–':
			{
				if (is_first)
				{
					is_negative = true;
				}
				else
				{
					throw std::invalid_argument("Couldn't convert a string to integer");
				}
				break;
			}
			case L'.':
			case L',':
			{
				if (!was_dot)
				{
					was_dot = true;
				}
				else
				{
					throw std::invalid_argument("Couldn't convert a string to integer");
				}
				break;
			}
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
				if (!was_dot)
				{
					res *= 10;
					res += static_cast<int>(i - L'0');
				}
				break;
			}
			case L' ':
			case L'\'':
			case L'`':
			case L'\t':
			{
				// We don't need to reset is_first flag
				continue;
			}
			default:
			{
				throw std::invalid_argument("Couldn't convert a string to integer");
			}
			}
			is_first = false;
		}
		return res;
	}
	else
	{
		throw std::invalid_argument("Couldn't convert a string to integer");
	}
}

int String::to_int_bin() const
{
	if (!is_empty())
	{
		int res = 0;
		bool is_first = true;
		bool is_negative = false;
		bool was_dot = false;
		for (wchar_t i : string_)
		{
			switch (i)
			{
			case L'-':
			case L'–':
			{
				if (is_first)
				{
					is_negative = true;
				}
				else
				{
					throw std::invalid_argument("Couldn't convert a string to integer as binary");
				}
				break;
			}
			case L'.':
			case L',':
			{
				if (!was_dot)
				{
					was_dot = true;
				}
				else
				{
					throw std::invalid_argument("Couldn't convert a string to integer as binary");
				}
				break;
			}
			case L'0':
			case L'1':
			{
				if (!was_dot)
				{
					res *= 2;
					res += static_cast<int>(i - L'0');
				}
				break;
			}
			case L' ':
			case L'\'':
			case L'`':
			case L'\t':
			{
				// We don't need to reset is_first flag
				continue;
			}
			default:
			{
				throw std::invalid_argument("Couldn't convert a string to integer as binary");
			}
			}
			is_first = false;
		}
		return res;
	}
	else
	{
		throw std::invalid_argument("Couldn't convert a string to integer as binary");
	}
}

int String::to_int_oct() const
{
	if (!is_empty())
	{
		int res = 0;
		bool is_first = true;
		bool is_negative = false;
		bool was_dot = false;
		for (wchar_t i : string_)
		{
			switch (i)
			{
			case L'-':
			case L'–':
			{
				if (is_first)
				{
					is_negative = true;
				}
				else
				{
					throw std::invalid_argument("Couldn't convert a string to integer as octal");
				}
				break;
			}
			case L'.':
			case L',':
			{
				if (!was_dot)
				{
					was_dot = true;
				}
				else
				{
					throw std::invalid_argument("Couldn't convert a string to integer as octal");
				}
				break;
			}
			case L'0':
			case L'1':
			case L'2':
			case L'3':
			case L'4':
			case L'5':
			case L'6':
			case L'7':
			{
				if (!was_dot)
				{
					res *= 8;
					res += static_cast<int>(i - L'0');
				}
				break;
			}
			case L' ':
			case L'\'':
			case L'`':
			case L'\t':
			{
				// We don't need to reset is_first flag
				continue;
			}
			default:
			{
				throw std::invalid_argument("Couldn't convert a string to integer as octal");
			}
			}
			is_first = false;
		}
		return res;
	}
	else
	{
		throw std::invalid_argument("Couldn't convert a string to integer as octal");
	}
}

int String::to_int_hex() const
{
	if (!is_empty())
	{
		int res = 0;
		bool is_first = true;
		bool is_negative = false;
		bool was_dot = false;
		for (wchar_t i : string_)
		{
			switch (i)
			{
			case L'-':
			case L'–':
			{
				if (is_first)
				{
					is_negative = true;
				}
				else
				{
					throw std::invalid_argument("Couldn't convert a string to integer as hexademical");
				}
				break;
			}
			case L'.':
			case L',':
			{
				if (!was_dot)
				{
					was_dot = true;
				}
				else
				{
					throw std::invalid_argument("Couldn't convert a string to integer as hexademical");
				}
				break;
			}
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
				if (!was_dot)
				{
					res *= 16;
					res += static_cast<int>(i - L'0');
				}
				break;
			}
			case L'A':
			case L'B':
			case L'C':
			case L'D':
			case L'E':
			case L'F':
			{
				if (!was_dot)
				{
					res *= 16;
					res += static_cast<int>(i - L'A') + 10;
				}
				break;
			}
			case L' ':
			case L'\'':
			case L'`':
			case L'\t':
			{
				// We don't need to reset is_first flag
				continue;
			}
			default:
			{
				throw std::invalid_argument("Couldn't convert a string to integer as hexademical");
			}
			}
			is_first = false;
		}
		return res;
	}
	else
	{
		throw std::invalid_argument("Couldn't convert a string to integer as hexademical");
	}
}

float String::to_float() const
{
	if (!is_empty())
	{
		int int_res = 0;
		float float_res = 0.f;
		bool is_first = true;
		bool is_negative = false;
		bool was_dot = false;
		for (wchar_t i : string_)
		{
			switch (i)
			{
			case L'-':
			case L'–':
			{
				if (is_first)
				{
					is_negative = true;
				}
				else
				{
					throw std::invalid_argument("Couldn't convert a string to float");
				}
				break;
			}
			case L'.':
			case L',':
			{
				if (!was_dot)
				{
					was_dot = true;
				}
				else
				{
					throw std::invalid_argument("Couldn't convert a string to float");
				}
				break;
			}
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
				if (was_dot)
				{
					float_res /= 10.f;
					float_res += static_cast<float>(i - L'0') / 10.f;
				}
				else
				{
					int_res *= 10;
					int_res += static_cast<int>(i - L'0');
				}
				break;
			}
			case L' ':
			case L'\'':
			case L'`':
			case L'\t':
			{
				// We don't need to reset is_first flag
				continue;
			}
			default:
			{
				throw std::invalid_argument("Couldn't convert a string to float");
			}
			}
			is_first = false;
		}
		return static_cast<float>(int_res) + float_res;
	}
	else
	{
		throw std::invalid_argument("Couldn't convert a string to float");
	}
}

bool String::to_bool() const
{
	if (is_empty())
	{
		return false;
	}
	String lower = to_lower();
	if (lower == L"true" || lower == L"t" || lower == L"1")
	{
		return true;
	}
	else if (lower == L"false" || lower == L"f" || lower == L"0")
	{
		return false;
	}
	else
	{
		try
		{
			return static_cast<bool>(to_float());
		}
		catch (std::invalid_argument e)
		{
			return true;
		}
	}
}

int String::find_first(wchar_t ch) const noexcept
{
	for (int i = 0; i < size(); i++)
	{
		if (string_[i] == ch)
		{
			return i;
		}
	}
	return -1;
}

int String::find_last(wchar_t ch) const noexcept
{
	for (int i = size() - 1; i >= 0; i--)
	{
		if (string_[i] == ch)
		{
			return i;
		}
	}
	return -1;
}

int String::find_first(const String& string) const noexcept
{
	int this_len = size();
	int other_len = string.size();
	if (this_len < other_len || other_len == 0)
	{
		return -1;
	}

	int match = other_len - 1;
	for (int i = size() - 1; i >= 0; i--)
	{
		if ((*this)[i] == string[match])
		{
			match--;
			if (match < 0)
			{
				return i;
			}
		}
		else
		{
			match = other_len - 1;
		}
	}
	return -1;
}

int String::find_last(const String& string) const noexcept
{
	int this_len = size();
	int other_len = string.size();
	if (this_len < other_len)
	{
		return -1;
	}

	int match = other_len - 1;
	for (int i = size() - 1; i >= 0; i--)
	{
		if ((*this)[i] == string[match])
		{
			match--;
			if (match < 0)
			{
				return i;
			}
		}
		else
		{
			match = other_len - 1;
		}
	}
	return -1;
}

bool String::contains(wchar_t ch) const noexcept
{
	return find_first(ch) > 0;
}

bool String::contains(const String& string) const noexcept
{
	return find_first(string) > 0;
}

int String::count(wchar_t ch) const noexcept
{
	int res = 0;
	for (wchar_t i : string_)
	{
		if (i == ch)
		{
			res++;
		}
	}
	return res;
}

int String::count(const String& string) const noexcept
{
	if (string.is_empty())
	{
		return 0;
	}

	int res = 0;
	for (int i = 0; i <= size() - string.size(); i++)
	{
		bool match = true;
		for (int j = 0; j < string.size(); j++)
		{
			if ((*this)[i + j] != string[j])
			{
				match = false;
				break;
			}
		}
		res += static_cast<int>(match);
	}
	return res;
}

String String::substring(int from, int to) const
{
	if (from >= 0 && to <= size() && from < to)
	{
		return String(string_.substr(from, to - from));
	}
	else
	{
		throw std::invalid_argument("Couldn't create a substring because of invalid range");
	}
}

std::vector<String> String::split(const String& separator, int parts, bool case_sensivity) const
{
	std::vector<String> ret;
	if (parts <= 0)
	{
		parts = 0;
		parts = size();
	}
	else if (parts == 1)
	{
		ret.push_back(*this);
		return ret;
	}
	String current;

	for (int i = 0; i < size(); i++)
	{
		bool is_sep = true;
		if (size() - i > separator.size())
		{
			for (int j = 0; j < separator.size() && i + j < size(); j++)
			{
				if (case_sensivity ?
					(*this)[i + j] != separator[j] :
					std::towlower((*this)[i + j]) != std::towlower(separator[j]))
				{
					is_sep = false;
					break;
				}
			}
		}
		else
		{
			is_sep = false;
		}

		if (is_sep)
		{
			ret.push_back(current);
			current.clear();
			i += separator.size() - 1;
			if (ret.size() >= parts - 1 && i < size() - 1)
			{
				ret.push_back(substring(i + 1, size()));
				return ret;
			}
		}
		else
		{
			current.add((*this)[i]);
		}
	}
	ret.push_back(current);
	return ret;
}

String String::reverse() const
{
	String ret = *this;
	for (int i = 0; i < size(); i++)
	{
		ret[i] = (*this)[size() - 1 - i];
	}
	return ret;
}

String String::to_lower() const
{
	String ret = *this;
	for (int i = 0; i < size(); i++)
	{
		ret[i] = std::towlower(ret[i]);
	}
	return ret;
}

String String::to_upper() const
{
	String ret = *this;
	for (int i = 0; i < size(); i++)
	{
		ret[i] = std::towupper(ret[i]);
	}
	return ret;
}

int String::compare(const String& first, const String& second) noexcept
{
	return first.to_std_string().compare(second.to_std_string());
}

String String::format(String string, ...)
{
	String ret;
	va_list list;

	va_start(list, string);
	for (int i = 0; i < string.size(); i++)
	{
		if (string[i] == L'%')
		{
			String seq = L'%';
			bool finish = false;
			int value = 0;
			wchar_t char_to_fill = L' ';
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
					seq = util::to_string_bin(va_arg(list, int));
					for (int j = seq.size(); j < value; j++)
					{
						seq.add(char_to_fill, 0);
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
						seq.add(char_to_fill, 0);
					}
					finish = true;
					break;
				}
				case L'f':
				{
					seq = util::to_string(va_arg(list, float));
					for (int j = seq.size(); j < value; j++)
					{
						seq.add(char_to_fill, 0);
					}
					finish = true;
					break;
				}
				case L'h':
				{
					seq = util::to_string_hex(va_arg(list, int));
					for (int j = seq.size(); j < value; j++)
					{
						seq.add(char_to_fill, 0);
					}
					finish = true;
					break;
				}
				case L'o':
				{
					seq = util::to_string_oct(va_arg(list, int));
					for (int j = seq.size(); j < value; j++)
					{
						seq.add(char_to_fill, 0);
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
			ret += seq;
			i--;
		}
		else
		{
			ret += string[i];
		}
	}
	va_end(list);

	return ret;
}

std::wstring::iterator String::begin() noexcept
{
	return string_.begin();
}

std::wstring::iterator String::end() noexcept
{
	return string_.end();
}

std::wstring::const_iterator String::begin() const noexcept
{
	return string_.cbegin();
}

std::wstring::const_iterator String::end() const noexcept
{
	return string_.cend();
}

std::wstring::const_iterator String::cbegin() const noexcept
{
	return string_.cbegin();
}

std::wstring::const_iterator String::cend() const noexcept
{
	return string_.cend();
}

String& String::operator=(wchar_t ch)
{
	string_ = ch;
	return *this;
}

String& String::operator=(const wchar_t* ch)
{
	string_ = ch;
	return *this;
}

String& String::operator=(const std::wstring& string) 
{
	std::wstring str = L"Lo";
	str = string;
	string_ = L"Hello";
	string_ = str;
	return *this;
}

String& String::operator=(std::wstring&& string) noexcept
{
	string_ = std::move(string);
	return *this;
}

String& String::operator=(const String& string)
{
	string_ = string.string_;
	return *this;
}

String& String::operator=(String&& string) noexcept
{
	string_ = std::move(string.string_);
	return *this;
}

String String::operator+(wchar_t ch) const
{
	return String(string_ + ch);
}

String String::operator+(const wchar_t* ch) const
{
	return String(string_ + std::wstring(ch));
}

String String::operator+(const std::wstring& string) const
{
	return String(string_ + string);
}

String String::operator+(const String& string) const
{
	String ret = *this;
	ret.add(string);
	return ret;
}

String snow::operator+(wchar_t ch, const String& string)
{
	String ret(string);
	ret.add(ch, 0);
	return ret;
}

String snow::operator+(const wchar_t* ch, const String& string)
{
	String ret(string);
	ret.add(ch, 0);
	return ret;
}

String snow::operator+(const std::wstring& std_str, const String& string)
{
	return String(std_str) + string;
}

String String::operator*(int value) const
{
	if (value <= 0)
	{
		return String();
	}

	String res = string_;
	int i;
	for (i = 1; 2 * i <= value; i *= 2)
	{
		res += res;
	}
	for (; i < value; i++)
	{
		res += string_;
	}
	return res;
}

String snow::operator*(int value, const String& string)
{
	return string * value;
}

String& String::operator+=(wchar_t ch)
{
	add(ch);
	return *this;
}

String& String::operator+=(const wchar_t* ch)
{
	add(String(ch));
	return *this;
}

String& String::operator+=(const std::wstring& string)
{
	add(String(string));
	return *this;
}

String& String::operator+=(const String& string)
{
	add(string);
	return *this;
}

String& String::operator*=(int value)
{
	*this = *this * value;
	return *this;
}

bool String::operator==(wchar_t ch) const noexcept
{
	return size() == 1 && string_[0] == ch;
}

bool String::operator==(const wchar_t* ch) const noexcept
{
	for (int i = 0; i < size(); i++)
	{
		if (ch[i] == '\0' || ch[i] != string_[i])
		{
			return false;
		}
	}
	return true;
}

bool String::operator==(const std::wstring& string) const noexcept
{
	return string_ == string;
}

bool String::operator==(const String& string) const noexcept
{
	return string_ == string.string_;
}

bool String::operator!=(wchar_t ch) const noexcept
{
	return !(*this == ch);
}

bool String::operator!=(const wchar_t* ch) const noexcept
{
	return !(*this == ch);
}

bool String::operator!=(const std::wstring& string) const noexcept
{
	return !(*this == string);
}

bool String::operator!=(const String& string) const noexcept
{
	return !(*this == string);
}

wchar_t& String::operator[](int index)
{
	if (index >= 0 && index < size())
	{
		return string_[index];
	}
	else
	{
		throw std::out_of_range("Index is out of string bounds");
	}
}

const wchar_t& String::operator[](int index) const
{
	if (index >= 0 && index < size())
	{
		return string_[index];
	}
	else
	{
		throw std::out_of_range("Index is out of string bounds");
	}
}

std::wostream& snow::operator<<(std::wostream& stream, const String& string)
{
	return stream << string.string_;
}

String snow::operator""_s(const wchar_t* string, std::size_t length)
{
	return String(string);
}

		/* std::hash<String>: public */

std::size_t std::hash<String>::operator()(String str) const noexcept
{
	return static_cast<size_t>(str.hash_code());
}

