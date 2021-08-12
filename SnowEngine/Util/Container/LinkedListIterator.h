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

template<typename T_Container, typename T_Element, typename T_Node>
class BaseLinkedListIterator_ :
	public Object,
	public IIterator<T_Container, T_Element>
{
	template<typename T>
	friend class LinkedList;

public:
	BaseLinkedListIterator_(const BaseLinkedListIterator_<T_Container, T_Element, T_Node>& iterator);
	BaseLinkedListIterator_(BaseLinkedListIterator_<T_Container, T_Element, T_Node>&& iterator);
	~BaseLinkedListIterator_();

	virtual const std::string to_string() const override;
	virtual int hash_code() const override;

	virtual bool is_valid() const override;
	virtual bool is_element_valid() const override;

	virtual T_Container& get_container() const override;
	virtual T_Element& get() const override;
	int get_index() const;

	virtual bool is_begin() const override;
	virtual bool is_last() const override;
	virtual bool is_end() const override;
	virtual bool next() override;
	virtual bool prev() override;

	virtual T_Element& operator*() const override;
	BaseLinkedListIterator_<T_Container, T_Element, T_Node> operator++();
	BaseLinkedListIterator_<T_Container, T_Element, T_Node> operator--();
	BaseLinkedListIterator_<T_Container, T_Element, T_Node> operator++(int);
	BaseLinkedListIterator_<T_Container, T_Element, T_Node> operator--(int);

	bool operator==(const BaseLinkedListIterator_<T_Container, T_Element, T_Node>& iterator) const;
	bool operator!=(const BaseLinkedListIterator_<T_Container, T_Element, T_Node>& iterator) const;

	T_Element* operator->() const;

protected:
	BaseLinkedListIterator_(T_Container& linked_list, int index, std::shared_ptr<T_Node> node = nullptr, bool is_valid = true);

	T_Container& container_;
	std::weak_ptr<T_Node> node_;
	int index_;
	bool is_valid_;
};

}

template<typename T>
using ConstLinkedListIterator = BaseLinkedListIterator_<const LinkedList<T>, const T, LinkedListNode_<T>>;

template<typename T>
using LinkedListIterator = BaseLinkedListIterator_<LinkedList<T>, T, LinkedListNode_<T>>;


		/* DEFINITIONS of BaseLinkedListIterator_ */

template<typename T_Container, typename T_Element, typename T_Node>
BaseLinkedListIterator_<T_Container, T_Element, T_Node>::BaseLinkedListIterator_(const BaseLinkedListIterator_<T_Container, T_Element, T_Node>& iterator) :
	container_(iterator.container_),
	node_(iterator.node_),
	index_(iterator.index_),
	is_valid_(iterator.is_valid_)
{
	if (is_valid_)
	{
		container_.register_iterator_(this);
	}
}

template<typename T_Container, typename T_Element, typename T_Node>
BaseLinkedListIterator_<T_Container, T_Element, T_Node>::BaseLinkedListIterator_(BaseLinkedListIterator_<T_Container, T_Element, T_Node>&& iterator) :
	container_(iterator.container_),
	node_(iterator.node_),
	index_(iterator.index_),
	is_valid_(iterator.is_valid_)
{
	if (is_valid_)
	{
		iterator.is_valid_ = false;
		container_.unregister_iterator_(&iterator);
		container_.register_iterator_(this);
	}
}

template<typename T_Container, typename T_Element, typename T_Node>
BaseLinkedListIterator_<T_Container, T_Element, T_Node>::~BaseLinkedListIterator_()
{
	if (is_valid_)
	{
		container_.unregister_iterator_(this);
	}
}

template<typename T_Container, typename T_Element, typename T_Node>
const std::string BaseLinkedListIterator_<T_Container, T_Element, T_Node>::to_string() const
{
	return util::to_string(get());
}

template<typename T_Container, typename T_Element, typename T_Node>
int BaseLinkedListIterator_<T_Container, T_Element, T_Node>::hash_code() const
{
	return util::hash_code(get());
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::is_valid() const
{
	return is_valid_ && index_ >= 0 && index_ <= container_.size();
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::is_element_valid() const
{
	return is_valid_ && node_.lock() && index_ >= 0 && index_ < container_.size();
}

template<typename T_Container, typename T_Element, typename T_Node>
T_Container& BaseLinkedListIterator_<T_Container, T_Element, T_Node>::get_container() const
{
	if (is_valid())
	{
		return container_;
	}
	else
	{
		throw std::logic_error("Attempt to get container of invalid iterator");
	}
}

template<typename T_Container, typename T_Element, typename T_Node>
T_Element& BaseLinkedListIterator_<T_Container, T_Element, T_Node>::get() const
{
	if (is_element_valid())
	{
		return node_.lock()->value;
	}
	else
	{
		throw std::logic_error("Attempt to get element of invalid iterator");
	}
}

template<typename T_Container, typename T_Element, typename T_Node>
int BaseLinkedListIterator_<T_Container, T_Element, T_Node>::get_index() const
{
	if (is_valid())
	{
		return index_;
	}
	else
	{
		throw std::logic_error("Attempt to get index of invalid iterator");
	}
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::is_begin() const
{
	return is_valid_ && index_ == 0;
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::is_last() const
{
	return is_valid_ && index_ == container_.size() - 1;
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::is_end() const
{
	return is_valid_ && index_ == container_.size();
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::next()
{
	if (is_valid_ && index_ < container_.size())
	{
		node_ = node_.lock()->next;
		return ++index_ < container_.size();
	}
	else
	{
		return false;
	}
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::prev()
{
	if (is_valid_ && index_ > 0)
	{
		if (node_.lock()) // If is not end
		{
			node_ = node_.lock()->prev;
		}
		else
		{
			node_ = container_.get_last_node_();
		}
		index_--;
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T_Container, typename T_Element, typename T_Node>
T_Element& BaseLinkedListIterator_<T_Container, T_Element, T_Node>::operator*() const
{
	return get();
}

template<typename T_Container, typename T_Element, typename T_Node>
BaseLinkedListIterator_<T_Container, T_Element, T_Node> BaseLinkedListIterator_<T_Container, T_Element, T_Node>::operator++()
{
	next();
	return *this;
}

template<typename T_Container, typename T_Element, typename T_Node>
BaseLinkedListIterator_<T_Container, T_Element, T_Node> BaseLinkedListIterator_<T_Container, T_Element, T_Node>::operator--()
{
	prev();
	return *this;
}

template<typename T_Container, typename T_Element, typename T_Node>
BaseLinkedListIterator_<T_Container, T_Element, T_Node> BaseLinkedListIterator_<T_Container, T_Element, T_Node>::operator++(int)
{
	auto ret = *this;
	next();
	return ret;
}

template<typename T_Container, typename T_Element, typename T_Node>
BaseLinkedListIterator_<T_Container, T_Element, T_Node> BaseLinkedListIterator_<T_Container, T_Element, T_Node>::operator--(int)
{
	auto ret = *this;
	prev();
	return ret;
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::operator==(const BaseLinkedListIterator_<T_Container, T_Element, T_Node>& iterator) const
{
	return !is_valid_ && !iterator.is_valid_ ||
		&container_ == &iterator.container_ && index_ == iterator.index_;
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::operator!=(const BaseLinkedListIterator_<T_Container, T_Element, T_Node>& iterator) const
{
	return !(*this == iterator);
}

template<typename T_Container, typename T_Element, typename T_Node>
T_Element* BaseLinkedListIterator_<T_Container, T_Element, T_Node>::operator->() const
{
	return &get();
}

template<typename T_Container, typename T_Element, typename T_Node>
BaseLinkedListIterator_<T_Container, T_Element, T_Node>::BaseLinkedListIterator_(T_Container& linked_list, int index, std::shared_ptr<T_Node> node, bool is_valid) :
	container_(linked_list),
	node_(node),
	index_(index),
	is_valid_(is_valid)
{
	if (is_valid_)
	{
		container_.register_iterator_(this);
	}
}

}
