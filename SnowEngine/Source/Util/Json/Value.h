    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Value.h                     //
////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//*+ *+ *+ *+ *** ____************************* ____***|*******SnowStorm*************************//
//**+ *+ *+ *+ **|*****************************|*******|*****************************************//
//*+ *+ *+ *+ ***____ ** ___ ** ___ **|*****|**____ **_|_** ___ ** ___ ** __ __ *****************//
//**+ *+ *+ *+ ******|**|***|**|***|**|**|**|******|***|***|***|**|***_**|**|**|*** SnowEngine **//
//*+ *+ *+ *+ ***_____**_***_**_____***__|__***_____***__**_____**_******_**_**_** JSON  system *//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Element.h"

#include <type_traits>

#include "../Util.h"

namespace snow
{

namespace json
{

namespace snow_
{

template<typename T>
class Value_ : public Element
{
public:
	Value_();
	Value_(const Value_<T>& object);
	Value_(Value_<T>&& object);
	Value_(const T& value);
	Value_(T&& value);
	
	virtual int hash_code() const noexcept override;
	
	virtual EType get_type() const override;
	
	T& get() noexcept;
	const T& get() const noexcept;
	void set(const T& value) noexcept(noexcept(std::declval<T>() = std::declval<T>()));
	
protected:
	virtual void to_stream(std::wostream& stream, int nesting = 0) const override;
	
private:
	T value_;
};

template<>
class Value_<std::nullptr_t> : public Element
{
public:
	Value_();
	
	virtual int hash_code() const noexcept override;
	
	virtual EType get_type() const override;
	
protected:
	virtual void to_stream(std::wostream& stream, int nesting = 0) const override;
};

template<typename T>
extern EType type_() noexcept = delete;

template<>
extern EType type_<String>() noexcept;

template<>
extern EType type_<int>() noexcept;

template<>
extern EType type_<double>() noexcept;

template<>
extern EType type_<bool>() noexcept;

template<>
extern EType type_<std::nullptr_t>() noexcept;

}

using StringValue = snow_::Value_<String>;
using IntValue = snow_::Value_<int>;
using DoubleValue = snow_::Value_<double>;
using BoolValue = snow_::Value_<bool>;
using NullValue = snow_::Value_<std::nullptr_t>;

}


template<typename T>
json::snow_::Value_<T>::Value_() :
	value_()
{}

template<typename T>
json::snow_::Value_<T>::Value_(const Value_<T>& object) :
	value_(object.value_)
{}

template<typename T>
json::snow_::Value_<T>::Value_(Value_<T>&& object) :
	value_(std::move(object.value_))
{}

template<typename T>
json::snow_::Value_<T>::Value_(const T& value) :
	value_(value)
{}

template<typename T>
json::snow_::Value_<T>::Value_(T&& value) :
	value_(std::move(value))
{}

template<typename T>
int json::snow_::Value_<T>::hash_code() const noexcept
{
	return util::hash_code(value_);
}

template<typename T>
json::EType json::snow_::Value_<T>::get_type() const
{
	return snow_::type_<T>();
}

template<typename T>
T& json::snow_::Value_<T>::get() noexcept
{
	return value_;
}

template<typename T>
const T& json::snow_::Value_<T>::get() const noexcept
{
	return value_;
}

template<typename T>
void json::snow_::Value_<T>::set(const T& value) noexcept(noexcept(std::declval<T>() = std::declval<T>()))
{
	value_ = value;
}

template<typename T>
void json::snow_::Value_<T>::to_stream(std::wostream& stream, int nesting) const
{
	if (std::is_same<T, String>::value)
	{
		stream << L'"' << util::to_string(value_).escape() << L'"';
	}
	else
	{
		stream << util::to_string(value_);
	}
}

}
