    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Array.h                     //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\brief The file of array class
 *	
 *	This file contains the definition of the Array class.
 */

#include <list>

#include "ArrayIterator.h"
#include "LinkedList.h"
#include "../../Math/Math.h"

namespace snow
{

/**
 *	\brief The SnowEngine array
 *	
 *	This class is used as the array. It should be used if you need to have a fast access to its
 *	elements. Increasing the size of the array, inserting or removing elements in its middle or
 *	beginning is slow and should be avoided. If you need to insert or remove elements in the middle
 *	or beginning, the LinkedList container may be more suitable for you.
 *	\tparam T Type of the array elements. If you need to store objects of some class in the array,
 *	it is highly recommended to store pointers to them. If `T` is not a pointer, it must have
 *	default constructor, assignment operator (`=`) and equality operator (`==`). Also it must have
 *	`to_string()` and `hash_code()` methods (any `snow::Object` has them) or be a primitive type.
 *	The default and copy constructors are assumed not to throw any exceptions.
 */
template<typename T>
class Array :
	public Object,
	public IContainer<T>
{
	template<typename T_Container, typename T_Element>
	friend class BaseArrayIterator_;

public:
	
	/**
	 *	\brief Create an empty array
	 *	
	 *	The default constructor creates an empty array.
	 */
	Array() noexcept;

	/**
	 *	\brief Copy constructor
	 *	
	 *	Creates a new array as a copy of the passed one.
	 *	\param array The array to copy.
	 */
	Array(const Array<T>& array) noexcept;

	/**
	 *	\brief Move constructor
	 *	
	 *	Moves elements to a new array from the passed one.
	 *	\param array The array whose elements will be moved.
	 */
	Array(Array<T>&& array) noexcept;

	/**
	 *	\brief Create an array of the passed size
	 *	
	 *	Creates an array of the passed size and fills it with default elements. If the array
	 *	stores pointers, `nullptr`s will be added. Otherwise inserted elements will be created
	 *	using a default constructor.
	 *	\param size The size of the array.
	 */
	Array(int size);

	/**
	 *	\brief The destructor
	 *	
	 *	The destructor is used to invalidate all iterators.
	 */
	virtual ~Array() noexcept;

	/**
	 *	\brief Converts the array content to string
	 *	
	 *	Creates a string representing the list of the array elements. `util::to_string()` is used
	 *	to convert elements to string.
	 *	\return A result string in the format `"{ x, x, ..., x }"`. `"{ }"` if the array is empty.
	 */
	virtual const std::string to_string() const noexcept override;

	/**
	 *	\brief Hash code of the array
	 *	
	 *	Hash code is calculated using `util::hash_code()` function and formula:
	 *	\f[
	 *		\sum^{n}_{i = 0} ((-1)^i \cdot hash_code(a[i]))
	 *	\f]
	 *	\f$ n \f$ is the array size, \f$ a[i] \f$ is i-th element of the array.
	 *	\return Hash code of the array.
	 */
	virtual int hash_code() const noexcept override;

	/**
	 *	\brief The size of the array
	 *
	 *	Allows to get the number of elements in the array.
	 *	\return The number of elements in the array.
	 */
	virtual int size() const noexcept override;

	/**
	 *	\brief Whether the array is empty
	 *
	 *	Checks whether the array is empty.
	 *	\return `true` if the container does not contain any element, `false` otherwise.
	 */
	virtual bool is_empty() const noexcept override;

	/**
	 *	\brief Clears the array
	 *
	 *	Removes all of the elements in the container and sets all of its iterators to the end.
	 */
	virtual void clear() noexcept override;
	
	/**
	 *	\brief Change the array size
	 *	
	 *	Increases or decreases the array size. If a new size is more than an old one, a formed
	 *	space will be filled with default elements (`nullptr`s for pointers, default constructor
	 *	otherwise). In this case end iterators will be moved in order to continue to be end. If a
	 *	new size is less than an old one, the last elements that didn't fit in the array will be
	 *	removed. Iterators pointing to removed elements become end (`is_end()` is true).
	 *	\param new_size The new array size.
	 *	\return `true` if the array has been successfully resized, `false` otherwise (i. g. if
	 *	new size is negative).
	 */
	bool resize(int new_size) noexcept;

	/**
	 *	\brief Add a new element
	 *	
	 *	Inserts a new element into the end of the array. If there are iterators that points to the
	 *	end (`is_end()` is true), they will continue to be end after executing this method.
	 *	\param element The element that will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 */
	virtual bool add(const T& element);

	/**
	 *	\brief Add a new element
	 *
	 *	Inserts a new element into the end of the array. If there are iterators that points to the
	 *	end (`is_end()` is true), they will continue to be end after executing this method.
	 *	\param element The element that will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 */
	virtual bool add(T&& element);

	/**
	 *	\brief Add a new element with the passed index
	 *	
	 *	Inserts a new element into the array. The new element will have the passed index. Moves the
	 *	subsequent elements towards the end of the array. The iterators will also be moved and
	 *	continue to point to their elements.
	 *	\param element The element that will be added.
	 *	\param index The index that the new element will have.
	 *	\return `true` if the element has been successfully added, `false` otherwise (i. g. if the
	 *	index is out of the array bounds).
	 */
	virtual bool add(const T& element, int index);
	
	/**
	 *	\brief Add a new element with the passed index
	 *	
	 *	Inserts a new element into the array. The new element will have the passed index. Moves the
	 *	subsequent elements towards the end of the array. The iterators will also be moved and
	 *	continue to point to their elements.
	 *	\param element The element that will be added.
	 *	\param index The index that the new element will have.
	 *	\return `true` if the element has been successfully added, `false` otherwise (i. g. if the
	 *	index is out of the array bounds).
	 */
	virtual bool add(T&& element, int index);

	/**
	 *	\brief Add into the array copies of elements of the passed array
	 *	
	 *	Inserts into the end of the array copies of elements of the passed array. If there are
	 *	iterators that points to the end (`is_end()` is true), they will continue to be end after
	 *	executing this method.
	 *	\param array The array whose elements will be added.
	 *	\return The number of elements that have been successfully added.
	 */
	virtual int add(const Array<T>& array);

	/**
	 *	\brief Move into the array elements of the passed array
	 *
	 *	Moves into the end of the array elements of the passed array. If there are iterators that
	 *	points to the end (`is_end()` is true), they will continue to be end after executing this
	 *	method.
	 *	\param array The array whose elements will be moved.
	 *	\return The number of elements that have been successfully added.
	 */
	virtual int add(Array<T>&& array);

	/**
	 *	\brief Remove an element with the passed index
	 *	
	 *	Removes element that has the passed index. The subsequent elements are moved and fill
	 *	a formed space. All iterators will continue to point to their elements. Iterators that
	 *	pointed to the removed element will point to the next element after executing this method.
	 *	\param index The index of an element that will be removed.
	 *	\return `true` if the element has been successfully removed, `false` otherwise (i. g. if
	 *	the index is out of the array bounds).
	 */
	bool remove(int index);

	/**
	 *	\brief Remove an element by iterator
	 *	
	 *	Removes an element that the iterator points to. The subsequent elements are moved and fill
	 *	a formed space. All iterators will continue to point to their elements. Iterators that
	 *	pointed to the removed element will point to the next element after executing this method.
	 *	\param element The iterator pointing to the element that will be removed.
	 *	\return `true` if the element has been successfully removed, `false` otherwise (i. g. if
	 *	the iterator points to the element of other array).
	 */
	bool remove(const ArrayIterator<T>& element);

	/**
	 *	\brief Remove an element by iterator
	 *	
	 *	Removes an element that the iterator points to. The subsequent elements are moved and fill
	 *	a formed space. All iterators will continue to point to their elements. Iterators that
	 *	pointed to the removed element will point to the next element after executing this method.
	 *	\param element The iterator pointing to the element that will be removed.
	 *	\return `true` if the element has been successfully removed, `false` otherwise (i. g. if
	 *	the iterator points to the element of other array).
	 */
	bool remove(const ConstArrayIterator<T>& element);

	/**
	 *	\brief Remove elements in the passed range
	 *	
	 *	Removes elements that are in the passed range. The subsequent elements are moved and fill a
	 *	formed space. All iterators will continue to point to their elements. Iterators that
	 *	pointed to the removed elements will point to the next element after executing this method.
	 *	\param from The beginning of range that will be removed.
	 *	\param to The index of an element after the last element in the range that will be removed.
	 *	This element won't be removed.
	 *	\return The number of elements that have been successfully removed.
	 */
	int remove(int from, int to);

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
	int remove(const ArrayIterator<T>& from, const ArrayIterator<T>& to);

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
	int remove(const ConstArrayIterator<T>& from, const ConstArrayIterator<T>& to);

	/**
	 *	\brief Remove any element that is equal to the passed one
	 *
	 *	Compares elements of the array with the passed one and removes any match. All iterators
	 *	will continue to point to their elements. Iterators that pointed to the removed element
	 *	will point to the next element after executing this method.
	 *	\param element The object to compare.
	 *	\return `true` if an element has been successfully removed, `false` otherwise (i. g. if the
	 *	array doesn't contain the passed object).
	 */
	bool remove_any(const T& element);

	/**
	 *	\brief Remove the first element that is equal to the passed one
	 *	
	 *	Compares elements of the array with the passed one starting from the beginning and
	 *	removes the first match. All iterators will continue to point to their elements. Iterators
	 *	that pointed to the removed element will point to the next element after executing this
	 *	method.
	 *	\param element The object to compare.
	 *	\return `true` if an element has been successfully removed, `false` otherwise (i. g. if the
	 *	array doesn't contain the passed object).
	 */
	bool remove_first(const T& element);

	/**
	 *	\brief Remove the last element that is equal to the passed one
	 *	
	 *	Compares elements of the array with the passed one starting from the end and removes
	 *	the first match. All iterators will continue to point to their elements. Iterators that 
	 *	that pointed to the removed element will point to the next element after executing this
	 *	method.
	 *	\param element The object to compare.
	 *	\return `true` if an element has been successfully removed, `false` otherwise (i. g. if the
	 *	array doesn't contain the passed object).
	 */
	bool remove_last(const T& element);

	/**
	 *	\brief Remove all elements that are equal to the passed one
	 *	
	 *	Compares all elements of the array with the passed one and removes all matches. All
	 *	iterators will continue to point to their elements. Iterators that pointed to the removed
	 *	elements will point to the next element after executing this method.
	 *	\param element The object to compare.
	 *	\return Number of elements that have been successfully removed.
	 */
	virtual int remove_all(const T& element) override;

	/**
	 *	\brief Find any element that is equal to the passed one
	 *	
	 *	Compares elements of the array with the passed one. If any match is found, returns its
	 *	index.
	 *	\param element The desired element.
	 *	\return An index of a match; a negative value if no match has been found.
	 */
	virtual int find_any(const T& element) const;

	/**
	 *	\brief Find the first element that is equal to the passed one
	 *	
	 *	Compares elements of the array with the passed one starting from the beginning. If a match
	 *	is found, returns its index.
	 *	\param element The desired element.
	 *	\return An index of the first match; a negative value if no match has been found.
	 */
	virtual int find_first(const T& element) const;

	/**
	 *	\brief Find the last element that is equal to the passed one
	 *	
	 *	Compares elements of the array with the passed one starting from the end. If a match is
	 *	found, returns its index.
	 *	\param element The desired element.
	 *	\return An index of the last match; a negative value if no match has been found.
	 */
	virtual int find_last(const T& element) const;

	/**
	 *	\brief Find all elements that are equal to the passed one
	 *	
	 *	Compares all elements of the array with the passed one. Returns indexes of all found
	 *	matches.
	 *	\param element The desired element.
	 *	\return A linked list with indexes of all found matches. If no match is found, the list is
	 *	empty.
	 */
	virtual LinkedList<int> find_all(const T& element) const;

	/**
	 *	\brief Whether the array contains the passed element
	 *
	 *	Checks whether the array has an element that is equal to the passed one.
	 *	\param element The desired element.
	 *	\return `true` if the array contains the passed element, `false` otherwise.
	 */
	virtual bool contains(const T& element) const override;

	/**
	 *	\brief How many elements of the array are equal to the passed one
	 *	
	 *	Counts elements that are equal to the passed one.
	 *	\param element The desired element.
	 *	\return Number of matches.
	 */
	virtual int count(const T& element) const override;

	/**
	 *	\brief Create an iterator to the first element
	 *	
	 *	Creates an iterator that points to the first element of the array. If the array is empty,
	 *	the created iterator is end (`is_end()` is true).
	 *	\return The iterator to the first element of the array.
	 */
	ArrayIterator<T> begin() noexcept;

	/**
	 *	\brief Create an iterator to the last element
	 *
	 *	Creates an iterator that points to the last element of the array. If the array is empty,
	 *	the created iterator is end (`is_end()` is true).
	 *	\return The iterator to the last element of the array.
	 */
	ArrayIterator<T> last() noexcept;

	/**
	 *	\brief Create an iterator pointing after the last element
	 *
	 *	Creates an iterator that points to a space after the last element of the array (this
	 *	iterator is end: `is_end()` is true).
	 *	\return The iterator after the last element of the array.
	 */
	ArrayIterator<T> end() noexcept;

	/**
	 *	\brief Create an iterator pointing to the specified element
	 *	
	 *	Creates an iterator that points to an element with the passed index.
	 *	\param index The index of an element that the iterator will points to.
	 *	\return The iterator pointing to the specified element.
	 *	\throw std::out_of_range Index is out of the array bounds.
	 */
	ArrayIterator<T> create_iterator(int index);

	/**
	 *	\brief Create a constant iterator to the first element
	 *	
	 *	Creates a constant iterator that points to the first element of the array. If the array is
	 *	empty, the created iterator is also end (`is_end()` is true).
	 *	\return Th constant iterator to the first element of the array.
	 */
	ConstArrayIterator<T> begin() const noexcept;

	/**
	 *	\brief Create a constant iterator to the last element
	 *
	 *	Creates a constant iterator that points to the last element of the array.
	 *	\return The constant iterator to the last element of the array.
	 */
	ConstArrayIterator<T> end() const noexcept;

	/**
	 *	\brief Create a constant iterator pointing after the last element
	 *
	 *	Creates a constant iterator that points to a space after the last element of the array
	 *	(this iterator is end: `is_end()` is true).
	 *	\return The constant iterator after the last element of the array.
	 */
	ConstArrayIterator<T> last() const noexcept;

	/**
	 *	\brief Create a constant iterator pointing to the specified element
	 *	
	 *	Creates a constant iterator that points to an element with the passed index.
	 *	\param index The index of an element that the iterator will points to.
	 *	\return The constant iterator pointing to the specified element.
	 *	\throw std::out_of_range Index is out of the array bounds.
	 */
	ConstArrayIterator<T> create_iterator(int index) const;

	/**
	 *	\brief Copy assignment operator
	 *	
	 *	Clears the array and assigns it the passed one. Invalidates all iterators.
	 *	\param array The array to assign.
	 *	\return A reference to itself.
	 */
	virtual Array<T>& operator=(const Array<T>& array);

	/**
	 *	\brief Move assignment operator
	 *	
	 *	Clears the array and moves elements of the passed one into it. Invalidates all iterators.
	 *	\param array The array to move.
	 *	\return A reference to itself.
	 */
	virtual Array<T>& operator=(Array<T>&& array);

	/**
	 *	\brief Whether two arrays are equal
	 *	
	 *	Two arrays are equal if all of their elements are equal and have the same order.
	 *	\param array The array to compare.
	 *	\return `true` if two arrays are equal, `false` otherwise.
	 */
	bool operator==(const Array<T>& array) const;

	/**
	 *	\brief Whether two arrays are not equal
	 *
	 *	Two arrays are equal if all of their elements are equal and have the same order.
	 *	\param array The array to compare.
	 *	\return `true` if two arrays are not equal, `false` otherwise.
	 */
	bool operator!=(const Array<T>& array) const;

	/**
	 *	\brief Get the specifies element.
	 *	
	 *	Allows to access an element with the specified index.
	 *	\param index The index of the element.
	 *	\return A reference to the desired element.
	 *	\throw std::out_of_range Index is out of the array bounds.
	 */
	T& operator[](int index);

	/**
	 *	\brief Get the specifies element.
	 *	
	 *	Allows to read an element with the specified index.
	 *	\param index The index of the element.
	 *	\return A reference to the desired element.
	 *	\throw std::out_of_range Index is out of the array bounds.
	 */
	const T& operator[](int index) const;

	/**
	 *	\brief ArrayIterator to ConstArrayIterator
	 *	
	 *	Converts the passed array iterator to constant array iterator that points to the same
	 *	element of the same array.
	 *	\param iterator The array iterator that will be converted.
	 *	\return A result constant array iterator.
	 */
	static ConstArrayIterator<T> iterator_to_const(const ArrayIterator<T>& iterator) noexcept;

private:
	int real_size_;
	int size_;
	std::unique_ptr<T[]> array_;

	bool add_to_end_(const T& element);
	bool add_to_end_(T&& element);
	void check_real_size_to_add_(int required_size);

	mutable std::list<ArrayIterator<T>*> iterators_;
	mutable std::list<ConstArrayIterator<T>*> const_iterators_;
	void register_iterator_(ArrayIterator<T>* iterator) noexcept;
	void unregister_iterator_(ArrayIterator<T>* iterator) noexcept;
	void register_iterator_(ConstArrayIterator<T>* iterator) const noexcept;
	void unregister_iterator_(ConstArrayIterator<T>* iterator) const noexcept;
	void clear_iterators_() const noexcept;

	static const int DEFAULT_REAL_SIZE_;
};


		/* DEFINITIONS */

#define FOR_ITERATORS_(i, arg) \
	for (auto i : iterators_) arg \
	for (auto i : const_iterators_) arg

template<typename T>
Array<T>::Array() noexcept :
	real_size_(DEFAULT_REAL_SIZE_),
	size_(0),
	array_(new T[real_size_])
{}

template<typename T>
Array<T>::Array(const Array<T>& array) noexcept :
	real_size_(array.real_size_),
	size_(array.size_),
	array_(new T[real_size_])
{
	for (int i = 0; i < size_; i++)
	{
		array_[i] = array.array_[i];
	}
}

template<typename T>
Array<T>::Array(Array<T>&& array) noexcept :
	real_size_(array.real_size_),
	size_(array.size_),
	array_(std::move(array.array_))
{
	array.clear_iterators_();
}

template<typename T>
Array<T>::Array(int size) :
	real_size_(size),
	size_(size),
	array_(new T[size] { })
{}

template<typename T>
Array<T>::~Array() noexcept
{
	clear_iterators_();
}

template<typename T>
const std::string Array<T>::to_string() const noexcept
{
	if (is_empty())
	{
		return "{ }";
	}
	else
	{
		std::string str = "{ ";
		for (int i = 0; i < size_ - 1; i++)
		{
			str += util::to_string(array_[i]) + ", ";
		}
		return str + util::to_string(array_[size_ - 1]) + " }";
	}
}

template<typename T>
int Array<T>::hash_code() const noexcept
{
	int hash = 0;
	for (int i = 0; i < size_; i += 2)
	{
		hash += util::hash_code(array_[i]);
	}
	for (int i = 1; i < size_; i += 2)
	{
		hash -= util::hash_code(array_[i]);
	}
	return hash;
}

template<typename T>
int Array<T>::size() const noexcept
{
	return size_;
}

template<typename T>
bool Array<T>::is_empty() const noexcept
{
	return size_ == 0;
}

template<typename T>
void Array<T>::clear() noexcept
{
	real_size_ = DEFAULT_REAL_SIZE_;
	size_ = 0;
	array_.reset(new T[real_size_]);

	FOR_ITERATORS_(i,
	{
		i->index_ = 0;
	})
}

template<typename T>
bool Array<T>::resize(int new_size) noexcept
{
	if (new_size > 0)
	{
		if (new_size <= size_)
		{
			size_ = new_size;

			FOR_ITERATORS_(i,
			{
				if (i->index_ > new_size)
				{
					i->index_ = new_size;
				}
			})
		}
		else
		{
			int to_reset = math::min(new_size, real_size_);
			for (int i = size_; i < to_reset; i++)
			{
				array_[i] = T();
			}
			check_real_size_to_add_(new_size);

			FOR_ITERATORS_(i,
			{
				if (i->index_ >= size_)
				{
					i->index_ = new_size;
				}
			})

			size_ = new_size;
		}
		return true;
	}
	else if (new_size == 0)
	{
		clear();
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
bool Array<T>::add(const T& element)
{
	check_real_size_to_add_(size_ + 1);
	array_[size_] = element;

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
bool Array<T>::add(T&& element)
{
	check_real_size_to_add_(size_ + 1);
	array_[size_] = std::move(element);

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
bool Array<T>::add(const T& element, int index)
{
	if (index < 0 || index > size_)
	{
		return false;
	}
	else
	{
		if (index == size_)
		{
			return add_to_end_(element);
		}
		else
		{
			check_real_size_to_add_(size_ + 1);
			for (int i = size_++; i > index; i--)
			{
				array_[i] = std::move(array_[i - 1]);
			}

			FOR_ITERATORS_(i,
			{
				if (i->index_ >= index)
				{
					i->index_++;
				}
			})

			array_[index] = element;
			return true;
		}
	}
}

template<typename T>
bool Array<T>::add(T&& element, int index)
{
	if (index < 0 || index > size_)
	{
		return false;
	}
	else
	{
		if (index == size_)
		{
			return add_to_end_(std::forward<T>(element));
		}
		else
		{
			check_real_size_to_add_(size_ + 1);
			for (int i = size_++; i > index; i--)
			{
				array_[i] = std::move(array_[i - 1]);
			}

			FOR_ITERATORS_(i,
			{
				if (i->index_ >= index)
				{
					i->index_++;
				}
			})

			array_[index] = std::move(element);
			return true;
		}
	}
}

template<typename T>
int Array<T>::add(const Array<T>& array)
{
	if (!array.is_empty())
	{
		check_real_size_to_add_(size_ + array.size_);
		int old_size = size_;
		for (int i = 0; i < array.size_; i++)
		{
			array_[size_++] = array.array_[i];
		}

		FOR_ITERATORS_(i,
		{
			if (i->index_ >= old_size)
			{
				i->index_ += array.size_;
			}
		})
	}
	return array.size_;
}

template<typename T>
int Array<T>::add(Array<T>&& array)
{
	if (!array.is_empty())
	{
		check_real_size_to_add_(size_ + array.size_);
		int old_size = size_;
		for (int i = 0; i < array.size_; i++)
		{
			array_[size_++] = std::move(array.array_[i]);
		}

		FOR_ITERATORS_(i,
		{
			if (i->index_ >= old_size)
			{
				i->index_ += array.size_;
			}
		})
	}
	return array.size_;
}

template<typename T>
bool Array<T>::remove(int index)
{
	return remove(index, index + 1) > 0;
}

template<typename T>
int Array<T>::remove(int from, int to)
{
	if (from < to && from >= 0 && to <= size_)
	{
		int delta = to - from;
		size_ -= delta;
		for (int i = from; i < size_; i++)
		{
			array_[i] = std::move(array_[i + delta]);
		}
		
		FOR_ITERATORS_(i,
		{
			if (i->index_ > from && i->index_ < to)
			{
				i->index_ = from;
			}
			else if (i->index_ >= to)
			{
				i->index_ -= delta;
			}
		})

		return delta;
	}
	else
	{
		return 0;
	}
}

template<typename T>
bool Array<T>::remove(const ArrayIterator<T>& element)
{
	return remove(iterator_to_const(element));
}

template<typename T>
bool Array<T>::remove(const ConstArrayIterator<T>& element)
{
	if (element.is_element_valid() && &element.get_container() == this)
	{
		return remove(element.get_index());
	}
	else
	{
		return false;
	}
}

template<typename T>
int Array<T>::remove(const ArrayIterator<T>& from, const ArrayIterator<T>& to)
{
	return remove(iterator_to_const(from), iterator_to_const(to));
}

template<typename T>
int Array<T>::remove(const ConstArrayIterator<T>& from, const ConstArrayIterator<T>& to)
{
	if (from.is_element_valid() && from.is_valid() && &from.get_container() == this && &to.get_container() == this)
	{
		return remove(from.get_index(), to.get_index());
	}
	else
	{
		return 0;
	}
}

template<typename T>
bool Array<T>::remove_any(const T& element)
{
	return remove(find_any(element));
}

template<typename T>
bool Array<T>::remove_first(const T& element)
{
	return remove(find_first(element));
}

template<typename T>
bool Array<T>::remove_last(const T& element)
{
	return remove(find_last(element));
}

template<typename T>
int Array<T>::remove_all(const T& element)
{
	for (int to = 0, from = -1; to < size_; to++)
	{
		do
		{
			if (++from >= size_)
			{
				size_ -= from - to;
				return from - to;
			}
		} while (array_[from] == element);
		if (from != to)
		{
			array_[to] = std::move(array_[from]);

			FOR_ITERATORS_(i,
			{
				if (i->index_ == from)
				{
					i->index_ = to;
				}
			})
		}
	}
	return 0;
}

template<typename T>
int Array<T>::find_any(const T& element) const
{
	return find_first(element);
}

template<typename T>
int Array<T>::find_first(const T& element) const
{
	for (int i = 0; i < size_; i++)
	{
		if (array_[i] == element)
		{
			return i;
		}
	}
	return -1;
}

template<typename T>
int Array<T>::find_last(const T& element) const
{
	for (int i = size_ - 1; i >= 0; i--)
	{
		if (array_[i] == element)
		{
			return i;
		}
	}
	return -1;
}

template<typename T>
LinkedList<int> Array<T>::find_all(const T& element) const
{
	LinkedList<int> result;
	for (int i = 0; i < size_; i++)
	{
		if (array_[i] == element)
		{
			result.add(i);
		}
	}
	return result;
}

template<typename T>
bool Array<T>::contains(const T& element) const
{
	return find_first(element) >= 0;
}

template<typename T>
int Array<T>::count(const T& element) const
{
	int counter = 0;
	for (int i = 0; i < size_; i++)
	{
		if (array_[i] == element)
		{
			counter++;
		}
	}
	return counter;
}

template<typename T>
ArrayIterator<T> Array<T>::begin() noexcept
{
	return ArrayIterator<T>(*this, 0);
}

template<typename T>
ArrayIterator<T> Array<T>::last() noexcept
{
	return ArrayIterator<T>(*this, size_ - 1);
}

template<typename T>
ArrayIterator<T> Array<T>::end() noexcept
{
	return ArrayIterator<T>(*this, size_);
}

template<typename T>
ArrayIterator<T> Array<T>::create_iterator(int index)
{
	if (index >= 0 && index <= size_)
	{
		return ArrayIterator<T>(*this, index);
	}
	else
	{
		throw std::out_of_range("Index is out of array bounds");
	}
}

template<typename T>
ConstArrayIterator<T> Array<T>::begin() const noexcept
{
	return ConstArrayIterator<T>(*this, 0);
}

template<typename T>
ConstArrayIterator<T> Array<T>::last() const noexcept
{
	return ConstArrayIterator<T>(*this, size_ - 1);
}

template<typename T>
ConstArrayIterator<T> Array<T>::end() const noexcept
{
	return ConstArrayIterator<T>(*this, size_);
}

template<typename T>
ConstArrayIterator<T> Array<T>::create_iterator(int index) const
{
	if (index >= 0 && index <= size_)
	{
		return ConstArrayIterator<T>(*this, index);
	}
	else
	{
		throw std::out_of_range("Index is out of array bounds");
	}
}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& array)
{
	clear_iterators_();
	real_size_ = array.real_size_;
	size_ = array.size_;
	array_.reset(new T[real_size_]);
	for (int i = 0; i < size_; i++)
	{
		array_[i] = array.array_[i];
	}
	return *this;
}

template<typename T>
Array<T>& Array<T>::operator=(Array<T>&& array)
{
	clear_iterators_();
	real_size_ = array.real_size_;
	size_ = array.size_;
	array_ = std::move(array.array_);
	return *this;
}

template<typename T>
bool Array<T>::operator==(const Array<T>& array) const
{
	if (size_ == array.size_)
	{
		for (int i = 0; i < size_; i++)
		{
			if (!(array_[i] == array.array_[i]))
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
bool Array<T>::operator!=(const Array<T>& array) const
{
	return !(*this == array);
}

template<typename T>
T& Array<T>::operator[](int index)
{
	if (index >= 0 && index < size_)
	{
		return array_[index];
	}
	else
	{
		throw std::out_of_range("Index is out of array bounds");
	}
}

template<typename T>
const T& Array<T>::operator[](int index) const
{
	if (index >= 0 && index < size_)
	{
		return array_[index];
	}
	else
	{
		throw std::out_of_range("Index is out of array bounds");
	}
}

template<typename T>
ConstArrayIterator<T> Array<T>::iterator_to_const(const ArrayIterator<T>& iterator) noexcept
{
	return ConstArrayIterator<T>(iterator.container_, iterator.index_, iterator.is_valid_);
}

template<typename T>
bool Array<T>::add_to_end_(const T& element)
{
	return Array<T>::add(element);
}

template<typename T>
bool Array<T>::add_to_end_(T&& element)
{
	return Array<T>::add(std::forward<T>(element));
}

template<typename T>
void Array<T>::check_real_size_to_add_(int required_size)
{
	if (required_size > real_size_)
	{
		int old_size = real_size_;
		if (old_size < 2)
		{
			real_size_ = DEFAULT_REAL_SIZE_;
		}
		else
		{
			real_size_ = math::max(static_cast<int>(real_size_ * 1.5f), required_size);
		}
		std::unique_ptr<T[]> new_ptr(new T[real_size_] { });
		for (int i = 0; i < old_size; i++)
		{
			new_ptr[i] = std::move(array_[i]);
		}
		array_ = std::move(new_ptr);
	}
}

template<typename T>
void Array<T>::register_iterator_(ArrayIterator<T>* iterator) noexcept
{
	iterators_.push_back(iterator);
}

template<typename T>
void Array<T>::unregister_iterator_(ArrayIterator<T>* iterator) noexcept
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
void Array<T>::register_iterator_(ConstArrayIterator<T>* iterator) const noexcept
{
	const_iterators_.push_back(iterator);
}

template<typename T>
void Array<T>::unregister_iterator_(ConstArrayIterator<T>* iterator) const noexcept
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
void Array<T>::clear_iterators_() const noexcept
{
	FOR_ITERATORS_(i,
	{
		i->is_valid_ = false;
	})
	iterators_.clear();
	const_iterators_.clear();
}

template<typename T>
const int Array<T>::DEFAULT_REAL_SIZE_ = 5;

#undef FOR_ITERATORS_

}
