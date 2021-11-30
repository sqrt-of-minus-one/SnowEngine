    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Deque.h                     //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\brief The file of the Deque class
 *	
 *	This file contains the definition of the SnowEngine Deque class.
 */

#include "LinkedList.h"

namespace snow
{

/**
 *	\brief The class of the SnowEngine deque
 *	
 *	This deque is based on linked list (the LinkedList class). It allows you to push elements into
 *	its beginning and its end, and pop elements from the beginning and the end.
 *	\tparam T The type of elements that are contained in the deque. This type must meet the same
 *	conditions as the template of the LinkedList class.
 */
template<typename T>
class Deque :
	public Object,
	public IContainer<T>
{
public:

	/**
	 *	\brief The default constructor
	 *	
	 *	Creates an empty deque.
	 */
	Deque() noexcept;

	/**
	 *	\brief Copy constructor
	 *	
	 *	Creates a new deque as the copy of the passed one.
	 *	\param deque The deque for copying.
	 */
	Deque(const Deque<T>& deque) noexcept;

	/**
	 *	\brief The move constructor
	 *	
	 *	Creates a new deque by moving the value of the passed one.
	 *	\param deque The deque whose value will be moved.
	 */
	Deque(Deque<T>&& deque) noexcept;
	
	/**
	 *	\brief Convert the deque to string
	 *	
	 *	Uses `to_string()` method of the internal linked list to convert itself to string.
	 *	\return The resultant string.
	 */
	virtual String to_string() const noexcept override;

	/**
	 *	\brief The hash code
	 *	
	 *	The hash code of the deque is the hash code of the internal linked list.
	 *	\return The hash code of the deque.
	 */
	virtual int hash_code() const noexcept override;
	
	/**
	 *	\brief Get the size of the deque
	 *	
	 *	Allows to the the number of elements in the deque.
	 *	\return The number of elements in the deque.
	 */
	virtual int size() const noexcept override;

	/**
	 *	\brief Check whether the deque is empty
	 *	
	 *	Checks if the deque doesn't contains any elements.
	 *	\return `true` if the deque is empty, `false` otherwise.
	 */
	virtual bool is_empty() const noexcept override;

	/**
	 *	\brief Clear the deque
	 *
	 *	Removes all the elements of the deque.
	 */
	virtual void clear() noexcept override;
	
	/**
	 *	\brief Get the first element of the deque
	 *	
	 *	Allows to get an access (read and modify) to the first element of the deque.
	 *	\return The reference to the first element.
	 *	\throw std::out_of_range The deque is empty.
	 */
	T& get_begin();
	
	/**
	 *	\brief Get the last element of the deque
	 *	
	 *	Allows to get an access (read and modify) to the last element of the deque.
	 *	\return The reference to the last element.
	 *	\throw std::out_of_range The deque is empty.
	 */
	T& get_last();
	
	/**
	 *	\brief Get the first element of the deque
	 *	
	 *	Allows to get the value of the first element of the deque.
	 *	\return The constant reference to the first element.
	 *	\throw std::out_of_range The deque is empty.
	 */
	const T& get_begin() const;
	
	/**
	 *	\brief Get the last element of the deque
	 *	
	 *	Allows to get the value of the last element of the deque.
	 *	\return The constant reference to the last element.
	 *	\throw std::out_of_range The deque is empty.
	 */
	const T& get_last() const;
	
	/**
	 *	\brief Pop the first element of the deque
	 *	
	 *	Removes the first element of the deque and returns its value.
	 *	\return The value of the removed element.
	 *	\throw std::out_of_range The deque is empty.
	 */
	T pop_begin();
	
	/**
	 *	\brief Pop the last element of the deque
	 *	
	 *	Removes the last element of the deque and returns its value.
	 *	\return The value of the removed element.
	 *	\throw std::out_of_range The deque is empty.
	 */
	T pop_last();

	/**
	 *	\brief Insert the element into the beginning of the deque.
	 *	
	 *	Inserts the passed element into the beginning of the deque.
	 *	\param T The element that will be inserted.
	 */
	bool push_begin(const T& element);

	/**
	 *	\brief Insert the element into the end of the deque.
	 *	
	 *	Inserts the passed element into the end of the deque.
	 *	\param T The element that will be inserted.
	 */
	bool push_last(const T& element);

	/**
	 *	\brief Insert the element into the beginning of the deque.
	 *	
	 *	Inserts the passed element into the beginning of the deque.
	 *	\param T The element that will be inserted.
	 */
	bool push_begin(T&& element);

	/**
	 *	\brief Insert the element into the end of the deque.
	 *	
	 *	Inserts the passed element into the end of the deque.
	 *	\param T The element that will be inserted.
	 */
	bool push_last(T&& element);
	
	/**
	 *	\brief Remove all elements that are equal to the passed one
	 *	
	 *	Compares every element of the deque with the passed one and removes all mathces.
	 *	\param element The element to compare.
	 *	\return The number of removed elements.
	 */
	virtual int remove_all(const T& element) override;
	
	/**
	 *	\brief Check whether the deque contains the passed element
	 *	
	 *	Compares elements of the deque with the passed one until a match is found.
	 *	\param element The element to compare.
	 *	\return `true` if a match is found, `false` otherwise.
	 */
	virtual bool contains(const T& element) const override;
	
	/**
	 *	\brief Count how many elements of the deque is equal to the passed one
	 *	
	 *	Compares elements of the deque with the passed one and counts matches.
	 *	\param element The element to compare.
	 *	\return The number of matches.
	 */
	virtual int count(const T& element) const override;
	
	/**
	 *	\brief The copy assignment operator
	 *	
	 *	Clears the deque and assigns it the passed one.
	 *	\param deque The deque to assign.
	 *	\return A reference to itself.
	 */	
	Deque<T>& operator=(const Deque<T>& deque);

	/**
	 *	\brief The move assignment operator
	 *	
	 *	Clears the deque and moves elements of the passed one into it.
	 *	\param deque The deque whose elements will be moved.
	 *	\return A reference to itself.
	 */
	Deque<T>& operator=(Deque<T>&& deque);
	
	/**
	 *	\brief Whether two deques are equal
	 *	
	 *	Two deques are equal if they have the same elements in the same order.
	 *	\param deque The deque to compare.
	 *	\return `true` if two deques are equal, `false` otherwise.
	 */
	bool operator==(const Deque<T>& deque) const;
	
	/**
	 *	\brief Whether two deques are not equal
	 *	
	 *	Two deques are equal if they have the same elements in the same order.
	 *	\param deque The deque to compare.
	 *	\return `true` if two deques are not equal, `false` otherwise.
	 */
	bool operator!=(const Deque<T>& deque) const;

private:
	LinkedList<T> list;
};

		/* DEFINITIONS */

template<typename T>
Deque<T>::Deque() noexcept :
	list()
{}

template<typename T>
Deque<T>::Deque(const Deque<T>& deque) noexcept :
	list(deque.list)
{}

template<typename T>
Deque<T>::Deque(Deque<T>&& deque) noexcept :
	list(std::move(deque.list))
{}

template<typename T>
String Deque<T>::to_string() const noexcept
{
	return list.to_string();
}

template<typename T>
int Deque<T>::hash_code() const noexcept
{
	return list.hash_code();
}

template<typename T>
int Deque<T>::size() const noexcept
{
	return list.size();
}

template<typename T>
bool Deque<T>::is_empty() const noexcept
{
	return list.is_empty();
}

template<typename T>
void Deque<T>::clear() noexcept
{
	return list.clear();
}

template<typename T>
T& Deque<T>::get_begin()
{
	return list.get_begin();
}

template<typename T>
T& Deque<T>::get_last()
{
	return list.get_last();
}

template<typename T>
const T& Deque<T>::get_begin() const
{
	return list.get_begin();
}

template<typename T>
const T& Deque<T>::get_last() const
{
	return list.get_last();
}

template<typename T>
T Deque<T>::pop_begin()
{
	T ret = list.get_begin();
	list.remove(list.begin());
	return ret;
}

template<typename T>
T Deque<T>::pop_last()
{
	T ret = list.get_last();
	list.remove(list.last());
	return ret;
}

template<typename T>
bool Deque<T>::push_begin(const T& element)
{
	return list.add_to_begin(element);
}

template<typename T>
bool Deque<T>::push_last(const T& element)
{
	return list.add(element);
}

template<typename T>
bool Deque<T>::push_begin(T&& element)
{
	return list.add_to_begin(std::forward<T>(element));
}

template<typename T>
bool Deque<T>::push_last(T&& element)
{
	return list.add(std::forward<T>(element));
}

template<typename T>
int Deque<T>::remove_all(const T& element)
{
	return list.remove_all(element);
}

template<typename T>
bool Deque<T>::contains(const T& element) const
{
	return list.contains(element);
}

template<typename T>
int Deque<T>::count(const T& element) const
{
	return list.count(element);
}

template<typename T>
Deque<T>& Deque<T>::operator=(const Deque<T>& deque)
{
	list = deque.list;
	return *this;
}

template<typename T>
Deque<T>& Deque<T>::operator=(Deque<T>&& deque)
{
	list = std::move(deque.list);
	return *this;
}

template<typename T>
bool Deque<T>::operator==(const Deque<T>& deque) const
{
	return list == deque.list;
}

template<typename T>
bool Deque<T>::operator!=(const Deque<T>& deque) const
{
	return list != deque.list;
}

}
