    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Container.h                 //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include <functional>

#include "../Util.h"

namespace snow
{

template<typename T>
class Container;

namespace
{

template<typename T_Container, typename T_Element>
class BaseIterator_ : public Object
{
public:
	virtual const std::string to_string() const override;

	virtual bool is_valid() const;

	virtual T_Container& get_container() const = 0;

	virtual T_Element& get() const = 0;

	virtual bool is_begin() const = 0;
	virtual bool is_end() const = 0;
	virtual bool next() = 0;
	virtual bool prev() = 0;

	virtual bool operator==(const BaseIterator_<T_Container, T_Element>& iterator) const = 0;
	virtual bool operator!=(const BaseIterator_<T_Container, T_Element>& iterator) const = 0;

protected:
	bool is_valid_;

	virtual void destroy_();
};

}

template<typename T>
using ConstIterator = BaseIterator_<const Container<T>, const T>;

template<typename T>
using Iterator = BaseIterator_<Container<T>, T>;

template<typename T>
class Container : public Object
{
public:
	virtual const std::string to_string() const override;

	virtual int size() const = 0;
	virtual bool is_empty() const;
	virtual void empty() = 0;

	virtual bool add(const T& element) = 0;
	virtual bool add(T&& element) = 0;

	virtual int remove_all(const T& element) = 0;

	virtual int contains(const T& element) const = 0;

	virtual void for_each(std::function<void(T&)> f) = 0;
	virtual void for_each_const(std::function<void(const T&)> f) const = 0;

	virtual std::shared_ptr<Iterator<T>> create_iterator() = 0;
	virtual std::shared_ptr<ConstIterator<T>> create_const_iterator() const = 0;
};


		/* DEFINITIONS of BaseIterator_ */

template<typename T_Container, typename T_Element>
const std::string BaseIterator_<T_Container, T_Element>::to_string() const
{
	return util::to_string(get());
}

template<typename T_Container, typename T_Element>
bool BaseIterator_<T_Container, T_Element>::is_valid() const
{
	return is_valid_;
}

template<typename T_Container, typename T_Element>
void BaseIterator_<T_Container, T_Element>::destroy_()
{
	is_valid_ = false;
}

		/* DEFINITIONS of Container */

template<typename T>
const std::string Container<T>::to_string() const
{
	return ""; // Todo: Use ConstIterator
}

template<typename T>
bool Container<T>::is_empty() const
{
	return size() == 0;
}

}
