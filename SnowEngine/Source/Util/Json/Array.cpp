    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Array.cpp                   //
////////////////////////////////////////

#include "Array.h"

#include <ostream>

using namespace snow;

json::Array::Array() :
	content_()
{}

json::Array::Array(Array&& array) :
	content_(std::move(array.content_))
{}

int json::Array::hash_code() const noexcept
{
	int result = 0;
	int one = 1;
	for (const auto& i : content_)
	{
		result += one * i->hash_code();
		one = -one;
	}
	return result;
}

json::EType json::Array::get_type() const
{
	return EType::ARRAY;
}

std::vector<std::unique_ptr<json::Element>>& json::Array::get_content() noexcept
{
	return content_;
}

const std::vector<std::unique_ptr<json::Element>>& json::Array::get_content() const noexcept
{
	return content_;
}

void json::Array::to_stream(std::wostream& stream, int nesting) const
{
	stream << L"[ ";
	bool is_first = true;
	for (const auto& i : content_)
	{
		if (!is_first)
		{
			stream << L", ";
		}
		i->to_stream(stream, nesting + 1);
		is_first = false;
	}
	stream << L" ]";
}
