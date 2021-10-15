    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: String.cpp                  //
////////////////////////////////////////

#include "String.h"

#include "../Util.h"

#include <iostream>
#include <string>
#include <cwctype>
#include <cstdarg>

using namespace snow;

String::String() noexcept :
	string_(new std::wstring)
{}

String::String(const String& string) noexcept :
	string_(new std::wstring)
{
	*string_ = *string.string_;
}

String::String(String&& string) noexcept :
	string_(std::move(string.string_))
{}

String::String(wchar_t ch) noexcept :
	string_(new std::wstring)
{
	string_->push_back(ch);
}

String::String(const wchar_t* string) noexcept :
	string_(new std::wstring(string))
{}

String::String(const std::wstring& string) noexcept :
	string_(new std::wstring(string))
{}

String::String(std::wstring&& string) noexcept :
	string_(new std::wstring(std::move(string)))
{}

String String::to_string() const noexcept
{
	return *this;
}

int String::hash_code() const noexcept
{
	int code = 0;
	int one = 1;
	for (wchar_t i : *string_)
	{
		code += one * static_cast<int>(i);
		one = -one;
	}
	return code;
}

std::wstring String::to_std_string() const noexcept
{
	return *string_;
}

int String::size() const noexcept
{
	return string_->length();
}

bool String::is_empty() const noexcept
{
	return size() == 0;
}

void String::clear() noexcept
{
	string_->clear();
}

void String::shrink_to_fit()
{
	string_->shrink_to_fit();
}

bool String::add(wchar_t ch)
{
	string_->push_back(ch);
	return true;
}

int String::add(const String& string)
{
	string_->append(*string.string_);
	return string.size();
}

bool String::add(wchar_t ch, int pos)
{
	*string_ += ch;
	return true;
}

int String::add(const String& string, int pos)
{
	string_->insert(pos, *string.string_);
	return string.size();
}

int String::to_int() const
{
	if (!is_empty())
	{
		int res = 0;
		bool is_first = true;
		bool is_negative = false;
		bool was_dot = false;
		for (wchar_t i : *string_)
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
					break;
				}
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

float String::to_float() const
{
	if (!is_empty())
	{
		int int_res = 0;
		float float_res = 0.f;
		bool is_first = true;
		bool is_negative = false;
		bool was_dot = false;
		for (wchar_t i : *string_)
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

int String::find_first(wchar_t ch) const
{
	for (int i = 0; i < size(); i++)
	{
		if ((*string_)[i] == ch)
		{
			return i;
		}
	}
	return -1;
}

int String::find_last(wchar_t ch) const
{
	for (int i = size() - 1; i >= 0; i--)
	{
		if ((*string_)[i] == ch)
		{
			return i;
		}
	}
	return -1;
}

int String::find_first(const String& string) const
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

int String::find_last(const String& string) const
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

bool String::contains(wchar_t ch) const
{
	return find_first(ch) > 0;
}

bool String::contains(const String& string) const
{
	return find_first(string) > 0;
}

int String::count(wchar_t ch) const
{
	int res = 0;
	for (wchar_t i : *string_)
	{
		if (i == ch)
		{
			res++;
		}
	}
	return res;
}

int String::count(const String& string) const
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
		return String(string_->substr(from, to - from));
	}
	else
	{
		throw std::invalid_argument("Couldn't create a substring because of invalid range");
	}
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

std::wstring::iterator String::begin() noexcept
{
	return string_->begin();
}

std::wstring::iterator String::end() noexcept
{
	return string_->end();
}

std::wstring::const_iterator String::begin() const noexcept
{
	return string_->cbegin();
}

std::wstring::const_iterator String::end() const noexcept
{
	return string_->cend();
}

std::wstring::const_iterator String::cbegin() const noexcept
{
	return string_->cbegin();
}

std::wstring::const_iterator String::cend() const noexcept
{
	return string_->cend();
}

String& String::operator=(wchar_t ch) noexcept
{
	*string_ = ch;
	return *this;
}

String& String::operator=(const wchar_t* ch) noexcept
{
	*string_ = ch;
	return *this;
}

String& String::operator=(const std::wstring& string) noexcept
{
	*string_ = string;
	return *this;
}

String& String::operator=(std::wstring&& string) noexcept
{
	*string_ = std::move(string);
	return *this;
}

String& String::operator=(const String& string) noexcept
{
	*string_ = *string.string_;
	return *this;
}

String& String::operator=(String&& string) noexcept
{
	string_ = std::move(string.string_);
	return *this;
}

String String::operator+(wchar_t ch) const
{
	return String(*string_ + ch);
}

String String::operator+(const wchar_t* ch) const
{
	return String(*string_ + std::wstring(ch));
}

String String::operator+(const std::wstring& string) const
{
	return String(*string_ + string);
}

String String::operator+(const String& string) const
{
	String ret = *this;
	ret.add(string);
	return ret;
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

bool String::operator==(wchar_t ch) noexcept
{
	return size() == 1 && (*this)[0] == ch;
}

bool String::operator==(const wchar_t* ch) noexcept
{
	for (int i = 0; i < size(); i++)
	{
		if (ch[i] == '\0' || ch[i] != (*this)[i])
		{
			return false;
		}
	}
	return true;
}

bool String::operator==(const std::wstring& string) noexcept
{
	return *string_ == string;
}

bool String::operator==(const String& string) noexcept
{
	return *string_ == *string.string_;
}

bool String::operator!=(wchar_t ch) noexcept
{
	return !(*this == ch);
}

bool String::operator!=(const wchar_t* ch) noexcept
{
	return !(*this == ch);
}

bool String::operator!=(const std::wstring& string) noexcept
{
	return !(*this == string);
}

bool String::operator!=(const String& string) noexcept
{
	return !(*this == string);
}

wchar_t& String::operator[](int index)
{
	if (index >= 0 && index < size())
	{
		return (*string_)[index];
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
		return (*string_)[index];
	}
	else
	{
		throw std::out_of_range("Index is out of string bounds");
	}
}

std::wostream& snow::operator<<(std::wostream& stream, const String& string)
{
	return stream << *string.string_;
}

int String::compare(const String& first, const String& second)
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
			if (++i >= string.size())
			{
				ret.add(L'%');
				break;
			}
			else
			{
				switch (string[i])
				{
				case L'%':
				{
					ret.add(L'%');
					break;
				}
				case L'c':
				{
					ret.add(va_arg(list, wchar_t));
					break;
				}
				case L's':
				{
					ret.add(va_arg(list, String));
					break;
				}
				case L'd':
				case L'i':
				{
					ret.add(util::to_string(va_arg(list, int)));
					break;
				}
				case L'f':
				{
					ret.add(util::to_string(va_arg(list, float)));
					break;
				}
				default:
				{
					ret.add(L'%');
					ret.add(string[i]);
				}
				}
			}
		}
		else
		{
			ret.add(string[i]);
		}
	}
	va_end(list);

	return ret;
}

String snow::operator""_s(const wchar_t* string, std::size_t length) noexcept
{
	return String(string);
}
