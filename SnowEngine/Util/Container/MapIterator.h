    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: MapIterator.h               //
////////////////////////////////////////

#pragma once

#include "../../Object.h"
#include "Container.h"

#include "Array.h"

namespace snow
{

template<typename T_Key, typename T_Value>
class Map;

namespace
{

template<typename T_Container, typename T_Key, typename T_Value>
class BaseMapIterator_ :
	public Object,
	public IIterator<T_Container, T_Value>
{
	template<typename T_Key, typename T_Value>
	friend class Map;

public:
	BaseMapIterator_(const BaseMapIterator_<T_Container, T_Key, T_Value>& iterator);
	BaseMapIterator_(BaseMapIterator_<T_Container, T_Key, T_Value>&& iterator);
	~BaseMapIterator_();

	virtual const std::string to_string() const override;
	virtual int hash_code() const override;

	virtual bool is_valid() const override;
	virtual bool is_element_valid() const override;

	virtual T_Container& get_container() const override;
	T_Key get_key() const;
	virtual T_Value& get() const override;

	virtual bool is_begin() const override;
	virtual bool is_last() const override;
	virtual bool is_end() const override;
	virtual bool next() override;
	virtual bool prev() override;

	virtual T_Value& operator*() const override;
	BaseMapIterator_<T_Container, T_Key, T_Value> operator++();
	BaseMapIterator_<T_Container, T_Key, T_Value> operator--();
	BaseMapIterator_<T_Container, T_Key, T_Value> operator++(int);
	BaseMapIterator_<T_Container, T_Key, T_Value> operator--(int);

	bool operator==(const BaseMapIterator_<T_Container, T_Key, T_Value>& iterator) const;
	bool operator!=(const BaseMapIterator_<T_Container, T_Key, T_Value>& iterator) const;

	T_Value* operator->() const;

protected:
	BaseMapIterator_(T_Container& map, const T_Key& key, bool is_end, bool is_valid = true);

	T_Container& container_;
	T_Key key_;
	bool is_end_;
	bool is_valid_;
};

}

template<typename T_Key, typename T_Value>
using ConstMapIterator = BaseMapIterator_<const Map<T_Key, T_Value>, T_Key, const T_Value>;

template<typename T_Key, typename T_Value>
using MapIterator = BaseMapIterator_<Map<T_Key, T_Value>, T_Key, T_Value>;


		/* DEFINITIONS of BaseMapIterator_ */

template<typename T_Container, typename T_Key, typename T_Value>
BaseMapIterator_<T_Container, T_Key, T_Value>::BaseMapIterator_(const BaseMapIterator_<T_Container, T_Key, T_Value>& iterator) :
	container_(iterator.container_),
	key_(iterator.key_),
	is_end_(iterator.is_end_),
	is_valid_(iterator.is_valid_)
{
	if (is_valid_)
	{
		container_.register_iterator_(this);
	}
}

template<typename T_Container, typename T_Key, typename T_Value>
BaseMapIterator_<T_Container, T_Key, T_Value>::BaseMapIterator_(BaseMapIterator_<T_Container, T_Key, T_Value>&& iterator) :
	container_(iterator.container_),
	key_(iterator.key_),
	is_end_(iterator.is_end_),
	is_valid_(iterator.is_valid_)
{
	if (is_valid_)
	{
		iterator.is_valid_ = false;
		container_.unregister_iterator_(&iterator);
		container_.register_iterator_(this);
	}
}

template<typename T_Container, typename T_Key, typename T_Value>
BaseMapIterator_<T_Container, T_Key, T_Value>::~BaseMapIterator_()
{
	if (is_valid_)
	{
		container_.unregister_iterator_(this);
	}
}

template<typename T_Container, typename T_Key, typename T_Value>
const std::string BaseMapIterator_<T_Container, T_Key, T_Value>::to_string() const
{
	return util::to_string(get());
}

template<typename T_Container, typename T_Key, typename T_Value>
int BaseMapIterator_<T_Container, T_Key, T_Value>::hash_code() const
{
	return util::hash_code(get());
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::is_valid() const
{
	return is_valid_;
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::is_element_valid() const
{
	return is_valid_ && !is_end_;
}

template<typename T_Container, typename T_Key, typename T_Value>
T_Container& BaseMapIterator_<T_Container, T_Key, T_Value>::get_container() const
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

template<typename T_Container, typename T_Key, typename T_Value>
T_Key BaseMapIterator_<T_Container, T_Key, T_Value>::get_key() const
{
	if (is_element_valid())
	{
		return key_;
	}
	else
	{
		throw std::logic_error("Attempt to get key of invalid iterator");
	}
}

template<typename T_Container, typename T_Key, typename T_Value>
T_Value& BaseMapIterator_<T_Container, T_Key, T_Value>::get() const
{
	if (is_element_valid())
	{
		return container_[key_];
	}
	else
	{
		throw std::logic_error("Attempt to get element of invalid iterator");
	}
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::is_begin() const
{
	return is_valid_ && !is_end_ && container_.map_[container_.first_filled_].get_begin().get_first() == key_;
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::is_last() const
{
	return is_valid_ && !is_end_ && container_.map_[container_.last_filled_].get_last().get_first() == key_;
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::is_end() const
{
	return is_valid_ && is_end_;
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::next()
{
	if (is_valid_ && !is_end_)
	{
		if (container_.map_[container_.last_filled_].get_last().get_first() != key_)
		{
			int hash = math::abs(util::hash_code(key_) % container_.internal_size_);
			auto& list = container_.map_[hash];
			auto itr = list.begin();
			while (itr.get().get_first() != key_ && itr.next());
			if (itr.is_end())
			{
				while (container_.map_[++hash].is_empty());
				key_ = container_.map_[hash].get_begin().get_first();
			}
			else
			{
				itr.next();
				key_ = itr.get().get_first();
			}
			return true;
		}
		else
		{
			is_end_ = true;
			return false;
		}
	}
	else
	{
		return false;
	}
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::prev()
{
	if (is_valid_ && container_.map_[container_.first_filled_].get_begin().get_first() != key_)
	{
		if (!is_end_)
		{
			int hash = math::abs(util::hash_code(key_) % container_.internal_size_);
			auto& list = container_.map_[hash];
			auto itr = --(list.end());
			while (itr.get().get_first() != key_ && itr.prev());
			if (itr.is_begin())
			{
				while (container_.map_[--hash].is_empty());
				key_ = container_.map_[hash].get_last().get_first();
			}
			else
			{
				itr.prev();
				key_ = itr.get().get_first();
			}
		}
		else
		{
			key_ = container_.map_[container_.last_filled_].get_last().get_first();
			is_end_ = false;
		}
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T_Container, typename T_Key, typename T_Value>
T_Value& BaseMapIterator_<T_Container, T_Key, T_Value>::operator*() const
{
	return get();
}

template<typename T_Container, typename T_Key, typename T_Value>
BaseMapIterator_<T_Container, T_Key, T_Value> BaseMapIterator_<T_Container, T_Key, T_Value>::operator++()
{
	next();
	return *this;
}

template<typename T_Container, typename T_Key, typename T_Value>
BaseMapIterator_<T_Container, T_Key, T_Value> BaseMapIterator_<T_Container, T_Key, T_Value>::operator--()
{
	prev();
	return *this;
}

template<typename T_Container, typename T_Key, typename T_Value>
BaseMapIterator_<T_Container, T_Key, T_Value> BaseMapIterator_<T_Container, T_Key, T_Value>::operator++(int)
{
	auto ret = *this;
	next();
	return ret;
}

template<typename T_Container, typename T_Key, typename T_Value>
BaseMapIterator_<T_Container, T_Key, T_Value> BaseMapIterator_<T_Container, T_Key, T_Value>::operator--(int)
{
	auto ret = *this;
	prev();
	return ret;
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::operator==(const BaseMapIterator_<T_Container, T_Key, T_Value>& iterator) const
{
	return !is_valid() && !iterator.is_valid() ||
		&container_ == &iterator.container_ &&
		(is_end_ && iterator.is_end_ || !is_end_ && !iterator.is_end_ && key_ == iterator.key_);
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::operator!=(const BaseMapIterator_<T_Container, T_Key, T_Value>& iterator) const
{
	return !(*this == iterator);
}

template<typename T_Container, typename T_Key, typename T_Value>
T_Value* BaseMapIterator_<T_Container, T_Key, T_Value>::operator->() const
{
	return &get();
}

template<typename T_Container, typename T_Key, typename T_Value>
BaseMapIterator_<T_Container, T_Key, T_Value>::BaseMapIterator_(T_Container& map, const T_Key& key, bool is_end, bool is_valid) :
	container_(map),
	key_(key),
	is_end_(is_end),
	is_valid_(is_valid)
{
	if (is_valid_)
	{
		container_.register_iterator_(this);
	}
}

}