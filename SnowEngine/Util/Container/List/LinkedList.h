    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Array.h                     //
////////////////////////////////////////

#pragma once

#include "List.h"

namespace snow
{

template<typename T>
class LinkedList;

enum class E_LinkedListIteratorType
{
	BEGIN = 0,
	END
};

namespace
{

template<typename T>
struct LinkedListNode_
{
public:
	T value;
	std::weak_ptr<LinkedListNode_<T>> prev;
	std::shared_ptr<LinkedListNode_<T>> next;
};

template<typename T_Container, typename T_Element>
class BaseLinkedListIterator_ : public BaseListIterator_<T_Container, T_Element>
{
	template<typename T>
	friend class LinkedList;

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
	BaseLinkedListIterator_(T_Container& linked_list, int index);
	T_Container& container_;
	std::weak_ptr<LinkedListNode_<T_Element>> node_;
};

}

template<typename T>
using ConstLinkedListIterator = BaseLinkedListIterator_<const LinkedList<T>, const T>;

template<typename T>
using LinkedListIterator = BaseLinkedListIterator_<LinkedList<T>, T>;

template<typename T>
class LinkedList : public List<T>
{
	template<typename T_Container, typename T_Element>
	friend class BaseLinkedListIterator_;
	
public:
	LinkedList();
	LinkedList(const Container<T>& container);
	LinkedList(LinkedList<T>&& array);
	LinkedList(Container<T>&& container);
	~LinkedList();

	virtual int size() const override;
	virtual void empty() override;

	virtual T& get_begin();
	virtual T& get_end();
	virtual const T& get_begin() const;
	virtual const T& get_end() const;

	virtual bool add(const T& element) override;
	virtual bool add(T&& element) override;
	virtual bool add(const T& element, int index) override;
	virtual bool add(T&& element, int index) override;
	virtual bool add_after(const T& element, std::shared_ptr<LinkedListIterator<T>> iterator);
	virtual bool add_after(T&& element, std::shared_ptr<LinkedListIterator<T>> iterator);
	virtual bool add_begin(const T& element);
	virtual bool add_begin(T&& element);

	virtual bool remove(int index) override;
	virtual bool remove(std::shared_ptr<Iterator<T>> iterator) override;
	virtual bool remove(std::shared_ptr<ListIterator<T>> iterator) override;
	virtual bool remove(std::shared_ptr<LinkedListIterator<T>> iterator);
	virtual bool remove_first(const T& element) override;
	virtual bool remove_last(const T& element) override;
	virtual int remove_all(const T& element) override;

	virtual int find_first(const T& element) const override;
	virtual int find_last(const T& element) const override;
	virtual LinkedList<int> find_all(const T& element) const override;

	virtual void sort(std::function<int(const T&, const T&)> comparator) override;

	virtual void for_each(std::function<void(T&)> f) override;
	virtual void for_each_const(std::function<void(const T&)> f) const override;

	virtual std::shared_ptr<LinkedListIterator<T>> create_linked_list_iterator(E_LinkedListIteratorType type = DefaultType);
	virtual std::shared_ptr<LinkedListIterator<T>> create_linked_list_iterator(int index);
	virtual std::shared_ptr<ListIterator<T>> create_list_iterator() override;
	virtual std::shared_ptr<ListIterator<T>> create_list_iterator(int index) override;
	virtual std::shared_ptr<Iterator<T>> create_iterator() override;
	virtual std::shared_ptr<ConstLinkedListIterator<T>> create_const_linked_list_iterator(E_LinkedListIteratorType type = DefaultType) const;
	virtual std::shared_ptr<ConstLinkedListIterator<T>> create_const_linkrd_list_iterator(int index) const;
	virtual std::shared_ptr<ConstListIterator<T>> create_const_list_iterator() const override;
	virtual std::shared_ptr<ConstListIterator<T>> create_const_list_iterator(int index) const override;
	virtual std::shared_ptr<ConstIterator<T>> create_const_iterator() const override;
	
	virtual std::shared_ptr<LinkedListIterator<T>> find_first_by_iterator(const T& element);
	virtual std::shared_ptr<LinkedListIterator<T>> find_last_by_iterator(const T& element);
	virtual std::shared_ptr<ConstLinkedListIterator<T>> find_first_by_const_iterator(const T& element) const;
	virtual std::shared_ptr<ConstLinkedListIterator<T>> find_last_by_const_iterator(const T& element) const;

	virtual T& operator[](int index) override;
	virtual const T& operator[](int index) const override;

	static const E_LinkedListIteratorType DefaultType;

private:
	std::shared_ptr<LinkedListNode_<T>> begin_;
	std::shared_ptr<LinkedListNode_<T>> end_;
	int size_;

	LinkedList<std::weak_ptr<LinkedListIterator<T>>> iterators_;
	mutable LinkedList<std::weak_ptr<ConstLinkedListIterator<T>>> const_iterators_;

	std::function<int(const T&, const T&)>* comparator_;

	int get_index_of_node_(std::shared_ptr<LinkedListNode_<T>> node) const;

	void quick_sort_(int left, int right);
	void insertion_sort_(int left, int right);
	int median_(int left, int right);
	int partition_(int left, int right, const T& pivot);
	void swap_(int index_1, int index_2);
};


		/* DEFINITIONS of BaseLinkedListIterator_ */

template<typename T_Container, typename T_Element>
bool BaseLinkedListIterator_<T_Container, T_Element>::is_valid() const
{
	return BaseListIterator_<T_Container, T_Element>::is_valid() && node_.lock();
}

template<typename T_Container, typename T_Element>
T_Container& BaseLinkedListIterator_<T_Container, T_Element>::get_container() const
{
	return container_;
}

template<typename T_Container, typename T_Element>
T_Element& BaseLinkedListIterator_<T_Container, T_Element>::get() const
{
	return node_->value;
}

template<typename T_Container, typename T_Element>
int BaseLinkedListIterator_<T_Container, T_Element>::get_index() const
{
	return container_.get_index_of_node_(node_.lock());
}

template<typename T_Container, typename T_Element>
bool BaseLinkedListIterator_<T_Container, T_Element>::is_begin() const
{
	return is_valid() && !node_.prev;
}

template<typename T_Container, typename T_Element>
bool BaseLinkedListIterator_<T_Container, T_Element>::is_end() const
{
	return is_valid() && !node_.next;
}

template<typename T_Container, typename T_Element>
bool BaseLinkedListIterator_<T_Container, T_Element>::next()
{
	if (is_end())
	{
		return false;
	}
	else
	{
		node_ = node_->next;
		return true;
	}
}

template<typename T_Container, typename T_Element>
bool BaseLinkedListIterator_<T_Container, T_Element>::prev()
{
	if (is_begin())
	{
		return false;
	}
	else
	{
		node_ = node_->prev;
		return true;
	}
}

template<typename T_Container, typename T_Element>
bool BaseLinkedListIterator_<T_Container, T_Element>::operator==(const BaseIterator_<T_Container, T_Element>& iterator) const
{
	BaseLinkedListIterator_<T_Container, T_Element>* iter =
		dynamic_cast<BaseLinkedListIterator_<T_Container, T_Element>>(&iterator);
	return iter && node_ == iter->node_;
}

template<typename T_Container, typename T_Element>
bool BaseLinkedListIterator_<T_Container, T_Element>::operator!=(const BaseIterator_<T_Container, T_Element>& iterator) const
{
	return !(*this == iterator);
}
/*
template<typename T_Container, typename T_Element>
BaseArrayIterator_<T_Container, T_Element>::BaseArrayIterator_(T_Container& array, int index) :
	container_(array),
	index_(index),
	is_valid_(true)
{}*/

		/* DEFINITIONS of LinkedList */
/*
template<typename T>
LinkedList<T>::LinkedList() :
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
			size_++;
			
			add_move_iterators_(index);

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
			size_++;
			
			add_move_iterators_(index);

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
			
			remove_move_iterators_(index);
			
			return true;
		}
	}
}

template<typename T>
bool Array<T>::remove(std::shared_ptr<Iterator> iterator)
{
	std::shared_ptr<ArrayIterator> iter = std::dynamic_pointer_cast<ArrayIterator>(iterator);
	if (iter && &iter->get_container() == this)
	{
		return remove(iter->get_index());
	}
	else
	{
		return false;
	}
}

template<typename T>
bool Array<T>::remove(std::shared_ptr<ListIterator> iterator)
{
	std::shared_ptr<ArrayIterator> iter = std::dynamic_pointer_cast<ArrayIterator>(iterator);
	if (iter && &iter->get_container() == this)
	{
		return remove(iter->get_index());
	}
	else
	{
		return false;
	}
}

template<typename T>
bool Array<T>::remove(std::shared_ptr<ArrayIterator> iterator)
{
	if (iterator && &iterator->get_container() == this)
	{
		return remove(iterator->get_index());
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
	int counter = 0;
	for (int i = 0; i < size_; i++)
	{
		if (array_[i] == element)
		{
			remove(i);
			counter++;
		}
	}
	return counter;
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
std::shared_ptr<ConstArrayIterator<T>> Array<T>::create_const_array_iterator(E_ArrayIteratorType type) const
{
	switch (type)
	{
	case E_ArrayIteratorType::BEGIN:
	{
		std::shared_ptr<ConstArrayIterator<T>> ptr = std::make_shared<ConstArrayIterator<T>>(*this, 0);
		const_iterators_.add(std::weak_ptr(ptr));
		return ptr;
		break;
	}
	case E_ArrayIteratorType::END:
	{
		std::shared_ptr<ConstArrayIterator<T>> ptr = std::make_shared<ConstArrayIterator<T>>(*this, size() - 1);
		const_iterators_.add(std::weak_ptr(ptr));
		return ptr;
		break;
	}
	}
}

template<typename T>
std::shared_ptr<ConstArrayIterator<T>> Array<T>::create_const_array_iterator(int index) const
{
	if (index < 0 || index >= size_)
	{
		throw std::range_error("Index is out of range");
	}
	else
	{
		std::shared_ptr<ConstArrayIterator<T>> ptr = std::make_shared<ConstArrayIterator<T>>(*this, index);
		const_iterators_.add(std::weak_ptr(ptr));
		return ptr;
	}
}

template<typename T>
std::shared_ptr<ConstListIterator<T>> Array<T>::create_const_list_iterator() const
{
	return create_const_array_iterator();
}

template<typename T>
std::shared_ptr<ConstListIterator<T>> Array<T>::create_const_list_iterator(int index) const
{
	return create_const_array_iterator(index);
}

template<typename T>
std::shared_ptr<ConstIterator<T>> Array<T>::create_const_iterator() const
{
	return create_const_array_iterator();
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
*/
}
