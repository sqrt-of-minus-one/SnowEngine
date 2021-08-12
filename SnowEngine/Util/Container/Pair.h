    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Pair.h                      //
////////////////////////////////////////

#pragma once

#include "../../Object.h"
#include "../Util.h"

namespace snow
{

template<typename T_First, typename T_Second>
class Pair : public Object
{
public:
	Pair(const Pair<T_First, T_Second>& pair);
	Pair(Pair<T_First, T_Second>&& pair);
	Pair(const T_First& first, const T_Second& second);
	Pair(T_First&& first, T_Second&& second);
	
	virtual const std::string to_string() const override;
	virtual int hash_code() const override;
	
	T_First& get_first();
	T_Second& get_second();
	const T_First& get_first() const;
	const T_Second& get_second() const;
	void set_first(const T_First& first);
	void set_second(const T_Second& second);
	void set_first(T_First&& first);
	void set_second(T_Second&& second);

	Pair<T_First, T_Second>& operator=(const Pair<T_First, T_Second>& pair);
	Pair<T_First, T_Second>& operator=(Pair<T_First, T_Second>&& pair);

	bool operator==(const Pair<T_First, T_Second>& pair) const;
	bool operator!=(const Pair<T_First, T_Second>& pair) const;

private:
	T_First first_;
	T_Second second_;
};

		/* DEFINITIONS of Pair */

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>::Pair(const Pair<T_First, T_Second>& pair) :
	first_(pair.first_),
	second_(pair.second_)
{}

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>::Pair(Pair<T_First, T_Second>&& pair) :
	first_(std::move(pair.first_)),
	second_(std::move(pair.second_))
{}

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>::Pair(const T_First& first, const T_Second& second) :
	first_(first),
	second_(second)
{}

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>::Pair(T_First&& first, T_Second&& second) :
	first_(std::move(first)),
	second_(std::move(second))
{}

template<typename T_First, typename T_Second>
const std::string Pair<T_First, T_Second>::to_string() const
{
	return "[ " + util::to_string(first_) + ": " + util::to_string(second_) + " ]";
}

template<typename T_First, typename T_Second>
int Pair<T_First, T_Second>::hash_code() const
{
	return util::hash_code(first_) - util::hash_code(second_);
}

template<typename T_First, typename T_Second>
T_First& Pair<T_First, T_Second>::get_first()
{
	return first_;
}

template<typename T_First, typename T_Second>
T_Second& Pair<T_First, T_Second>::get_second()
{
	return second_;
}

template<typename T_First, typename T_Second>
const T_First& Pair<T_First, T_Second>::get_first() const
{
	return first_;
}

template<typename T_First, typename T_Second>
const T_Second& Pair<T_First, T_Second>::get_second() const
{
	return second_;
}

template<typename T_First, typename T_Second>
void Pair<T_First, T_Second>::set_first(const T_First& first)
{
	first_ = first;
}

template<typename T_First, typename T_Second>
void Pair<T_First, T_Second>::set_second(const T_Second& second)
{
	second_ = second;
}

template<typename T_First, typename T_Second>
void Pair<T_First, T_Second>::set_first(T_First&& first)
{
	first_ = std::move(first);
}

template<typename T_First, typename T_Second>
void Pair<T_First, T_Second>::set_second(T_Second&& second)
{
	second_ = std::move(second);
}

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>& Pair<T_First, T_Second>::operator=(const Pair<T_First, T_Second>& pair)
{
	first_ = pair.first_;
	second_ = pair.second_;
	return *this;
}

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>& Pair<T_First, T_Second>::operator=(Pair<T_First, T_Second>&& pair)
{
	first_ = std::move(pair.first_);
	second_ = std::move(pair.second_);
	return *this;
}

template<typename T_First, typename T_Second>
bool Pair<T_First, T_Second>::operator==(const Pair<T_First, T_Second>& pair) const
{
	return first_ == pair.first_ && second_ == pair.second_;
}

template<typename T_First, typename T_Second>
bool Pair<T_First, T_Second>::operator!=(const Pair<T_First, T_Second>& pair) const
{
	return !(*this == pair);
}

}
