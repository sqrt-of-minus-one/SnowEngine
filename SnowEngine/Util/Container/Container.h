    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Container.h                 //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\brief The file with IContainer and IIterator interfaces
 *	
 *	This file contains the definitions of IContainer and IIterator interfaces.
*/

namespace snow
{

/**
 *	\brief The interface that is implemented by SnowEngine containers' iterators
 *	
 *	Any of SnowEngine iterators implements this interface.
 *	\tparam T_Container Type of the iterator's container.
 *	\tparam T_Element Type of elements in the iterator's container.
*/

template<typename T_Container, typename T_Element>
class IIterator
{
public:

	/**
	 *	\brief Whether the iterator is valid
	 *	
	 *	The iterator may be invalid if its container has been destroyed.
	 *	\return `true` if the iterator is valid, `false` otherwise.
	*/
	virtual bool is_valid() const noexcept = 0;

	/**
	 *	\brief Whether the iterator points to a valid element
	 *	
	 *	This function returns `false` if the iterator is not valid or points to the end of the
	 *	container (i. e. after the last container element).
	 *	\return `true` if the iterator points to a valid element, `false` otherwise.
	 */
	virtual bool is_element_valid() const noexcept = 0;

	/**
	 *	\brief The container of the iterator
	 *	
	 *	Allows to get the container that has the element that the iterator points to.
	 *	\return The container of the iterator.
	 */
	virtual T_Container& get_container() const = 0;

	/**
	 *	\brief Get the element that the iterator points to
	 *	
	 *	Allows to get the element that the iterator points to.
	 *	\return The element that the iterator points to.
	 */
	virtual T_Element& get() const = 0;

	/**
	 *	\brief Whether the iterator points to the first element of the container
	 *	
	 *	The iterator is begin if it points to the first element.
	 *	\return `true` if the iterator points to the first element of the container.
	 */
	virtual bool is_begin() const noexcept = 0;

	/**
	 *	\brief Whether the iterator points to the last element of the container
	 *
	 *	The iterator is last if it points to the last element.
	 *	\return `true` if the iterator points to the last element of the container.
	 */
	virtual bool is_last() const noexcept = 0;
	
	/**
	 *	\brief Whether the iterator points after the last element of the container
	 *
	 *	The iterator is end if it points to a space that is after the last element. In this case
	 *	`is_element_valid()` method returns `false`.
	 *	\return `true` if the iterator points after the last element of the container.
	 */
	virtual bool is_end() const noexcept = 0;

	/**
	 *	\brief Moves the iterator forward
	 *	
	 *	Changes the iterator so that it points to the next element. The iterator won't be changed
	 *	if it already points after the last element.
	 *	\return `true` if the new element of the iterator is valid (is not end), `false` otherwise.
	 */
	virtual bool next() = 0;

	/**
	 *	\brief Moves the iterator backward
	 *	
	 *	Changes the iterator so that it points to the previous element. The iterator won't be
	 *	changed if it already points to the first element.
	 *	\return `true` if the iterator was moved, `false` otherwise.
	 */
	virtual bool prev() = 0;

	/**
	 *	\brief Get the element that the iterator points to
	 *	
	 *	This operator is equal to the `get()` method.
	 *	\return The element that the iterator points to.
	 */
	virtual T_Element& operator*() const = 0;

	/**
	 *	\brief Get access to the element that the iterator points to
	 *	
	 *	This operator allows to get access to members of the element that the iterator points to.
	 *	\return The pointer to the iterator element.
	 */
	virtual T_Element* operator->() const = 0;
};

/**
 *	\brief The interface of all of the SnowEngine containers
 *	
 *	All of the SnowEngine containers implement this interface.
 *	\tparam T Type of elements being in the container.
 */
template<typename T>
class IContainer
{
public:
	
	/**
	 *	\brief The size of the container
	 *	
	 *	Allows to get the number of elements in the container.
	 *	\return The number of elements in the container.
	 */
	virtual int size() const noexcept = 0;

	/**
	 *	\brief Whether the container is empty
	 *	
	 *	Checks whether the container is empty.
	 *	\return `true` if the container does not contain any element, `false` otherwise.
	 */
	virtual bool is_empty() const noexcept = 0;

	/**
	 *	\brief Clears the container
	 *	
	 *	Removes all of the elements in the container.
	 */
	virtual void clear() noexcept = 0;

	/**
	 *	\brief Removes all the occurrences of the passed element
	 *	
	 *	Removes all of the elements that are equal to the passed one.
	 *	\param element The element to compare.
	 *	\return Number of removed elements.
	 */
	virtual int remove_all(const T& element) = 0;

	/**
	 *	\brief Checks whether the container contains the passed element
	 *	
	 *	Looks up the container. If it contains the passed element, returns `true`.
	 *	\param element The desired element.
	 *	\return `true` if the container contains the passed element, `false` otherwise.
	 */
	virtual bool contains(const T& element) const = 0;

	/**
	 *	\brief Counts elements of the container that are equal to the passed one
	 *	
	 *	\param element The element to compare.
	 *	\return The number of occurrences.
	 */
	virtual int count(const T& element) const = 0;
};

}
