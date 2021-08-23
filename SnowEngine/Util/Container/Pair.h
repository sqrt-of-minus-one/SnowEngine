    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Pair.h                      //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\brief The file of the pair
 *	
 *	This file contains the definition of the Pair class.
 */

#include "../../Object.h"
#include "../Util.h"

namespace snow
{

/**
 *	\brief The container to keep two objects
 *	
 *	An object of the Pair class can keep two variables. Types of these variables must have default
 *	constructor, copy constructors, assignment operator (`=`) and equality operator (`==`). The
 *	default and copy constructors are assumed not to throw any exceptions. They also must have
 *	`to_string()` and `hash_code()` methods (any `snow::Object` has them) or be a primitive type.
 *	\tparam T_First Type of the first variable in the pair.
 *	\tparam T_Second Type of the second variable in the pair.
 */
template<typename T_First, typename T_Second>
class Pair : public Object
{
public:

	/**
	 *	\brief Default constructor
	 *	
	 *	Creates a new pair. Variables of the pair are initialised using default constructors.
	 */
	Pair() noexcept;

	/**
	 *	\brief Copy constructor
	 *	
	 *	Creates a new pair as a copy of the passed one.
	 *	\param pair The pair to copy.
	 */
	Pair(const Pair<T_First, T_Second>& pair) noexcept;

	/**
	 *	\brief Move constructor
	 *	
	 *	Moves variables of the passed pair to the new one.
	 *	\param pair Source pair.
	 */
	Pair(Pair<T_First, T_Second>&& pair) noexcept;

	/**
	 *	\brief Elementwise copy constructor
	 *	
	 *	Creates a new pair using the passed values.
	 *	\param first The value for the first variable.
	 *	\param second The value for the second variable.
	 */
	Pair(const T_First& first, const T_Second& second);

	/**
	 *	\brief Elementwise move constructor
	 *
	 *	Creates a new pair using the passed values.
	 *	\param first The value for the first variable.
	 *	\param second The value for the second variable.
	 */
	Pair(T_First&& first, T_Second&& second);
	
	/**
	 *	\brief Convert the pair to string
	 *	
	 *	Makes a string in the format `"[1: 2]"` where `1` represents the first variable and `2`
	 *	represents the second. The variables are converted to string using `util::to_string()`
	 *	method.
	 *	\return A result string.
	 */
	virtual const std::string to_string() const noexcept override;

	/**
	 *	\brief Hash code of the pair
	 *	
	 *	Hash code of a pair is a difference between a hash code of the first pair variable and a
	 *	hash code of the second.
	 *	\return Hash code of the pair.
	 */
	virtual int hash_code() const noexcept override;
	
	/**
	 *	\brief Get the first variable
	 *	
	 *	Allows to access (read and write) the first variable of the pair.
	 *	\return A reference to the first variable of the pair.
	 */
	T_First& get_first() noexcept;

	/**
	 *	\brief Get the second variable
	 *
	 *	Allows to access (read and write) the second variable of the pair.
	 *	\return A reference to the second variable of the pair.
	 */
	T_Second& get_second() noexcept;

	/**
	 *	\brief Get the first variable
	 *
	 *	Allows to read the first variable of the pair.
	 *	\return The first variable of the pair.
	 */
	const T_First& get_first() const noexcept;

	/**
	 *	\brief Get the second variable
	 *
	 *	Allows to read the second variable of the pair.
	 *	\return The second variable of the pair.
	 */
	const T_Second& get_second() const noexcept;

	/**
	 *	\brief Set the first variable
	 *	
	 *	Allows to set the first variable of the pair.
	 *	\param first The value that will be assigned to the first variable.
	 */
	void set_first(const T_First& first);

	/**
	 *	\brief Set the second variable
	 *
	 *	Allows to set the second variable of the pair.
	 *	\param second The value that will be assigned to the second variable.
	 */
	void set_second(const T_Second& second);

	/**
	 *	\brief Set the first variable
	 *
	 *	Allows to set the first variable of the pair.
	 *	\param first The value that will be assigned to the first variable.
	 */
	void set_first(T_First&& first);

	/**
	 *	\brief Set the second variable
	 *
	 *	Allows to set the second variable of the pair.
	 *	\param second The value that will be assigned to the second variable.
	 */
	void set_second(T_Second&& second);

	/**
	 *	\brief Copy assignment operator
	 *	
	 *	Copies variables of the passed pair.
	 *	\param pair The pair that will be copied.
	 */
	Pair<T_First, T_Second>& operator=(const Pair<T_First, T_Second>& pair);

	/**
	 *	\brief Move assignment operator
	 *	
	 *	Moves variables to the iterator from the passed one.
	 *	\param pair The source pair.
	 */
	Pair<T_First, T_Second>& operator=(Pair<T_First, T_Second>&& pair);

	/**
	 *	\brief Whether two pairs are equal
	 *	
	 *	Compares two pairs. They are equal if their variables are equal.
	 *	\param pair The pair to compare.
	 *	\return `true` if the pairs are equal, `false` otherwise.
	 */
	bool operator==(const Pair<T_First, T_Second>& pair) const;

	/**
	 *	\brief Whether two pairs are not equal
	 *	
	 *	Compares two pairs. They are equal if their variables are equal.
	 *	\param pair The pair to compare.
	 *	\return `true` if the pairs are not equal, `false` otherwise.
	 */
	bool operator!=(const Pair<T_First, T_Second>& pair) const;

private:
	T_First first_;
	T_Second second_;
};

		/* DEFINITIONS */

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>::Pair() noexcept :
	first_(),
	second_()
{}

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>::Pair(const Pair<T_First, T_Second>& pair) noexcept :
	first_(pair.first_),
	second_(pair.second_)
{}

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>::Pair(Pair<T_First, T_Second>&& pair) noexcept :
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
const std::string Pair<T_First, T_Second>::to_string() const noexcept
{
	return "[" + util::to_string(first_) + ": " + util::to_string(second_) + "]";
}

template<typename T_First, typename T_Second>
int Pair<T_First, T_Second>::hash_code() const noexcept
{
	return util::hash_code(first_) - util::hash_code(second_);
}

template<typename T_First, typename T_Second>
T_First& Pair<T_First, T_Second>::get_first() noexcept
{
	return first_;
}

template<typename T_First, typename T_Second>
T_Second& Pair<T_First, T_Second>::get_second() noexcept
{
	return second_;
}

template<typename T_First, typename T_Second>
const T_First& Pair<T_First, T_Second>::get_first() const noexcept
{
	return first_;
}

template<typename T_First, typename T_Second>
const T_Second& Pair<T_First, T_Second>::get_second() const noexcept
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
