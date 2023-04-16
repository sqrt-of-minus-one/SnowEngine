    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Value.h                     //
////////////////////////////////////////

#pragma once

#include "Element.h"

#include <type_traits>

#include "../Util.h"

namespace snow
{

namespace json
{

namespace
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
	
	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;
	
	virtual EType get_type() const override;
	
protected:
	virtual void to_stream(std::wostream& stream, int nesting = 0) const override;
};

template<typename T>
EType type_() noexcept = delete;

template<>
EType type_<String>() noexcept;

template<>
EType type_<int>() noexcept;

template<>
EType type_<double>() noexcept;

template<>
EType type_<bool>() noexcept;

template<>
EType type_<std::nullptr_t>() noexcept;

}

using StringValue = Value_<String>;
using IntValue = Value_<int>;
using DoubleValue = Value_<double>;
using BoolValue = Value_<bool>;
using NullValue = Value_<std::nullptr_t>;

}


template<typename T>
json::Value_<T>::Value_() :
	value_()
{}

template<typename T>
json::Value_<T>::Value_(const Value_<T>& object) :
	value_(object.value_)
{}

template<typename T>
json::Value_<T>::Value_(Value_<T>&& object) :
	value_(std::move(object.value_))
{}

template<typename T>
json::Value_<T>::Value_(const T& value) :
	value_(value)
{}

template<typename T>
json::Value_<T>::Value_(T&& value) :
	value_(std::move(value))
{}

template<typename T>
int json::Value_<T>::hash_code() const noexcept
{
	return util::hash_code(value_);
}

template<typename T>
json::EType json::Value_<T>::get_type() const
{
	return json::type_<T>();
}

template<typename T>
T& json::Value_<T>::get() noexcept
{
	return value_;
}

template<typename T>
const T& json::Value_<T>::get() const noexcept
{
	return value_;
}

template<typename T>
void json::Value_<T>::set(const T& value) noexcept(noexcept(std::declval<T>() = std::declval<T>()))
{
	value_ = value;
}

template<typename T>
void json::Value_<T>::to_stream(std::wostream& stream, int nesting) const
{
	if (std::is_same<T, String>::value)
	{
		stream << L'"' << util::to_string(value_).escape() << L'"';
	}
	stream << util::to_string(value_);
}

json::Value_<std::nullptr_t>::Value_()
{}

String snow::json::Value_<std::nullptr_t>::to_string() const
{
	return String();
}

int json::Value_<std::nullptr_t>::hash_code() const noexcept
{
	return 0;
}

json::EType json::Value_<std::nullptr_t>::get_type() const
{
	return EType::NULL_VALUE;
}

void json::Value_<std::nullptr_t>::to_stream(std::wostream& stream, int nesting) const
{
	stream << L"null";
}

template<>
json::EType json::type_<String>() noexcept
{
	return EType::STRING_VALUE;
}

template<>
json::EType json::type_<int>() noexcept
{
	return EType::INT_VALUE;
}

template<>
json::EType json::type_<double>() noexcept
{
	return EType::DOUBLE_VALUE;
}

template<>
json::EType json::type_<bool>() noexcept
{
	return EType::BOOL_VALUE;
}

template<>
json::EType json::type_<std::nullptr_t>() noexcept
{
	return EType::NULL_VALUE;
}

}
