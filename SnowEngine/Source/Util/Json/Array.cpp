    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Array.cpp                   //
////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//*+ *+ *+ *+ *** ____************************* ____***|*******SnowStorm*************************//
//**+ *+ *+ *+ **|*****************************|*******|*****************************************//
//*+ *+ *+ *+ ***____ ** ___ ** ___ **|*****|**____ **_|_** ___ ** ___ ** __ __ *****************//
//**+ *+ *+ *+ ******|**|***|**|***|**|**|**|******|***|***|***|**|***_**|**|**|*** SnowEngine **//
//*+ *+ *+ *+ ***_____**_***_**_____***__|__***_____***__**_____**_******_**_**_** JSON  system *//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Array.h"

#include <ostream>

using namespace snow;

		/* Array: public */

json::Array::Array() :
	content_()
{}

json::Array::Array(Array&& array) :
	content_(std::move(array.content_))
{}

std::shared_ptr<json::Element> json::Array::to_json() const
{
	return std::make_shared<json::Array>(*this);
}

json::EType json::Array::get_type() const
{
	return EType::ARRAY;
}

void json::Array::to_stream(std::wostream& stream, int nesting) const
{
	stream << L'[';
	bool is_first = true;
	for (const auto& i : content_)
	{
		if (!is_first)
		{
			stream << L',';
		}
		stream << L' ';
		i->to_stream(stream, nesting + 1);
		is_first = false;
	}
	stream << L" ]";
}

std::vector<std::shared_ptr<json::Element>>& json::Array::get_content() noexcept
{
	return content_;
}

const std::vector<std::shared_ptr<json::Element>>& json::Array::get_content() const noexcept
{
	return content_;
}
