    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Array.h                     //
////////////////////////////////////////

#pragma once

#include "List.h"
#include "LinkedList.h"

namespace snow
{

template<typename T>
class Array;

enum class E_ArrayIteratorType
{
	BEGIN = 0,
	END
};

namespace
{

template<typename T_Container, typename T_Element>
class BaseArrayIterator_ : public BaseListIterator_<T_Container, T_Element>
{
	template<typename T>
	friend class Array;

public:
	virtual bool is_valid() const override;

	virtual T_Container& get_container() const override;

	virtual T_Element& get() const override;
	virtual int get_index() const override;

	virtual bool is_begin() const override;
	virtual bool is_end() const override;
	virtual bool next() override;
	virtual bool prev() override;

	virtual bool operator==(const BaseIterator_<T_Container, T_Element>& iterator) const override;
	virtual bool operator!=(const BaseIterator_<T_Container, T_Element>& iterator) const override;

private:
	BaseArrayIterator_(T_Container& array, int index);
	T_Container& container_;
	int index_;
};

}

template<typename T>
using ConstArrayIterator = BaseArrayIterator_<const Array<T>, const T>;

template<typename T>
using ArrayIterator = BaseArrayIterator_<Array<T>, T>;

template<typename T>
class Array : public List<T>
{
public:
	Array();
	Array(const Container<T>& container);
	Array(Array<T>&& array);
	Array(Container<T>&& container);
	Array(int size);
	~Array();

	virtual int size() const override;
	virtual void empty() override;

	virtual bool add(const T& element) override;
	virtual bool add(T&& element) override;
	virtual bool add(const T& element, int index) override;
	virtual bool add(T&& element, int index) override;

	virtual bool remove(int index) override;
	virtual bool remove_first(const T& element) override;
	virtual bool remove_last(const T& element) override;
	virtual int remove_all(const T& element) override;

	virtual int find_first(const T& element) const override;
	virtual int find_last(const T& element) const override;
	virtual LinkedList<int> find_all(const T& element) const override;

	virtual int contains(const T& element) const override;

	virtual void sort(std::function<int(const T&, const T&)> comparator) override;

	virtual void for_each(std::function<void(T&)> f) override;
	virtual void for_each_const(std::function<void(const T&)> f) const override;

	virtual std::shared_ptr<ArrayIterator<T>> create_array_iterator(E_ArrayIteratorType type = DefaultType);
	virtual std::shared_ptr<ArrayIterator<T>> create_array_iterator(int index);
	virtual std::shared_ptr<ListIterator<T>> create_list_iterator() override;
	virtual std::shared_ptr<ListIterator<T>> create_list_iterator(int index) override;
	virtual std::shared_ptr<Iterator<T>> create_iterator() override;
	virtual std::shared_ptr<ConstArrayIterator<T>> create_const_array_iterator(E_ArrayIteratorType type = DefaultType) const;
	virtual std::shared_ptr<ConstArrayIterator<T>> create_const_array_iterator(int index) const;
	virtual std::shared_ptr<ConstListIterator<T>> create_const_list_iterator() const override;
	virtual std::shared_ptr<ConstListIterator<T>> create_const_list_iterator(int index) const override;
	virtual std::shared_ptr<ConstIterator<T>> create_const_iterator() const override;

	virtual T& operator[](int index) override;
	virtual const T& operator[](int index) const override;

	static const E_ArrayIteratorType DefaultType;

private:
	int real_size_;
	int size_;
	std::shared_ptr<T[]> array_;

	LinkedList<std::weak_ptr<ArrayIterator<T>>> iterators_;

	std::function<int(const T&, const T&)>* comparator_;

	void check_real_size_();

	void quick_sort_(int left, int right);
	void insertion_sort_(int left, int right);
	int median_(int left, int right);
	int partition_(int left, int right, const T& pivot);
	void swap_(int index_1, int index_2);
};


		/* DEFINITIONS of BaseArrayIterator_ */

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::is_valid() const
{
	return BaseListIterator_<T_Container, T_Element>::is_valid() &&
		index_ >= 0 && index_ < container_.size();
}

template<typename T_Container, typename T_Element>
T_Container& BaseArrayIterator_<T_Container, T_Element>::get_container() const
{
	return container_;
}

template<typename T_Container, typename T_Element>
T_Element& BaseArrayIterator_<T_Container, T_Element>::get() const
{
	return container_[index_];
}

template<typename T_Container, typename T_Element>
int BaseArrayIterator_<T_Container, T_Element>::get_index() const
{
	return index_;
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::is_begin() const
{
	return index_ == 0;
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::is_end() const
{
	return index_ == container_.size() - 1;
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::next()
{
	if (is_end())
	{
		return false;
	}
	else
	{
		index_++;
		return true;
	}
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::prev()
{
	if (is_begin())
	{
		return false;
	}
	else
	{
		index_--;
		return true;
	}
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::operator==(const BaseIterator_<T_Container, T_Element>& iterator) const
{
	BaseArrayIterator_<T_Container, T_Element>* iter =
		dynamic_cast<BaseArrayIterator_<T_Container, T_Element>>(&iterator);
	return iter && &container_ == &iter->container_ && index_ == iter->index_;
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::operator!=(const BaseIterator_<T_Container, T_Element>& iterator) const
{
	return !(*this == iterator);
}

template<typename T_Container, typename T_Element>
BaseArrayIterator_<T_Container, T_Element>::BaseArrayIterator_(T_Container& array, int index) :
	container_(array),
	index_(index),
	is_valid_(true)
{}

		/* DEFINITIONS of Array */

template<typename T>
Array<T>::Array() :
	real_size_(5),
	size_(0),
	array_(new T[5]),
	comparator_(nullptr)
{}

template<typename T>
Array<T>::Array(const Container<T>& container) :
	real_size_(container.size()),
	size_(real_size_),
	array_(new T[container.size()]),
	comparator_(nullptr)
{
	std::shared_ptr<ConstIterator<T>> iterator = container.create_const_iterator();
	for (int i = 0; i < size_; i++, iterator->next())
	{
		array_[i] = iterator->get();
	}
}

template<typename T>
Array<T>::Array(Array<T>&& array) :
	real_size_(std::move(array.real_size_)),
	size_(std::move(array.size_)),
	array_(std::move(array.array_)),
	comparator_(nullptr)
{}

template<typename T>
Array<T>::Array(Container<T>&& container) :
	real_size_(container.size()),
	size_(real_size_),
	array_(new T[real_size_]),
	comparator_(nullptr)
{
	std::shared_ptr<Iterator<T>> iterator = container.create_iterator();
	for (int i = 0; i < size_; i++, iterator->next())
	{
		array_[i] = std::move(iterator->get());
	}
}

template<typename T>
Array<T>::Array(int size) :
	real_size_(size),
	size_(size),
	array_(new T[size]),
	comparator_(nullptr)
{}

template<typename T>
Array<T>::~Array()
{
	iterators_.for_each([](std::weak_ptr<ArrayIterator<T>>& i)
	{
		if (i.lock())
		{
			i->destroy_();
		}
	});
}

template<typename T>
int Array<T>::size() const
{
	return size_;
}

template<typename T>
void Array<T>::empty()
{
	real_size_ = 5;
	size_ = 0;
	array_.reset(new T[5]);
}

template<typename T>
bool Array<T>::add(const T& element)
{
	check_real_size_();
	array_[size_++] = element;
	return true;
}

template<typename T>
bool Array<T>::add(T&& element)
{
	check_real_size_();
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
			check_real_size_();
			for (int i = size_; i > index; i--)
			{
				array_[i] = std::move(array_[i - 1]);
			}
			array_[index] = element;
			
			if (move_iterators)
			{
				// Todo: Use LinkedListIterator
			}

			return true;
		}
	}
}

template<typename T>
bool Array<T>::add(T&& element, int index, bool move_iterators)
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
			check_real_size_();
			for (int i = size_; i > index; i--)
			{
				array_[i] = std::move(array_[i - 1]);
			}
			array_[index] = std::move(element);

			if (move_iterators)
			{
				// Todo: Use LinkedListIterator
			}

			return true;
		}
	}
}

template<typename T>
bool Array<T>::remove(int index)
{
	if (index < 0 || index >= size_)
	{
		return false;
	}
	else
	{
		if (index == size_ - 1)
		{
			size_--;
			return true;
		}
		else
		{
			size_--;
			for (int i = index; i < size_; i++)
			{
				array_[i] = std::move(array_[i + 1]);
			}
			return true;
		}
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
bool Array<T>::contains(const T& element) const
{
	return find_first(element) >= 0;
}

template<typename T>
void Array<T>::sort(std::function<int(const T&, const T&)> comparator)
{
	comparator_ = &comparator;
	quick_sort_(0, size_ - 1);
	comparator_ = nullptr;
}

template<typename T>
void Array<T>::for_each(std::function<void(T&)> f)
{
	for (int i = 0; i < size_; i++)
	{
		f(array_[i]);
	}
}

template<typename T>
void Array<T>::for_each_const(std::function<void(const T&)> f) const
{
	for (int i = 0; i < size_; i++)
	{
		f(array_[i]);
	}
}

template<typename T>
std::shared_ptr<ArrayIterator<T>> Array<T>::create_array_iterator(E_ArrayIteratorType type)
{
	switch (type)
	{
	case E_ArrayIteratorType::BEGIN:
	{
		std::shared_ptr<ArrayIterator<T>> ptr = std::make_shared<ArrayIterator<T>>(*this, 0);
		iterators_.add(std::weak_ptr(ptr));
		return ptr;
		break;
	}
	case E_ArrayIteratorType::END:
	{
		std::shared_ptr<ArrayIterator<T>> ptr = std::make_shared<ArrayIterator<T>>(*this, size() - 1);
		iterators_.add(std::weak_ptr(ptr));
		return ptr;
		break;
	}
	}
}

template<typename T>
std::shared_ptr<ArrayIterator<T>> Array<T>::create_array_iterator(int index)
{
	if (index < 0 || index >= size_)
	{
		throw std::range_error("Index is out of range");
	}
	else
	{
		std::shared_ptr<ArrayIterator<T>> ptr = std::make_shared<ArrayIterator<T>>(*this, index);
		iterators_.add(std::weak_ptr(ptr));
		return ptr;
	}
}

template<typename T>
std::shared_ptr<ListIterator<T>> Array<T>::create_list_iterator()
{
	return create_array_iterator();
}

template<typename T>
std::shared_ptr<ListIterator<T>> Array<T>::create_list_iterator(int index)
{
	return create_array_iterator(index);
}

template<typename T>
std::shared_ptr<Iterator<T>> Array<T>::create_iterator()
{
	return create_array_iterator();
}

template<typename T>
T& Array<T>::operator[](int index)
{
	if (index < 0 || index >= size_)
	{
		throw std::range_error("Index is out of range");
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
		throw std::range_error("Index is out of range");
	}
	else
	{
		return array_[index];
	}
}

template<typename T>
void Array<T>::check_real_size_()
{
	if (size_ >= real_size_)
	{
		int old_size = real_size_;
		if (real_size_ < 2)
		{
			real_size_ = 5;
		}
		else
		{
			real_size_ = static_cast<int>(real_size_ * 1.5f);
		}
		std::shared_ptr<T[]> new_ptr(new T[real_size_]);
		for (int i = 0; i < old_size; i++)
		{
			new_ptr[i] = std::move(array_[i]);
		}
		array_ = new_ptr;
	}
}

template<typename T>
void Array<T>::quick_sort_(int left, int right)
{
	if (right - left < 9)
	{
		insertion_sort_(left, right);
	}
	else
	{
		int median = median_(left, right);
		int part = partition_(left, right, array_[median]);
		quick_sort_(left, part - 1);
		quick_sort_(part + 1, right);
	}
}

template<typename T>
void Array<T>::insertion_sort_(int left, int right)
{
	for (int i = left + 1; i <= right; i++)
	{
		T tmp = array_[i];
		int j;
		for (j = i; j > left && (*comparator_)(array_[j - 1], tmp) >= 0; j--)
		{
			array_[j] = array_[j - 1];
		}
		array_[j] = tmp;
	}
}

template<typename T>
int Array<T>::median_(int left, int right)
{
	int centre = (left + right) / 2;

	if ((*comparator_)(array_[left], array_[centre]) > 0)
	{
		swap_(left, centre);
	}
	if ((*comparator_)(array_[left], array_[right]) > 0)
	{
		swap_(left, right);
	}
	if ((*comparator_)(array_[centre], array_[right]) > 0)
	{
		swap_(centre, right);
	}

	swap_(centre, right - 1);
	return right - 1;
}

template<typename T>
int Array<T>::partition_(int left, int right, const T& pivot)
{
	int left_ptr = left;
	int right_ptr = right - 1;
	while (true)
	{
		while ((*comparator_)(array_[++left_ptr], pivot) < 0)
			;
		while ((*comparator_)(array_[--right_ptr], pivot) > 0)
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
void Array<T>::swap_(int index_1, int index_2)
{
	T tmp = array_[index_2];
	array_[index_2] = std::move(array_[index_1]);
	array_[index_1] = std::move(tmp);
}

template<typename T>
const E_ArrayIteratorType Array<T>::DefaultType = E_ArrayIteratorType::BEGIN;

}
