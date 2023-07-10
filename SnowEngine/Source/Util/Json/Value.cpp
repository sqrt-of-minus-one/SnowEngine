    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Value.cpp                   //
////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//*+ *+ *+ *+ *** ____************************* ____***|*******SnowStorm*************************//
//**+ *+ *+ *+ **|*****************************|*******|*****************************************//
//*+ *+ *+ *+ ***____ ** ___ ** ___ **|*****|**____ **_|_** ___ ** ___ ** __ __ *****************//
//**+ *+ *+ *+ ******|**|***|**|***|**|**|**|******|***|***|***|**|***_**|**|**|*** SnowEngine **//
//*+ *+ *+ *+ ***_____**_***_**_____***__|__***_____***__**_____**_******_**_**_** JSON  system *//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Value.h"

using namespace snow;

template<>
json::EType json::snow_::type_<String>() noexcept
{
	return EType::STRING_VALUE;
}

template<>
json::EType json::snow_::type_<int>() noexcept
{
	return EType::INT_VALUE;
}

template<>
json::EType json::snow_::type_<double>() noexcept
{
	return EType::DOUBLE_VALUE;
}

template<>
json::EType json::snow_::type_<bool>() noexcept
{
	return EType::BOOL_VALUE;
}

template<>
json::EType json::snow_::type_<std::nullptr_t>() noexcept
{
	return EType::NULL_VALUE;
}

		/* Value_<std::nullptr_t>: public */

json::snow_::Value_<std::nullptr_t>::Value_()
{}

std::shared_ptr<json::Element> json::snow_::Value_<std::nullptr_t>::to_json() const
{
	return std::make_shared<json::snow_::Value_<std::nullptr_t>>(*this);
}

json::EType json::snow_::Value_<std::nullptr_t>::get_type() const
{
	return EType::NULL_VALUE;
}

void json::snow_::Value_<std::nullptr_t>::to_stream(std::wostream& stream, int nesting) const
{
	stream << L"null";
}

std::shared_ptr<json::snow_::Value_<std::nullptr_t>> json::snow_::Value_<std::nullptr_t>::make()
{
	return std::make_shared<NullValue>();
}
