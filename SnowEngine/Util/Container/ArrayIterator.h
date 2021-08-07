    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ArrayIterator.h             //
////////////////////////////////////////

#pragma once

#include "../../Object.h"
#include "Container.h"

#include <exception>

#include "../Util.h"

namespace snow
{

template<typename T>
class Array;

namespace
{

template<typename T_Container, typename T_Element>
class BaseArrayIterator_ :
	public Object,
	public IIterator<T_Container, T_Element>
{
	template<typename T>
	friend class Array;

public:
	BaseArrayIterator_(const BaseArrayIterator_<T_Container, T_Element>& iterator);
	BaseArrayIterator_(BaseArrayIterator_<T_Container, T_Element>&& iterator);
	~BaseArrayIterator_();

	virtual const std::string to_string() const override;
	virtual int hash_code() const override;

	virtual bool is_valid() const override;
	virtual bool is_element_valid() const override;

	virtual T_Container& get_container() const override;
	virtual T_Element& get() const override;
	int get_index() const;

	virtual bool is_begin() const override;
	virtual bool is_last() const override;
	virtual bool is_end() const override;
	virtual bool next() override;
	virtual bool prev() override;

	virtual T_Element& operator*() const override;
	BaseArrayIterator_<T_Container, T_Element> operator++();
	BaseArrayIterator_<T_Container, T_Element> operator--();
	BaseArrayIterator_<T_Container, T_Element> operator++(int);
	BaseArrayIterator_<T_Container, T_Element> operator--(int);

	bool operator==(const BaseArrayIterator_<T_Container, T_Element>& iterator) const;
	bool operator!=(const BaseArrayIterator_<T_Container, T_Element>& iterator) const;

protected:
	BaseArrayIterator_(T_Container& array, int index, bool is_valid = true);

	T_Container& container_;
	int index_;
	bool is_valid_;
};

}

template<typename T>
using ConstArrayIterator = BaseArrayIterator_<const Array<T>, const T>;

template<typename T>
using ArrayIterator = BaseArrayIterator_<Array<T>, T>;


		/* DEFINITIONS of BaseArrayIterator_ */

template<typename T_Container, typename T_Element>
BaseArrayIterator_<T_Container, T_Element>::BaseArrayIterator_(const BaseArrayIterator_<T_Container, T_Element>& iterator) :
	container_(iterator.container_),
	index_(iterator.index_),
	is_valid_(iterator.is_valid_)
{
	if (is_valid_)
	{
		container_.register_iterator_(this);
	}
}

template<typename T_Container, typename T_Element>
BaseArrayIterator_<T_Container, T_Element>::BaseArrayIterator_(BaseArrayIterator_<T_Container, T_Element>&& iterator) :
	container_(iterator.container_),
	index_(iterator.index_),
	is_valid_(iterator.is_valid_)
{
	if (is_valid_)
	{
		iterator.is_valid_ = false;
		container_.unregister_iterator_(&iterator);
		container_.register_iterator_(this);
	}
}

template<typename T_Container, typename T_Element>
BaseArrayIterator_<T_Container, T_Element>::~BaseArrayIterator_()
{
	if (is_valid_)
	{
		container_.unregister_iterator_(this);
	}
}

template<typename T_Container, typename T_Element>
const std::string BaseArrayIterator_<T_Container, T_Element>::to_string() const
{
	return util::to_string(get());
}

template<typename T_Container, typename T_Element>
int BaseArrayIterator_<T_Container, T_Element>::hash_code() const
{
	return util::hash_code(get());
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::is_valid() const
{
	return is_valid_ && index_ >= 0 && index_ <= container_.size();
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::is_element_valid() const
{
	return is_valid_ && index_ >= 0 && index_ < container_.size();
}

template<typename T_Container, typename T_Element>
T_Container& BaseArrayIterator_<T_Container, T_Element>::get_container() const
{
	if (is_valid())
	{
		return container_;
	}
	else
	{
		throw std::logic_error("Attempt to get container of invalid iterator");
	}
}

template<typename T_Container, typename T_Element>
T_Element& BaseArrayIterator_<T_Container, T_Element>::get() const
{
	if (is_element_valid())
	{
		return container_[index_];
	}
	else
	{
		throw std::logic_error("Attempt to get element of invalid iterator");
	}
}

template<typename T_Container, typename T_Element>
int BaseArrayIterator_<T_Container, T_Element>::get_index() const
{
	if (is_valid())
	{
		return index_;
	}
	else
	{
		throw std::logic_error("Attempt to get index of invalid iterator");
	}
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::is_begin() const
{
	return is_valid_ && index_ == 0;
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::is_last() const
{
	return is_valid_ && index_ == container_.size() - 1;
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::is_end() const
{
	return is_valid_ && index_ == container_.size();
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::next()
{
	return is_valid_ && index_ < container_.size() && ++index_ < container_.size();

//	// This do the same:
//	if (is_valid_)
//	{
//		if (is_end())
//		{
//			return false;
//		}
//		else
//		{
//			index_++;
//			return !is_end();
//		}
//	}
//	else
//	{
//		return false;
//	}
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::prev()
{
	if (is_valid_ && index_ > 0)
	{
		index_++;
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T_Container, typename T_Element>
T_Element& BaseArrayIterator_<T_Container, T_Element>::operator*() const
{
	return get();
}

template<typename T_Container, typename T_Element>
BaseArrayIterator_<T_Container, T_Element> BaseArrayIterator_<T_Container, T_Element>::operator++()
{
	next();
	return *this;
}

template<typename T_Container, typename T_Element>
BaseArrayIterator_<T_Container, T_Element> BaseArrayIterator_<T_Container, T_Element>::operator--()
{
	prev();
	return *this;
}

template<typename T_Container, typename T_Element>
BaseArrayIterator_<T_Container, T_Element> BaseArrayIterator_<T_Container, T_Element>::operator++(int)
{
	auto ret = *this;
	next();
	return ret;
}

template<typename T_Container, typename T_Element>
BaseArrayIterator_<T_Container, T_Element> BaseArrayIterator_<T_Container, T_Element>::operator--(int)
{
	auto ret = *this;
	prev();
	return ret;
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::operator==(const BaseArrayIterator_<T_Container, T_Element>& iterator) const
{
	return !is_valid() && !iterator.is_valid() ||
		&container_ == &iterator.container_ && index_ == iterator.index_;
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::operator!=(const BaseArrayIterator_<T_Container, T_Element>& iterator) const
{
	return !(*this == iterator);
}

template<typename T_Container, typename T_Element>
BaseArrayIterator_<T_Container, T_Element>::BaseArrayIterator_(T_Container& array, int index, bool is_valid) :
	container_(array),
	index_(index),
	is_valid_(is_valid)
{
	if (is_valid_)
	{
		container_.register_iterator_(this);
	}
}

}