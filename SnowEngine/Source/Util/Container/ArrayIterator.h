    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ArrayIterator.h             //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\brief The file of array iterator
 *	
 *	This file contains the definition of the array iterator classes.
*/

#include "../../Object.h"
#include "Container.h"

#include "../Util.h"
#include "../Types/String.h"

namespace snow
{

template<typename T>
class Array;

namespace
{

/**
 *	\brief The base for array iterators
 *	
 *	This class is used as a template for ArrayIterator and ConstArrayIterator classes.
 *	\warning Do not use this class directly.
 */
template<typename T_Container, typename T_Element>
class BaseArrayIterator_ :
	public Object,
	public IIterator<T_Container, T_Element>
{
	template<typename T>
	friend class Array;

public:

	/**
	 *	\brief Copy constructor
	 *	
	 *	Creates a copy of the passed iterator.
	 *	\param iterator The iterator that will be copied.
	 */
	BaseArrayIterator_(const BaseArrayIterator_<T_Container, T_Element>& iterator) noexcept;

	/**
	 *	\brief Move constructor
	 *	
	 *	Creates a new iterator by moving the passed one.
	 *	\param iterator The iterator that will be moved.
	 */
	BaseArrayIterator_(BaseArrayIterator_<T_Container, T_Element>&& iterator) noexcept;

	/**
	 *	\brief The destructor
	 *	
	 *	The destructor of the array iterator.
	 */
	virtual ~BaseArrayIterator_() noexcept;

	/**
	 *	\brief Converts an element of the iterator to string
	 *	
	 *	Gets the element that the iterator points to and converts it to string using
	 *	`util::to_string()` function.
	 *	\code
	 *		// These two strings are equal:
	 *		iterator.to_string();
	 *		util::to_string(iterator.get());
	 *	\endcode
	 *	\return A result string.
	 */
	virtual String to_string() const noexcept override;

	/**
	 *	\brief Hash code of an element of the iterator
	 *
	 *	Gets the element that the iterator points to and calculates its hash code using
	 *	`util::hash_code()` function.
	 *	\code
	 *		// These two strings are equal:
	 *		iterator.hash_code();
	 *		util::hash_code(iterator.get());
	 *	\endcode
	 *	\return Hash code of the element.
	 */
	virtual int hash_code() const noexcept override;

	/**
	 *	\brief Whether the iterator is valid
	 *
	 *	The iterator may be invalid if its container has been destroyed.
	 *	\return `true` if the iterator is valid, `false` otherwise.
	*/
	virtual bool is_valid() const noexcept override;

	/**
	 *	\brief Whether the iterator points to a valid element
	 *
	 *	This function returns `false` if the iterator is not valid or points to the end of the
	 *	array (i. e. after the last array element).
	 *	\return `true` if the iterator points to a valid element, `false` otherwise.
	 */
	virtual bool is_element_valid() const noexcept override;
	
	/**
	 *	\brief The container of the iterator
	 *
	 *	Allows to get the array that has the element that the iterator points to.
	 *	\return The container of the iterator.
	 *	\throw std::logic_error The iterator is not valid.
	 */
	virtual T_Container& get_container() const override;

	/**
	 *	\brief Get the element that the iterator points to
	 *
	 *	Allows to get the element that the iterator points to.
	 *	\return The element that the iterator points to.
	 *	\throw std::logic_error The element is not valid (`is_element_valid()` method returns
	 *	`false`.
	 */
	virtual T_Element& get() const override;

	/**
	 *	\brief Index of the element that the iterator points to
	 *	
	 *	Allows to get index of the element that the iterator points to.
	 *	\return Index of the element.
	 *	\throw std::logic_error The iterator is not valid.
	 */
	int get_index() const;

	/**
	 *	\brief Whether the iterator points to the first element of the array
	 *
	 *	The iterator is begin if it points to the first element.
	 *	\return `true` if the iterator points to the first element of the array.
	 */
	virtual bool is_begin() const noexcept override;
	
	/**
	 *	\brief Whether the iterator points to the last element of the array
	 *
	 *	The iterator is last if it points to the last element.
	 *	\return `true` if the iterator points to the last element of the array.
	 */
	virtual bool is_last() const noexcept override;

	/**
	 *	\brief Whether the iterator points after the last element of the array
	 *
	 *	The iterator is end if it points to a space that is after the last element. In this case
	 *	`is_element_valid()` method returns `false`.
	 *	\return `true` if the iterator points after the last element of the array.
	 */
	virtual bool is_end() const noexcept override;

	/**
	 *	\brief Moves iterator forward
	 *
	 *	Increases the iterator index so that it points to the next element. The iterator won't be
	 *	changed if it already points after the last element.
	 *	\return `true` if the new element of the iterator is valid (is not end), `false` otherwise.
	 *	\throw std::logic_error The iterator is not valid.
	 */
	virtual bool next() override;

	/**
	 *	\brief Moves the iterator backward
	 *
	 *	Decreases the iterator index so that it points to the previous element. The iterator won't
	 *	be changed if it already points to the first element.
	 *	\return `true` if the iterator has been moved, `false` otherwise.
	 *	\throw std::logic_error The iterator is not valid.
	 */
	virtual bool prev() override;

	/**
	 *	\brief Get the element that the iterator points to
	 *
	 *	This operator is equal to the `get()` method.
	 *	\return The element that the iterator points to.
	 *	\throw std::logic_error The element is not valid (`is_element_valid()` method returns
	 *	`false`.
	 */
	virtual T_Element& operator*() const override;

	/**
	 *	\brief The iterator prefix increment
	 *
	 *	Increases the iterator index so that it points to the next element. The iterator won't be
	 *	changed if it already points after the last element.
	 *	\return The increased iterator.
	 *	\throw std::logic_error The iterator is not valid.
	 */
	BaseArrayIterator_<T_Container, T_Element> operator++();

	/**
	 *	\brief The iterator prefix decrement
	 *
	 *	Decreases the iterator index so that it points to the previous element. The iterator won't
	 *	be changed if it already points to the first element.
	 *	\return The decreased iterator.
	 *	\throw std::logic_error The iterator is not valid.
	 */
	BaseArrayIterator_<T_Container, T_Element> operator--();

	/**
	 *	\brief The iterator postfix increment
	 *
	 *	Increases the iterator index so that it points to the next element. The iterator won't be
	 *	changed if it already points after the last element.
	 *	\return The iterator before increasing.
	 *	\throw std::logic_error The iterator is not valid.
	 */
	BaseArrayIterator_<T_Container, T_Element> operator++(int);

	/**
	 *	\brief The iterator prefix decrement
	 *
	 *	Decreases the iterator index so that it points to the previous element. The iterator won't
	 *	be changed if it already points to the first element.
	 *	\return The iterator before decreasing.
	 *	\throw std::logic_error The iterator is not valid.
	 */
	BaseArrayIterator_<T_Container, T_Element> operator--(int);

	/**
	 *	\brief Compare two iterators
	 *
	 *	Two array iterators are equal if they point to the same element of the same array. The
	 *	iterators are also equal if they are both invalid.
	 *	\return `true` if the iterators are equal, `false` otherwise.
	 */
	bool operator==(const BaseArrayIterator_<T_Container, T_Element>& iterator) const noexcept;

	/**
	 *	\brief Compare two iterators
	 *
	 *	Two array iterators are equal if they point to the same element of the same array. The
	 *	iterators are also equal if they are both invalid.
	 *	\return `true` if the iterators are not equal, `false` otherwise.
	 */
	bool operator!=(const BaseArrayIterator_<T_Container, T_Element>& iterator) const noexcept;
	
	/**
	 *	\brief Get access to the element that the iterator points to
	 *
	 *	This operator allows to get access to members of the element that the iterator points to.
	 *	\return The pointer to the iterator element.
	 *	\throw std::logic_error The element is not valid (`is_element_valid()` method returns
	 *	`false`.
	 */
	virtual T_Element* operator->() const override;

private:
	BaseArrayIterator_(T_Container& array, int index, bool is_valid = true) noexcept;

	T_Container& container_;
	int index_;
	bool is_valid_;
};

}

/**
 *	\brief The iterator to the element of a constant array
 *	
 *	This iterator allows to read elements of an array but doesn't allow to modify them or the
 *	array. Can be created by a constant array (or using `iterator_to_const()` method).
 *	\tparam T Type of the array elements.
 */
template<typename T>
using ConstArrayIterator = BaseArrayIterator_<const Array<T>, const T>;

/**
 *	\brief The iterator to the element of an array
 *	
 *	This iterator allows to access elements of an array (read and modify them).
 *	\tparam T Type of the array elements.
 */
template<typename T>
using ArrayIterator = BaseArrayIterator_<Array<T>, T>;


		/* DEFINITIONS */

template<typename T_Container, typename T_Element>
BaseArrayIterator_<T_Container, T_Element>::BaseArrayIterator_(const BaseArrayIterator_<T_Container, T_Element>& iterator) noexcept :
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
BaseArrayIterator_<T_Container, T_Element>::BaseArrayIterator_(BaseArrayIterator_<T_Container, T_Element>&& iterator) noexcept :
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
BaseArrayIterator_<T_Container, T_Element>::~BaseArrayIterator_() noexcept
{
	if (is_valid_)
	{
		container_.unregister_iterator_(this);
	}
}

template<typename T_Container, typename T_Element>
String BaseArrayIterator_<T_Container, T_Element>::to_string() const noexcept
{
	return util::to_string(get());
}

template<typename T_Container, typename T_Element>
int BaseArrayIterator_<T_Container, T_Element>::hash_code() const noexcept
{
	return util::hash_code(get());
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::is_valid() const noexcept
{
	return is_valid_ && index_ >= 0 && index_ <= container_.size();
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::is_element_valid() const noexcept
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
		throw std::logic_error("Attempt to get container of an invalid iterator");
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
		throw std::logic_error("Attempt to get element of an invalid iterator");
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
		throw std::logic_error("Attempt to get index of an invalid iterator");
	}
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::is_begin() const noexcept
{
	return is_valid_ && index_ == 0;
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::is_last() const noexcept
{
	return is_valid_ && index_ == container_.size() - 1;
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::is_end() const noexcept
{
	return is_valid_ && index_ == container_.size();
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::next()
{
	if (is_valid_)
	{
		return index_ < container_.size() && ++index_ < container_.size();

//		// This do the same:
//		if (is_end())
//		{
//			return false;
//		}
//		else
//		{
//			index_++;
//			return !is_end();
//		}
	}
	else
	{
		throw std::logic_error("Attempt to increment an invalid iterator");
	}
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::prev()
{
	if (is_valid_)
	{
		if (index_ > 0)
		{
			index_--;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		throw std::logic_error("Attempt to decrement an invalid iterator");
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
bool BaseArrayIterator_<T_Container, T_Element>::operator==(const BaseArrayIterator_<T_Container, T_Element>& iterator) const noexcept
{
	return !is_valid() && !iterator.is_valid() ||
		&container_ == &iterator.container_ && index_ == iterator.index_;
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::operator!=(const BaseArrayIterator_<T_Container, T_Element>& iterator) const noexcept
{
	return !(*this == iterator);
}

template<typename T_Container, typename T_Element>
T_Element* BaseArrayIterator_<T_Container, T_Element>::operator->() const
{
	return &get();
}

template<typename T_Container, typename T_Element>
BaseArrayIterator_<T_Container, T_Element>::BaseArrayIterator_(T_Container& array, int index, bool is_valid) noexcept :
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