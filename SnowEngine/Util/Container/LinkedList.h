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
	template<typename T_Container, typename T_Element, typename T_Node>
	friend class BaseLinkedListIterator_;

public:
	LinkedList();
	LinkedList(const LinkedList<T>& linked_list);
	LinkedList(LinkedList<T>&& linked_list);
	~LinkedList();

	virtual const std::string to_string() const override;
	virtual int hash_code() const override;

	virtual int size() const override;
	virtual bool is_empty() const override;
	virtual void clear() override;

	T& get_begin();
	T& get_last();
	const T& get_begin() const;
	const T& get_last() const;

	virtual bool add(const T& element);
	virtual bool add(T&& element);
	virtual bool add(const T& element, int index);
	virtual bool add(T&& element, int index);
	virtual int add(const LinkedList<T>& list);
	virtual int add(LinkedList<T>&& list);
	virtual bool add_before(const T& element, const LinkedListIterator<T>& iterator);
	virtual bool add_before(T&& element, const LinkedListIterator<T>& iterator);
	virtual bool add_before(const T& element, const ConstLinkedListIterator<T>& iterator);
	virtual bool add_before(T&& element, const ConstLinkedListIterator<T>& iterator);
	virtual bool add_to_begin(const T& element);
	virtual bool add_to_begin(T&& element);

	virtual bool remove(int index);
	virtual bool remove(const LinkedListIterator<T>& element);
	virtual bool remove(const ConstLinkedListIterator<T>& element);
	virtual int remove(int from, int to);
	virtual int remove(const LinkedListIterator<T>& from, const LinkedListIterator<T>& to);
	virtual int remove(const ConstLinkedListIterator<T>& from, const ConstLinkedListIterator<T>& to);
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

	LinkedListIterator<T> begin();
	LinkedListIterator<T> last();
	LinkedListIterator<T> end();
	LinkedListIterator<T> create_iterator(int index);
	ConstLinkedListIterator<T> begin() const;
	ConstLinkedListIterator<T> last() const;
	ConstLinkedListIterator<T> end() const;
	ConstLinkedListIterator<T> create_iterator(int index) const;

	virtual LinkedList<T>& operator=(const LinkedList<T>& linked_list);
	virtual LinkedList<T>& operator=(LinkedList<T>&& linked_list);

	bool operator==(const LinkedList<T>& linked_list) const;
	bool operator!=(const LinkedList<T>& linked_list) const;

	T& operator[](int index);
	const T& operator[](int index) const;

	static ConstLinkedListIterator<T> iterator_to_const(const LinkedListIterator<T> iterator);

private:
	std::shared_ptr<LinkedListNode_<T>> begin_;
	std::shared_ptr<LinkedListNode_<T>> end_;
	int size_;

	std::shared_ptr<LinkedListNode_<T>> get_last_node_() const;

	mutable std::list<LinkedListIterator<T>*> iterators_;
	mutable std::list<ConstLinkedListIterator<T>*> const_iterators_;
	void register_iterator_(LinkedListIterator<T>* iterator);
	void unregister_iterator_(LinkedListIterator<T>* iterator);
	void register_iterator_(ConstLinkedListIterator<T>* iterator) const;
	void unregister_iterator_(ConstLinkedListIterator<T>* iterator) const;
	void clear_iterators_() const;
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
	size_(std::move(linked_list.size_)),
	iterators_(std::move(linked_list.iterators_)),
	const_iterators_(std::move(linked_list.const_iterators_))
{}

template<typename T>
LinkedList<T>::~LinkedList()
{
	clear_iterators_();
}

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
		for (auto p = begin(); !p.is_last(); p.next())
		{
			str += p.to_string() + ", ";
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
	clear_iterators_();
	begin_.reset();
	end_.reset();
	size_ = 0;
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

		for (auto i : iterators_)
		{
			if (i->index_ >= size_)
			{
				i->index_ += ret;
			}
		}
		for (auto i : const_iterators_)
		{
			if (i->index_ >= size_)
			{
				i->index_ += ret;
			}
		}

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

	for (auto i : iterators_)
	{
		i->index_++;
	}
	for (auto i : const_iterators_)
	{
		i->index_++;
	}

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

	for (auto i : iterators_)
	{
		i->index_++;
	}
	for (auto i : const_iterators_)
	{
		i->index_++;
	}

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

		for (auto i : iterators_)
		{
			if (i->index_ > index)
			{
				i->index_--;
			}
		}
		for (auto i : const_iterators_)
		{
			if (i->index_ > index)
			{
				i->index_--;
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
		
		for (auto i : iterators_)
		{
			if (i->index_ > from_index && i->index_ < to_index)
			{
				i->index_ = from_index;
			}
			else if (i->index_ >= to_index)
			{
				i->index_ -= to_index - from_index;
			}
		}
		for (auto i : const_iterators_)
		{
			if (i->index_ > from_index && i->index_ < to_index)
			{
				i->index_ = from_index;
			}
			else if (i->index_ >= to_index)
			{
				i->index_ -= to_index - from_index;
			}
		}
		
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
	iterators_ = std::move(linked_list.iterators_);
	const_iterators_ = std::move(linked_list.const_iterators_);
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
		throw std::out_of_range("Index is out of linked list bounds");
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
		throw std::out_of_range("Index is out of linked list bounds");
	}

	std::shared_ptr<LinkedListNode_<T>> ptr = begin_;
	for (int i = 0; i < index; i++)
	{
		ptr = ptr->next;
	}
	return ptr->value;
}

template<typename T>
ConstLinkedListIterator<T> LinkedList<T>::iterator_to_const(const LinkedListIterator<T> iterator)
{
	return ConstLinkedListIterator<T>(iterator.container_, iterator.index_, iterator.node_.lock(), iterator.is_valid_);
}

template<typename T>
std::shared_ptr<LinkedListNode_<T>> LinkedList<T>::get_last_node_() const
{
	return end_;
}

template<typename T>
void LinkedList<T>::register_iterator_(LinkedListIterator<T>* iterator)
{
	iterators_.push_back(iterator);
}

template<typename T>
void LinkedList<T>::unregister_iterator_(LinkedListIterator<T>* iterator)
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
void LinkedList<T>::register_iterator_(ConstLinkedListIterator<T>* iterator) const
{
	const_iterators_.push_back(iterator);
}

template<typename T>
void LinkedList<T>::unregister_iterator_(ConstLinkedListIterator<T>* iterator) const
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
void LinkedList<T>::clear_iterators_() const
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

}
