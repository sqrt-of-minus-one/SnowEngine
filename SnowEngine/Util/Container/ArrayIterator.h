    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ArrayIterator.h             //
////////////////////////////////////////

#pragma once

#include "../../Object.h"
#include "Container.h"
#include "../Util.h"

namespace snow
{

template<typename T>
class Array;

namespace
{

class BaseArrayIterator_ :
	public Object,
	public IIterator
{
public:
	int get_index() const;

	virtual bool next() override;
	virtual bool prev() override;

protected:
	BaseArrayIterator_(int index, bool is_container_valid);

	int index_;
	bool is_valid_;
};

}

template<typename T>
class ConstArrayIterator : public BaseArrayIterator_
{
	template<typename T>
	friend class Array;

public:
	ConstArrayIterator(const ConstArrayIterator<T>& iterator);
	ConstArrayIterator(ConstArrayIterator<T>&& iterator);

	virtual const std::string to_string() const override;
	virtual int hash_code() const override;

	virtual bool is_valid() const override;

	const Array<T>& get_container() const;
	const T& get() const;

	virtual bool is_begin() const override;
	virtual bool is_last() const override;
	virtual bool is_end() const override;

	const T& operator*() const;
	ConstArrayIterator<T> operator++();
	ConstArrayIterator<T> operator--();
	ConstArrayIterator<T> operator++(int);
	ConstArrayIterator<T> operator--(int);

	bool operator==(const ConstArrayIterator<T>& iterator) const;
	bool operator!=(const ConstArrayIterator<T>& iterator) const;

private:
	ConstArrayIterator(const Array<T>& array, int index);

	const Array<T>& container_;
};

template<typename T>
class ArrayIterator : public BaseArrayIterator_
{
	template<typename T>
	friend class Array;

public:
	ArrayIterator(const ArrayIterator<T>& iterator);
	ArrayIterator(ArrayIterator<T>&& iterator);

	virtual const std::string to_string() const override;
	virtual int hash_code() const override;

	virtual bool is_valid() const override;

	Array<T>& get_container() const;
	T& get() const;

	virtual bool is_begin() const override;
	virtual bool is_last() const override;
	virtual bool is_end() const override;

	T& operator*() const;
	ArrayIterator<T> operator++();
	ArrayIterator<T> operator--();
	ArrayIterator<T> operator++(int);
	ArrayIterator<T> operator--(int);

	bool operator==(const ArrayIterator<T>& iterator) const;
	bool operator!=(const ArrayIterator<T>& iterator) const;

	operator ConstArrayIterator<T>() const;
	
private:
	ArrayIterator(Array<T>& array, int index);

	Array<T>& container_;
};


		/* DEFINITIONS of BaseArrayIterator_ */

int BaseArrayIterator_::get_index() const
{
	return index_;
}

bool BaseArrayIterator_::next()
{
	if (is_end())
	{
		return false;
	}
	else
	{
		index_++;
		return !is_end();
	}
}

bool BaseArrayIterator_::prev()
{
	if (is_begin())
	{
		return false;
	}
	else
	{
		index_--;
		return true;
	}
}

BaseArrayIterator_::BaseArrayIterator_(int index, bool is_container_valid) :
	index_(index),
	is_valid_(is_container_valid)
{}

		/* DEFINITIONS of ConstArrayIterator */

template<typename T>
ConstArrayIterator<T>::ConstArrayIterator(const ConstArrayIterator<T>& iterator) :
	container_(iterator.container_),
	BaseArrayIterator_(iterator.index_, iterator.is_valid_)
{}
template<typename T>
ConstArrayIterator<T>::ConstArrayIterator(ConstArrayIterator<T>&& iterator) :
	container_(iterator.container_),
	BaseArrayIterator_(std::move(iterator.index_), std::move(iterator.is_valid_))
{}

template<typename T>
const std::string ConstArrayIterator<T>::to_string() const
{
	return util::to_string(get());
}

template<typename T>
int ConstArrayIterator<T>::hash_code() const
{
	return util::hash_code(get());
}

template<typename T>
bool ConstArrayIterator<T>::is_valid() const
{
	return is_valid_ && index_ >= 0 && index_ < container_.size();
}

template<typename T>
const Array<T>& ConstArrayIterator<T>::get_container() const
{
	return container_;
}

template<typename T>
const T& ConstArrayIterator<T>::get() const
{
	return container_[index_];
}

template<typename T>
bool ConstArrayIterator<T>::is_begin() const
{
	return index_ == 0;
}

template<typename T>
bool ConstArrayIterator<T>::is_last() const
{
	return index_ == container_.size() - 1;
}

template<typename T>
bool ConstArrayIterator<T>::is_end() const
{
	return index_ == container_.size();
}

template<typename T>
const T& ConstArrayIterator<T>::operator*() const
{
	return get();
}

template<typename T>
ConstArrayIterator<T> ConstArrayIterator<T>::operator++()
{
	next();
	return *this;
}

template<typename T>
ConstArrayIterator<T> ConstArrayIterator<T>::operator--()
{
	prev();
	return *this;
}

template<typename T>
ConstArrayIterator<T> ConstArrayIterator<T>::operator++(int)
{
	ConstArrayIterator<T> ret = *this;
	next();
	return ret;
}

template<typename T>
ConstArrayIterator<T> ConstArrayIterator<T>::operator--(int)
{
	ConstArrayIterator<T> ret = *this;
	prev();
	return ret;
}

template<typename T>
bool ConstArrayIterator<T>::operator==(const ConstArrayIterator<T>& iterator) const
{
	return &container_ == &iterator.container_ && index_ == iterator.index_;
}

template<typename T>
bool ConstArrayIterator<T>::operator!=(const ConstArrayIterator& iterator) const
{
	return !(*this == iterator);
}

template<typename T>
ConstArrayIterator<T>::ConstArrayIterator(const Array<T>& array, int index) :
	container_(array),
	BaseArrayIterator_(index, true)
{}

		/* DEFINITIONS of ConstArrayIterator */

template<typename T>
ArrayIterator<T>::ArrayIterator(const ArrayIterator<T>& iterator) :
	container_(iterator.container_),
	BaseArrayIterator_(iterator.index_, iterator.is_valid_)
{}
template<typename T>
ArrayIterator<T>::ArrayIterator(ArrayIterator<T>&& iterator) :
	container_(iterator.container_),
	BaseArrayIterator_(std::move(iterator.index_), std::move(iterator.is_valid_))
{}

template<typename T>
const std::string ArrayIterator<T>::to_string() const
{
	return util::to_string(get());
}

template<typename T>
int ArrayIterator<T>::hash_code() const
{
	return util::hash_code(get());
}

template<typename T>
bool ArrayIterator<T>::is_valid() const
{
	return is_valid_ && index_ >= 0 && index_ < container_.size();
}

template<typename T>
Array<T>& ArrayIterator<T>::get_container() const
{
	return container_;
}

template<typename T>
T& ArrayIterator<T>::get() const
{
	return container_[index_];
}

template<typename T>
bool ArrayIterator<T>::is_begin() const
{
	return index_ == 0;
}

template<typename T>
bool ArrayIterator<T>::is_last() const
{
	return index_ == container_.size() - 1;
}

template<typename T>
bool ArrayIterator<T>::is_end() const
{
	return index_ == container_.size();
}

template<typename T>
T& ArrayIterator<T>::operator*() const
{
	return get();
}

template<typename T>
ArrayIterator<T> ArrayIterator<T>::operator++()
{
	next();
	return *this;
}

template<typename T>
ArrayIterator<T> ArrayIterator<T>::operator--()
{
	prev();
	return *this;
}

template<typename T>
ArrayIterator<T> ArrayIterator<T>::operator++(int)
{
	ArrayIterator<T> ret = *this;
	next();
	return ret;
}

template<typename T>
ArrayIterator<T> ArrayIterator<T>::operator--(int)
{
	ArrayIterator<T> ret = *this;
	prev();
	return ret;
}

template<typename T>
bool ArrayIterator<T>::operator==(const ArrayIterator<T>& iterator) const
{
	return &container_ == &iterator.container_ && index_ == iterator.index_;
}

template<typename T>
bool ArrayIterator<T>::operator!=(const ArrayIterator& iterator) const
{
	return !(*this == iterator);
}

template<typename T>
ArrayIterator<T>::operator ConstArrayIterator<T>() const
{
	return ArrayIterator<T>(container_, index_);
}

template<typename T>
ArrayIterator<T>::ArrayIterator(Array<T>& array, int index) :
	container_(array),
	BaseArrayIterator_(index, true)
{}

}