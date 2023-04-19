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

json::snow_::Value_<std::nullptr_t>::Value_()
{}

int json::snow_::Value_<std::nullptr_t>::hash_code() const noexcept
{
	return 0;
}

json::EType json::snow_::Value_<std::nullptr_t>::get_type() const
{
	return EType::NULL_VALUE;
}

void json::snow_::Value_<std::nullptr_t>::to_stream(std::wostream& stream, int nesting) const
{
	stream << L"null";
}

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
