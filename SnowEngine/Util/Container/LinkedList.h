    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: LinkedList.h                //
////////////////////////////////////////

#pragma once

/**
 *	\brief The file of linked list.
 *	
 *	This file contains the definition of the LinkedList class.
 */

#include "LinkedListIterator.h"

namespace snow
{

template<typename T>
class LinkedList;

namespace
{

template<typename T>
struct LinkedListNode_
{
public:
	LinkedListNode_(const LinkedListNode_<T>&) noexcept = default;
	LinkedListNode_(LinkedListNode_<T>&&) noexcept = default;
	LinkedListNode_(const T& val) noexcept;
	LinkedListNode_(T&& val) noexcept;

	T value;
	std::weak_ptr<LinkedListNode_<T>> prev;
	std::shared_ptr<LinkedListNode_<T>> next;
};

}

/**
 *	\brief The SnowEngine linked list
 *	
 *	This class is used as linked list. You should use it if you don't need a fast access to an
 *	arbitrary element. The linked list can also quickly insert and remove elements anywhere.
 *	Linked lists take up more space than arrays. This class has methods that allow to work with the
 *	list using indexes of elements, but they can be significantly slower than those that use
 *	iterators.
 *	\tparam T Type of the linked list elements. If you need to store objects of some class in the
 *	linked list, it is highly recommended to store pointers to them. If `T` is not a pointer, it
 *	must have default constructor, copy constructor, assignment operator (`=`) and equality
 *	operator (`==`). Also it must have `to_string()` and `hash_code()` methods (any `snow::Object`
 *	has them) or be a primitive type. The default and copy constructors are assumed not to throw
 *	any exceptions.
 */
template<typename T>
class LinkedList :
	public Object,
	public IContainer<T>
{
	template<typename T_Container, typename T_Element, typename T_Node>
	friend class BaseLinkedListIterator_;

public:

	/**
	 *	\brief Create an empty linked list
	 *
	 *	The default constructor creates an empty linked list.
	 */
	LinkedList() noexcept;

	/**
	 *	\brief Copy constructor
	 *
	 *	Creates a new linked list as a copy of the passed one.
	 *	\param linked_list The linked list to copy.
	 */
	LinkedList(const LinkedList<T>& linked_list) noexcept;

	/**
	 *	\brief Move constructor
	 *
	 *	Moves elements to a new linked list from the passed one.
	 *	\param linked_list The linked list whose elements will be moved.
	 */
	LinkedList(LinkedList<T>&& linked_list) noexcept;

	/**
	 *	\brief The destructor
	 *
	 *	The destructor is used to invalidate all iterators.
	 */
	~LinkedList() noexcept;

	/**
	 *	\brief Converts the linked list content to string
	 *
	 *	Creates a string representing the list of the container elements. `util::to_string()` is
	 *	used to convert elements to string.
	 *	\return A result string in the format `"{ x, x, ..., x }"`. `"{ }"` if the list is empty.
	 */
	virtual String to_string() const noexcept override;

	/**
	 *	\brief Hash code of the linked list
	 *
	 *	Hash code is calculated using `util::hash_code()` function and formula:
	 *	\f[
	 *		\sum^{n}_{i = 0} ((-1)^i \cdot hash_code(a[i]))
	 *	\f]
	 *	\f$ n \f$ is the linked list size, \f$ a[i] \f$ is i-th element of the list.
	 *	\return Hash code of the linked list.
	 */
	virtual int hash_code() const noexcept override;

	/**
	 *	\brief The size of the linked list
	 *
	 *	Allows to get the number of elements in the linked list.
	 *	\return The number of elements in the linked list.
	 */
	virtual int size() const noexcept override;

	/**
	 *	\brief Whether the linked list is empty
	 *
	 *	Checks whether the linked list is empty.
	 *	\return `true` if the container does not contain any element, `false` otherwise.
	 */
	virtual bool is_empty() const noexcept override;

	/**
	 *	\brief Clears the linked list
	 *
	 *	Removes all of the elements in the container and sets all of its iterators to the end.
	 */
	virtual void clear() noexcept override;

	/**
	 *	\brief Get the first element
	 *	
	 *	Allows to access the first element of the linked list. `list.get_begin()` works faster than
	 *	`list[0]` or `list.begin().get()`.
	 *	\return The reference to the first element of the linked list.
	 */
	T& get_begin();

	/**
	 *	\brief Get the last element
	 *
	 *	Allows to access the last element of the linked list. `list.get_last()` works faster than
	 *	`list[list.size() - 1]` or `list.last().get()`.
	 *	\return The reference to the first element of the linked list.
	 */
	T& get_last();

	/**
	 *	\brief Get the first element
	 *
	 *	Allows to read the first element of the linked list. `list.get_begin()` works faster than
	 *	`list[0]` or `list.begin().get()`.
	 *	\return The reference to the first element of the linked list.
	 */
	const T& get_begin() const;

	/**
	 *	\brief Get the last element
	 *
	 *	Allows to read the last element of the linked list. `list.get_last()` works faster than
	 *	`list[list.size() - 1]` or `list.last().get()`.
	 *	\return The reference to the first element of the linked list.
	 */
	const T& get_last() const;

	/**
	 *	\brief Add a new element
	 *
	 *	Inserts a new element into the end of the linked list. If there are iterators that points
	 *	to the end (`is_end()` is true), they will continue to be end after executing this method.
	 *	\param element The element that will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 */
	virtual bool add(const T& element);

	/**
	 *	\brief Add a new element
	 *
	 *	Inserts a new element into the end of the linked list. If there are iterators that points
	 *	to the end (`is_end()` is true), they will continue to be end after executing this method.
	 *	\param element The element that will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 */
	virtual bool add(T&& element);

	/**
	 *	\brief Add a new element with the passed index
	 *
	 *	Inserts a new element into the linked list. The new element will be added before an element
	 *	with the passed index (i. e. it will have this index). It is faster to put the element
	 *	using an iterator if you have one.
	 *	\param element The element that will be added.
	 *	\param index The index that the new element will have.
	 *	\return `true` if the element has been successfully added, `false` otherwise (i. g. if the
	 *	index is out of the linked list bounds).
	 */
	virtual bool add(const T& element, int index);

	/**
	 *	\brief Add a new element with the passed index
	 *
	 *	Inserts a new element into the linked list. The new element will be added before an element
	 *	with the passed index (i. e. it will have this index). It is faster to put the element
	 *	using an iterator if you have one.
	 *	\param element The element that will be added.
	 *	\param index The index that the new element will have.
	 *	\return `true` if the element has been successfully added, `false` otherwise (i. g. if the
	 *	index is out of the linked list bounds).
	 */
	virtual bool add(T&& element, int index);

	/**
	 *	\brief Add into the linked list copies of elements of the passed list
	 *
	 *	Inserts into the end of the linked list copies of elements of the passed list.
	 *	\param list The linked list whose elements will be added.
	 *	\return The number of elements that have been successfully added.
	 */
	virtual int add(const LinkedList<T>& list);

	/**
	 *	\brief Move into the linked list elements of the passed list
	 *
	 *	Moves into the end of the linked list elements of the passed list.
	 *	\param list The linked list whose elements will be moved.
	 *	\return The number of elements that have been successfully added.
	 */
	virtual int add(LinkedList<T>&& list);

	/**
	 *	\brief Add element before the passed one
	 *	
	 *	Inserts a new element before the one that the passed iterator points to.
	 *	\param element The element that will be added.
	 *	\param iterator The iterator pointing to an element before which the new one will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 */
	virtual bool add_before(const T& element, const LinkedListIterator<T>& iterator);

	/**
	 *	\brief Add element before the passed one
	 *
	 *	Inserts a new element before the one that the passed iterator points to.
	 *	\param element The element that will be added.
	 *	\param iterator The iterator pointing to an element before which the new one will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 */
	virtual bool add_before(T&& element, const LinkedListIterator<T>& iterator);

	/**
	 *	\brief Add element before the passed one
	 *
	 *	Inserts a new element before the one that the passed iterator points to.
	 *	\param element The element that will be added.
	 *	\param iterator The iterator pointing to an element before which the new one will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 */
	virtual bool add_before(const T& element, const ConstLinkedListIterator<T>& iterator);

	/**
	 *	\brief Add element before the passed one
	 *
	 *	Inserts a new element before the one that the passed iterator points to.
	 *	\param element The element that will be added.
	 *	\param iterator The iterator pointing to an element before which the new one will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 */
	virtual bool add_before(T&& element, const ConstLinkedListIterator<T>& iterator);

	/**
	 *	\brief Add a new element to the beginning of the linked list
	 *
	 *	Inserts a new element into the beginning of the linked list.
	 *	\param element The element that will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 */
	virtual bool add_to_begin(const T& element);

	/**
	 *	\brief Add a new element to the beginning of the linked list
	 *
	 *	Inserts a new element into the beginning of the linked list.
	 *	\param element The element that will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 */
	virtual bool add_to_begin(T&& element);

	/**
	 *	\brief Remove an element with the passed index
	 *
	 *	Removes element that has the passed index. The subsequent elements are moved and fill
	 *	a formed space. All iterators will continue to point to their elements. Iterators that
	 *	pointed to the removed element will point to the next element after executing this method.
	 *	It is fasted to do it using an iterator if you have one.
	 *	\param index The index of an element that will be removed.
	 *	\return `true` if the element has been successfully removed, `false` otherwise (i. g. if
	 *	the index is out of the linked list bounds).
	 */
	virtual bool remove(int index);

	/**
	 *	\brief Remove an element by an iterator
	 *	
	 *	Removes element that the passed iterator points to. The subsequent elements are moved and
	 *	fill a formed space. All iterators will continue to point to their elements. Iterators that
	 *	pointed to the removed element (including the passed one) will point to the next element
	 *	after executing this method.
	 *	\param element The iterator pointing to the element that will be removed.
	 *	\return `true` if the element has been successfully removed, `false` otherwise (i. g. if
	 *	the iterator is not valid).
	 */
	virtual bool remove(const LinkedListIterator<T>& element);

	/**
	 *	\brief Remove an element by an iterator
	 *
	 *	Removes element that the passed iterator points to. The subsequent elements are moved and
	 *	fill a formed space. All iterators will continue to point to their elements. Iterators that
	 *	pointed to the removed element (including the passed one) will point to the next element
	 *	after executing this method.
	 *	\param element The iterator pointing to the element that will be removed.
	 *	\return `true` if the element has been successfully removed, `false` otherwise (i. g. if
	 *	the iterator is not valid).
	 */
	virtual bool remove(const ConstLinkedListIterator<T>& element);

	/**
	 *	\brief Remove elements in the passed range
	 *
	 *	Removes elements that are in the passed range. The subsequent elements are moved and fill a
	 *	formed space. All iterators will continue to point to their elements. Iterators that
	 *	pointed to the removed elements will point to the next element after executing this method.
	 *	It is faster to do this using iterators if you have them.
	 *	\param from The beginning of range that will be removed.
	 *	\param to The index of an element after the last element in the range that will be removed.
	 *	This element won't be removed.
	 *	\return The number of elements that have been successfully removed.
	 */
	virtual int remove(int from, int to);

	/**
	 *	\brief Remove elements in the passed range
	 *
	 *	Removes elements that are in the passed range. The subsequent elements are moved and fill a
	 *	formed space. All iterators will continue to point to their elements. Iterators that
	 *	pointed to the removed elements will point to the next element after executing this method.
	 *	\param from The iterator pointing to the first element that will be removed.
	 *	\param to The iterator pointing after the last element that will be removed. This element
	 *	won't be removed.
	 *	\return The number of elements that have been successfully removed.
	 */
	virtual int remove(const LinkedListIterator<T>& from, const LinkedListIterator<T>& to);

	/**
	 *	\brief Remove elements in the passed range
	 *
	 *	Removes elements that are in the passed range. The subsequent elements are moved and fill a
	 *	formed space. All iterators will continue to point to their elements. Iterators that
	 *	pointed to the removed elements will point to the next element after executing this method.
	 *	\param from The iterator pointing to the first element that will be removed.
	 *	\param to The iterator pointing after the last element that will be removed. This element
	 *	won't be removed.
	 *	\return The number of elements that have been successfully removed.
	 */
	virtual int remove(const ConstLinkedListIterator<T>& from, const ConstLinkedListIterator<T>& to);

	/**
	 *	\brief Remove the first element that is equal to the passed one
	 *
	 *	Compares elements of the linked list with the passed one starting from the beginning and
	 *	removes the first match. All iterators will continue to point to their elements. Iterators
	 *	that pointed to the removed element will point to the next element after executing this
	 *	method.
	 *	\param element The object to compare.
	 *	\return `true` if an element has been successfully removed, `false` otherwise (i. g. if the
	 *	linked list doesn't contain the passed object).
	 */
	virtual bool remove_first(const T& element);

	/**
	 *	\brief Remove the last element that is equal to the passed one
	 *
	 *	Compares elements of the linked list with the passed one starting from the end and removes
	 *	the first match. All iterators will continue to point to their elements. Iterators that
	 *	that pointed to the removed element will point to the next element after executing this
	 *	method.
	 *	\param element The object to compare.
	 *	\return `true` if an element has been successfully removed, `false` otherwise (i. g. if the
	 *	linked list doesn't contain the passed object).
	 */
	virtual bool remove_last(const T& element);

	/**
	 *	\brief Remove all elements that are equal to the passed one
	 *
	 *	Compares all elements of the linked list with the passed one and removes all matches. All
	 *	iterators will continue to point to their elements. Iterators that pointed to the removed
	 *	elements will point to the next element after executing this method.
	 *	\param element The object to compare.
	 *	\return Number of elements that have been successfully removed.
	 */
	virtual int remove_all(const T& element) override;

	/**
	 *	\brief Find the first element that is equal to the passed one
	 *
	 *	Compares elements of the linked list with the passed one starting from the beginning. If a
	 *	match is found, returns its index. In most cases it's better to use
	 *	`find_first_by_iterator()`.
	 *	\param element The desired element.
	 *	\return An index of the first match; a negative value if no match has been found.
	 */
	virtual int find_first_by_index(const T& element) const;

	/**
	 *	\brief Find the last element that is equal to the passed one
	 *
	 *	Compares elements of the linked list with the passed one starting from the end. If a match
	 *	is found, returns its index. In most cases it's better to use `find_last_by_iterator()`.
	 *	\param element The desired element.
	 *	\return An index of the last match; a negative value if no match has been found.
	 */
	virtual int find_last_by_index(const T& element) const;

	/**
	 *	\brief Find the first element that is equal to the passed one
	 *
	 *	Compares elements of the linked list with the passed one starting from the beginning. If a
	 *	match is found, returns an iterator to the found element.
	 *	\param element The desired element.
	 *	\return The iterator to the found element or the end iterator if no match has been found.
	 */
	virtual LinkedListIterator<T> find_first_by_iterator(const T& element);

	/**
	 *	\brief Find the last element that is equal to the passed one
	 *
	 *	Compares elements of the linked list with the passed one starting from the end. If a match
	 *	is found, returns an iterator to the found element.
	 *	\param element The desired element.
	 *	\return The iterator to the found element or the end iterator if no match has been found.
	 */
	virtual LinkedListIterator<T> find_last_by_iterator(const T& element);

	/**
	 *	\brief Find the first element that is equal to the passed one
	 *
	 *	Compares elements of the linked list with the passed one starting from the beginning. If a
	 *	match is found, returns an iterator to the found element.
	 *	\param element The desired element.
	 *	\return The iterator to the found element or the end iterator if no match has been found.
	 */
	virtual ConstLinkedListIterator<T> find_first_by_iterator(const T& element) const;

	/**
	 *	\brief Find the last element that is equal to the passed one
	 *
	 *	Compares elements of the linked list with the passed one starting from the end. If a match
	 *	is found, returns an iterator to the found element.
	 *	\param element The desired element.
	 *	\return The iterator to the found element or the end iterator if no match has been found.
	 */
	virtual ConstLinkedListIterator<T> find_last_by_iterator(const T& element) const;

	/**
	 *	\brief Whether the linked list contains the passed element
	 *
	 *	Checks whether the linked list has an element that is equal to the passed one.
	 *	\param element The desired element.
	 *	\return `true` if the linked list contains the passed element, `false` otherwise.
	 */
	virtual bool contains(const T& element) const override;

	/**
	 *	\brief How many elements of the linked list are equal to the passed one
	 *
	 *	Counts elements that are equal to the passed one.
	 *	\param element The desired element.
	 *	\return Number of matches.
	 */
	virtual int count(const T& element) const override;

	/**
	 *	\brief Create an iterator to the first element
	 *
	 *	Creates an iterator that points to the first element of the linked list. If the list is
	 *	empty, the created iterator is end (`is_end()` is true).
	 *	\return The iterator to the first element of the linked list.
	 */
	LinkedListIterator<T> begin() noexcept;

	/**
	 *	\brief Create an iterator to the last element
	 *
	 *	Creates an iterator that points to the last element of the linked list. If the list is
	 *	empty, the created iterator is end (`is_end()` is true).
	 *	\return The iterator to the last element of the array.
	 */
	LinkedListIterator<T> last() noexcept;

	/**
	 *	\brief Create an iterator pointing after the last element
	 *
	 *	Creates an iterator that points to a space after the last element of the array (this
	 *	iterator is end: `is_end()` is true).
	 *	\return The iterator after the last element of the array.
	 */
	LinkedListIterator<T> end() noexcept;

	/**
	 *	\brief Create an iterator pointing to the specified element
	 *
	 *	Creates an iterator that points to an element with the passed index.
	 *	\param index The index of an element that the iterator will points to.
	 *	\return The iterator pointing to the specified element.
	 *	\throw std::out_of_range Index is out of the linked list bounds.
	 */
	LinkedListIterator<T> create_iterator(int index);

	/**
	 *	\brief Create an iterator to the first element
	 *
	 *	Creates an iterator that points to the first element of the linked list. If the list is
	 *	empty, the created iterator is end (`is_end()` is true).
	 *	\return The iterator to the first element of the linked list.
	 */
	ConstLinkedListIterator<T> begin() const noexcept;

	/**
	 *	\brief Create an iterator to the last element
	 *
	 *	Creates an iterator that points to the last element of the linked list. If the list is
	 *	empty, the created iterator is end (`is_end()` is true).
	 *	\return The iterator to the last element of the array.
	 */
	ConstLinkedListIterator<T> last() const noexcept;

	/**
	 *	\brief Create an iterator pointing after the last element
	 *
	 *	Creates an iterator that points to a space after the last element of the array (this
	 *	iterator is end: `is_end()` is true).
	 *	\return The iterator after the last element of the array.
	 */
	ConstLinkedListIterator<T> end() const noexcept;

	/**
	 *	\brief Create an iterator pointing to the specified element
	 *
	 *	Creates an iterator that points to an element with the passed index.
	 *	\param index The index of an element that the iterator will points to.
	 *	\return The iterator pointing to the specified element.
	 *	\throw std::out_of_range Index is out of the linked list bounds.
	 */
	ConstLinkedListIterator<T> create_iterator(int index) const;

	/**
	 *	\brief Copy assignment operator
	 *
	 *	Clears the linked list and assigns it the passed one. Invalidates all iterators.
	 *	\param linked_list The linked list to assign.
	 *	\return A reference to itself.
	 */
	virtual LinkedList<T>& operator=(const LinkedList<T>& linked_list);

	/**
	 *	\brief Move assignment operator
	 *
	 *	Clears the linked list and moves elements of the passed one into it. Invalidates all
	 *	iterators.
	 *	\param linked_list The linked list to move.
	 *	\return A reference to itself.
	 */
	virtual LinkedList<T>& operator=(LinkedList<T>&& linked_list);

	/**
	 *	\brief Whether two linked lists are equal
	 *
	 *	Two linked lists are equal if all of their elements are equal and have the same order.
	 *	\param linked_list The linked list to compare.
	 *	\return `true` if two linked lists are equal, `false` otherwise.
	 */
	bool operator==(const LinkedList<T>& linked_list) const;

	/**
	 *	\brief Whether two linked lists are not equal
	 *
	 *	Two linked lists are equal if all of their elements are equal and have the same order.
	 *	\param linked_list The linked list to compare.
	 *	\return `true` if two linked lists are not equal, `false` otherwise.
	 */
	bool operator!=(const LinkedList<T>& linked_list) const;

	/**
	 *	\brief Get the specifies element.
	 *
	 *	Allows to access an element with the specified index. Access to an arbitrary element of a
	 *	linked list can be slow.
	 *	\param index The index of the element.
	 *	\return A reference to the desired element.
	 *	\throw std::out_of_range Index is out of the linked list bounds.
	 */
	T& operator[](int index);

	/**
	 *	\brief Get the specifies element.
	 *
	 *	Allows to read an element with the specified index. Access to an arbitrary element of a
	 * linked list can be slow.
	 *	\param index The index of the element.
	 *	\return A reference to the desired element.
	 *	\throw std::out_of_range Index is out of the linked list bounds.
	 */
	const T& operator[](int index) const;

	/**
	 *	\brief LinkedListIterator to ConstLinkedListIterator
	 *
	 *	Converts the passed linked list iterator to constant linked list iterator that points to
	 *	the same element of the same linked list.
	 *	\param iterator The linked list iterator that will be converted.
	 *	\return A result constant linked list iterator.
	 */
	static ConstLinkedListIterator<T> iterator_to_const(const LinkedListIterator<T> iterator) noexcept;

private:
	std::shared_ptr<LinkedListNode_<T>> begin_;
	std::shared_ptr<LinkedListNode_<T>> end_;
	int size_;

	std::shared_ptr<LinkedListNode_<T>> get_last_node_() const noexcept;

	mutable std::list<LinkedListIterator<T>*> iterators_;
	mutable std::list<ConstLinkedListIterator<T>*> const_iterators_;
	void register_iterator_(LinkedListIterator<T>* iterator) noexcept;
	void unregister_iterator_(LinkedListIterator<T>* iterator) noexcept;
	void register_iterator_(ConstLinkedListIterator<T>* iterator) const noexcept;
	void unregister_iterator_(ConstLinkedListIterator<T>* iterator) const noexcept;
	void clear_iterators_() const noexcept;
};


		/* DEFINITIONS of LinkedListNode_ */

template<typename T>
LinkedListNode_<T>::LinkedListNode_(const T& val) noexcept :
	value(val),
	prev(),
	next()
{}

template<typename T>
LinkedListNode_<T>::LinkedListNode_(T&& val) noexcept :
	value(std::move(val)),
	prev(),
	next()
{}

		/* DEFINITIONS of LinkedList */

#define FOR_ITERATORS_(i, arg) \
	for (auto i : iterators_) arg \
	for (auto i : const_iterators_) arg

template<typename T>
LinkedList<T>::LinkedList() noexcept :
	begin_(nullptr),
	end_(nullptr),
	size_(0)
{}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& linked_list) noexcept :
	LinkedList()
{
	for (const T& i : linked_list)
	{
		add(i);
	}
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& linked_list) noexcept :
	begin_(std::move(linked_list.begin_)),
	end_(std::move(linked_list.end_)),
	size_(std::move(linked_list.size_))
{}

template<typename T>
LinkedList<T>::~LinkedList() noexcept
{
	clear_iterators_();
}

template<typename T>
String LinkedList<T>::to_string() const noexcept
{
	if (is_empty())
	{
		return L"{ }"_s;
	}
	else
	{
		String str = L"{ "_s;
		for (auto p = begin(); !p.is_last(); p.next())
		{
			str += p.to_string() + L", "_s;
		}
		return str + util::to_string(get_last()) + L" }"_s;
	}
}

template<typename T>
int LinkedList<T>::hash_code() const noexcept
{
	if (is_empty())
	{
		return 0;
	}
	else
	{
		int hash = 0, one = 1;
		for (const T& i : *this)
		{
			hash += one * util::hash_code(i);
			one = -one;
		}
		return hash;
	}
}

template<typename T>
int LinkedList<T>::size() const noexcept
{
	return size_;
}

template<typename T>
bool LinkedList<T>::is_empty() const noexcept
{
	return size_ == 0;
}

template<typename T>
void LinkedList<T>::clear() noexcept
{
	begin_.reset();
	end_.reset();
	size_ = 0;

	FOR_ITERATORS_(i,
	{
		i->index_ = 0;
		i->node_.reset();
	})
}

template<typename T>
T& LinkedList<T>::get_begin()
{
	if (size_ > 0)
	{
		return begin_->value;
	}
	else
	{
		throw std::out_of_range("Attempt to access an element of empty linked list");
	}
}

template<typename T>
T& LinkedList<T>::get_last()
{
	if (size_ > 0)
	{
		return end_->value;
	}
	else
	{
		throw std::out_of_range("Attempt to access an element of empty linked list");
	}
}

template<typename T>
const T& LinkedList<T>::get_begin() const
{
	if (size_ > 0)
	{
		return begin_->value;
	}
	else
	{
		throw std::out_of_range("Attempt to access an element of empty linked list");
	}
}

template<typename T>
const T& LinkedList<T>::get_last() const
{
	if (size_ > 0)
	{
		return end_->value;
	}
	else
	{
		throw std::out_of_range("Attempt to access an element of empty linked list");
	}
}

template<typename T>
bool LinkedList<T>::add(const T& element)
{
	if (size_ == 0)
	{
		begin_.reset(new LinkedListNode_<T>(element));
		end_ = begin_;
	}
	else
	{
		end_->next.reset(new LinkedListNode_<T>(element));
		end_->next->prev = end_;
		end_ = end_->next;
	}
	
	FOR_ITERATORS_(i,
	{
		if (i->index_ >= size_)
		{
			i->index_++;
		}
	})

	size_++;
	return true;
}

template<typename T>
bool LinkedList<T>::add(T&& element)
{
	if (size_ == 0)
	{
		begin_.reset(new LinkedListNode_<T>(std::forward<T>(element)));
		end_ = begin_;
	}
	else
	{
		end_->next.reset(new LinkedListNode_<T>(std::forward<T>(element)));
		end_->next->prev = end_;
		end_ = end_->next;
	}
	
	FOR_ITERATORS_(i,
	{
		if (i->index_ >= size_)
		{
			i->index_++;
		}
	})

	size_++;
	return true;
}

template<typename T>
bool LinkedList<T>::add(const T& element, int index)
{
	if (index >= 0 && index <= size_)
	{
		return add_before(element, create_iterator(index));
	}
	else
	{
		return false;
	}
}

template<typename T>
bool LinkedList<T>::add(T&& element, int index)
{
	if (index >= 0 && index <= size_)
	{
		return add_before(std::forward<T>(element), create_iterator(index));
	}
	else
	{
		return false;
	}
}

template<typename T>
int LinkedList<T>::add(const LinkedList<T>& list)
{
	int ret = 0;
	for (const T& i : list)
	{
		ret += static_cast<int>(add(i));
	}
	return ret;
}

template<typename T>
int LinkedList<T>::add(LinkedList<T>&& list)
{
	int ret = list.size_;
	if (!list.is_empty())
	{
		end_->next = list.begin_;
		list.begin_->prev = end_;
		end_ = list.end_;

		FOR_ITERATORS_(i,
		{
			if (i->index_ >= size_)
			{
				i->index_ += ret;
			}
		})

		size_ += list.size_;
	}
	return ret;
}

template<typename T>
bool LinkedList<T>::add_before(const T& element, const LinkedListIterator<T>& iterator)
{
	return add_before(element, iterator_to_const(iterator));
}

template<typename T>
bool LinkedList<T>::add_before(T&& element, const LinkedListIterator<T>& iterator)
{
	return add_before(std::forward<T>(element), iterator_to_const(iterator));
}

template<typename T>
bool LinkedList<T>::add_before(const T& element, const ConstLinkedListIterator<T>& iterator)
{
	if (iterator.is_valid() && &iterator.get_container() == this)
	{
		if (iterator.is_end())
		{
			return add(element);
		}
		else
		{
			std::shared_ptr<LinkedListNode_<T>> node = iterator.node_.lock();
			std::shared_ptr<LinkedListNode_<T>> new_node = std::make_shared<LinkedListNode_<T>>(element);
			new_node->next = node;
			new_node->prev = node->prev;
			node->prev = new_node;
			if (new_node->prev.lock())
			{
				new_node->prev.lock()->next = new_node;
			}
			size_++;

			int index = iterator.index_;
			FOR_ITERATORS_(i,
			{
				if (i->index_ >= index)
				{
					i->index_++;
				}
			})

			return true;
		}
	}
	else
	{
		return false;
	}
}

template<typename T>
bool LinkedList<T>::add_before(T&& element, const ConstLinkedListIterator<T>& iterator)
{
	if (iterator.is_valid() && &iterator.get_container() == this)
	{
		if (iterator.is_end())
		{
			return add(element);
		}
		else
		{
			std::shared_ptr<LinkedListNode_<T>> node = iterator.node_.lock();
			std::shared_ptr<LinkedListNode_<T>> new_node = std::make_shared<LinkedListNode_<T>>(std::forward<T>(element));
			new_node->next = node;
			new_node->prev = node->prev;
			node->prev = new_node;
			if (new_node->prev.lock())
			{
				new_node->prev.lock()->next = new_node;
			}
			size_++;

			int index = iterator.index_;
			FOR_ITERATORS_(i,
			{
				if (i->index_ >= index)
				{
					i->index_++;
				}
			})

			return true;
		}
	}
	else
	{
		return false;
	}
}

template<typename T>
bool LinkedList<T>::add_to_begin(const T& element)
{
	std::shared_ptr<LinkedListNode_<T>> new_node = std::make_shared<LinkedListNode_<T>>(element);
	new_node->next = begin_;
	begin_->prev = new_node;
	begin_ = new_node;
	size_++;

	FOR_ITERATORS_(i,
	{
		i->index_++;
	})

	return true;
}

template<typename T>
bool LinkedList<T>::add_to_begin(T&& element)
{
	std::shared_ptr<LinkedListNode_<T>> new_node = std::make_shared<LinkedListNode_<T>>(std::move(element));
	new_node->next = begin_;
	begin_->prev = new_node;
	begin_ = new_node;
	size_++;

	FOR_ITERATORS_(i,
	{
		i->index_++;
	})

	return true;
}

template<typename T>
bool LinkedList<T>::remove(int index)
{
	return remove(create_iterator(index));
}

template<typename T>
bool LinkedList<T>::remove(const LinkedListIterator<T>& element)
{
	return remove(iterator_to_const(element));
}

template<typename T>
bool LinkedList<T>::remove(const ConstLinkedListIterator<T>& element)
{
	if (element.is_element_valid() && &element.get_container() == this)
	{
		int index = element.index_;

		std::shared_ptr<LinkedListNode_<T>> node = element.node_.lock();
		if (!element.is_begin())
		{
			node->prev.lock()->next = node->next;
		}
		else
		{
			begin_ = node->next;
		}

		if (!element.is_last())
		{
			node->next->prev = node->prev;
		}
		else
		{
			end_ = node->prev.lock();
		}
		size_--;

		FOR_ITERATORS_(i,
		{
			if (i->index_ > index)
			{
				i->index_--;
			}
		})
		
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
int LinkedList<T>::remove(int from, int to)
{
	if (from < to && from >= 0 && to <= size_)
	{
		int index = 0;
		std::shared_ptr<LinkedListNode_<T>> i = begin_;
		for ( ; index < from; i = i->next, index++);
		LinkedListIterator<T> from_itr(*this, index, i);
		for ( ; index < to; i = i->next, index++);
		LinkedListIterator<T> to_itr(*this, index, i);
		return remove(from_itr, to_itr);
	}
	else
	{
		return false;
	}
}

template<typename T>
int LinkedList<T>::remove(const LinkedListIterator<T>& from, const LinkedListIterator<T>& to)
{
	return remove(iterator_to_const(from), iterator_to_const(to));
}

template<typename T>
int LinkedList<T>::remove(const ConstLinkedListIterator<T>& from, const ConstLinkedListIterator<T>& to)
{
	if (from.is_element_valid() && to.is_valid() &&
		&from.get_container() == this && &to.get_container() == this &&
		from.get_index() < to.get_index())
	{
		int from_index = from.index_;
		int to_index = to.index_;
		std::shared_ptr<LinkedListNode_<T>> from_node = from.node_.lock();
		std::shared_ptr<LinkedListNode_<T>> to_node = to.is_end() ? end_ : to.node_.lock()->prev.lock();

		if (!from.is_begin())
		{
			from_node->prev.lock()->next = to_node->next;
		}
		else
		{
			begin_ = to_node->next;
		}
		
		if (!to.is_end())
		{
			to_node->next->prev = from_node->prev;
		}
		else
		{
			end_ = from_node->prev.lock();
		}
		
		size_ -= to_index - from_index;
		
		FOR_ITERATORS_(i,
		{
			if (i->index_ > from_index && i->index_ < to_index)
			{
				i->index_ = from_index;
			}
			else if (i->index_ >= to_index)
			{
				i->index_ -= to_index - from_index;
			}
		})
		
		return to_index - from_index;
	}
	else
	{
		return false;
	}
}

template<typename T>
bool LinkedList<T>::remove_first(const T& element)
{
	return remove(find_first_by_iterator(element));
}

template<typename T>
bool LinkedList<T>::remove_last(const T& element)
{
	return remove(find_last_by_iterator(element));
}

template<typename T>
int LinkedList<T>::remove_all(const T& element)
{
	if (!is_empty())
	{
		int ret = 0;
		while (get_begin() == element)
		{
			ret += static_cast<int>(remove(begin()));
		}
		auto i = begin();
		while (i.next())
		{
			if (i.get() == element)
			{
				ret += static_cast<int>(remove(i--));
			}
		}
		return ret;
	}
	else
	{
		return 0;
	}
}

template<typename T>
int LinkedList<T>::find_first_by_index(const T& element) const
{
	int index = 0;
	for (std::shared_ptr<LinkedListNode_<T>> i = begin_; i; i = i->next, index++)
	{
		if (i->value == element)
		{
			return index;
		}
	}
	return -1;
}

template<typename T>
int LinkedList<T>::find_last_by_index(const T& element) const
{
	int index = size_ - 1;
	for (std::shared_ptr<LinkedListNode_<T>> i = end_; i; i = i->prev.lock(), index--)
	{
		if (i->value == element)
		{
			return index;
		}
	}
	return -1;
}

template<typename T>
LinkedListIterator<T> LinkedList<T>::find_first_by_iterator(const T& element)
{
	int index = 0;
	for (std::shared_ptr<LinkedListNode_<T>> i = begin_; i; i = i->next, index++)
	{
		if (i->value == element)
		{
			return LinkedListIterator<T>(*this, index, i);
		}
	}
	return end();
}

template<typename T>
LinkedListIterator<T> LinkedList<T>::find_last_by_iterator(const T& element)
{
	int index = size_ - 1;
	for (std::shared_ptr<LinkedListNode_<T>> i = end_; i; i = i->prev.lock(), index--)
	{
		if (i->value == element)
		{
			return LinkedListIterator<T>(*this, index, i);
		}
	}
	return end();
}

template<typename T>
ConstLinkedListIterator<T> LinkedList<T>::find_first_by_iterator(const T& element) const
{
	int index = 0;
	for (std::shared_ptr<LinkedListNode_<T>> i = begin_; i; i = i->next, index++)
	{
		if (i->value == element)
		{
			return ConstLinkedListIterator<T>(*this, index, i);
		}
	}
	return end();
}

template<typename T>
ConstLinkedListIterator<T> LinkedList<T>::find_last_by_iterator(const T& element) const
{
	int index = size_ - 1;
	for (std::shared_ptr<LinkedListNode_<T>> i = end_; i; i = i->prev.lock(), index--)
	{
		if (i->value == element)
		{
			return ConstLinkedListIterator<T>(*this, index, i);
		}
	}
	return end();
}

template<typename T>
bool LinkedList<T>::contains(const T& element) const
{
	for (std::shared_ptr<LinkedListNode_<T>> i = begin_; i; i = i->next)
	{
		if (i->value == element)
		{
			return true;
		}
	}
	return false;
}

template<typename T>
int LinkedList<T>::count(const T& element) const
{
	int result = 0;
	for (std::shared_ptr<LinkedListNode_<T>> i = begin_; i; i = i->next)
	{
		if (i->value == element)
		{
			result++;
		}
	}
	return result;
}

template<typename T>
LinkedListIterator<T> LinkedList<T>::begin() noexcept
{
	return LinkedListIterator<T>(*this, 0, begin_);
}

template<typename T>
LinkedListIterator<T> LinkedList<T>::last() noexcept
{
	return LinkedListIterator<T>(*this, size_ - 1, end_);
}

template<typename T>
LinkedListIterator<T> LinkedList<T>::end() noexcept
{
	return LinkedListIterator<T>(*this, size_);
}

template<typename T>
LinkedListIterator<T> LinkedList<T>::create_iterator(int index)
{
	if (index >= 0 && index <= size_)
	{
		if (index < size_ / 2)
		{
			auto ret = begin();
			for (int i = 0; i < index; i++)
			{
				ret.next();
			}
			return ret;
		}
		else
		{
			auto ret = last();
			for (int i = size_ - 1; i > index; i--)
			{
				ret.prev();
			}
			return ret;
		}
	}
	else
	{
		throw std::out_of_range("Index is out of linked list bounds");
	}
}

template<typename T>
ConstLinkedListIterator<T> LinkedList<T>::begin() const noexcept
{
	return ConstLinkedListIterator<T>(*this, 0, begin_);
}

template<typename T>
ConstLinkedListIterator<T> LinkedList<T>::last() const noexcept
{
	return ConstLinkedListIterator<T>(*this, size_ - 1, end_);
}

template<typename T>
ConstLinkedListIterator<T> LinkedList<T>::end() const noexcept
{
	return ConstLinkedListIterator<T>(*this, size_);
}

template<typename T>
ConstLinkedListIterator<T> LinkedList<T>::create_iterator(int index) const
{
	if (index >= 0 && index <= size_)
	{
		if (index < size_ / 2)
		{
			auto ret = begin();
			for (int i = 0; i < index; i++)
			{
				ret.next();
			}
			return ret;
		}
		else
		{
			auto ret = last();
			for (int i = size_ - 1; i > index; i--)
			{
				ret.prev();
			}
			return ret;
		}
	}
	else
	{
		throw std::out_of_range("Index is out of linked list bounds");
	}
}


template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& linked_list)
{
	clear();
	for (const T& i : linked_list)
	{
		add(i);
	}
	return *this;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& linked_list)
{
	clear_iterators_();
	begin_ = std::move(linked_list.begin_);
	end_ = std::move(linked_list.end_);
	size_ = std::move(linked_list.size_);
	return *this;
}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& linked_list) const
{
	if (size_ == linked_list.size_)
	{
		auto this_iter = begin();
		auto other_iter = linked_list.begin();
		do 
		{
			if (!(this_iter.get() == other_iter.get()))
			{
				return false;
			}
		} while (this_iter.next() && other_iter.next());
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
bool LinkedList<T>::operator!=(const LinkedList<T>& linked_list) const
{
	return !(*this == linked_list);
}

template<typename T>
T& LinkedList<T>::operator[](int index)
{
	if (index >= 0 && index < size_)
	{
		return create_iterator(index).get();
	}
	else
	{
		throw std::out_of_range("Index is out of linked list bounds");
	}
}

template<typename T>
const T& LinkedList<T>::operator[](int index) const
{
	if (index >= 0 && index < size_)
	{
		return create_iterator(index).get();
	}
	else
	{
		throw std::out_of_range("Index is out of linked list bounds");
	}
}

template<typename T>
ConstLinkedListIterator<T> LinkedList<T>::iterator_to_const(const LinkedListIterator<T> iterator) noexcept
{
	return ConstLinkedListIterator<T>(iterator.container_, iterator.index_, iterator.node_.lock(), iterator.is_valid_);
}

template<typename T>
std::shared_ptr<LinkedListNode_<T>> LinkedList<T>::get_last_node_() const noexcept
{
	return end_;
}

template<typename T>
void LinkedList<T>::register_iterator_(LinkedListIterator<T>* iterator) noexcept
{
	iterators_.push_back(iterator);
}

template<typename T>
void LinkedList<T>::unregister_iterator_(LinkedListIterator<T>* iterator) noexcept
{
	auto end = iterators_.end();
	for (auto ptr = iterators_.begin(); ptr != end; ptr++)
	{
		if (*ptr == iterator)
		{
			iterators_.erase(ptr);
			break;
		}
	}
}

template<typename T>
void LinkedList<T>::register_iterator_(ConstLinkedListIterator<T>* iterator) const noexcept
{
	const_iterators_.push_back(iterator);
}

template<typename T>
void LinkedList<T>::unregister_iterator_(ConstLinkedListIterator<T>* iterator) const noexcept
{
	auto end = const_iterators_.end();
	for (auto ptr = const_iterators_.begin(); ptr != end; ptr++)
	{
		if (*ptr == iterator)
		{
			const_iterators_.erase(ptr);
			break;
		}
	}
}

template<typename T>
void LinkedList<T>::clear_iterators_() const noexcept
{
	FOR_ITERATORS_(i,
	{
		i->is_valid_ = false;
	})
	iterators_.clear();
	const_iterators_.clear();
}

#undef FOR_ITERATORS_

}
