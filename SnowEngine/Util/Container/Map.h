    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Map.h                       //
////////////////////////////////////////

#pragma once

#include <list>

#include "MapIterator.h"
#include "Pair.h"

namespace snow
{

template<typename T_Key, typename T_Value>
class Map :
	public Object,
	public IContainer<T_Value>
{
	template<typename T_Container, typename T_Key, typename T_Value>
	friend class BaseMapIterator_;

public:
	Map();
	Map(const Map<T_Key, T_Value>& map);
	Map(Map<T_Key, T_Value>&& map);
	Map(int size);
	~Map();

	virtual const std::string to_string() const override;
	virtual int hash_code() const override;
	
	virtual int size() const override;
	int internal_size() const;
	virtual bool is_empty() const override;
	virtual void clear() override;
	
	void resize(int new_size);
	
	virtual bool add(const T_Value& element) override;
	virtual bool add(T_Value&& element) override;
	bool add(const T_Key& key, const T_Value& value, bool allow_override = true);
	bool add(const T_Key& key, T_Value&& value, bool allow_override = true);
	bool add(const Pair<T_Key, T_Value>& pair, bool allow_override = true);
	bool add(Pair<T_Key, T_Value>&& pair, bool allow_override = true);
	int add(const Map<T_Key, T_Value>& map, bool allow_override = true);
	int add(Map<T_Key, T_Value>&& map, bool allow_override = true);

	bool remove(const T_Key& key);
	bool remove(const MapIterator<T_Key, T_Value>& element);
	bool remove(const ConstMapIterator<T_Key, T_Value>& element);
	bool remove_one(const T_Value& element);
	virtual int remove_all(const T_Value& element) override;

	T_Key find(const T_Value& element, bool& out_success) const;
	LinkedList<T_Key> find_all(const T_Value& element) const;

	bool contains_key(const T_Key& key) const;
	virtual bool contains(const T_Value& element) const override;
	virtual int count(const T_Value& element) const override;
	
	Array<T_Key> get_keys() const;
	Array<T_Value> get_values() const;
	Array<Pair<T_Key, T_Value>> get_pairs() const;

	MapIterator<T_Key, T_Value> begin();
	MapIterator<T_Key, T_Value> last();
	MapIterator<T_Key, T_Value> end();
	MapIterator<T_Key, T_Value> create_iterator(const T_Key& key);
	ConstMapIterator<T_Key, T_Value> begin() const;
	ConstMapIterator<T_Key, T_Value> last() const;
	ConstMapIterator<T_Key, T_Value> end() const;
	ConstMapIterator<T_Key, T_Value> create_iterator(const T_Key& key) const;

	Map<T_Key, T_Value>& operator=(const Map<T_Key, T_Value>& map);
	Map<T_Key, T_Value>& operator=(Map<T_Key, T_Value>&& map);

	bool operator==(const Map<T_Key, T_Value>& map) const;
	bool operator!=(const Map<T_Key, T_Value>& map) const;

	T_Value& operator[](const T_Key& key);
	const T_Value& operator[](const T_Key& key) const;

	static ConstMapIterator<T_Key, T_Value> iterator_to_const(const MapIterator<T_Key, T_Value>& iterator);

private:
	Array<LinkedList<Pair<T_Key, T_Value>>> map_;
	int size_;
	int internal_size_;
	
	int first_filled_;
	int last_filled_;

	mutable std::list<MapIterator<T_Key, T_Value>*> iterators_;
	mutable std::list<ConstMapIterator<T_Key, T_Value>*> const_iterators_;
	void register_iterator_(MapIterator<T_Key, T_Value>* iterator);
	void unregister_iterator_(MapIterator<T_Key, T_Value>* iterator);
	void register_iterator_(ConstMapIterator<T_Key, T_Value>* iterator) const;
	void unregister_iterator_(ConstMapIterator<T_Key, T_Value>* iterator) const;
	void clear_iterators_() const;

	static const int DEFAULT_SIZE_;
};

		/* DEFINITIONS of Map */

template<typename T_Key, typename T_Value>
Map<T_Key, T_Value>::Map() :
	map_(DEFAULT_SIZE_),
	size_(0),
	internal_size_(DEFAULT_SIZE_),
	first_filled_(-1),
	last_filled_(-1)
{}

template<typename T_Key, typename T_Value>
Map<T_Key, T_Value>::Map(const Map<T_Key, T_Value>& map) :
	map_(map.map_),
	size_(map.size_),
	internal_size_(map.internal_size_),
	first_filled_(map.first_filled_),
	last_filled_(map.last_filled_)
{}

template<typename T_Key, typename T_Value>
Map<T_Key, T_Value>::Map(Map<T_Key, T_Value>&& map) :
	map_(std::move(map.map_)),
	size_(map.size_),
	internal_size_(map.internal_size_),
	first_filled_(map.first_filled_),
	last_filled_(map.last_filled_),
	iterators_(std::move(map.iterators_)),
	const_iterators_(std::move(map.const_iterators_))
{}

template<typename T_Key, typename T_Value>
Map<T_Key, T_Value>::Map(int size) :
	map_(size),
	size_(0),
	internal_size_(size),
	first_filled_(-1),
	last_filled_(-1)
{}

template<typename T_Key, typename T_Value>
Map<T_Key, T_Value>::~Map()
{
	clear_iterators_();
}

template<typename T_Key, typename T_Value>
const std::string Map<T_Key, T_Value>::to_string() const
{
	if (size_ <= 0)
	{
		return "{ }";
	}
	else
	{
		std::string ret = "{ ";
		for (const auto& i : map_)
		{
			for (const auto& j : i)
			{
				ret += j.to_string() + "; ";
			}
		}
		ret[ret.length() - 2] = ' ';
		ret[ret.length() - 1] = '}';
		return ret;
	}
}
			

template<typename T_Key, typename T_Value>
int Map<T_Key, T_Value>::hash_code() const
{
	int ret = 0;
	for (const auto& i : map_)
	{
		for (const auto& j : i)
		{
			ret += j.hash_code();
		}
	}
	return ret;
}

template<typename T_Key, typename T_Value>
int Map<T_Key, T_Value>::size() const
{
	return size_;
}

template<typename T_Key, typename T_Value>
int Map<T_Key, T_Value>::internal_size() const
{
	return internal_size_;
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::is_empty() const
{
	return size_ == 0;
}

template<typename T_Key, typename T_Value>
void Map<T_Key, T_Value>::clear()
{
	map_.clear();
	map_.resize(internal_size_);
	clear_iterators_();
}

template<typename T_Key, typename T_Value>
void Map<T_Key, T_Value>::resize(int new_size)
{
	Array<Pair<T_Key, T_Value>> pairs(size_);
	for (auto& i : map_)
	{
		for (auto& j : i)
		{
			pairs.add(std::move(j));
		}
	}
	internal_size_ = new_size;
	map_.clear();
	map_.resize(new_size);
	for (const auto& i : pairs)
	{
		add(std::move(i));
	}
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::add(const T_Value& element)
{
	return add(T_Key(), element);
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::add(T_Value&& element)
{
	return add(T_Key(), std::forward<T_Value>(element));
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::add(const T_Key& key, const T_Value& value, bool allow_override)
{
	return add(Pair<T_Key, T_Value>(key, value));
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::add(const T_Key& key, T_Value&& value, bool allow_override)
{
	return add(Pair<T_Key, T_Value>(key, std::forward<T_Value>(value)));
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::add(const Pair<T_Key, T_Value>& pair, bool allow_override)
{
	int hash = math::abs(util::hash_code(pair.get_first()) % internal_size_);
	auto list = map_[hash];
	for (auto& i : list)
	{
		if (i.get_first() == pair.get_first())
		{
			if (allow_override)
			{
				i = pair;
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	if (size_ == 0 || list.is_empty() && hash < first_filled_)
	{
		first_filled_ = hash;
	}
	if (size_ == 0 || list.is_empty() && hash > last_filled_)
	{
		last_filled_ = hash;
	}
	list.add(pair);
	size_++;
	return true;
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::add(Pair<T_Key, T_Value>&& pair, bool allow_override)
{
	int hash = math::abs(util::hash_code(pair.get_first()) % internal_size_);
	auto list = map_[hash];
	for (auto& i : list)
	{
		if (i.get_first() == pair.get_first())
		{
			if (allow_override)
			{
				i = std::forward<Pair<T_Key, T_Value>>(pair);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	if (size_ == 0 || list.is_empty() && hash < first_filled_)
	{
		first_filled_ = hash;
	}
	if (size_ == 0 || list.is_empty() && hash > last_filled_)
	{
		last_filled_ = hash;
	}
	list.add(std::forward<Pair<T_Key, T_Value>>(pair));
	size_++;
	return true;
}

template<typename T_Key, typename T_Value>
int Map<T_Key, T_Value>::add(const Map<T_Key, T_Value>& map, bool allow_override)
{
	int ret = 0;
	Array<Pair<T_Key, T_Value>> pairs = map.get_pairs();
	for (auto& i : pairs)
	{
		ret += static_cast<int>(add(std::move(i), allow_override));
	}
	return ret;
}

template<typename T_Key, typename T_Value>
int Map<T_Key, T_Value>::add(Map<T_Key, T_Value>&& map, bool allow_override)
{
	int ret = 0;
	Array<Pair<T_Key, T_Value>> pairs(map.size_);
	for (auto& i : map.map_)
	{
		for (auto& j : i)
		{
			pairs.add(std::move(j));
		}
	}
	for (auto& i : pairs)
	{
		ret += static_cast<int>(add(std::move(i), allow_override));
	}
	return ret;
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::remove(const T_Key& key)
{
	int hash = math::abs(util::hash_code(key) % internal_size_);
	auto list = map_[hash];
	for (auto i = list.begin(); !i.is_end(); i.next())
	{
		if (i->get_first() == key)
		{
			for (auto j : iterators_)
			{
				if (j->get_key() == key)
				{
					j->next();
				}
			}
			for (auto j : const_iterators_)
			{
				if (j->get_key() == key)
				{
					j->next();
				}
			}
			list.remove(i);
			size_--;
			if (size_ == 0)
			{
				first_filled_ = -1;
				last_filled_ = -1;
			}
			else
			{
				if (list.is_empty() && first_filled_ == hash)
				{
					int index = hash;
					while (map_[++index].is_empty());
					first_filled_ = index;
				}
				if (list.is_empty() && last_filled_ == hash)
				{
					int index = hash;
					while (map_[--index].is_empty());
					last_filled_ = index;
				}
			}
			return true;
		}
	}
	return false;
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::remove(const MapIterator<T_Key, T_Value>& element)
{
	return remove(iterator_to_const(element));
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::remove(const ConstMapIterator<T_Key, T_Value>& element)
{
	return remove(element.get_key());
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::remove_one(const T_Value& element)
{
	for (auto i = begin(); !i.is_end(); i.next())
	{
		if (i.get() == element)
		{
			return remove(i.get_key());
		}
	}
	return false;
}

template<typename T_Key, typename T_Value>
int Map<T_Key, T_Value>::remove_all(const T_Value& element)
{
	int ret = 0;
	while (size_ > 0 && begin().get() == element)
	{
		ret += static_cast<int>(remove(begin()));
	}
	auto i = begin();
	while(i.next())
	{
		if (i.get() == element)
		{
			ret += static_cast<int>(remove(i--));
		}
	}
	return ret;
}

template<typename T_Key, typename T_Value>
T_Key Map<T_Key, T_Value>::find(const T_Value& element, bool& out_success) const
{
	for (auto i = begin(); !i.is_end(); i.next())
	{
		if (i.get() == element)
		{
			out_success = true;
			return i.get_key();
		}
	}
	out_success = false;
	return T_Key();
}

template<typename T_Key, typename T_Value>
LinkedList<T_Key> Map<T_Key, T_Value>::find_all(const T_Value& element) const
{
	LinkedList<T_Key> ret;
	for (auto i = begin(); !i.is_end(); i.next())
	{
		if (i.get() == element)
		{
			ret.add(i.get_key());
		}
	}
	return ret;
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::contains_key(const T_Key& key) const
{
	for (auto i = begin(); !i.is_end(); i.next())
	{
		if (i.get_key() == key)
		{
			return true;
		}
	}
	return false;
}	

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::contains(const T_Value& element) const
{
	for (auto i = begin(); !i.is_end(); i.next())
	{
		if (i.get() == element)
		{
			return true;
		}
	}
	return false;
}	

template<typename T_Key, typename T_Value>
int Map<T_Key, T_Value>::count(const T_Value& element) const
{
	int ret = 0;
for (auto i = begin(); !i.is_end(); i.next())
	{
		if (i.get() == element)
		{
			ret++;
		}
	}
	return ret;
}

template<typename T_Key, typename T_Value>
Array<T_Key> Map<T_Key, T_Value>::get_keys() const
{
	Array<T_Key> ret(size_);
	for (auto i = begin(); !i.is_end(); i.next())
	{
		ret.add(i.get_key());
	}
	return ret;
}

template<typename T_Key, typename T_Value>
Array<T_Value> Map<T_Key, T_Value>::get_values() const
{
	Array<T_Value> ret(size_);
	for (const auto& i : *this)
	{
		ret.add(i);
	}
	return ret;
}

template<typename T_Key, typename T_Value>
Array<Pair<T_Key, T_Value>> Map<T_Key, T_Value>::get_pairs() const
{
	Array<Pair<T_Key, T_Value>> ret(size_);
	for (auto& i : map_)
	{
		for (auto j = i.begin(); !j.is_end(); j.next())
		{
			ret.add(j.get());
		}
	}
	return ret;
}

template<typename T_Key, typename T_Value>
MapIterator<T_Key, T_Value> Map<T_Key, T_Value>::begin()
{
	if (size_ > 0)
	{
		return MapIterator<T_Key, T_Value>(*this, map_[first_filled_].get_begin().get_first(), false);
	}
	else
	{
		return MapIterator<T_Key, T_Value>(*this, T_Key(), true);
	}
}

template<typename T_Key, typename T_Value>
MapIterator<T_Key, T_Value> Map<T_Key, T_Value>::last()
{
	if (size_ > 0)
	{
		return MapIterator<T_Key, T_Value>(*this, map_[last_filled_].get_last().get_first(), false);
	}
	else
	{
		return MapIterator<T_Key, T_Value>(*this, T_Key(), true);
	}
}

template<typename T_Key, typename T_Value>
MapIterator<T_Key, T_Value> Map<T_Key, T_Value>::end()
{
	return MapIterator<T_Key, T_Value>(*this, T_Key(), true);
}

template<typename T_Key, typename T_Value>
MapIterator<T_Key, T_Value> Map<T_Key, T_Value>::create_iterator(const T_Key& key)
{
	if (contains_key(key))
	{
		return MapIterator<T_Key, T_Value>(*this, key, false);
	}
	else
	{
		return MapIterator<T_Key, T_Value>(*this, T_Key(), true);
	}
}

template<typename T_Key, typename T_Value>
ConstMapIterator<T_Key, T_Value> Map<T_Key, T_Value>::begin() const
{
	if (size_ > 0)
	{
		return ConstMapIterator<T_Key, T_Value>(*this, map_[first_filled_].get_begin().get_first(), false);
	}
	else
	{
		return ConstMapIterator<T_Key, T_Value>(*this, T_Key(), true);
	}
}

template<typename T_Key, typename T_Value>
ConstMapIterator<T_Key, T_Value> Map<T_Key, T_Value>::last() const
{
	if (size_ > 0)
	{
		return ConstMapIterator<T_Key, T_Value>(*this, map_[last_filled_].get_last().get_first(), false);
	}
	else
	{
		return ConstMapIterator<T_Key, T_Value>(*this, T_Key(), true);
	}
}

template<typename T_Key, typename T_Value>
ConstMapIterator<T_Key, T_Value> Map<T_Key, T_Value>::end() const
{
	return ConstMapIterator<T_Key, T_Value>(*this, T_Key(), true);
}


template<typename T_Key, typename T_Value>
ConstMapIterator<T_Key, T_Value> Map<T_Key, T_Value>::create_iterator(const T_Key& key) const
{
	if (contains_key(key))
	{
		return ConstMapIterator<T_Key, T_Value>(*this, key, false);
	}
	else
	{
		return ConstMapIterator<T_Key, T_Value>(*this, T_Key(), true);
	}
}

template<typename T_Key, typename T_Value>
Map<T_Key, T_Value>& Map<T_Key, T_Value>::operator=(const Map<T_Key, T_Value>& map)
{
	clear();
	map_ = map.map_;
	size_ = map.size_;
	internal_size_ = map.internal_size_;
	first_filled_ = map.first_filled_;
	last_filled_ = map.last_filled_;
}

template<typename T_Key, typename T_Value>
Map<T_Key, T_Value>& Map<T_Key, T_Value>::operator=(Map<T_Key, T_Value>&& map)
{
	clear();
	map_ = std::move(map.map_);
	size_ = map.size_;
	internal_size_ = map.internal_size_;
	first_filled_ = map.first_filled_;
	last_filled_ = map.last_filled_;
	iterators_ = std::move(map.iterators_);
	const_iterators_ = std::move(map.const_iterators_);
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::operator==(const Map<T_Key, T_Value>& map) const
{
	if (size_ == map.size_)
	{
		// Todo: use sorted container
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::operator!=(const Map<T_Key, T_Value>& map) const
{
	return !(*this == map);
}

template<typename T_Key, typename T_Value>
T_Value& Map<T_Key, T_Value>::operator[](const T_Key& key)
{
	int hash = math::abs(util::hash_code(key) % internal_size_);
	auto list = map_[hash];
	for (auto i = list.begin(); !i.is_end(); i.next())
	{
		if (i->get_first() == key)
		{
			return i->get_second();
		}
	}
	throw std::invalid_argument("Map does not contain passed key");
}

template<typename T_Key, typename T_Value>
const T_Value& Map<T_Key, T_Value>::operator[](const T_Key& key) const
{
	int hash = math::abs(util::hash_code(key) % internal_size_);
	auto list = map_[hash];
	for (auto i = list.begin(); !i.is_end(); i.next())
	{
		if (i->get_first() == key)
		{
			return i->get_second();
		}
	}
	throw std::invalid_argument("Map does not contain passed key");
}

template<typename T_Key, typename T_Value>
ConstMapIterator<T_Key, T_Value> Map<T_Key, T_Value>::iterator_to_const(const MapIterator<T_Key, T_Value>& iterator)
{
	return ConstMapIterator<T_Key, T_Value>(iterator.container_, iterator.key_, iterator.is_end_, iterator.is_valid_);
}

template<typename T_Key, typename T_Value>
void Map<T_Key, T_Value>::register_iterator_(MapIterator<T_Key, T_Value>* iterator)
{
	iterators_.push_back(iterator);
}

template<typename T_Key, typename T_Value>
void Map<T_Key, T_Value>::unregister_iterator_(MapIterator<T_Key, T_Value>* iterator)
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

template<typename T_Key, typename T_Value>
void Map<T_Key, T_Value>::register_iterator_(ConstMapIterator<T_Key, T_Value>* iterator) const
{
	const_iterators_.push_back(iterator);
}

template<typename T_Key, typename T_Value>
void Map<T_Key, T_Value>::unregister_iterator_(ConstMapIterator<T_Key, T_Value>* iterator) const
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

template<typename T_Key, typename T_Value>
void Map<T_Key, T_Value>::clear_iterators_() const
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

template<typename T_Key, typename T_Value>
const int Map<T_Key, T_Value>::DEFAULT_SIZE_ = 51;

}