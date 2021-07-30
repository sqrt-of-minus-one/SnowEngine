    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Array.h                     //
////////////////////////////////////////

#pragma once

#include "../Container.h"

#include <functional>

namespace snow
{

template<typename T>
class List;

template<typename T>
class LinkedList;

namespace
{

template<typename T_Container, typename T_Element>
class BaseListIterator_ : public BaseIterator_<T_Container, T_Element>
{
public:
	virtual int get_index() const = 0;
};

}

template<typename T>
using ConstListIterator = BaseListIterator_<const List<T>, const T>;

template<typename T>
using ListIterator = BaseListIterator_<List<T>, T>;

template<typename T>
class List : public Container<T>
{
public:
	virtual bool add(const T& element, int index) = 0;
	virtual bool add(T&& element, int index) = 0;

	virtual bool remove(int index) = 0;
	virtual bool remove(std::shared_ptr<ListIterator<T>> iterator) = 0;
	virtual bool remove_first(const T& element) = 0;
	virtual bool remove_last(const T& element) = 0;


	virtual int find_first(const T& element) const = 0;
	virtual int find_last(const T& element) const = 0;
	virtual LinkedList<int> find_all(const T& element) const = 0;

	virtual int contains(const T& element) const override;

	virtual void sort(std::function<int(const T&, const T&)> comparator) = 0;

	virtual std::shared_ptr<ListIterator<T>> create_list_iterator() = 0;
	virtual std::shared_ptr<ListIterator<T>> create_list_iterator(int index) = 0;
	virtual std::shared_ptr<ConstListIterator<T>> create_const_list_iterator() const = 0;
	virtual std::shared_ptr<ConstListIterator<T>> create_const_list_iterator(int index) const = 0;

	virtual T& operator[](int index) = 0;
	virtual const T& operator[](int index) const = 0;
	virtual bool operator==(const List<T>& list) const;
	virtual bool operator!=(const List<T>& list) const;
};


		/* DEFINITIONS of List */

template<typename T>
int List<T>::contains(const T& element) const
{
	return find_all(element).size();
}

template<typename T>
bool List<T>::operator==(const List<T>& list) const
{
	if (this->size() != list.size())
	{
		return false;
	}
	else if (this->size() == 0)
	{
		return true;
	}
	else
	{
		std::shared_ptr<ConstListIterator<T>> iterator_1 = create_const_list_iterator(0);
		std::shared_ptr<ConstListIterator<T>> iterator_2 = list.create_const_list_iterator(0);
		do 
		{
			if (iterator_1->get() != iterator_2->get())
			{
				return false;
			}
		} while (!iterator_1->is_end());
		return true;
	}
}

template<typename T>
bool List<T>::operator!=(const List<T>& list) const
{
	return !(*this == list);
}

}
