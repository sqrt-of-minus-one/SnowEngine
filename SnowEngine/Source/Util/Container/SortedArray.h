    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SortedArray.h               //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\brief The file of sorted array
 *	
 *	This file contains the definition of the SortedArray class.
 */

#include "Array.h"

#include <functional>

namespace snow
{

/**
 *	\brief The array that is always sorted
 *	
 *	This class is identical to an ordinary array, but is always sorted. Sorting is performed using
 *	a custom comparator function, it returns a positive value if the first object is more than the
 *	second, a negative value if the first object is less than the second, and zero if two objects
 *	are equal.
 *	\tparam T Type of the array elements. The requirements are the same as the Array class.
 */
template<typename T>
class SortedArray : public Array<T>
{
public:
	
	/**
	 *	\brief Copy constructor
	 *	
	 *	Creates a new sorted array as a copy of the passed one (its comparator is also copied).
	 *	\param array The sorted array that will be copied.
	 */
	SortedArray(const SortedArray<T>& array) noexcept;

	/**
	 *	\brief Move constructor
	 *	
	 *	Creates a new sorted array by moving elements of the passed one. The new array will use the
	 *	comparator of the passed array.
	 *	\param array The sorted array the will be moved.
	 */
	SortedArray(SortedArray<T>&& array) noexcept;

	/**
	 *	\brief Create an empty sorted array
	 *	
	 *	Creates an empty array with the passed comparator.
	 *	\param comparator The comparator function for the array.
	 */
	SortedArray(std::function<int(const T&, const T&)> comparator) noexcept;
	
	/**
	 *	\brief Copy an array
	 *	
	 *	Creates a new array using the passed one. Sorts the array using the passed comparator.
	 *	\param array The array that will be copied.
	 *	\param comparator The comparator to sort.
	 */
	SortedArray(const Array<T>& array, std::function<int(const T&, const T&)> comparator) noexcept;

	/**
	 *	\brief Move an array
	 *
	 *	Creates a new array my moving elements of the passed one. Sorts the array using the passed
	 *	comparator.
	 *	\param array The array that will be moved.
	 *	\param comparator The comparator to sort.
	 */
	SortedArray(Array<T>&& array, std::function<int(const T&, const T&)> comparator) noexcept;

	/**
	 *	\brief Create a sorted array of the passed size
	 *
	 *	Creates a sorted array of the passed size and fills it with default elements. If the array
	 *	stores pointers, `nullptr`s will be added. Otherwise inserted elements will be created
	 *	using a default constructor. It is possible that two objects created by default constructor
	 *	are not equal, so sorting will be performed.
	 *	\param size The size of the array.
	 *	\param comparator The comparator function.
	 */
	SortedArray(int size, std::function<int(const T&, const T&)> comparator);

	/**
	 *	\brief Add a new element
	 *
	 *	Inserts a new element in the array, preserving its sorting.
	 *	\param element The element that will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 */
	virtual bool add(const T& element) override;

	/**
	 *	\brief Add a new element
	 *
	 *	Inserts a new element in the array, preserving its sorting.
	 *	\param element The element that will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 */
	virtual bool add(T&& element) override;

	/**
	 *	\brief Add a new element
	 *
	 *	Inserts a new element in the array. The array will continue to be sorted.
	 *	\param element The element that will be added.
	 *	\param index This parameter does not affect the insertion.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 *	\warning The array must stay sorted so you cannot insert an element to an arbitrary
	 *	position.
	 */
	virtual bool add(const T& element, int index) override;

	/**
	 *	\brief Add a new element
	 *
	 *	Inserts a new element in the array. The array will continue to be sorted.
	 *	\param element The element that will be added.
	 *	\param index This parameter does not affect the insertion.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 *	\warning The array must stay sorted so you cannot insert an element to an arbitrary
	 *	position.
	 */
	virtual bool add(T&& element, int index) override;

	/**
	 *	\brief Add into the array copies of elements of the passed array
	 *
	 *	Inserts in the array copies of elements of the passed array. The array will continue to be
	 *	sorted.
	 *	\param array The array whose elements will be added.
	 *	\return The number of elements that have been successfully added.
	 */
	virtual int add(const Array<T>& array) override;

	/**
	 *	\brief Move into the array elements of the passed array
	 *
	 *	Moves in the array elements of the passed array. The array will continue to be sorted.
	 *	\param array The array whose elements will be moved.
	 *	\return The number of elements that have been successfully added.
	 */
	virtual int add(Array<T>&& array) override;

	/**
	 *	\brief Remove all elements that are equal to the passed one
	 *
	 *	Finds all elements of the array with the passed one and removes them. All iterators will
	 *	continue to point to their elements. Iterators that pointed to the removed elements will
	 *	point to the next element after executing this method.
	 *	\param element The object to compare.
	 *	\return Number of elements that have been successfully removed.
	 */
	virtual int remove_all(const T& element) override;

	/**
	 *	\brief Find any element that is equal to the passed one
	 *
	 *	Returns an index of any element of the array that is equal to the passed one
	 *	\param element The desired element.
	 *	\return An index of a match; a negative value if no match has been found.
	 */
	virtual int find_any(const T& element) const override;

	/**
	 *	\brief Find the first element that is equal to the passed one
	 *
	 *	Returns an index of the first element that is equal to the passed one.
	 *	\param element The desired element.
	 *	\return An index of the first match; a negative value if no match has been found.
	 */
	virtual int find_first(const T& element) const override;

	/**
	 *	\brief Find the last element that is equal to the passed one
	 *
	 *	Returns an index of the last element that is equal to the passed one.
	 *	\param element The desired element.
	 *	\return An index of the last match; a negative value if no match has been found.
	 */
	virtual int find_last(const T& element) const override;

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
	 *	\brief Compares two values using the comparator.
	 *	
	 *	Uses the comparator to compare two values.
	 *	\param first The first value.
	 *	\param second The second value.
	 *	\return A positive number if the first value is more than the second; a negative number if
	 *	the first value is less than the second; zero if two values are equal.
	 */
	int compare(const T& first, const T& second) const;

	/**
	 *	\brief Compares two array elements using the comparator.
	 *
	 *	Uses the comparator to compare two elements of the array.
	 *	\param first The index of the first element.
	 *	\param second The index of the second element.
	 *	\return A positive number if the first element is more than the second; a negative number
	 *	if the first element is less than the second; zero if two elements are equal.
	 */
	int compare_by_index(int first, int second) const;

	/**
	 *	\brief Copy assignment operator
	 *
	 *	Clears the array and assigns it the passed one. Invalidates all iterators. Sorts the array.
	 *	\param array The array to assign.
	 *	\return A reference to itself.
	 */
	virtual SortedArray<T>& operator=(const Array<T>& array) override;

	/**
	 *	\brief Move assignment operator
	 *
	 *	Clears the array and moves elements of the passed one into it. Invalidates all iterators.
	 *	Sorts the array.
	 *	\param array The array to move.
	 *	\return A reference to itself.
	 */
	virtual SortedArray<T>& operator=(Array<T>&& array) override;
	
private:
	std::function<int(const T&, const T&)> comparator_;
	int get_index_to_add_(const T& element) const;
	int get_index_to_add_(const T& element, int from, int to) const;
	void sort_();

	void quick_sort_(int left, int right);
	void insertion_sort_(int left, int right);
	int median_(int left, int right);
	int partition_(int left, int right, const T& pivot);
	void swap_(int index_1, int index_2);
};


		/* DEFINITIONS */

template<typename T>
SortedArray<T>::SortedArray(const SortedArray<T>& array) noexcept :
	Array<T>(array),
	comparator_(array.comparator_)
{}

template<typename T>
SortedArray<T>::SortedArray(SortedArray<T>&& array) noexcept :
	Array<T>(std::forward<Array<T>>(array)),
	comparator_(array.comparator_)
{}

template<typename T>
SortedArray<T>::SortedArray(std::function<int(const T&, const T&)> comparator) noexcept :
	Array<T>(),
	comparator_(comparator)
{}

template<typename T>
SortedArray<T>::SortedArray(const Array<T>& array, std::function<int(const T&, const T&)> comparator) noexcept :
	Array<T>(array),
	comparator_(comparator)
{
	sort_();
}

template<typename T>
SortedArray<T>::SortedArray(Array<T>&& array, std::function<int(const T&, const T&)> comparator) noexcept :
	Array<T>(std::forward<Array<T>>(array)),
	comparator_(comparator)
{
	sort_();
}

template<typename T>
SortedArray<T>::SortedArray(int size, std::function<int(const T&, const T&)> comparator) :
	Array<T>(size),
	comparator_(comparator)
{}

template<typename T>
bool SortedArray<T>::add(const T& element)
{
	return Array<T>::add(element, get_index_to_add_(element));
}

template<typename T>
bool SortedArray<T>::add(T&& element)
{
	return Array<T>::add(std::forward<T>(element), get_index_to_add_(element));
}

template<typename T>
bool SortedArray<T>::add(const T& element, int index)
{
	return add(element);
}

template<typename T>
bool SortedArray<T>::add(T&& element, int index)
{
	return add(std::forward<T>(element));
}

template<typename T>
int SortedArray<T>::add(const Array<T>& array)
{
	int res = 0;
	for (int i = 0; i < array.size(); i++)
	{
		res += static_cast<int>(add(array[i]));
	}
	return res;
}

template<typename T>
int SortedArray<T>::add(Array<T>&& array)
{
	int res = 0;
	for (int i = 0; i < array.size(); i++)
	{
		res += static_cast<int>(add(std::move(array[i])));
	}
	return res;
}

template<typename T>
int SortedArray<T>::remove_all(const T& element)
{
	int found = get_index_to_add_(element);
	int first = found;
	int last = found;
	if (found > 0 && comparator_((*this)[found - 1], element) == 0)
	{
		while (--first > 0 && comparator_((*this)[first - 1], element) == 0);
		while (++last < Array<T>::size() && comparator_((*this)[last], element) == 0);
		return Array<T>::remove(first, last);
	}
	else
	{
		return 0;
	}
}

template<typename T>
int SortedArray<T>::find_any(const T& element) const
{
	int found = get_index_to_add_(element);
	if (found > 0 && comparator_((*this)[--found], element) == 0)
	{
		return found;
	}
	else
	{
		return -1;
	}
}

template<typename T>
int SortedArray<T>::find_first(const T& element) const
{
	int found = get_index_to_add_(element);
	if (found > 0 && comparator_((*this)[found - 1], element) == 0)
	{
		while (--found > 0 && comparator_((*this)[found - 1], element) == 0);
		return found;
	}
	else
	{
		return -1;
	}
}

template<typename T>
int SortedArray<T>::find_last(const T& element) const
{
	int found = get_index_to_add_(element);
	if (found > 0 && comparator_((*this)[--found], element) == 0)
	{
		while (++found < Array<T>::size() && comparator_((*this)[found], element) == 0);
		return found - 1;
	}
	else
	{
		return -1;
	}
}

template<typename T>
bool SortedArray<T>::contains(const T& element) const
{
	int index = get_index_to_add_(element);
	return index > 0 && comparator_((*this)[index - 1], element) == 0;
}

template<typename T>
int SortedArray<T>::count(const T& element) const
{
	int found = get_index_to_add_(element);
	int first = found;
	int last = found;
	if (found > 0 && comparator_((*this)[found - 1], element) == 0)
	{
		while (--first > 0 && comparator_((*this)[first - 1], element) == 0);
		while (++last < Array<T>::size() && comparator_((*this)[last], element) == 0);
		return last - first;
	}
	else
	{
		return 0;
	}
}

template<typename T>
int SortedArray<T>::compare(const T& first, const T& second) const
{
	return comparator_(first, second);
}

template<typename T>
int SortedArray<T>::compare_by_index(int first, int second) const
{
	return comparator_((*this)[first], (*this)[second]);
}

template<typename T>
SortedArray<T>& SortedArray<T>::operator=(const Array<T>& array)
{
	Array<T>::operator=(array);
	sort_();
	return *this;
}

template<typename T>
SortedArray<T>& SortedArray<T>::operator=(Array<T>&& array)
{
	Array<T>::operator=(std::forward<Array<T>>(array));
	sort_();
	return *this;
}

template<typename T>
int SortedArray<T>::get_index_to_add_(const T& element) const
{
	return Array<T>::is_empty() ? 0 : get_index_to_add_(element, 0, Array<T>::size() - 1);
}

template<typename T>
int SortedArray<T>::get_index_to_add_(const T& element, int from, int to) const
{
	int middle = (from + to) / 2;
	int comp_res = comparator_((*this)[middle], element);
	if (comp_res == 0)
	{
		return middle + 1;
	}
	else if (comp_res < 0)
	{
		return from < to ? get_index_to_add_(element, middle + 1, to) : middle + 1;
	}
	else
	{
		return from < to ? get_index_to_add_(element, from, middle - 1) : middle;
	}
}

template<typename T>
void SortedArray<T>::sort_()
{
	quick_sort_(0, Array<T>::size() - 1);
}

template<typename T>
void SortedArray<T>::quick_sort_(int left, int right)
{
	if (right - left < 9)
	{
		insertion_sort_(left, right);
	}
	else
	{
		int median = median_(left, right);
		int part = partition_(left, right, (*this)[median]);
		quick_sort_(left, part - 1);
		quick_sort_(part + 1, right);
	}
}

template<typename T>
void SortedArray<T>::insertion_sort_(int left, int right)
{
	for (int i = left + 1; i <= right; i++)
	{
		T tmp = (*this)[i];
		int j;
		for (j = i; j > left && comparator_((*this)[j - 1], tmp) >= 0; j--)
		{
			(*this)[j] = (*this)[j - 1];
		}
		(*this)[j] = tmp;
	}
}

template<typename T>
int SortedArray<T>::median_(int left, int right)
{
	int centre = (left + right) / 2;

	if (compare_by_index(left, centre) > 0)
	{
		swap_(left, centre);
	}
	if (compare_by_index(left, right) > 0)
	{
		swap_(left, right);
	}
	if (compare_by_index(centre, right) > 0)
	{
		swap_(centre, right);
	}

	swap_(centre, right - 1);
	return right - 1;
}

template<typename T>
int SortedArray<T>::partition_(int left, int right, const T& pivot)
{
	int left_ptr = left;
	int right_ptr = right - 1;
	while (true)
	{
		while (comparator_((*this)[++left_ptr], pivot) < 0)
			;
		while (comparator_((*this)[--right_ptr], pivot) > 0)
			;
		if (left_ptr >= right_ptr)
		{
			break;
		}
		else
		{
			swap_(left_ptr, right_ptr);
		}
	}
	swap_(left_ptr, right - 1);
	return left_ptr;
}

template<typename T>
void SortedArray<T>::swap_(int index_1, int index_2)
{
	T tmp = (*this)[index_2];
	(*this)[index_2] = std::move((*this)[index_1]);
	(*this)[index_1] = std::move(tmp);
}

}