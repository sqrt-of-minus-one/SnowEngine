    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: LinkedListIterator.h        //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\brief The file of linked list iterator
 *	
 *	This file contains the definition of the linked list iterator classes.
 */

#include "../../Object.h"
#include "Container.h"

#include "../Util.h"
#include "../Types/String.h"

namespace snow
{

template<typename T>
class LinkedList;

namespace
{

template<typename T>
struct LinkedListNode_;

/**
 *	\brief The base for linked list iterators
 *	
 *	This class is used as a template for LinkedListIterator and ConstLinkedListIterator classes.
 *	\warning Do not use this class directly.
 */
template<typename T_Container, typename T_Element, typename T_Node>
class BaseLinkedListIterator_ :
	public Object,
	public IIterator<T_Container, T_Element>
{
	template<typename T>
	friend class LinkedList;

public:

	/**
	 *	\brief Copy constructor
	 *
	 *	Creates a copy of the passed iterator.
	 *	\param iterator The iterator that will be copied.
	 */
	BaseLinkedListIterator_(const BaseLinkedListIterator_<T_Container, T_Element, T_Node>& iterator) noexcept;

	/**
	 *	\brief Move constructor
	 *
	 *	Creates a new iterator by moving the passed one.
	 *	\param iterator The iterator that will be moved.
	 */
	BaseLinkedListIterator_(BaseLinkedListIterator_<T_Container, T_Element, T_Node>&& iterator) noexcept;

	/**
	 *	\brief The destructor
	 *
	 *	The destructor of the linked list iterator.
	 */
	~BaseLinkedListIterator_() noexcept;

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
	 *	linked list (i. e. after the last linked list element).
	 *	\return `true` if the iterator points to a valid element, `false` otherwise.
	 */
	virtual bool is_element_valid() const noexcept override;

	/**
	 *	\brief The container of the iterator
	 *
	 *	Allows to get the linked list that has the element that the iterator points to.
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
	 *	\brief Whether the iterator points to the first element of the linked list
	 *
	 *	The iterator is begin if it points to the first element.
	 *	\return `true` if the iterator points to the first element of the linked list.
	 */
	virtual bool is_begin() const noexcept override;

	/**
	 *	\brief Whether the iterator points to the last element of the linked list
	 *
	 *	The iterator is last if it points to the last element.
	 *	\return `true` if the iterator points to the last element of the linked list.
	 */
	virtual bool is_last() const noexcept override;

	/**
	 *	\brief Whether the iterator points after the last element of the linked list
	 *
	 *	The iterator is end if it points to a space that is after the last element. In this case
	 *	`is_element_valid()` method returns `false`.
	 *	\return `true` if the iterator points after the last element of the linked list.
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
	virtual T_Element& operator*() const override;

	/**
	 *	\brief The iterator prefix increment
	 *
	 *	Changes the iterator so that it points to the next element. The iterator won't be changed
	 *	if it already points after the last element.
	 *	\return The increased iterator.
	 *	\throw std::logic_error The iterator is not valid.
	 */
	BaseLinkedListIterator_<T_Container, T_Element, T_Node> operator++();

	/**
	 *	\brief The iterator prefix decrement
	 *
	 *	Changes the iterator so that it points to the previous element. The iterator won't be
	 *	changed if it already points to the first element.
	 *	\return The decreased iterator.
	 *	\throw std::logic_error The iterator is not valid.
	 */
	BaseLinkedListIterator_<T_Container, T_Element, T_Node> operator--();

	/**
	 *	\brief The iterator postfix increment
	 *
	 *	Changes the iterator so that it points to the next element. The iterator won't be changed
	 *	if it already points after the last element.
	 *	\return The iterator before increasing.
	 *	\throw std::logic_error The iterator is not valid.
	 */
	BaseLinkedListIterator_<T_Container, T_Element, T_Node> operator++(int);

	/**
	 *	\brief The iterator prefix decrement
	 *
	 *	Changes the iterator so that it points to the previous element. The iterator won't be
	 *	changed if it already points to the first element.
	 *	\return The iterator before decreasing.
	 *	\throw std::logic_error The iterator is not valid.
	 */
	BaseLinkedListIterator_<T_Container, T_Element, T_Node> operator--(int);

	/**
	 *	\brief Compare two iterators
	 *
	 *	Two linked list iterators are equal if they point to the same element of the same list. The
	 *	iterators are also equal if they are both invalid.
	 *	\return `true` if the iterators are equal, `false` otherwise.
	 */
	bool operator==(const BaseLinkedListIterator_<T_Container, T_Element, T_Node>& iterator) const noexcept;

	/**
	 *	\brief Compare two iterators
	 *
	 *	Two linked list iterators are equal if they point to the same element of the same list. The
	 *	iterators are also equal if they are both invalid.
	 *	\return `true` if the iterators are not equal, `false` otherwise.
	 */
	bool operator!=(const BaseLinkedListIterator_<T_Container, T_Element, T_Node>& iterator) const noexcept;

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
	BaseLinkedListIterator_(T_Container& linked_list, int index, std::shared_ptr<T_Node> node = nullptr, bool is_valid = true) noexcept;

	T_Container& container_;
	std::weak_ptr<T_Node> node_;
	int index_;
	bool is_valid_;
};

}

/**
 *	\brief The iterator to the element of a constant linked list
 *
 *	This iterator allows to read elements of a linked list but doesn't allow to modify them or the
 *	list. Can be created by a constant linked list (or using `iterator_to_const()` method).
 *	\tparam T Type of the linked list elements.
 */
template<typename T>
using ConstLinkedListIterator = BaseLinkedListIterator_<const LinkedList<T>, const T, LinkedListNode_<T>>;

/**
 *	\brief The iterator to the element of a linked list
 *
 *	This iterator allows to access elements of a linked list (read and modify them).
 *	\tparam T Type of the linked list elements.
 */
template<typename T>
using LinkedListIterator = BaseLinkedListIterator_<LinkedList<T>, T, LinkedListNode_<T>>;


		/* DEFINITIONS */

template<typename T_Container, typename T_Element, typename T_Node>
BaseLinkedListIterator_<T_Container, T_Element, T_Node>::BaseLinkedListIterator_(const BaseLinkedListIterator_<T_Container, T_Element, T_Node>& iterator) noexcept :
	container_(iterator.container_),
	node_(iterator.node_),
	index_(iterator.index_),
	is_valid_(iterator.is_valid_)
{
	if (is_valid_)
	{
		container_.register_iterator_(this);
	}
}

template<typename T_Container, typename T_Element, typename T_Node>
BaseLinkedListIterator_<T_Container, T_Element, T_Node>::BaseLinkedListIterator_(BaseLinkedListIterator_<T_Container, T_Element, T_Node>&& iterator) noexcept :
	container_(iterator.container_),
	node_(iterator.node_),
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

template<typename T_Container, typename T_Element, typename T_Node>
BaseLinkedListIterator_<T_Container, T_Element, T_Node>::~BaseLinkedListIterator_() noexcept
{
	if (is_valid_)
	{
		container_.unregister_iterator_(this);
	}
}

template<typename T_Container, typename T_Element, typename T_Node>
String BaseLinkedListIterator_<T_Container, T_Element, T_Node>::to_string() const noexcept
{
	return util::to_string(get());
}

template<typename T_Container, typename T_Element, typename T_Node>
int BaseLinkedListIterator_<T_Container, T_Element, T_Node>::hash_code() const noexcept
{
	return util::hash_code(get());
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::is_valid() const noexcept
{
	return is_valid_ && index_ >= 0 && index_ <= container_.size();
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::is_element_valid() const noexcept
{
	return is_valid_ && node_.lock() && index_ >= 0 && index_ < container_.size();
}

template<typename T_Container, typename T_Element, typename T_Node>
T_Container& BaseLinkedListIterator_<T_Container, T_Element, T_Node>::get_container() const
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

template<typename T_Container, typename T_Element, typename T_Node>
T_Element& BaseLinkedListIterator_<T_Container, T_Element, T_Node>::get() const
{
	if (is_element_valid())
	{
		return node_.lock()->value;
	}
	else
	{
		throw std::logic_error("Attempt to get element of an invalid iterator");
	}
}

template<typename T_Container, typename T_Element, typename T_Node>
int BaseLinkedListIterator_<T_Container, T_Element, T_Node>::get_index() const
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

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::is_begin() const noexcept
{
	return is_valid_ && index_ == 0;
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::is_last() const noexcept
{
	return is_valid_ && index_ == container_.size() - 1;
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::is_end() const noexcept
{
	return is_valid_ && index_ == container_.size();
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::next()
{
	if (is_valid_)
	{
		if (index_ < container_.size())
		{
			node_ = node_.lock()->next;
			return ++index_ < container_.size();
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

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::prev()
{
	if (is_valid_)
	{
		if (index_ > 0)
		{
			if (node_.lock()) // If is not end
			{
				node_ = node_.lock()->prev;
			}
			else
			{
				node_ = container_.get_last_node_();
			}
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

template<typename T_Container, typename T_Element, typename T_Node>
T_Element& BaseLinkedListIterator_<T_Container, T_Element, T_Node>::operator*() const
{
	return get();
}

template<typename T_Container, typename T_Element, typename T_Node>
BaseLinkedListIterator_<T_Container, T_Element, T_Node> BaseLinkedListIterator_<T_Container, T_Element, T_Node>::operator++()
{
	next();
	return *this;
}

template<typename T_Container, typename T_Element, typename T_Node>
BaseLinkedListIterator_<T_Container, T_Element, T_Node> BaseLinkedListIterator_<T_Container, T_Element, T_Node>::operator--()
{
	prev();
	return *this;
}

template<typename T_Container, typename T_Element, typename T_Node>
BaseLinkedListIterator_<T_Container, T_Element, T_Node> BaseLinkedListIterator_<T_Container, T_Element, T_Node>::operator++(int)
{
	auto ret = *this;
	next();
	return ret;
}

template<typename T_Container, typename T_Element, typename T_Node>
BaseLinkedListIterator_<T_Container, T_Element, T_Node> BaseLinkedListIterator_<T_Container, T_Element, T_Node>::operator--(int)
{
	auto ret = *this;
	prev();
	return ret;
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::operator==(const BaseLinkedListIterator_<T_Container, T_Element, T_Node>& iterator) const noexcept
{
	return !is_valid_ && !iterator.is_valid_ ||
		&container_ == &iterator.container_ && index_ == iterator.index_;
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::operator!=(const BaseLinkedListIterator_<T_Container, T_Element, T_Node>& iterator) const noexcept
{
	return !(*this == iterator);
}

template<typename T_Container, typename T_Element, typename T_Node>
T_Element* BaseLinkedListIterator_<T_Container, T_Element, T_Node>::operator->() const
{
	return &get();
}

template<typename T_Container, typename T_Element, typename T_Node>
BaseLinkedListIterator_<T_Container, T_Element, T_Node>::BaseLinkedListIterator_(T_Container& linked_list, int index, std::shared_ptr<T_Node> node, bool is_valid) noexcept :
	container_(linked_list),
	node_(node),
	index_(index),
	is_valid_(is_valid)
{
	if (is_valid_)
	{
		container_.register_iterator_(this);
	}
}

}
