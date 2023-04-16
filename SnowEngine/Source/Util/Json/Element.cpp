    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Element.cpp                 //
////////////////////////////////////////

#include "Element.h"

#include <fstream>
#include <sstream>
#include <filesystem>

#include "../Types/String.h"
#include "JsonObject.h"
#include "Array.h"
#include "Value.h"

using namespace snow;

#define PASS(c) \
	while ((c) == L' ' || (c) == L'\t' || (c) == L'\n') \
	{ \
		stream.get(c); \
		(c) = stream.peek(); \
	} \

String json::Element::to_string() const
{
	std::wostringstream stream;
	to_stream(stream);
	return stream.str();
}

void json::Element::save(const String& filename) const
{
	if (!std::filesystem::exists(filename.to_std_string()))
	{
		std::filesystem::create_directories(filename.to_std_string());
	}
	std::wofstream file(filename.to_std_string());
	if (!file.is_open())
	{
		throw std::runtime_error("The file couldn't be created or accessed");
	}
	to_stream(file);
	file.close();
}

std::unique_ptr<json::Element> json::Element::from_string(const String& string)
{
	std::wistringstream stream(string.to_std_string());
	return read_element_(stream);
}

std::unique_ptr<json::Element> json::Element::load(const String& filename)
{
	std::wifstream file(filename.to_std_string());
	if (!file.is_open())
	{
		throw std::runtime_error("The file does not exist or cannot be accessed");
	}
	
	return read_element_(file);
}

std::unique_ptr<json::Element> json::Element::read_element_(std::wistream& stream)
{
	wchar_t c;
	while (stream.read(&c, 1))
	{
		switch (c)
		{
		case L' ':
		case L'\t':
		case L'\n':
		{
			break;
		}
		case L'{':
		{
			return read_object_(stream);
		}
		case L'[':
		{
			return read_array_(stream);
		}
		case L'"':
		case L'\'':
		{
			return std::make_unique<StringValue>(read_string_(stream, c));
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
		case L'.':
		case L'-':
		case L'+':
		{
			return read_number_(stream, c);
		}
		case L't':
		case L'T':
		{
			if (!read_lit_(stream, L"true"_s))
			{
				throw std::runtime_error("Invalid JSON");
			}
			return std::make_unique<BoolValue>(true);
		}
		case L'f':
		case L'F':
		{
			if (!read_lit_(stream, L"false"_s))
			{
				throw std::runtime_error("Invalid JSON");
			}
			return std::make_unique<BoolValue>(false);
		}
		case L'n':
		case L'N':
		{
			if (!read_lit_(stream, L"null"_s))
			{
				throw std::runtime_error("Invalid JSON");
			}
			return std::make_unique<NullValue>();
		}
		case L'/':
		{
			read_comment_(stream);
			break;
		}
		default:
		{
			throw std::runtime_error("Invalid JSON");
		}
		}
	}
	throw std::runtime_error("Invalid JSON");
}

std::unique_ptr<json::JsonObject> json::Element::read_object_(std::wistream& stream)
{
	std::unique_ptr<JsonObject> result;
	while (true)
	{
		wchar_t c = stream.peek();
		PASS(c);
		if (c == L'}')
		{
			stream.get(c);
			return result;
		}
		
		String key;
		if (c == L'"' || c == L'\'')
		{
			stream.get(c);
			key = read_string_(stream, c);
		}
		else
		{
			throw("Invalid JSON: invalid object, a key was expected");
		}
		
		c = stream.peek();
		PASS(c);
		if (c != L':')
		{
			throw("Invalid JSON: invalid object, ':' was expected aftee the key");
		}
		stream.get(c);
		c = stream.peek();
		PASS(c);
		
		result->get_content()[key] = read_element_(stream);
		
		c = stream.peek();
		while (c == L' ' || c == L'\t' || c == L'\n')
		{
			stream.get(c);
			c = stream.peek();
		}
		if (c == L'}')
		{
			stream.get(c);
			return result;
		}
		if (c == L',')
		{
			continue;
		}
		throw std::runtime_error("Invalid JSON: invalid object");
	}
}

std::unique_ptr<json::Array> json::Element::read_array_(std::wistream& stream)
{
	std::unique_ptr<Array> result;
	while (true)
	{
		wchar_t c = stream.peek();
		PASS(c);
		if (c == L']')
		{
			stream.get(c);
			return result;
		}
		
		result->get_content().push_back(read_element_(stream));
		
		c = stream.peek();
		PASS(c);
		if (c == L']')
		{
			stream.get(c);
			return result;
		}
		if (c == L',')
		{
			continue;
		}
		throw std::runtime_error("Invalid JSON: invalid array");
	}
}

String json::Element::read_string_(std::wistream& stream, wchar_t first)
{
	wchar_t c;
	String str;
	bool escape = false;
	while (stream.get(c))
	{
		if (escape)
		{
			switch (c)
			{
			case L't':
			{
				str += L'\t';
				break;
			}
			case L'n':
			{
				str += L'\n';
				break;
			}
			case L'r':
			{
				str += L'\r';
				break;
			}
			case L'f':
			{
				str += L'\f';
				break;
			}
			case L'b':
			{
				str += L'\b';
				break;
			}
			case L'\n':
			{
				break;
			}
			default:
			{
				str += c;
			}
			}
			escape = false;
		}
		else
		{
			switch (c)
			{
			case L'\\':
			{
				escape = true;
				break;
			}
			case L'"':
			case L'\'':
			{
				if (c == first)
				{
					return str;
				}
				[[fallthrough]];
			}
			default:
			{
				str += c;
			}
			}
		}
	}
	throw std::runtime_error("Invalid JSON: the string is not closed");
}
			

std::unique_ptr<json::Element> json::Element::read_number_(std::wistream& stream, wchar_t first)
{
	String result;
	wchar_t c = stream.peek();
	int base = 10;
	if (first == L'0' && (c == L'x' || c == L'X' || c == L'h' || c == L'H'))
	{
		base = 16;
		stream.get(c);
		c = stream.peek();
	}
	else if (first == L'0' && (c == L'b' || c == L'B'))
	{
		base = 2;
		stream.get(c);
		c = stream.peek();
	}
	else if (first == L'0' && (c == L'o' || c == L'O'))
	{
		base = 8;
		stream.get(c);
		c = stream.peek();
	}
	else
	{
		result += first;
	}
	double has_point = false;
	while (c >= L'0' && c <= L'9' ||
		   c >= L'A' && c <= L'F' ||
		   c == L'.' || c == L'\'')
	{
		has_point = c == L'.';
		result += c;
		stream.get(c);
		c = stream.peek();
	}
	
	try
	{
		switch (base)
		{
		case 2:
		{
			return std::make_unique<IntValue>(result.to_int<2>());
		}
		case 8:
		{
			return std::make_unique<IntValue>(result.to_int<8>());
		}
		case 10:
		{
			if (has_point && base == 10)
			{
				return std::make_unique<DoubleValue>(result.to_double());
			}
			return std::make_unique<IntValue>(result.to_int<10>());
		}
		case 16:
		{
			return std::make_unique<IntValue>(result.to_int<16>());
		}
		}
	}
	catch (std::invalid_argument e)
	{
		throw std::runtime_error("Invalid JSON");
	}
}

bool json::Element::read_lit_(std::wistream& stream, const String& lit)
{
	String up = lit.to_upper();
	String low = lit.to_lower();
	for (int i = 1; i < lit.size(); i++)
	{
		wchar_t c = stream.peek();
		if (c != up[i] && c != low[i])
		{
			return false;
		}
		stream.get(c);
	}
	return true;
}

void json::Element::read_comment_(std::wistream& stream)
{
	wchar_t c;
	stream.get(c);
	if (c == L'/')
	{
		while (stream.get(c) && c != L'\n')
			;
		return;
	}
	if (c == L'*')
	{
		while (stream.get(c))
		{
			if (c == L'*' && stream.peek() == L'/')
			{
				stream.get(c);
				return;
			}
		}
		throw std::runtime_error("Invalid JSON: the multi-line comment is not closed");
	}
	throw std::runtime_error("Invalid JSON");
}
