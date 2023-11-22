    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: JsonObject.cpp              //
////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//*+ *+ *+ *+ *** ____************************* ____** | *****|SnowStorm|************************//
//**+ *+ *+ *+ **|*****************************|****** | ****************************************//
//*+ *+ *+ *+ ***\___ ** ___ ** ___ **|*****|**\___ **_|_** ___ ** ___ ** __ __ *****************//
//**+ *+ *+ *+ ******|**|***|**|***|**|**|**|******|** | **|***|**|***\**|**|**|*** SnowEngine **//
//*+ *+ *+ *+ ***____/**|***|**\___/***\/ \/***____/** \_**\___/**|******|**|**|** JSON  system *//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "JsonObject.h"

#include "../String.h"
#include "../Util.h"

using namespace snow;

		/* JsonObject: public */

json::JsonObject::JsonObject() :
	content_()
{}

json::JsonObject::JsonObject(JsonObject&& object) :
	content_(std::move(object.content_))
{}

std::shared_ptr<json::Element> json::JsonObject::to_json() const
{
	return std::make_shared<json::JsonObject>(*this);
}

json::EType json::JsonObject::get_type() const
{
	return EType::OBJECT;
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
		stream << (is_first ? L"\n" : L",\n") << tab << L'"' << string::escape(k) << L"\": ";
		v->to_stream(stream, nesting + 1);
		is_first = false;
	}
	
	if (!is_first)
	{
		stream << L'\n' << (tab + 1);
	}
	stream << L'}';
}

std::map<String, std::shared_ptr<json::Element>>& json::JsonObject::get_content() noexcept
{
	return content_;
}

const std::map<String, std::shared_ptr<json::Element>>& json::JsonObject::get_content() const noexcept
{
	return content_;
}
