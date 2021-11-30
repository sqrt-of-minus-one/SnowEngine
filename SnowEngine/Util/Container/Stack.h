    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Stack.h                     //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\brief The file of the Stack class
 *	
 *	This file contains the definition of the SnowEngine Stack class.
 */

#include "LinkedList.h"

namespace snow
{

/**
 *	\brief The class of the SnowEngine stack
 *	
 *	This stack is based on linked list (the LinkedList class). It allows you to push elements only
 *	into its end, and pop elements only from its the end.
 *	\tparam T The type of elements that are contained in the stack. This type must meet the same
 *	conditions as the template of the LinkedList class.
 */
template<typename T>
class Stack :
	public Object,
	public IContainer<T>
{
public:

	/**
	 *	\brief The default constructor
	 *	
	 *	Creates an empty stack.
	 */
	Stack() noexcept;

	/**
	 *	\brief Copy constructor
	 *	
	 *	Creates a new stack as the copy of the passed one.
	 *	\param stack The stack for copying.
	 */
	Stack(const Stack<T>& stack) noexcept;

	/**
	 *	\brief The move constructor
	 *	
	 *	Creates a new stack by moving the value of the passed one.
	 *	\param stack The stack whose value will be moved.
	 */
	Stack(Stack<T>&& stack) noexcept;
	
	/**
	 *	\brief Convert the stack to string
	 *	
	 *	Uses `to_string()` method of the internal linked list to convert itself to string.
	 *	\return The resultant string.
	 */
	virtual String to_string() const noexcept override;

	/**
	 *	\brief The hash code
	 *	
	 *	The hash code of the stack is the hash code of the internal linked list.
	 *	\return The hash code of the stack.
	 */
	virtual int hash_code() const noexcept override;
	
	/**
	 *	\brief Get the size of the stack
	 *	
	 *	Allows to the the number of elements in the stack.
	 *	\return The number of elements in the stack.
	 */
	virtual int size() const noexcept override;

	/**
	 *	\brief Check whether the stack is empty
	 *	
	 *	Checks if the stack doesn't contains any elements.
	 *	\return `true` if the stack is empty, `false` otherwise.
	 */
	virtual bool is_empty() const noexcept override;

	/**
	 *	\brief Clear the stack
	 *
	 *	Removes all the elements of the stack.
	 */
	virtual void clear() noexcept override;
	
	/**
	 *	\brief Get the last element of the stack
	 *	
	 *	Allows to get an access (read and modify) to the last element of the stack.
	 *	\return The reference to the last element.
	 *	\throw std::out_of_range The stack is empty.
	 */
	T& get();
	
	/**
	 *	\brief Get the last element of the stack
	 *	
	 *	Allows to get the value of the last element of the stack.
	 *	\return The constant reference to the last element.
	 *	\throw std::out_of_range The stack is empty.
	 */
	const T& get() const;
	
	/**
	 *	\brief Pop the last element of the stack
	 *	
	 *	Removes the last element of the stack and returns its value.
	 *	\return The value of the removed element.
	 */
	T pop();

	/**
	 *	\brief Insert the element into the end of the stack.
	 *	
	 *	Inserts the passed element into the end of the stack.
	 *	\param T The element that will be inserted.
	 */
	bool push(const T& element);

	/**
	 *	\brief Insert the element into the end of the stack.
	 *	
	 *	Inserts the passed element into the end of the stack.
	 *	\param T The element that will be inserted.
	 */
	bool push(T&& element);
	
	/**
	 *	\brief Remove all elements that are equal to the passed one
	 *	
	 *	Compares every element of the stack with the passed one and removes all mathces.
	 *	\param element The element to compare.
	 *	\return The number of removed elements.
	 */
	virtual int remove_all(const T& element) override;
	
	/**
	 *	\brief Check whether the stack contains the passed element
	 *	
	 *	Compares elements of the stack with the passed one until a match is found.
	 *	\param element The element to compare.
	 *	\return `true` if a match is found, `false` otherwise.
	 */
	virtual bool contains(const T& element) const override;
	
	/**
	 *	\brief Count how many elements of the stack is equal to the passed one
	 *	
	 *	Compares elements of the stack with the passed one and counts matches.
	 *	\param element The element to compare.
	 *	\return The number of matches.
	 */
	virtual int count(const T& element) const override;
	
	/**
	 *	\brief The copy assignment operator
	 *	
	 *	Clears the stack and assigns it the passed one.
	 *	\param stack The stack to assign.
	 *	\return A reference to itself.
	 */	
	Stack<T>& operator=(const Stack<T>& stack);

	/**
	 *	\brief The move assignment operator
	 *	
	 *	Clears the stack and moves elements of the passed one into it.
	 *	\param stack The stack whose elements will be moved.
	 *	\return A reference to itself.
	 */
	Stack<T>& operator=(Stack<T>&& stack);
	
	/**
	 *	\brief Whether two stacks are equal
	 *	
	 *	Two stacks are equal if they have the same elements in the same order.
	 *	\param stack The stack to compare.
	 *	\return `true` if two stacks are equal, `false` otherwise.
	 */
	bool operator==(const Stack<T>& stack) const;
	
	/**
	 *	\brief Whether two stacks are not equal
	 *	
	 *	Two stacks are equal if they have the same elements in the same order.
	 *	\param stack The stack to compare.
	 *	\return `true` if two stacks are not equal, `false` otherwise.
	 */
	bool operator!=(const Stack<T>& stack) const;

private:
	LinkedList<T> list;
};

		/* DEFINITIONS */

template<typename T>
Stack<T>::Stack() noexcept :
	list()
{}

template<typename T>
Stack<T>::Stack(const Stack<T>& stack) noexcept :
	list(stack.list)
{}

template<typename T>
Stack<T>::Stack(Stack<T>&& stack) noexcept :
	list(std::move(stack.list))
{}

template<typename T>
String Stack<T>::to_string() const noexcept
{
	return list.to_string();
}

template<typename T>
int Stack<T>::hash_code() const noexcept
{
	return list.hash_code();
}

template<typename T>
int Stack<T>::size() const noexcept
{
	return list.size();
}

template<typename T>
bool Stack<T>::is_empty() const noexcept
{
	return list.is_empty();
}

template<typename T>
void Stack<T>::clear() noexcept
{
	return list.clear();
}

template<typename T>
T& Stack<T>::get()
{
	return list.get_last();
}

template<typename T>
const T& Stack<T>::get() const
{
	return list.get_last();
}

template<typename T>
T Stack<T>::pop()
{
	T ret = list.get_last();
	list.remove(list.last());
	return ret;
}

template<typename T>
bool Stack<T>::push(const T& element)
{
	return list.add(element);
}

template<typename T>
bool Stack<T>::push(T&& element)
{
	return list.add(std::forward<T>(element));
}

template<typename T>
int Stack<T>::remove_all(const T& element)
{
	return list.remove_all(element);
}

template<typename T>
bool Stack<T>::contains(const T& element) const
{
	return list.contains(element);
}

template<typename T>
int Stack<T>::count(const T& element) const
{
	return list.count(element);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& stack)
{
	list = stack.list;
	return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& stack)
{
	list = std::move(stack.list);
	return *this;
}

template<typename T>
bool Stack<T>::operator==(const Stack<T>& stack) const
{
	return list == stack.list;
}

template<typename T>
bool Stack<T>::operator!=(const Stack<T>& stack) const
{
	return list != stack.list;
}

}
