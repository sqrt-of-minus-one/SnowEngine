    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: MapIterator.h               //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\brief The file of map iterator
 *	
 *	This file contains the definition of the map iterator classes.
 */

#include "../../Object.h"
#include "Container.h"

#include "../Types/String.h"

namespace snow
{

template<typename T_Key, typename T_Value>
class Map;

namespace
{

/**
 *	\brief The base for linked list iterators
 *	
 *	This class is used as a template for MapIterator and ConstMapIterator classes.
 *	\warning Do not use this class directly.
 */
template<typename T_Container, typename T_Key, typename T_Value>
class BaseMapIterator_ :
	public Object,
	public IIterator<T_Container, T_Value>
{
	template<typename T_Key, typename T_Value>
	friend class Map;

public:

	/**
	 *	\brief Copy constructor
	 *
	 *	Creates a copy of the passed iterator.
	 *	\param iterator The iterator that will be copied.
	 */
	BaseMapIterator_(const BaseMapIterator_<T_Container, T_Key, T_Value>& iterator) noexcept;

	/**
	 *	\brief Move constructor
	 *
	 *	Creates a new iterator by moving the passed one.
	 *	\param iterator The iterator that will be moved.
	 */
	BaseMapIterator_(BaseMapIterator_<T_Container, T_Key, T_Value>&& iterator) noexcept;

	/**
	 *	\brief The destructor
	 *
	 *	The destructor of the map iterator.
	 */
	virtual ~BaseMapIterator_() noexcept;

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
	 *	This function returns `false` if the iterator is not valid or points to the end of the map
	 *	(i. e. after the last map element).
	 *	\return `true` if the iterator points to a valid element, `false` otherwise.
	 */
	virtual bool is_element_valid() const noexcept override;

	/**
	 *	\brief The container of the iterator
	 *
	 *	Allows to get the map that has the element that the iterator points to.
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
	 *	`false`).
	 */
	virtual T_Value& get() const override;

	/**
	 *	\brief Get a key of the iterator element
	 *	
	 *	Allows to get a key that the iterator element is associated with.
	 *	\return The key of the iterator element.
	 *	\throw std::logic_error The element is not valid (`is_element_valid()` method returns
	 *	`false`).
	 */
	const T_Key& get_key() const;

	/**
	 *	\brief Whether the iterator points to the first element of the map
	 *
	 *	The iterator is begin if it points to the first element.
	 *	\return `true` if the iterator points to the first element of the map.
	 */
	virtual bool is_begin() const noexcept override;

	/**
	 *	\brief Whether the iterator points to the last element of the map
	 *
	 *	The iterator is last if it points to the last element.
	 *	\return `true` if the iterator points to the last element of the map.
	 */
	virtual bool is_last() const noexcept override;

	/**
	 *	\brief Whether the iterator points after the last element of the map
	 *
	 *	The iterator is end if it points to a space that is after the last element. In this case
	 *	`is_element_valid()` method returns `false`.
	 *	\return `true` if the iterator points after the last element of the map.
	 */
	virtual bool is_end() const noexcept override;

	/**
	 *	\brief Moves iterator forward
	 *
	 *	Changes the iterator so that it points to the next element. The iterator won't be changed
	 *	if it already points after the last element.
	 *	\return `true` if the new element of the iterator is valid (is not end), `false` otherwise.
	 *	\throw std::logic_error The iterator is not valid.
	 */
	virtual bool next() override;

	/**
	 *	\brief Moves the iterator backward
	 *
	 *	Changes the iterator so that it points to the previous element. The iterator won't be
	 *	changed if it already points to the first element.
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
	virtual T_Value& operator*() const override;

	/**
	 *	\brief The iterator prefix increment
	 *
	 *	Changes the iterator so that it points to the next element. The iterator won't be changed
	 *	if it already points after the last element.
	 *	\return The increased iterator.
	 *	\throw std::logic_error The iterator is not valid.
	 */
	BaseMapIterator_<T_Container, T_Key, T_Value> operator++();

	/**
	 *	\brief The iterator prefix decrement
	 *
	 *	Changes the iterator so that it points to the previous element. The iterator won't be
	 *	changed if it already points to the first element.
	 *	\return The decreased iterator.
	 *	\throw std::logic_error The iterator is not valid.
	 */
	BaseMapIterator_<T_Container, T_Key, T_Value> operator--();

	/**
	 *	\brief The iterator postfix increment
	 *
	 *	Changes the iterator so that it points to the next element. The iterator won't be changed
	 *	if it already points after the last element.
	 *	\return The iterator before increasing.
	 *	\throw std::logic_error The iterator is not valid.
	 */
	BaseMapIterator_<T_Container, T_Key, T_Value> operator++(int);

	/**
	 *	\brief The iterator prefix decrement
	 *
	 *	Changes the iterator so that it points to the previous element. The iterator won't be
	 *	changed if it already points to the first element.
	 *	\return The iterator before decreasing.
	 *	\throw std::logic_error The iterator is not valid.
	 */
	BaseMapIterator_<T_Container, T_Key, T_Value> operator--(int);

	/**
	 *	\brief Compare two iterators
	 *
	 *	Two map iterators are equal if they point to the same element of the same map. The
	 *	iterators are also equal if they are both invalid.
	 *	\return `true` if the iterators are equal, `false` otherwise.
	 */
	bool operator==(const BaseMapIterator_<T_Container, T_Key, T_Value>& iterator) const noexcept;

	/**
	 *	\brief Compare two iterators
	 *
	 *	Two map iterators are equal if they point to the same element of the same map. The
	 *	iterators are also equal if they are both invalid.
	 *	\return `true` if the iterators are not equal, `false` otherwise.
	 */
	bool operator!=(const BaseMapIterator_<T_Container, T_Key, T_Value>& iterator) const noexcept;

	/**
	 *	\brief Get access to the element that the iterator points to
	 *
	 *	This operator allows to get access to members of the element that the iterator points to.
	 *	\return The pointer to the iterator element.
	 *	\throw std::logic_error The element is not valid (`is_element_valid()` method returns
	 *	`false`.
	 */
	T_Value* operator->() const;

protected:
	BaseMapIterator_(T_Container& map, const T_Key& key, bool is_end, bool is_valid = true) noexcept;

	T_Container& container_;
	T_Key key_;
	bool is_end_;
	bool is_valid_;
};

}

template<typename T_Key, typename T_Value>
using ConstMapIterator = BaseMapIterator_<const Map<T_Key, T_Value>, T_Key, const T_Value>;

template<typename T_Key, typename T_Value>
using MapIterator = BaseMapIterator_<Map<T_Key, T_Value>, T_Key, T_Value>;


		/* DEFINITIONS */

template<typename T_Container, typename T_Key, typename T_Value>
BaseMapIterator_<T_Container, T_Key, T_Value>::BaseMapIterator_(const BaseMapIterator_<T_Container, T_Key, T_Value>& iterator) noexcept :
	container_(iterator.container_),
	key_(iterator.key_),
	is_end_(iterator.is_end_),
	is_valid_(iterator.is_valid_)
{
	if (is_valid_)
	{
		container_.register_iterator_(this);
	}
}

template<typename T_Container, typename T_Key, typename T_Value>
BaseMapIterator_<T_Container, T_Key, T_Value>::BaseMapIterator_(BaseMapIterator_<T_Container, T_Key, T_Value>&& iterator) noexcept :
	container_(iterator.container_),
	key_(iterator.key_),
	is_end_(iterator.is_end_),
	is_valid_(iterator.is_valid_)
{
	if (is_valid_)
	{
		iterator.is_valid_ = false;
		container_.unregister_iterator_(&iterator);
		container_.register_iterator_(this);
	}
}

template<typename T_Container, typename T_Key, typename T_Value>
BaseMapIterator_<T_Container, T_Key, T_Value>::~BaseMapIterator_() noexcept
{
	if (is_valid_)
	{
		container_.unregister_iterator_(this);
	}
}

template<typename T_Container, typename T_Key, typename T_Value>
String BaseMapIterator_<T_Container, T_Key, T_Value>::to_string() const noexcept
{
	return util::to_string(get());
}

template<typename T_Container, typename T_Key, typename T_Value>
int BaseMapIterator_<T_Container, T_Key, T_Value>::hash_code() const noexcept
{
	return util::hash_code(get());
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::is_valid() const noexcept
{
	return is_valid_;
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::is_element_valid() const noexcept
{
	return is_valid_ && !is_end_;
}

template<typename T_Container, typename T_Key, typename T_Value>
T_Container& BaseMapIterator_<T_Container, T_Key, T_Value>::get_container() const
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

template<typename T_Container, typename T_Key, typename T_Value>
T_Value& BaseMapIterator_<T_Container, T_Key, T_Value>::get() const
{
	if (is_element_valid())
	{
		return container_[key_];
	}
	else
	{
		throw std::logic_error("Attempt to get element of an invalid iterator");
	}
}

template<typename T_Container, typename T_Key, typename T_Value>
const T_Key& BaseMapIterator_<T_Container, T_Key, T_Value>::get_key() const
{
	if (is_element_valid())
	{
		return key_;
	}
	else
	{
		throw std::logic_error("Attempt to get key of an invalid iterator");
	}
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::is_begin() const noexcept
{
	return is_valid_ && !is_end_ && container_.map_[container_.first_filled_].get_begin().get_first() == key_;
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::is_last() const noexcept
{
	return is_valid_ && !is_end_ && container_.map_[container_.last_filled_].get_last().get_first() == key_;
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::is_end() const noexcept
{
	return is_valid_ && is_end_;
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::next()
{
	if (is_valid_)
	{
		if (!is_end_)
		{
			if (container_.map_[container_.last_filled_].get_last().get_first() != key_)
			{
				int hash = math::abs(util::hash_code(key_) % container_.internal_size_);
				auto& list = container_.map_[hash];
				auto itr = list.begin();
				while (itr.get().get_first() != key_ && itr.next());
				if (itr.is_last())
				{
					while (container_.map_[++hash].is_empty());
					key_ = container_.map_[hash].get_begin().get_first();
				}
				else
				{
					itr.next();
					key_ = itr.get().get_first();
				}
				return true;
			}
			else
			{
				is_end_ = true;
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		throw std::logic_error("Attempt to increment an invalid iterator");
	}
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::prev()
{
	if (is_valid_)
	{
		if (container_.map_[container_.first_filled_].get_begin().get_first() != key_)
		{
			if (!is_end_)
			{
				int hash = math::abs(util::hash_code(key_) % container_.internal_size_);
				auto& list = container_.map_[hash];
				auto itr = --(list.end());
				while (itr.get().get_first() != key_ && itr.prev());
				if (itr.is_begin())
				{
					while (container_.map_[--hash].is_empty());
					key_ = container_.map_[hash].get_last().get_first();
				}
				else
				{
					itr.prev();
					key_ = itr.get().get_first();
				}
			}
			else
			{
				key_ = container_.map_[container_.last_filled_].get_last().get_first();
				is_end_ = false;
			}
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

template<typename T_Container, typename T_Key, typename T_Value>
T_Value& BaseMapIterator_<T_Container, T_Key, T_Value>::operator*() const
{
	return get();
}

template<typename T_Container, typename T_Key, typename T_Value>
BaseMapIterator_<T_Container, T_Key, T_Value> BaseMapIterator_<T_Container, T_Key, T_Value>::operator++()
{
	next();
	return *this;
}

template<typename T_Container, typename T_Key, typename T_Value>
BaseMapIterator_<T_Container, T_Key, T_Value> BaseMapIterator_<T_Container, T_Key, T_Value>::operator--()
{
	prev();
	return *this;
}

template<typename T_Container, typename T_Key, typename T_Value>
BaseMapIterator_<T_Container, T_Key, T_Value> BaseMapIterator_<T_Container, T_Key, T_Value>::operator++(int)
{
	auto ret = *this;
	next();
	return ret;
}

template<typename T_Container, typename T_Key, typename T_Value>
BaseMapIterator_<T_Container, T_Key, T_Value> BaseMapIterator_<T_Container, T_Key, T_Value>::operator--(int)
{
	auto ret = *this;
	prev();
	return ret;
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::operator==(const BaseMapIterator_<T_Container, T_Key, T_Value>& iterator) const noexcept
{
	return !is_valid() && !iterator.is_valid() ||
		&container_ == &iterator.container_ &&
		(is_end_ && iterator.is_end_ || !is_end_ && !iterator.is_end_ && key_ == iterator.key_);
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::operator!=(const BaseMapIterator_<T_Container, T_Key, T_Value>& iterator) const noexcept
{
	return !(*this == iterator);
}

template<typename T_Container, typename T_Key, typename T_Value>
T_Value* BaseMapIterator_<T_Container, T_Key, T_Value>::operator->() const
{
	return &get();
}

template<typename T_Container, typename T_Key, typename T_Value>
BaseMapIterator_<T_Container, T_Key, T_Value>::BaseMapIterator_(T_Container& map, const T_Key& key, bool is_end, bool is_valid) noexcept :
	container_(map),
	key_(key),
	is_end_(is_end),
	is_valid_(is_valid)
{
	if (is_valid_)
	{
		container_.register_iterator_(this);
	}
}

}