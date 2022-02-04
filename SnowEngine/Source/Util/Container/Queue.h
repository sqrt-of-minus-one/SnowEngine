    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Queue.h                     //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\brief The file of the Queue class
 *	
 *	This file contains the definition of the SnowEngine Queue class.
 */

#include "LinkedList.h"

namespace snow
{

/**
 *	\brief The class of the SnowEngine queue
 *	
 *	This queue is based on linked list (the LinkedList class). It allows you to push elements only
 *	into its end, and pop elements only from its the beginning.
 *	\tparam T The type of elements that are contained in the queue. This type must meet the same
 *	conditions as the template of the LinkedList class.
 */
template<typename T>
class Queue :
	public Object,
	public IContainer<T>
{
public:

	/**
	 *	\brief The default constructor
	 *	
	 *	Creates an empty queue.
	 */
	Queue() noexcept;

	/**
	 *	\brief Copy constructor
	 *	
	 *	Creates a new queue as the copy of the passed one.
	 *	\param queue The queue for copying.
	 */
	Queue(const Queue<T>& queue) noexcept;

	/**
	 *	\brief The move constructor
	 *	
	 *	Creates a new queue by moving the value of the passed one.
	 *	\param queue The queue whose value will be moved.
	 */
	Queue(Queue<T>&& queue) noexcept;
	
	/**
	 *	\brief Convert the queue to string
	 *	
	 *	Uses `to_string()` method of the internal linked list to convert itself to string.
	 *	\return The resultant string.
	 */
	virtual String to_string() const noexcept override;

	/**
	 *	\brief The hash code
	 *	
	 *	The hash code of the queue is the hash code of the internal linked list.
	 *	\return The hash code of the queue.
	 */
	virtual int hash_code() const noexcept override;
	
	/**
	 *	\brief Get the size of the queue
	 *	
	 *	Allows to the the number of elements in the queue.
	 *	\return The number of elements in the queue.
	 */
	virtual int size() const noexcept override;

	/**
	 *	\brief Check whether the queue is empty
	 *	
	 *	Checks if the queue doesn't contains any elements.
	 *	\return `true` if the queue is empty, `false` otherwise.
	 */
	virtual bool is_empty() const noexcept override;

	/**
	 *	\brief Clear the queue
	 *
	 *	Removes all the elements of the queue.
	 */
	virtual void clear() noexcept override;
	
	/**
	 *	\brief Get the first element of the queue
	 *	
	 *	Allows to get an access (read and modify) to the first element of the queue.
	 *	\return The reference to the first element.
	 *	\throw std::out_of_range The queue is empty.
	 */
	T& get();
	
	/**
	 *	\brief Get the first element of the queue
	 *	
	 *	Allows to get the value of the first element of the queue.
	 *	\return The constant reference to the first element.
	 *	\throw std::out_of_range The queue is empty.
	 */
	const T& get() const;
	
	/**
	 *	\brief Pop the first element of the queue
	 *	
	 *	Removes the first element of the queue and returns its value.
	 *	\return The value of the removed element.
	 */
	T pop();

	/**
	 *	\brief Insert the element into the end of the queue.
	 *	
	 *	Inserts the passed element into the end of the queue.
	 *	\param T The element that will be inserted.
	 */
	bool push(const T& element);

	/**
	 *	\brief Insert the element into the end of the queue.
	 *	
	 *	Inserts the passed element into the end of the queue.
	 *	\param T The element that will be inserted.
	 */
	bool push(T&& element);
	
	/**
	 *	\brief Remove all elements that are equal to the passed one
	 *	
	 *	Compares every element of the queue with the passed one and removes all mathces.
	 *	\param element The element to compare.
	 *	\return The number of removed elements.
	 */
	virtual int remove_all(const T& element) override;
	
	/**
	 *	\brief Check whether the queue contains the passed element
	 *	
	 *	Compares elements of the queue with the passed one until a match is found.
	 *	\param element The element to compare.
	 *	\return `true` if a match is found, `false` otherwise.
	 */
	virtual bool contains(const T& element) const override;
	
	/**
	 *	\brief Count how many elements of the queue is equal to the passed one
	 *	
	 *	Compares elements of the queue with the passed one and counts matches.
	 *	\param element The element to compare.
	 *	\return The number of matches.
	 */
	virtual int count(const T& element) const override;
	
	/**
	 *	\brief The copy assignment operator
	 *	
	 *	Clears the queue and assigns it the passed one.
	 *	\param queue The queue to assign.
	 *	\return A reference to itself.
	 */	
	Queue<T>& operator=(const Queue<T>& queue);

	/**
	 *	\brief The move assignment operator
	 *	
	 *	Clears the queue and moves elements of the passed one into it.
	 *	\param queue The queue whose elements will be moved.
	 *	\return A reference to itself.
	 */
	Queue<T>& operator=(Queue<T>&& queue);
	
	/**
	 *	\brief Whether two queues are equal
	 *	
	 *	Two queues are equal if they have the same elements in the same order.
	 *	\param queue The queue to compare.
	 *	\return `true` if two queues are equal, `false` otherwise.
	 */
	bool operator==(const Queue<T>& queue) const;
	
	/**
	 *	\brief Whether two queues are not equal
	 *	
	 *	Two queues are equal if they have the same elements in the same order.
	 *	\param queue The queue to compare.
	 *	\return `true` if two queues are not equal, `false` otherwise.
	 */
	bool operator!=(const Queue<T>& queue) const;

private:
	LinkedList<T> list;
};

		/* DEFINITIONS */

template<typename T>
Queue<T>::Queue() noexcept :
	list()
{}

template<typename T>
Queue<T>::Queue(const Queue<T>& queue) noexcept :
	list(queue.list)
{}

template<typename T>
Queue<T>::Queue(Queue<T>&& queue) noexcept :
	list(std::move(queue.list))
{}

template<typename T>
String Queue<T>::to_string() const noexcept
{
	return list.to_string();
}

template<typename T>
int Queue<T>::hash_code() const noexcept
{
	return list.hash_code();
}

template<typename T>
int Queue<T>::size() const noexcept
{
	return list.size();
}

template<typename T>
bool Queue<T>::is_empty() const noexcept
{
	return list.is_empty();
}

template<typename T>
void Queue<T>::clear() noexcept
{
	return list.clear();
}

template<typename T>
T& Queue<T>::get()
{
	return list.get_begin();
}

template<typename T>
const T& Queue<T>::get() const
{
	return list.get_begin();
}

template<typename T>
T Queue<T>::pop()
{
	T ret = list.get_begin();
	list.remove(list.begin());
	return ret;
}

template<typename T>
bool Queue<T>::push(const T& element)
{
	return list.add(element);
}

template<typename T>
bool Queue<T>::push(T&& element)
{
	return list.add(std::forward<T>(element));
}

template<typename T>
int Queue<T>::remove_all(const T& element)
{
	return list.remove_all(element);
}

template<typename T>
bool Queue<T>::contains(const T& element) const
{
	return list.contains(element);
}

template<typename T>
int Queue<T>::count(const T& element) const
{
	return list.count(element);
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& queue)
{
	list = queue.list;
	return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& queue)
{
	list = std::move(queue.list);
	return *this;
}

template<typename T>
bool Queue<T>::operator==(const Queue<T>& queue) const
{
	return list == queue.list;
}

template<typename T>
bool Queue<T>::operator!=(const Queue<T>& queue) const
{
	return list != queue.list;
}

}
