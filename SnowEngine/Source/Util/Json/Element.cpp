    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Element.cpp                 //
////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//*+ *+ *+ *+ *** ____************************* ____***|*******SnowStorm*************************//
//**+ *+ *+ *+ **|*****************************|*******|*****************************************//
//*+ *+ *+ *+ ***____ ** ___ ** ___ **|*****|**____ **_|_** ___ ** ___ ** __ __ *****************//
//**+ *+ *+ *+ ******|**|***|**|***|**|**|**|******|***|***|***|**|***_**|**|**|*** SnowEngine **//
//*+ *+ *+ *+ ***_____**_***_**_____***__|__***_____***__**_____**_******_**_**_** JSON  system *//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Element.h"

#include <fstream>
#include <sstream>
#include <filesystem>

#include "../Types/String.h"
#include "JsonObject.h"
#include "Array.h"
#include "Value.h"

using namespace snow;

		/* Element: public */

String json::Element::to_string() const
{
	std::wostringstream stream;
	to_stream(stream);
	return stream.str();
}

void json::Element::save(const String& filename, bool allow_override) const
{
	if (!std::filesystem::exists(filename.to_std_string()))
	{
		std::filesystem::create_directories(filename.to_std_string());
	}
	else if (!allow_override)
	{
		throw std::runtime_error("The file with the same name already exists");
	}

	std::wofstream file(filename.to_std_string());
	if (!file.is_open())
	{
		throw std::runtime_error("The file couldn't be created or accessed");
	}
	to_stream(file);
	file.close();
}

std::shared_ptr<json::Element> json::Element::from_string(const String& string)
{
	std::wistringstream stream(string.to_std_string());
	return from_stream(stream);
}

std::shared_ptr<json::Element> json::Element::load(const String& filename)
{
	std::wifstream file(filename.to_std_string());
	if (!file.is_open())
	{
		throw std::runtime_error("The file does not exist or cannot be accessed");
	}
	return from_stream(file);
}

std::shared_ptr<json::Element> json::Element::from_stream(std::wistream& stream)
{
	wchar_t c;
	while (stream.read(&c, 1))
	{
		// Ignore space characters
		if (String::is_space(c))
		{
			continue;
		}

		switch (c)
		{
		// The beginning of an object
		case L'{':
		{
			return read_object_(stream);
		}
		// The beginning of an array
		case L'[':
		{
			return read_array_(stream);
		}
		// The bebinning of a string value
		case L'"':
		case L'\'':
		{
			return std::make_shared<StringValue>(read_string_(stream, c));
		}
		// The beginning of an integer or double value
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
		// The beginning of the true boolean value
		case L't':
		case L'T':
		{
			if (!read_lit_(stream, L"true"_s))
			{
				throw std::runtime_error("Invalid JSON");
			}
			return std::make_shared<BoolValue>(true);
		}
		// The beginning of the false boolean value
		case L'f':
		case L'F':
		{
			if (!read_lit_(stream, L"false"_s))
			{
				throw std::runtime_error("Invalid JSON");
			}
			return std::make_shared<BoolValue>(false);
		}
		// The beginning of the null value
		case L'n':
		case L'N':
		{
			if (!read_lit_(stream, L"null"_s))
			{
				throw std::runtime_error("Invalid JSON");
			}
			return std::make_shared<NullValue>();
		}
		// The beginning of a comment
		case L'/':
		{
			read_comment_(stream);
			break;
		}
		// JSON cannot have anything else => throw the exception
		default:
		{
			throw std::runtime_error("Invalid JSON");
		}
		}
	}
	throw std::runtime_error("Invalid JSON");
}

std::shared_ptr<json::JsonObject> json::Element::read_object_(std::wistream& stream)
{
	std::shared_ptr<JsonObject> result = std::make_shared<JsonObject>();
	while (true)
	{
		wchar_t c = stream.peek();
		pass_(stream, c);
		if (c == L'}')
		{
			stream.get(c);
			return result;
		}
		
		// Read a key
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
		pass_(stream, c);
		if (c != L':')
		{
			throw("Invalid JSON: invalid object, ':' was expected after the key");
		}
		stream.get(c);
		c = stream.peek();
		pass_(stream, c);
		
		result->get_content()[key] = from_stream(stream);
		
		c = stream.peek();
		pass_(stream, c);
		if (c == L'}')
		{
			stream.get(c);
			return result;
		}
		if (c == L',')
		{
			stream.get(c);
			continue;
		}
		throw std::runtime_error("Invalid JSON: invalid object");
	}
}

std::shared_ptr<json::Array> json::Element::read_array_(std::wistream& stream)
{
	std::shared_ptr<Array> result = std::make_shared<Array>();
	while (true)
	{
		wchar_t c = stream.peek();
		pass_(stream, c);
		if (c == L']')
		{
			stream.get(c);
			return result;
		}
		
		result->get_content().push_back(from_stream(stream));
		
		c = stream.peek();
		pass_(stream, c);
		if (c == L']')
		{
			stream.get(c);
			return result;
		}
		if (c == L',')
		{
			stream.get(c);
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
			escape = false;
		}
		else
		{
			if (c == first)
			{
				return str.unescape();
			}
			if (c == L'\\')
			{
				escape = true;
			}
		}
		str += c;
	}
	throw std::runtime_error("Invalid JSON: the string is not closed");
}
			

std::shared_ptr<json::Element> json::Element::read_number_(std::wistream& stream, wchar_t first)
{
	String result;
	wchar_t c = stream.peek();

	// Define the base
	int base = 10;
	if (first == L'0')
	{
		switch (c)
		{
		case L'x':
		case L'X':
		case L'h':
		case L'H':
		{
			base = 16;
			stream.get(c);
			c = stream.peek();
			break;
		}
		case L'b':
		case L'B':
		{
			base = 2;
			stream.get(c);
			c = stream.peek();
			break;
		}
		case L'o':
		case L'O':
		{
			base = 8;
			stream.get(c);
			c = stream.peek();
			break;
		}
		default:
		{
			result += first;
		}
		}
	}
	else
	{
		result += first;
	}

	bool has_point = false;
	while (c >= L'0' && c <= L'9' ||
		   c >= L'A' && c <= L'F' ||
		   c >= L'a' && c <= L'f' ||
		   c == L'.' || c == L'\'')
	{
		has_point |= c == L'.';
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
			return std::make_shared<IntValue>(result.to_int<2>(false));
		}
		case 8:
		{
			return std::make_shared<IntValue>(result.to_int<8>(false));
		}
		case 10:
		{
			if (has_point)
			{
				return std::make_shared<DoubleValue>(result.to_double());
			}
			return std::make_shared<IntValue>(result.to_int<10>(false));
		}
		case 16:
		{
			return std::make_shared<IntValue>(result.to_int<16>(false));
		}
		}
		throw std::runtime_error("Invalid JSON");
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
	// The first character is supposed to be already read
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

void json::Element::pass_(std::wistream& stream, wchar_t& c)
{
	while (true)
	{
		if (c == std::wistream::traits_type::eof())
		{
			throw std::runtime_error("Invalid JSON: unexpected end of JSON");
		}
		if (c == L'//')
		{
			stream.get(c);
			read_comment_(stream);
			c = stream.peek();
			continue;
		}
		if (String::is_space(c))
		{
			stream.get(c);
			c = stream.peek();
			continue;
		}
		break;
	}
}
