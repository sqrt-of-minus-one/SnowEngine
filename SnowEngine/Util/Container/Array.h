    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Array.h                     //
////////////////////////////////////////

#pragma once

#include <list>

#include "ArrayIterator.h"
#include "LinkedList.h"
#include "../../Math/Math.h"

namespace snow
{

template<typename T>
class Array :
	public Object,
	public IContainer<T>
{
	template<typename T_Container, typename T_Element>
	friend class BaseArrayIterator_;

public:
	Array();
	Array(const Array<T>& array);
	Array(Array<T>&& array);
	Array(int size);
	virtual ~Array();

	virtual const std::string to_string() const override;
	virtual int hash_code() const override;
	
	virtual int size() const override;
	virtual bool is_empty() const override;
	virtual void clear() override;
	
	bool resize(int new_size);

	virtual bool add(const T& element);
	virtual bool add(T&& element);
	virtual bool add(const T& element, int index);
	virtual bool add(T&& element, int index);
	virtual int add(const Array<T>& array);
	virtual int add(Array<T>&& array);

	virtual bool remove(int index);
	bool remove(const ArrayIterator<T>& element);
	bool remove(const ConstArrayIterator<T>& element);
	int remove(int from, int to);
	int remove(const ArrayIterator<T>& from, const ArrayIterator<T>& to);
	int remove(const ConstArrayIterator<T>& from, const ConstArrayIterator<T>& to);
	virtual bool remove_first(const T& element);
	virtual bool remove_last(const T& element);
	virtual int remove_all(const T& element) override;

	virtual int find_first(const T& element) const;
	virtual int find_last(const T& element) const;
	virtual LinkedList<int> find_all(const T& element) const;

	virtual bool contains(const T& element) const override;
	virtual int count(const T& element) const override;

	ArrayIterator<T> begin();
	ArrayIterator<T> last();
	ArrayIterator<T> end();
	ArrayIterator<T> create_iterator(int index);
	ConstArrayIterator<T> begin() const;
	ConstArrayIterator<T> end() const;
	ConstArrayIterator<T> last() const;
	ConstArrayIterator<T> create_iterator(int index) const;

	virtual Array<T>& operator=(const Array<T>& array);
	virtual Array<T>& operator=(Array<T>&& array);

	bool operator==(const Array<T>& array) const;
	bool operator!=(const Array<T>& array) const;

	T& operator[](int index);
	const T& operator[](int index) const;

	static ConstArrayIterator<T> iterator_to_const(const ArrayIterator<T>& iterator);

private:
	int real_size_;
	int size_;
	std::unique_ptr<T[]> array_;

	void check_real_size_to_add_(int required_size);

	mutable std::list<ArrayIterator<T>*> iterators_;
	mutable std::list<ConstArrayIterator<T>*> const_iterators_;
	void register_iterator_(ArrayIterator<T>* iterator);
	void unregister_iterator_(ArrayIterator<T>* iterator);
	void register_iterator_(ConstArrayIterator<T>* iterator) const;
	void unregister_iterator_(ConstArrayIterator<T>* iterator) const;
	void clear_iterators_() const;

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
	real_size_(array.real_size_),
	size_(array.size_),
	array_(std::move(array.array_)),
	iterators_(std::move(array.iterators_)),
	const_iterators_(std::move(array.const_iterators_))
{}

template<typename T>
Array<T>::Array(int size) :
	real_size_(size),
	size_(size),
	array_(new T[real_size_] { })
{}

template<typename T>
Array<T>::~Array()
{
	clear_iterators_();
}

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
	clear_iterators_();
	real_size_ = DEFAULT_REAL_SIZE_;
	size_ = 0;
	array_.reset(new T[real_size_]);
}

template<typename T>
bool Array<T>::resize(int new_size)
{
	if (new_size > 0)
	{
		if (new_size <= size_)
		{
			size_ = new_size;
		}
		else
		{
			int to_reset = math::min(new_size, real_size_);
			for (int i = size_; i < to_reset; i++)
			{
				array_[i] = T();
			}
			check_real_size_to_add_(new_size);
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

	for (auto i : iterators_)
	{
		if (i->index_ >= size_)
		{
			i->index_++;
		}
	}
	for (auto i : const_iterators_)
	{
		if (i->index_ >= size_)
		{
			i->index_++;
		}
	}

	size_++;
	return true;
}

template<typename T>
bool Array<T>::add(T&& element)
{
	check_real_size_to_add_(size_ + 1);
	array_[size_] = std::move(element);

	for (auto i : iterators_)
	{
		if (i->index_ >= size_)
		{
			i->index_++;
		}
	}
	for (auto i : const_iterators_)
	{
		if (i->index_ >= size_)
		{
			i->index_++;
		}
	}

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
			return add(element);
		}
		else
		{
			check_real_size_to_add_(size_ + 1);
			for (int i = size_++; i > index; i--)
			{
				array_[i] = std::move(array_[i - 1]);
			}

			for (auto i : iterators_)
			{
				if (i->index_ >= index)
				{
					i->index_++;
				}
			}
			for (auto i : const_iterators_)
			{
				if (i->index_ >= index)
				{
					i->index_++;
				}
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
			check_real_size_to_add_(size_ + 1);
			for (int i = size_++; i > index; i--)
			{
				array_[i] = std::move(array_[i - 1]);
			}

			for (auto i : iterators_)
			{
				if (i->index_ >= index)
				{
					i->index_++;
				}
			}
			for (auto i : const_iterators_)
			{
				if (i->index_ >= index)
				{
					i->index_++;
				}
			}

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

		for (auto i : iterators_)
		{
			if (i->index_ >= old_size)
			{
				i->index_ += array.size_;
			}
		}
		for (auto i : const_iterators_)
		{
			if (i->index_ >= old_size)
			{
				i->index_ += array.size_;
			}
		}
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

		for (auto i : iterators_)
		{
			if (i->index_ >= old_size)
			{
				i->index_ += array.size_;
			}
		}
		for (auto i : const_iterators_)
		{
			if (i->index_ >= old_size)
			{
				i->index_ += array.size_;
			}
		}
	}
	return array.size_;
}

template<typename T>
bool Array<T>::remove(int index)
{
	return remove(index, index + 1);
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
		
		for (auto i : iterators_)
		{
			if (i->index_ > from && i->index_ < to)
			{
				i->index_ = from;
			}
			else if (i->index_ >= to)
			{
				i->index_ -= delta;
			}
		}
		for (auto i : const_iterators_)
		{
			if (i->index_ > from && i->index_ < to)
			{
				i->index_ = from;
			}
			else if (i->index_ >= to)
			{
				i->index_ -= delta;
			}
		}

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

			for (auto i : iterators_)
			{
				if (i->index_ == from)
				{
					i->index_ = to;
				}
			}
			for (auto i : const_iterators_)
			{
				if (i->index_ == from)
				{
					i->index_ = to;
				}
			}
		}
	}
	return 0;
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
	iterators_ = std::move(array.iterators_);
	const_iterators_ = std::move(array.const_iterators_);
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
ConstArrayIterator<T> Array<T>::iterator_to_const(const ArrayIterator<T>& iterator)
{
	return ConstArrayIterator<T>(iterator.container_, iterator.index_, iterator.is_valid_);
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
void Array<T>::register_iterator_(ArrayIterator<T>* iterator)
{
	iterators_.push_back(iterator);
}

template<typename T>
void Array<T>::unregister_iterator_(ArrayIterator<T>* iterator)
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
void Array<T>::register_iterator_(ConstArrayIterator<T>* iterator) const
{
	const_iterators_.push_back(iterator);
}

template<typename T>
void Array<T>::unregister_iterator_(ConstArrayIterator<T>* iterator) const
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
void Array<T>::clear_iterators_() const
{
	for (auto i : iterators_)
	{
		i->is_valid_ = false;
	}
	iterators_.clear();
	for (auto i : const_iterators_)
	{
		i->is_valid_ = false;
	}
	const_iterators_.clear();
}

template<typename T>
const int Array<T>::DEFAULT_REAL_SIZE_ = 5;

}
