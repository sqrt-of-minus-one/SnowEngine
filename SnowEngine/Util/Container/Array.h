    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Array.h                     //
////////////////////////////////////////

#pragma once

#include <map>
#include <list>

#include "ArrayIterator.h"
#include "LinkedList.h"

namespace snow
{

template<typename T>
class Array :
	public Object,
	public IContainer<T>
{
	template<typename T>
	friend class ArrayIterator;

	template<typename T>
	friend class ConstArrayIterator;

public:
	Array();
	Array(const Array<T>& array);
	Array(Array<T>&& array);
	Array(int size);

	virtual const std::string to_string() const override;
	virtual int hash_code() const override;
	
	virtual int size() const override;
	virtual bool is_empty() const override;
	virtual void clear() override;

	virtual bool add(const T& element) override;
	virtual bool add(T&& element) override;
	virtual bool add(const T& element, int index);
	virtual bool add(T&& element, int index);

	virtual bool remove(int index);
	virtual bool remove(const ConstArrayIterator<T>& element);
	virtual bool remove(int from, int to);
	virtual bool remove(const ConstArrayIterator<T>& from, const ConstArrayIterator<T>& to);
	virtual bool remove_first(const T& element);
	virtual bool remove_last(const T& element);
	virtual int remove_all(const T& element) override;

	virtual int find_first(const T& element) const;
	virtual int find_last(const T& element) const;
	virtual LinkedList<int> find_all(const T& element) const;

	virtual bool contains(const T& element) const override;
	virtual int count(const T& element) const override;

	virtual ArrayIterator<T> begin();
	virtual ArrayIterator<T> last();
	virtual ArrayIterator<T> end();
	virtual ArrayIterator<T> create_iterator(int index);
	virtual ConstArrayIterator<T> begin() const;
	virtual ConstArrayIterator<T> end() const;
	virtual ConstArrayIterator<T> last() const;
	virtual ConstArrayIterator<T> create_iterator(int index) const;

	virtual Array<T>& operator=(const Array<T>& array);
	virtual Array<T>& operator=(Array<T>&& array);

	virtual bool operator==(const Array<T>& array) const;
	virtual bool operator!=(const Array<T>& array) const;

	virtual T& operator[](int index);
	virtual const T& operator[](int index) const;

private:
	int real_size_;
	int size_;
	std::unique_ptr<T[]> array_;

	void check_real_size_to_add_();

	mutable std::list<BaseArrayIterator_*> iterators_;
	void register_iterator_(BaseArrayIterator_* iterator) const;
	void unregister_iterator_(BaseArrayIterator_* iterator) const;

	static const int DEFAULT_REAL_SIZE_;
};

		/* DEFINITIONS of Array */

template<typename T>
Array<T>::Array() :
	real_size_(DEFAULT_REAL_SIZE_),
	size_(0),
	array_(new T[real_size_])
{}

template<typename T>
Array<T>::Array(const Array<T>& array) :
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
Array<T>::Array(Array<T>&& array) :
	real_size_(std::move(array.real_size_)),
	size_(std::move(array.size_)),
	array_(std::move(array.array_))
{}

template<typename T>
Array<T>::Array(int size) :
	real_size_(size),
	size_(size),
	array_(new T[real_size_])
{}

template<typename T>
const std::string Array<T>::to_string() const
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
int Array<T>::hash_code() const
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
int Array<T>::size() const
{
	return size_;
}

template<typename T>
bool Array<T>::is_empty() const
{
	return size_ == 0;
}

template<typename T>
void Array<T>::clear()
{
	real_size_ = DEFAULT_REAL_SIZE_;
	size_ = 0;
	array_.reset(new T[real_size_]);
}

template<typename T>
bool Array<T>::add(const T& element)
{
	check_real_size_to_add_();
	array_[size_++] = element;
	return true;
}

template<typename T>
bool Array<T>::add(T&& element)
{
	check_real_size_to_add_();
	array_[size_++] = std::move(element);
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
			return add(element);
		}
		else
		{
			check_real_size_to_add_();
			for (int i = size_++; i > index; i--)
			{
				array_[i] = std::move(array_[i - 1]);
			}
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
			return add(std::forward<T>(element));
		}
		else
		{
			check_real_size_to_add_();
			for (int i = size_++; i > index; i--)
			{
				array_[i] = std::move(array_[i - 1]);
			}
			array_[index] = std::move(element);
			return true;
		}
	}
}

template<typename T>
bool Array<T>::remove(int index)
{
	return remove(index, index + 1);
}

template<typename T>
bool Array<T>::remove(int from, int to)
{
	if (from < to && from >= 0 && to <= size_)
	{
		int delta = to - from;
		size_ -= delta;
		for (int i = from; i < size_; i++)
		{
			array_[i] = std::move(array_[i + delta]);
		}
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
bool Array<T>::remove(const ConstArrayIterator<T>& element)
{
	if (&element.get_container() == this)
	{
		return remove(element.get_index());
	}
	else
	{
		return false;
	}
}

template<typename T>
bool Array<T>::remove(const ConstArrayIterator<T>& from, const ConstArrayIterator<T>& to)
{
	if (&from.get_container() == this && &to.get_container() == this)
	{
		return remove(from.get_index(), to.get_index());
	}
	else
	{
		return false;
	}
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
	for (int to = 0, from = 0; to < size_; to++)
	{
		do
		{
			if (++from >= size_)
			{
				size_ -= from - to;
				return from - to;
			}
		}
		while (array_[from] == element);
		if (from != to)
		{
			array_[to] = std::move(array_[from]);
		}
	}
	return 0;
}

template<typename T>
int Array<T>::find_first(const T& element) const
{
	for (int i = 0; i < size_; i++)
	{
		if (array_[i] = element)
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
ArrayIterator<T> Array<T>::begin()
{
	return ArrayIterator<T>(*this, 0);
}

template<typename T>
ArrayIterator<T> Array<T>::last()
{
	return ArrayIterator<T>(*this, size_ - 1);
}

template<typename T>
ArrayIterator<T> Array<T>::end()
{
	return ArrayIterator<T>(*this, size_);
}

template<typename T>
ArrayIterator<T> Array<T>::create_iterator(int index)
{
	if (index < 0 || index > size_)
	{
		throw std::range_error("Index is out of array bounds");
	}
	return ArrayIterator<T>(*this, index);
}

template<typename T>
ConstArrayIterator<T> Array<T>::begin() const
{
	return ConstArrayIterator<T>(*this, 0);
}

template<typename T>
ConstArrayIterator<T> Array<T>::last() const
{
	return ConstArrayIterator<T>(*this, size_ - 1);
}

template<typename T>
ConstArrayIterator<T> Array<T>::end() const
{
	return ConstArrayIterator<T>(*this, size_);
}

template<typename T>
ConstArrayIterator<T> Array<T>::create_iterator(int index) const
{
	if (index < 0 || index > size_)
	{
		throw std::range_error("Index is out of array bounds");
	}
	return ConstArrayIterator<T>(*this, index);
}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& array)
{
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
	real_size_ = std::move(array.real_size_);
	size_ = std::move(array.size_);
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
			if (array_[i] != array.array_[i])
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
	if (index < 0 || index >= size_)
	{
		throw std::range_error("Index is out of array bounds");
	}
	else
	{
		return array_[index];
	}
}

template<typename T>
const T& Array<T>::operator[](int index) const
{
	if (index < 0 || index >= size_)
	{
		throw std::range_error("Index is out of array bounds");
	}
	else
	{
		return array_[index];
	}
}

template<typename T>
void Array<T>::check_real_size_to_add_()
{
	if (size_ >= real_size_)
	{
		int old_size = real_size_;
		if (old_size < 2)
		{
			real_size_ = DEFAULT_REAL_SIZE_;
		}
		else
		{
			real_size_ = static_cast<int>(real_size_ * 1.5f);
		}
		std::unique_ptr<T[]> new_ptr(new T[real_size_]);
		for (int i = 0; i < old_size; i++)
		{
			new_ptr[i] = std::move(array_[i]);
		}
		array_ = std::move(new_ptr);
	}
}

template<typename T>
void Array<T>::register_iterator_(BaseArrayIterator_* iterator) const
{
	iterators_.push_back(iterator);
}

template<typename T>
void Array<T>::unregister_iterator_(BaseArrayIterator_* iterator) const
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
const int Array<T>::DEFAULT_REAL_SIZE_ = 5;

}
