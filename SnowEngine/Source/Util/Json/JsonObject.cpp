    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: JsonObject.cpp              //
////////////////////////////////////////

#include "JsonObject.h"

#include "../Types/String.h"
#include "../Util.h"

using namespace snow;

json::JsonObject::JsonObject() :
	content_()
{}

json::JsonObject::JsonObject(JsonObject&& object) :
	content_(std::move(object.content_))
{}

int json::JsonObject::hash_code() const noexcept
{
	int result = 0;
	for (const auto& [i, j] : content_)
	{
		result += i.hash_code() - util::hash_code(j);
	}
	return result;
}

json::EType json::JsonObject::get_type() const
{
	return EType::OBJECT;
}

std::map<String, std::unique_ptr<json::Element>>& json::JsonObject::get_content() noexcept
{
	return content_;
}

const std::map<String, std::unique_ptr<json::Element>>& json::JsonObject::get_content() const noexcept
{
	return content_;
}

void json::JsonObject::to_stream(std::wostream& stream, int nesting) const
{
	wchar_t* tab = new wchar_t[nesting + 2];
	for (int i = 0; i < nesting + 1; i++)
	{
		tab[i] = '\t';
	}
	tab[nesting + 1] = '\0';
	
	stream << L'{';
	bool is_first = true;
	for (const auto& [k, v] : content_)
	{
		stream << (is_first ? L"\n" : L",\n") << tab << L'"' << k.escape() << L"\": ";
		v->to_stream(stream, nesting + 1);
		is_first = false;
	}
	
	if (!is_first)
	{
		stream << L'\n' << (tab + 1);
	}
	stream << L'}';
}
