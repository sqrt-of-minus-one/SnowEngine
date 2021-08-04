    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: LinkedList.h                //
////////////////////////////////////////

#pragma once

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
	LinkedListNode_(const LinkedListNode_<T>&) = default;
	LinkedListNode_(LinkedListNode_<T>&&) = default;
	LinkedListNode_(const T& val);
	LinkedListNode_(T&& val);

	T value;
	std::weak_ptr<LinkedListNode_<T>> prev;
	std::shared_ptr<LinkedListNode_<T>> next;
};

}

template<typename T>
class LinkedList :
	public Object,
	public IContainer<T>
{
	template<typename T>
	friend class LinkedListIterator;

	template<typename T>
	friend class ConstLinkedListIterator;

public:
	LinkedList();
	LinkedList(const LinkedList<T>& linked_list);
	LinkedList(LinkedList<T>&& linked_list);

	virtual const std::string to_string() const override;
	virtual int hash_code() const override;

	virtual int size() const override;
	virtual bool is_empty() const override;
	virtual void clear() override;

	virtual T& get_begin();
	virtual T& get_last();
	virtual const T& get_begin() const;
	virtual const T& get_last() const;

	virtual bool add(const T& element) override;
	virtual bool add(T&& element) override;
	virtual bool add(const T& element, int index);
	virtual bool add(T&& element, int index);
	virtual bool add_after(const T& element, const ConstLinkedListIterator<T>& iterator);
	virtual bool add_after(T&& element, const ConstLinkedListIterator<T>& iterator);
	virtual bool add_to_begin(const T& element);
	virtual bool add_to_begin(T&& element);

	virtual bool remove(int index);
	virtual bool remove(const ConstLinkedListIterator<T>& element);
	virtual bool remove(int from, int to);
	virtual bool remove(const ConstLinkedListIterator<T>& from, const ConstLinkedListIterator<T>& to);
	virtual bool remove_first(const T& element);
	virtual bool remove_last(const T& element);
	virtual int remove_all(const T& element) override;

	virtual int find_first_by_index(const T& element) const;
	virtual int find_last_by_index(const T& element) const;
	virtual LinkedList<int> find_all(const T& element) const;
	virtual LinkedListIterator<T> find_first_by_iterator(const T& element);
	virtual LinkedListIterator<T> find_last_by_iterator(const T& element);
	virtual ConstLinkedListIterator<T> find_first_by_iterator(const T& element) const;
	virtual ConstLinkedListIterator<T> find_last_by_iterator(const T& element) const;

	virtual bool contains(const T& element) const override;
	virtual int count(const T& element) const override;

	virtual LinkedListIterator<T> begin();
	virtual LinkedListIterator<T> last();
	virtual LinkedListIterator<T> end();
	virtual LinkedListIterator<T> create_iterator(int index);
	virtual ConstLinkedListIterator<T> begin() const;
	virtual ConstLinkedListIterator<T> last() const;
	virtual ConstLinkedListIterator<T> end() const;
	virtual ConstLinkedListIterator<T> create_iterator(int index) const;

	virtual LinkedList<T>& operator=(const LinkedList<T>& linked_list);
	virtual LinkedList<T>& operator=(LinkedList<T>&& linked_list);

	virtual bool operator==(const LinkedList<T>& linked_list) const;
	virtual bool operator!=(const LinkedList<T>& linked_list) const;

	virtual T& operator[](int index);
	virtual const T& operator[](int index) const;

private:
	std::shared_ptr<LinkedListNode_<T>> begin_;
	std::shared_ptr<LinkedListNode_<T>> end_;
	int size_;

	mutable std::list<BaseLinkedListIterator_*> iterators_;
	void register_iterator_(BaseLinkedListIterator_* iterator) const;
	void unregister_iterator_(BaseLinkedListIterator_* iterator) const;
};


		/* DEFINITIONS of LinkedListNode_ */

template<typename T>
LinkedListNode_<T>::LinkedListNode_(const T& val) :
	value(val),
	prev(),
	next()
{}

template<typename T>
LinkedListNode_<T>::LinkedListNode_(T&& val) :
	value(std::move(val)),
	prev(),
	next()
{}

		/* DEFINITIONS of LinkedList */

template<typename T>
LinkedList<T>::LinkedList() :
	begin_(nullptr),
	end_(nullptr),
	size_(0)
{}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& linked_list) :
	LinkedList()
{
	for (const T& i : linked_list)
	{
		add(i);
	}
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& linked_list) :
	begin_(std::move(linked_list.begin_)),
	end_(std::move(linked_list.end_)),
	size_(std::move(linked_list.size_))
{}

template<typename T>
const std::string LinkedList<T>::to_string() const
{
	if (is_empty())
	{
		return "{ }";
	}
	else
	{
		std::string str = "{ ";
		ConstLinkedListIterator<T> p = begin();
		for ( ; !p.is_end(); p++)
		{
			str += util::to_string(*p) + ", ";
		}
		return str + util::to_string(get_last()) + " }";
	}
}

template<typename T>
int LinkedList<T>::hash_code() const
{
	if (is_empty())
	{
		return 0;
	}
	else
	{
		int hash = 0, o = 1;
		for (const T& i : *this)
		{
			hash += o * util::hash_code(i);
			o = -o;
		}
		return hash;
	}
}

template<typename T>
int LinkedList<T>::size() const
{
	return size_;
}

template<typename T>
bool LinkedList<T>::is_empty() const
{
	return size_ == 0;
}

template<typename T>
void LinkedList<T>::clear()
{
	begin_.reset();
	end_.reset();
	size_ = 0;
}

template<typename T>
T& LinkedList<T>::get_begin()
{
	if (is_empty())
	{
		throw std::range_error("Attempt to access an element of empty linked list");
	}
	return begin_->value;
}

template<typename T>
T& LinkedList<T>::get_last()
{
	if (is_empty())
	{
		throw std::range_error("Attempt to access an element of empty linked list");
	}
	return end_->value;
}

template<typename T>
const T& LinkedList<T>::get_begin() const
{
	if (size_ <= 0)
	{
		throw std::range_error("Attempt to access an element of empty linked list");
	}
	return begin_->value;
}

template<typename T>
const T& LinkedList<T>::get_last() const
{
	if (size_ <= 0)
	{
		throw std::range_error("Attempt to access an element of empty linked list");
	}
	return end_->value;
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
	size_++;
	return true;
}

template<typename T>
bool LinkedList<T>::add(const T& element, int index)
{
	if (index == 0)
	{
		return add_to_begin(element);
	}
	else
	{
		return add_after(element, create_iterator(index - 1));
	}
}

template<typename T>
bool LinkedList<T>::add(T&& element, int index)
{
	if (index == 0)
	{
		return add_to_begin(std::forward<T>(element));
	}
	else
	{
		return add_after(std::forward<T>(element), create_iterator(index - 1));
	}
}

template<typename T>
bool LinkedList<T>::add_after(const T& element, const ConstLinkedListIterator<T>& iterator)
{
	std::shared_ptr<LinkedListNode_<T>> node = iterator.node_.lock();
	if (iterator.is_valid() && &iterator.get_container() == this && node)
	{
		std::shared_ptr<LinkedListNode_<T>> ptr = std::make_shared<LinkedListNode_<T>>(element);
		ptr->prev = node;
		ptr->next = node->next;
		if (node->next)
		{
			node->next->prev = ptr;
		}
		node->next = ptr;
		size_++;
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
bool LinkedList<T>::add_after(T&& element, const ConstLinkedListIterator<T>& iterator)
{
	std::shared_ptr<LinkedListNode_<T>> node = iterator.node_.lock();
	if (iterator.is_valid() && &iterator.get_container() == this && node)
	{
		std::shared_ptr<LinkedListNode_<T>> ptr = std::make_shared<LinkedListNode_<T>>(std::move(element));
		ptr->prev = iterator.node_;
		ptr->next = node->next;
		if (node->next)
		{
			node->next->prev = ptr;
		}
		node->next = ptr;
		size_++;
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
bool LinkedList<T>::add_to_begin(const T& element)
{
	std::shared_ptr<LinkedListNode_<T>> ptr = std::make_shared<LinkedListNode_<T>>(element);
	ptr->next = begin_;
	begin_->prev = ptr;
	begin_ = ptr;
	size_++;
	return true;
}

template<typename T>
bool LinkedList<T>::add_to_begin(T&& element)
{
	std::shared_ptr<LinkedListNode_<T>> ptr = std::make_shared<LinkedListNode_<T>>(std::move(element));
	ptr->next = begin_;
	begin_->prev = ptr;
	begin_ = ptr;
	size_++;
	return true;
}

template<typename T>
bool LinkedList<T>::remove(int index)
{
	return remove(create_iterator(index));
}

template<typename T>
bool LinkedList<T>::remove(const ConstLinkedListIterator<T>& element)
{
	std::shared_ptr<LinkedListNode_<T>> node = element.node_.lock();
	if (element.is_valid() && &element.get_container() == this)
	{
		if (node->prev.lock())
		{
			node->prev.lock()->next = node->next;
		}
		if (node->next)
		{
			node->next->prev = node->prev;
		}
		if (element.is_begin())
		{
			begin_ = node->next;
		}
		if (element.is_last())
		{
			end_ = node->prev.lock();
		}
		size_--;
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
bool LinkedList<T>::remove(int from, int to)
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
bool LinkedList<T>::remove(const ConstLinkedListIterator<T>& from, const ConstLinkedListIterator<T>& to)
{
	if (&from.get_container() == this && &to.get_container() == this && from.get_index() < to.get_index())
	{
		std::shared_ptr<LinkedListNode_<T>> from_node = from.node_.lock();
		std::shared_ptr<LinkedListNode_<T>> to_node = (--ConstLinkedListIterator<T>(to)).node_.lock();

		if (from_node->prev.lock())
		{
			from_node->prev.lock()->next = to_node->next;
		}
		if (to_node->next)
		{
			to_node->next->prev = from_node->prev;
		}
		if (from.is_begin())
		{
			begin_ = to_node->next;
		}
		if (to.is_end())
		{
			end_ = from_node->prev.lock();
		}
		size_--;
		return true;
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
	int result = 0;
	for (std::shared_ptr<LinkedListNode_<T>> i = begin_; i; i = i->next)
	{
		if (i->value == element)
		{
			if (i->prev.lock())
			{
				i->prev.lock()->next = i->next;
			}
			else
			{
				begin_ = i->next;
			}
			if (i->next)
			{
				i->next->prev = i->prev;
			}
			else
			{
				end_ = i->prev.lock();
			}
			size_--;
			result++;
		}
	}
	return result;
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
LinkedList<int> LinkedList<T>::find_all(const T& element) const
{
	LinkedList<int> result;
	int index = 0;
	for (std::shared_ptr<LinkedListNode_<T>> i = begin_; i; i = i->next, index++)
	{
		if (i->value == element)
		{
			result.add(index);
		}
	}
	return result;
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
LinkedListIterator<T> LinkedList<T>::begin()
{
	return LinkedListIterator<T>(*this, 0, begin_);
}

template<typename T>
LinkedListIterator<T> LinkedList<T>::last()
{
	return LinkedListIterator<T>(*this, size_ - 1, end_);
}

template<typename T>
LinkedListIterator<T> LinkedList<T>::end()
{
	return LinkedListIterator<T>(*this, size_);
}

template<typename T>
LinkedListIterator<T> LinkedList<T>::create_iterator(int index)
{
	if (index < 0 || index >= size_)
	{
		throw std::range_error("Index is out of linked list bounds");
	}

	std::shared_ptr<LinkedListNode_<T>> ptr = begin_;
	for (int i = 0; i < index; i++)
	{
		ptr = ptr->next;
	}
	return LinkedListIterator<T>(*this, index, ptr);
}

template<typename T>
ConstLinkedListIterator<T> LinkedList<T>::begin() const
{
	return ConstLinkedListIterator<T>(*this, 0, begin_);
}

template<typename T>
ConstLinkedListIterator<T> LinkedList<T>::last() const
{
	return ConstLinkedListIterator<T>(*this, size_ - 1, end_);
}

template<typename T>
ConstLinkedListIterator<T> LinkedList<T>::end() const
{
	return ConstLinkedListIterator<T>(*this, size_);
}

template<typename T>
ConstLinkedListIterator<T> LinkedList<T>::create_iterator(int index) const
{
	if (index < 0 || index >= size_)
	{
		throw std::range_error("Index is out of linked list bounds");
	}

	std::shared_ptr<LinkedListNode_<T>> ptr = begin_;
	for (int i = 0; i < index; i++)
	{
		ptr = ptr->next;
	}
	return ConstLinkedListIterator<T>(*this, index, ptr);
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
		ConstLinkedListIterator<T> this_iter = begin();
		ConstLinkedListIterator<T> other_iter = linked_list.end();
		do 
		{
			if (this_iter.get() != other_iter.get())
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
	if (index < 0 || index >= size_)
	{
		throw std::range_error("Index is out of linked list bounds");
	}

	std::shared_ptr<LinkedListNode_<T>> ptr = begin_;
	for (int i = 0; i < index; i++)
	{
		ptr = ptr->next;
	}
	return ptr->value;
}

template<typename T>
const T& LinkedList<T>::operator[](int index) const
{
	if (index < 0 || index >= size_)
	{
		throw std::range_error("Index is out of linked list bounds");
	}

	std::shared_ptr<LinkedListNode_<T>> ptr = begin_;
	for (int i = 0; i < index; i++)
	{
		ptr = ptr->next;
	}
	return ptr->value;
}

template<typename T>
void LinkedList<T>::register_iterator_(BaseLinkedListIterator_* iterator) const
{
	iterators_.push_back(iterator);
}

template<typename T>
void LinkedList<T>::unregister_iterator_(BaseLinkedListIterator_* iterator) const
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

}
