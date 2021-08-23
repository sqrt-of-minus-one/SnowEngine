    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SortedArray.h               //
////////////////////////////////////////

#pragma once

#include "Array.h"

#include <functional>

namespace snow
{

template<typename T>
class SortedArray : public Array<T>
{
public:
	SortedArray(std::function<int(const T&, const T&)> comparator);
	SortedArray(const Array<T>& array, std::function<int(const T&, const T&)> comparator);
	SortedArray(Array<T>&& array, std::function<int(const T&, const T&)> comparator);
	SortedArray(int size, std::function<int(const T&, const T&)> comparator);
	virtual ~SortedArray();

	virtual bool add(const T& element) override;
	virtual bool add(T&& element) override;
	virtual bool add(const T& element, int index) override;
	virtual bool add(T&& element, int index) override;
	virtual int add(const Array<T>& array) override;
	virtual int add(Array<T>&& array) override;
	int add(const SortedArray<T>& array);
	int add(SortedArray<T>& array);

	virtual bool remove(int index) override;
	virtual bool remove_first(const T& element) override;
	virtual bool remove_last(const T& element) override;
	virtual int remove_all(const T& element) override;

	virtual int find_first(const T& element) const override;
	virtual int find_last(const T& element) const override;
	virtual LinkedList<int> find_all(const T& element) const override;

	virtual bool contains(const T& element) const override;
	virtual int count(const T& element) const override;
	
	int compare(const T& first, const T& second) const;
	int compare_by_index(int first, int second) const;

	virtual Array<T>& operator=(const Array<T>& array) override;
	virtual Array<T>& operator=(Array<T>&& array) override;
	
private:
	std::function<int(const T&, const T&)> comparator_;
	int get_index_to_add_(const T& element) const;
	void sort_();
};

		/* DEFINITIONS */

template<typename T>
SortedArray<T>::SortedArray(std::function<int(const T&, const T&)> comparator) :
	Array<T>(),
	comparator_(comparator)
{}

template<typename T>
SortedArray<T>::SortedArray(const Array<T>& array, std::function<int(const T&, const T&)> comparator) :
	Array<T>(array),
	comparator_(comparator)
{
	sort_();
}

template<typename T>
SortedArray<T>::SortedArray(Array<T>&& array, std::function<int(const T&, const T&)> comparator) :
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
SortedArray<T>::~SortedArray()
{
	~Array();
}

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
	
}

template<typename T>
int SortedArray<T>::add(Array<T>&& array)

template<typename T>
bool SortedArray<T>::remove(int index)

template<typename T>
bool SortedArray<T>::remove_first(const T& element)

template<typename T>
bool SortedArray<T>::remove_last(const T& element)

template<typename T>
int SortedArray<T>::remove_all(const T& element)

template<typename T>
int SortedArray<T>::find_first(const T& element) const

template<typename T>
int SortedArray<T>::find_last(const T& element) const

template<typename T>
LinkedList<int> SortedArray<T>::find_all(const T& element) const

template<typename T>
bool SortedArray<T>::contains(const T& element) const

template<typename T>
int SortedArray<T>::count(const T& element) const

template<typename T>
int SortedArray<T>::compare(const T& first, const T& second) const

template<typename T>
int SortedArray<T>::compare_by_index(int first, int second) const

template<typename T>
Array<T>& SortedArray<T>::operator=(const Array<T>& array)

template<typename T>
Array<T>& SortedArray<T>::operator=(Array<T>&& array)
template<typename T>
int SortedArray<T>::get_index_to_add_(const T& element) const

template<typename T>
void SortedArray<T>::sort_()

}