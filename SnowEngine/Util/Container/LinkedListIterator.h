    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: LinkedListIterator.h        //
////////////////////////////////////////

#pragma once

#include "../../Object.h"
#include "Container.h"
#include "../Util.h"

namespace snow
{

template<typename T>
class LinkedList;

namespace
{

template<typename T>
struct LinkedListNode_;

class BaseLinkedListIterator_ :
	public Object,
	public IIterator
{
public:
	int get_index() const;

protected:
	BaseLinkedListIterator_(int index, bool is_valid);

	int index_;
	bool is_valid_;

	void move_index_(int delta_index);
};

}

template<typename T>
class ConstLinkedListIterator : public BaseLinkedListIterator_
{
	template<typename T>
	friend class LinkedList;

public:
	ConstLinkedListIterator(const ConstLinkedListIterator<T>& iterator);
	ConstLinkedListIterator(ConstLinkedListIterator<T>&& iterator);

	virtual const std::string to_string() const override;
	virtual int hash_code() const override;

	virtual bool is_valid() const override;

	const LinkedList<T>& get_container() const;
	const T& get() const;

	virtual bool is_begin() const override;
	virtual bool is_last() const override;
	virtual bool is_end() const override;
	virtual bool next() override;
	virtual bool prev() override;

	const T& operator*() const;
	ConstLinkedListIterator<T> operator++();
	ConstLinkedListIterator<T> operator--();
	ConstLinkedListIterator<T> operator++(int);
	ConstLinkedListIterator<T> operator--(int);

	bool operator==(const ConstLinkedListIterator<T>& iterator) const;
	bool operator!=(const ConstLinkedListIterator<T>& iterator) const;
	
private:
	ConstLinkedListIterator(const LinkedList<T>& linked_list, int index, std::shared_ptr<LinkedListNode_<T>> node = nullptr);

	const LinkedList<T>& container_;
	std::weak_ptr<LinkedListNode_<T>> node_;
};

template<typename T>
class LinkedListIterator : public BaseLinkedListIterator_
{
	template<typename T>
	friend class LinkedList;

public:
	LinkedListIterator(const LinkedListIterator<T>& iterator);
	LinkedListIterator(LinkedListIterator<T>&& iterator);

	virtual const std::string to_string() const override;
	virtual int hash_code() const override;

	virtual bool is_valid() const override;

	LinkedList<T>& get_container() const;
	T& get() const;

	virtual bool is_begin() const override;
	virtual bool is_last() const override;
	virtual bool is_end() const override;
	virtual bool next() override;
	virtual bool prev() override;

	T& operator*() const;
	LinkedListIterator<T> operator++();
	LinkedListIterator<T> operator--();
	LinkedListIterator<T> operator++(int);
	LinkedListIterator<T> operator--(int);

	bool operator==(const LinkedListIterator<T>& iterator) const;
	bool operator!=(const LinkedListIterator<T>& iterator) const;

	operator ConstLinkedListIterator<T>() const;

private:
	LinkedListIterator(LinkedList<T>& linked_list, int index, std::shared_ptr<LinkedListNode_<T>> node = nullptr);

	LinkedList<T>& container_;
	std::weak_ptr<LinkedListNode_<T>> node_;
};


		/* DEFINITIONS of BaseLinkedListIterator_ */

int BaseLinkedListIterator_::get_index() const
{
	return index_;
}

void BaseLinkedListIterator_::move_index_(int delta_index)
{
	index_ += delta_index;
}

BaseLinkedListIterator_::BaseLinkedListIterator_(int index, bool is_valid) :
	index_(index),
	is_valid_(is_valid)
{}

		/* DEFINITIONS of ConstLinkedListIterator */

template<typename T>
ConstLinkedListIterator<T>::ConstLinkedListIterator(const ConstLinkedListIterator<T>& iterator) :
	container_(iterator.container_),
	node_(iterator.node_),
	BaseLinkedListIterator_(iterator.index_, iterator.is_valid_)
{}

template<typename T>
ConstLinkedListIterator<T>::ConstLinkedListIterator(ConstLinkedListIterator<T>&& iterator) :
	container_(iterator.container_),
	node_(std::move(iterator.node_)),
	BaseLinkedListIterator_(std::move(iterator.index_), std::move(iterator.is_valid_))
{}

template<typename T>
const std::string ConstLinkedListIterator<T>::to_string() const
{
	return util::to_string(get());
}

template<typename T>
int ConstLinkedListIterator<T>::hash_code() const
{
	return util::hash_code(get());
}

template<typename T>
bool ConstLinkedListIterator<T>::is_valid() const
{
	return is_valid_ && node_.lock();
}

template<typename T>
const LinkedList<T>& ConstLinkedListIterator<T>::get_container() const
{
	return container_;
}

template<typename T>
const T& ConstLinkedListIterator<T>::get() const
{
	return node_.lock()->value;
}

template<typename T>
bool ConstLinkedListIterator<T>::is_begin() const
{
	return index_ == 0;
}

template<typename T>
bool ConstLinkedListIterator<T>::is_last() const
{
	return index_ == container_.size() - 1;
}

template<typename T>
bool ConstLinkedListIterator<T>::is_end() const
{
	return index_ == container_.size();
}

template<typename T>
bool ConstLinkedListIterator<T>::next()
{
	if (is_end())
	{
		return false;
	}
	else
	{
		node_ = node_.lock()->next;
		index_++;
		return !is_end();
	}
}

template<typename T>
bool ConstLinkedListIterator<T>::prev()
{
	if (is_begin())
	{
		return false;
	}
	else
	{
		node_ = node_.lock()->prev;
		index_--;
		return true;
	}
}

template<typename T>
const T& ConstLinkedListIterator<T>::operator*() const
{
	return get();
}

template<typename T>
ConstLinkedListIterator<T> ConstLinkedListIterator<T>::operator++()
{
	next();
	return *this;
}

template<typename T>
ConstLinkedListIterator<T> ConstLinkedListIterator<T>::operator--()
{
	prev();
	return *this;
}

template<typename T>
ConstLinkedListIterator<T> ConstLinkedListIterator<T>::operator++(int)
{
	ConstLinkedListIterator<T> ret = *this;
	next();
	return ret;
}

template<typename T>
ConstLinkedListIterator<T> ConstLinkedListIterator<T>::operator--(int)
{
	ConstLinkedListIterator<T> ret = *this;
	prev();
	return ret;
}

template<typename T>
bool ConstLinkedListIterator<T>::operator==(const ConstLinkedListIterator<T>& iterator) const
{
	return &container_ == &iterator.container_ && index_ == iterator.index_;
}

template<typename T>
bool ConstLinkedListIterator<T>::operator!=(const ConstLinkedListIterator<T>& iterator) const
{
	return !(*this == iterator);
}

template<typename T>
ConstLinkedListIterator<T>::ConstLinkedListIterator(const LinkedList<T>& linked_list, int index, std::shared_ptr<LinkedListNode_<T>> node) :
	container_(linked_list),
	node_(node),
	BaseLinkedListIterator_(index, true)
{}

		/* DEFINITIONS of LinkedListIterator */

template<typename T>
LinkedListIterator<T>::LinkedListIterator(const LinkedListIterator<T>& iterator) :
	container_(iterator.container_),
	node_(iterator.node_),
	BaseLinkedListIterator_(iterator.index_, iterator.is_valid_)
{}

template<typename T>
LinkedListIterator<T>::LinkedListIterator(LinkedListIterator<T>&& iterator) :
	container_(iterator.container_),
	node_(std::move(iterator.node_)),
	BaseLinkedListIterator_(std::move(iterator.index_), std::move(iterator.is_valid_))
{}

template<typename T>
const std::string LinkedListIterator<T>::to_string() const
{
	return util::to_string(get());
}

template<typename T>
int LinkedListIterator<T>::hash_code() const
{
	return util::hash_code(get());
}

template<typename T>
bool LinkedListIterator<T>::is_valid() const
{
	return is_valid_ && node_.lock();
}

template<typename T>
LinkedList<T>& LinkedListIterator<T>::get_container() const
{
	return container_;
}

template<typename T>
T& LinkedListIterator<T>::get() const
{
	return node_.lock()->value;
}

template<typename T>
bool LinkedListIterator<T>::is_begin() const
{
	return index_ == 0;
}

template<typename T>
bool LinkedListIterator<T>::is_last() const
{
	return index_ == container_.size() - 1;
}

template<typename T>
bool LinkedListIterator<T>::is_end() const
{
	return index_ == container_.size();
}

template<typename T>
bool LinkedListIterator<T>::next()
{
	if (is_end())
	{
		return false;
	}
	else
	{
		node_ = node_.lock()->next;
		index_++;
		return !is_end();
	}
}

template<typename T>
bool LinkedListIterator<T>::prev()
{
	if (is_begin())
	{
		return false;
	}
	else
	{
		node_ = node_.lock()->prev;
		index_--;
		return true;
	}
}

template<typename T>
T& LinkedListIterator<T>::operator*() const
{
	return get();
}

template<typename T>
LinkedListIterator<T> LinkedListIterator<T>::operator++()
{
	next();
	return *this;
}

template<typename T>
LinkedListIterator<T> LinkedListIterator<T>::operator--()
{
	prev();
	return *this;
}

template<typename T>
LinkedListIterator<T> LinkedListIterator<T>::operator++(int)
{
	LinkedListIterator<T> ret = *this;
	next();
	return ret;
}

template<typename T>
LinkedListIterator<T> LinkedListIterator<T>::operator--(int)
{
	LinkedListIterator<T> ret = *this;
	prev();
	return ret;
}

template<typename T>
bool LinkedListIterator<T>::operator==(const LinkedListIterator<T>& iterator) const
{
	return &container_ == &iterator.container_ && index_ == iterator.index_;
}

template<typename T>
bool LinkedListIterator<T>::operator!=(const LinkedListIterator<T>& iterator) const
{
	return !(*this == iterator);
}

template<typename T>
LinkedListIterator<T>::operator ConstLinkedListIterator<T>() const
{
	return ConstLinkedListIterator<T>(container_, index_, node_);
}

template<typename T>
LinkedListIterator<T>::LinkedListIterator(LinkedList<T>& linked_list, int index, std::shared_ptr<LinkedListNode_<T>> node) :
	container_(linked_list),
	node_(node),
	BaseLinkedListIterator_(index, true)
{}

}
