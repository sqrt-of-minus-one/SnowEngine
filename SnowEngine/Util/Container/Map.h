    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Map.h                       //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\brief The file of the map
 *	
 *	This file contains the definition of the Map class.
 */

#include <list>

#include "MapIterator.h"
#include "Pair.h"

namespace snow
{

/**
 *	\brief The SnowEngine map
 *	
 *	Each element of this container is associated with a key and each key corresponds to a single
 *	element. Each element can be accessed using its key. A map provides a fast access to an
 *	arbitrary element, fast inserting and removing. When you initialise a map, you can specify its
 *	internal size. Note that the more elements there are, the slower operations with a map are. For
 *	maximum speed, it is recommended that the number of elements doesn't exceed half of the
 *	internal size or two-thirds as a last resort. To organise the elements, the map uses hash codes
 *	of their keys. If the key is not a pointer, it's important that its hash code is calculated
 *	fast.
 *	\tparam T_Key The key type. It must have default and copy constructor, that are assumed not to
 *	throw any exceptions, assignment operator (`=`) and equality operator (`==`). It also must have
 *	`to_string()` and `hash_code()` methods (any `snow::Object` has them) or be a primitive type.
 *	It is strongly recommended that the `hash_code()` be fast.
 *	\tparam T_Value Type of the value. It must have default and copy constructor, that are assumed
 *	not to throw any exceptions, assignment operator (`=`) and equality operator (`==`). It also
 *	must have `to_string()` and `hash_code()` methods (any `snow::Object` has them) or be a
 *	primitive type.
 */
template<typename T_Key, typename T_Value>
class Map :
	public Object,
	public IContainer<T_Value>
{
	template<typename T_Container, typename T_Key, typename T_Value>
	friend class BaseMapIterator_;

public:

	/**
	 *	\brief Create an empty map
	 *
	 *	The default constructor creates an empty map with default internal size (you can get it
	 *	using `internal_size()` method.
	 */
	Map() noexcept;

	/**
	 *	\brief Copy constructor
	 *
	 *	Creates a new map as a copy of the passed one.
	 *	\param map The map to copy.
	 */
	Map(const Map<T_Key, T_Value>& map) noexcept;

	/**
	 *	\brief Move constructor
	 *
	 *	Moves elements to a new map from the passed one.
	 *	\param map The map whose elements will be moved.
	 */
	Map(Map<T_Key, T_Value>&& map) noexcept;

	/**
	 *	\brief Create a map with the specified internal size
	 *
	 *	Creates a map with the specified internal size. It is recommended that the number of
	 *	elements doesn't exceed half of the internal size or two-thirds as a last resort.
	 *	\param size The internal size of the map.
	 */
	Map(int size);

	/**
	 *	\brief The destructor
	 *
	 *	The destructor is used to invalidate all iterators.
	 */
	~Map() noexcept;

	/**
	 *	\brief Converts the map content to string
	 *
	 *	Creates a string representing the list of the container elements. `util::to_string()` is
	 *	used to convert elements to string.
	 *	\return A result string in the format `"{ [k: v], [k: v], ..., [k: v] }"` (`k` is key, `v`
	 *	is value). `"{ }"` if the map is empty.
	 */
	virtual const std::string to_string() const noexcept override;

	/**
	 *	\brief Hash code of the map
	 *
	 *	Hash code is calculated using `util::hash_code()` function. Hash code of a map is the sum
	 *	of its keys minus the sum of its values.
	 *	\return Hash code of the map.
	 */
	virtual int hash_code() const noexcept override;

	/**
	 *	\brief The size of the map
	 *
	 *	Allows to get the number of elements in the map.
	 *	\return The number of elements in the map.
	 */
	virtual int size() const noexcept override;

	/**
	 *	\brief The internal size of the map
	 *	
	 *	Allows to get the internal size of the map. It is recommended that the number of elements
	 *	doesn't exceed half of the internal size or two-thirds as a last resort.
	 *	\return The internal size of the map.
	 */
	int internal_size() const noexcept;

	/**
	 *	\brief Whether the map is empty
	 *
	 *	Checks whether the map is empty.
	 *	\return `true` if the container does not contain any element, `false` otherwise.
	 */
	virtual bool is_empty() const noexcept override;

	/**
	 *	\brief Clears the map
	 *
	 *	Removes all of the elements in the container and sets all of its iterators to the end.
	 */
	virtual void clear() noexcept override;
	
	/**
	 *	\brief Change the internal size of the map
	 *	
	 *	Changes the internal size without changing number of elements. Might work slowly. After
	 *	executing this method all iterators will continue pointing to their elements but the map
	 *	traversal order will be changed.
	 *	\param new_size The new internal size.
	 */
	void resize(int new_size);

	/**
	 *	\brief Add a new element
	 *
	 *	Inserts a new element with the specified key.
	 *	\param key The key of a new element.
	 *	\param value The added element.
	 *	\param allow_override Determines what actions will be performed if the map already contains
	 *	an element with the passed key. If `true`, the element will be overridden; if `false`, the
	 *	element won't be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise (i. g. if
	 *	there is already an element with this key and override is not allowed).
	 */
	bool add(const T_Key& key, const T_Value& value, bool allow_override = false);

	/**
	 *	\brief Add a new element
	 *
	 *	Inserts a new element with the specified key.
	 *	\param key The key of a new element.
	 *	\param value The added element.
	 *	\param allow_override Determines what actions will be performed if the map already contains
	 *	an element with the passed key. If `true`, the element will be overridden; if `false`, the
	 *	element won't be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise (i. g. if
	 *	there is already an element with this key and override is not allowed).
	 */
	bool add(const T_Key& key, T_Value&& value, bool allow_override = false);

	/**
	 *	\brief Add a new pair
	 *
	 *	Inserts a new element with the specified key.
	 *	\param pair The pair that contains key and value that will be added.
	 *	\param allow_override Determines what actions will be performed if the map already contains
	 *	an element with the passed key. If `true`, the element will be overridden; if `false`, the
	 *	element won't be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise (i. g. if
	 *	there is already an element with this key and override is not allowed).
	 */
	bool add(const Pair<T_Key, T_Value>& pair, bool allow_override = false);

	/**
	 *	\brief Add a new pair
	 *
	 *	Inserts a new element with the specified key.
	 *	\param pair The pair that contains key and value that will be added.
	 *	\param allow_override Determines what actions will be performed if the map already contains
	 *	an element with the passed key. If `true`, the element will be overridden; if `false`, the
	 *	element won't be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise (i. g. if
	 *	there is already an element with this key and override is not allowed).
	 */
	bool add(Pair<T_Key, T_Value>&& pair, bool allow_override = false);

	/**
	 *	\brief Add elements from the passed map
	 *
	 *	Tries to insert all elements of the passed map.
	 *	\param map The map whose elements will be copied.
	 *	\param allow_override Determines what actions will be performed if both maps contain
	 *	elements with the same key. If `true`, the element of this map will be overridden; if
	 *	`false`, the element won't be copied.
	 *	\return The number of elements that have been successfully added.
	 */
	int add(const Map<T_Key, T_Value>& map, bool allow_override = false);

	/**
	 *	\brief Move elements from the passed map
	 *
	 *	Tries to insert all elements of the passed map.
	 *	\param map The map whose elements will be moved.
	 *	\param allow_override Determines what actions will be performed if both maps contain
	 *	elements with the same key. If `true`, the element of this map will be overridden; if
	 *	`false`, the element won't be moved.
	 *	\return The number of elements that have been successfully moved.
	 */
	int add(Map<T_Key, T_Value>&& map, bool allow_override = false);
	
	/**
	 *	\brief Remove an element with the specified key
	 *	
	 *	Removes an element with the specified key. Iterators that pointed to the removed element
	 *	will point to the next element after executing this method.
	 *	\param key The key of an element that will be removed.
	 *	\return `true` if the element has been successfully removed, `false` otherwise (i. g. if
	 *	the map doesn't contain the element with the passed key).
	 */
	bool remove(const T_Key& key);

	/**
	 *	\brief Remove an element by iterator
	 *
	 *	Removes an element that the iterator points to. Iterators that pointed to the removed
	 *	element will point to the next element after executing this method.
	 *	\param element The iterator pointing to the element that will be removed.
	 *	\return `true` if the element has been successfully removed, `false` otherwise (i. g. if
	 *	the iterator points to the element of other map).
	 */
	bool remove(const MapIterator<T_Key, T_Value>& element);

	/**
	 *	\brief Remove an element by iterator
	 *
	 *	Removes an element that the iterator points to. Iterators that pointed to the removed
	 *	element will point to the next element after executing this method.
	 *	\param element The iterator pointing to the element that will be removed.
	 *	\return `true` if the element has been successfully removed, `false` otherwise (i. g. if
	 *	the iterator points to the element of other map).
	 */
	bool remove(const ConstMapIterator<T_Key, T_Value>& element);

	/**
	 *	\brief Remove one element that is equal to the passed one
	 *	
	 *	Compares elements of the map with the passed one and removes the first match.
	 *	\param element The object to compare.
	 *	\return `true` if an element has been successfully removed, `false` otherwise (i. g. if the
	 *	match hasn't been found).
	 */
	bool remove_one(const T_Value& element);

	/**
	 *	\brief Remove all elements that are equal to the passed one
	 *	
	 *	Compares elements of the map with the passed one and removes all matches.
	 *	\param element The object to compare.
	 *	\return The number of elements that have been successfully removed.
	 */
	virtual int remove_all(const T_Value& element) override;

	/**
	 *	\brief Find the element that is equal to the passed one
	 *	
	 *	Compares elements of the map with the passed one and returns a key of the first match.
	 *	\param element The object to compare.
	 *	\return The key of the first match. If no match has been found, creates an object using
	 *	a default constructor.
	 */
	T_Key find(const T_Value& element) const;

	/**
	 *	\brief Find the element that is equal to the passed one
	 *	
	 *	Compares elements of the map with the passed one and returns a key of the first match.
	 *	\param[in] element The object to compare.
	 *	\param[out] out_success `true` if a match has been found, `false` otherwise.
	 *	\return The key of the first match. If no match has been found, creates an object using
	 *	a default constructor.
	 */
	T_Key find(const T_Value& element, bool& out_success) const;

	/**
	 *	\brief Find all elements that are equal to the passed one
	 *
	 *	Compares all elements of the array with the passed one. Returns keys of all found matches.
	 *	\param element The desired element.
	 *	\return A linked list with keys of all found matches. If no match is found, the list is
	 *	empty.
	 */
	LinkedList<T_Key> find_all(const T_Value& element) const;

	/**
	 *	\brief Whether the map contains an element with the passed elements
	 *
	 *	Checks whether the map has an element with the passed key.
	 *	\param key The desired key.
	 *	\return `true` if the map contains the passed key, `false` otherwise.
	 */
	bool contains_key(const T_Key& key) const;

	/**
	 *	\brief Whether the map contains the passed element
	 *
	 *	Checks whether the map has an element that is equal to the passed one.
	 *	\param element The desired element.
	 *	\return `true` if the map contains the passed element, `false` otherwise.
	 */
	virtual bool contains(const T_Value& element) const override;

	/**
	 *	\brief How many elements of the array are equal to the passed one
	 *
	 *	Counts elements that are equal to the passed one.
	 *	\param element The desired element.
	 *	\return Number of matches.
	 */
	virtual int count(const T_Value& element) const override;
	
	/**
	 *	\brief Get all keys of the map
	 *	
	 *	Allows to get all keys contained in the map.
	 *	\return An array with all keys of the map.
	 */
	Array<T_Key> get_keys() const;

	/**
	 *	\brief Get all values of the map
	 *	
	 *	Allows to get all elements of the map without their keys.
	 *	\return An array with all values of the map.
	 */
	Array<T_Value> get_values() const;

	/**
	 *	\brief Get all key-value pairs
	 *	
	 *	Allows to get all pairs of the map.
	 *	\return An array that has all key-value pairs.
	 */
	Array<Pair<T_Key, T_Value>> get_pairs() const;

	/**
	 *	\brief Create an iterator to the first element
	 *
	 *	Creates an iterator that points to the first element of the map. If the map is empty, the
	 *	created iterator is end (`is_end()` is true).
	 *	\return The iterator to the first element of the map.
	 */
	MapIterator<T_Key, T_Value> begin() noexcept;

	/**
	 *	\brief Create an iterator to the last element
	 *
	 *	Creates an iterator that points to the last element of the map. If the map is empty, the
	 *	created iterator is end (`is_end()` is true).
	 *	\return The iterator to the last element of the map.
	 */
	MapIterator<T_Key, T_Value> last() noexcept;

	/**
	 *	\brief Create an iterator pointing after the last element
	 *
	 *	Creates an iterator that points to a space after the last element of the map (this iterator
	 *	is end: `is_end()` is true).
	 *	\return The iterator after the last element of the map.
	 */
	MapIterator<T_Key, T_Value> end() noexcept;

	/**
	 *	\brief Create an iterator pointing to the specified element
	 *
	 *	Creates an iterator that points to an element with the passed key.
	 *	\param key The key of an element that the iterator will points to.
	 *	\return The iterator pointing to the specified element.
	 *	\throw std::invalid_argument The map doesn't contain the passed key.
	 */
	MapIterator<T_Key, T_Value> create_iterator(const T_Key& key);

	/**
	 *	\brief Create an iterator to the first element
	 *
	 *	Creates an iterator that points to the first element of the map. If the map is empty, the
	 *	created iterator is end (`is_end()` is true).
	 *	\return The iterator to the first element of the map.
	 */
	ConstMapIterator<T_Key, T_Value> begin() const noexcept;

	/**
	 *	\brief Create an iterator to the last element
	 *
	 *	Creates an iterator that points to the last element of the map. If the map is empty, the
	 *	created iterator is end (`is_end()` is true).
	 *	\return The iterator to the last element of the map.
	 */
	ConstMapIterator<T_Key, T_Value> last() const noexcept;

	/**
	 *	\brief Create an iterator pointing after the last element
	 *
	 *	Creates an iterator that points to a space after the last element of the map (this iterator
	 *	is end: `is_end()` is true).
	 *	\return The iterator after the last element of the map.
	 */
	ConstMapIterator<T_Key, T_Value> end() const noexcept;

	/**
	 *	\brief Create an iterator pointing to the specified element
	 *
	 *	Creates an iterator that points to an element with the passed key.
	 *	\param key The key of an element that the iterator will points to.
	 *	\return The iterator pointing to the specified element.
	 *	\throw std::invalid_argument The map doesn't contain the passed key.
	 */
	ConstMapIterator<T_Key, T_Value> create_iterator(const T_Key& key) const;

	/**
	 *	\brief Copy assignment operator
	 *
	 *	Clears the map and assigns it the passed one. Invalidates all iterators.
	 *	\param map The map to assign.
	 *	\return A reference to itself.
	 */
	Map<T_Key, T_Value>& operator=(const Map<T_Key, T_Value>& map);

	/**
	 *	\brief Move assignment operator
	 *
	 *	Clears the map and moves elements of the passed one into it. Invalidates all iterators.
	 *	\param map The map to move.
	 *	\return A reference to itself.
	 */
	Map<T_Key, T_Value>& operator=(Map<T_Key, T_Value>&& map);

	/**
	 *	\brief Whether two maps are equal
	 *
	 *	Two maps are equal if all of their elements and keys are equal.
	 *	\param map The map to compare.
	 *	\return `true` if two maps are equal, `false` otherwise.
	 */
	bool operator==(const Map<T_Key, T_Value>& map) const;

	/**
	 *	\brief Whether two maps are not equal
	 *
	 *	Two maps are equal if all of their elements and keys are equal.
	 *	\param map The map to compare.
	 *	\return `true` if two maps are not equal, `false` otherwise.
	 */
	bool operator!=(const Map<T_Key, T_Value>& map) const;

	/**
	 *	\brief Get the specifies element.
	 *
	 *	Allows to access an element with the specified key.
	 *	\param key The key of the element.
	 *	\return A reference to the desired element.
	 *	\throw std::invalid_argument The map doesn't contain the passed key.
	 */
	T_Value& operator[](const T_Key& key);

	/**
	 *	\brief Get the specifies element.
	 *
	 *	Allows to access an element with the specified key.
	 *	\param key The key of the element.
	 *	\return A reference to the desired element.
	 *	\throw std::invalid_argument The map doesn't contain the passed key.
	 */
	const T_Value& operator[](const T_Key& key) const;

	/**
	 *	\brief MapIterator to ConstMapIterator
	 *
	 *	Converts the passed map iterator to constant map iterator that points to the same element
	 *	of the same map.
	 *	\param iterator The map iterator that will be converted.
	 *	\return A result constant map iterator.
	 */
	static ConstMapIterator<T_Key, T_Value> iterator_to_const(const MapIterator<T_Key, T_Value>& iterator) noexcept;

private:
	Array<LinkedList<Pair<T_Key, T_Value>>> map_;
	int size_;
	int internal_size_;
	
	int first_filled_;
	int last_filled_;

	mutable std::list<MapIterator<T_Key, T_Value>*> iterators_;
	mutable std::list<ConstMapIterator<T_Key, T_Value>*> const_iterators_;
	void register_iterator_(MapIterator<T_Key, T_Value>* iterator) noexcept;
	void unregister_iterator_(MapIterator<T_Key, T_Value>* iterator) noexcept;
	void register_iterator_(ConstMapIterator<T_Key, T_Value>* iterator) const noexcept;
	void unregister_iterator_(ConstMapIterator<T_Key, T_Value>* iterator) const noexcept;
	void clear_iterators_() const noexcept;

	static const int DEFAULT_SIZE_;
};

		/* DEFINITIONS */

#define FOR_ITERATORS_(i, arg) \
	for (auto i : iterators_) arg \
	for (auto i : const_iterators_) arg

template<typename T_Key, typename T_Value>
Map<T_Key, T_Value>::Map() noexcept :
	map_(DEFAULT_SIZE_),
	size_(0),
	internal_size_(DEFAULT_SIZE_),
	first_filled_(-1),
	last_filled_(-1)
{}

template<typename T_Key, typename T_Value>
Map<T_Key, T_Value>::Map(const Map<T_Key, T_Value>& map) noexcept :
	map_(map.map_),
	size_(map.size_),
	internal_size_(map.internal_size_),
	first_filled_(map.first_filled_),
	last_filled_(map.last_filled_)
{}

template<typename T_Key, typename T_Value>
Map<T_Key, T_Value>::Map(Map<T_Key, T_Value>&& map) noexcept :
	map_(std::move(map.map_)),
	size_(map.size_),
	internal_size_(map.internal_size_),
	first_filled_(map.first_filled_),
	last_filled_(map.last_filled_)
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
Map<T_Key, T_Value>::~Map() noexcept
{
	clear_iterators_();
}

template<typename T_Key, typename T_Value>
const std::string Map<T_Key, T_Value>::to_string() const noexcept
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
				ret += j.to_string() + ", ";
			}
		}
		ret[ret.length() - 2] = ' ';
		ret[ret.length() - 1] = '}';
		return ret;
	}
}
			

template<typename T_Key, typename T_Value>
int Map<T_Key, T_Value>::hash_code() const noexcept
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
int Map<T_Key, T_Value>::size() const noexcept
{
	return size_;
}

template<typename T_Key, typename T_Value>
int Map<T_Key, T_Value>::internal_size() const noexcept
{
	return internal_size_;
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::is_empty() const noexcept
{
	return size_ == 0;
}

template<typename T_Key, typename T_Value>
void Map<T_Key, T_Value>::clear() noexcept
{
	map_.clear();
	map_.resize(internal_size_);
	size_ = 0;

	FOR_ITERATORS_(i,
	{
		i->is_end_ = true;
	})
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
bool Map<T_Key, T_Value>::add(const T_Key& key, const T_Value& value, bool allow_override)
{
	return add(Pair<T_Key, T_Value>(key, value), allow_override);
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::add(const T_Key& key, T_Value&& value, bool allow_override)
{
	return add(Pair<T_Key, T_Value>(key, std::forward<T_Value>(value)), allow_override);
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::add(const Pair<T_Key, T_Value>& pair, bool allow_override)
{
	int hash = math::abs(util::hash_code(pair.get_first()) % internal_size_);
	auto& list = map_[hash];
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
	auto& list = map_[hash];
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
	auto& list = map_[hash];
	for (auto i = list.begin(); !i.is_end(); i.next())
	{
		if (i->get_first() == key)
		{
			FOR_ITERATORS_(j,
			{
				if (j->get_key() == key)
				{
					j->next();
				}
			})
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
T_Key Map<T_Key, T_Value>::find(const T_Value& element) const
{
	bool success;
	return find(element, success);
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
	int index = 0;
	for (auto i = begin(); !i.is_end(); i.next())
	{
		ret[index++] = i.get_key();
	}
	return ret;
}

template<typename T_Key, typename T_Value>
Array<T_Value> Map<T_Key, T_Value>::get_values() const
{
	Array<T_Value> ret(size_);
	int index = 0;
	for (const auto& i : *this)
	{
		ret[index++] = i;
	}
	return ret;
}

template<typename T_Key, typename T_Value>
Array<Pair<T_Key, T_Value>> Map<T_Key, T_Value>::get_pairs() const
{
	Array<Pair<T_Key, T_Value>> ret(size_);
	int index = 0;
	for (auto& i : map_)
	{
		for (auto j = i.begin(); !j.is_end(); j.next())
		{
			ret[index++] = j.get();
		}
	}
	return ret;
}

template<typename T_Key, typename T_Value>
MapIterator<T_Key, T_Value> Map<T_Key, T_Value>::begin() noexcept
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
MapIterator<T_Key, T_Value> Map<T_Key, T_Value>::last() noexcept
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
MapIterator<T_Key, T_Value> Map<T_Key, T_Value>::end() noexcept
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
		throw std::invalid_argument("A map doesn't contain the passed key");
	}
}

template<typename T_Key, typename T_Value>
ConstMapIterator<T_Key, T_Value> Map<T_Key, T_Value>::begin() const noexcept
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
ConstMapIterator<T_Key, T_Value> Map<T_Key, T_Value>::last() const noexcept
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
ConstMapIterator<T_Key, T_Value> Map<T_Key, T_Value>::end() const noexcept
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
		throw std::invalid_argument("A map doesn't contain the passed key");
	}
}

template<typename T_Key, typename T_Value>
Map<T_Key, T_Value>& Map<T_Key, T_Value>::operator=(const Map<T_Key, T_Value>& map)
{
	clear_iterators_();
	map_ = map.map_;
	size_ = map.size_;
	internal_size_ = map.internal_size_;
	first_filled_ = map.first_filled_;
	last_filled_ = map.last_filled_;
}

template<typename T_Key, typename T_Value>
Map<T_Key, T_Value>& Map<T_Key, T_Value>::operator=(Map<T_Key, T_Value>&& map)
{
	clear_iterators_();
	map_ = std::move(map.map_);
	size_ = map.size_;
	internal_size_ = map.internal_size_;
	first_filled_ = map.first_filled_;
	last_filled_ = map.last_filled_;
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
	auto& list = map_[hash];
	for (auto i = list.begin(); !i.is_end(); i.next())
	{
		if (i->get_first() == key)
		{
			return i->get_second();
		}
	}
	throw std::invalid_argument("A map doesn't contain the passed key");
}

template<typename T_Key, typename T_Value>
const T_Value& Map<T_Key, T_Value>::operator[](const T_Key& key) const
{
	int hash = math::abs(util::hash_code(key) % internal_size_);
	auto& list = map_[hash];
	for (auto i = list.begin(); !i.is_end(); i.next())
	{
		if (i->get_first() == key)
		{
			return i->get_second();
		}
	}
	throw std::invalid_argument("A map doesn't contain the passed key");
}

template<typename T_Key, typename T_Value>
ConstMapIterator<T_Key, T_Value> Map<T_Key, T_Value>::iterator_to_const(const MapIterator<T_Key, T_Value>& iterator) noexcept
{
	return ConstMapIterator<T_Key, T_Value>(iterator.container_, iterator.key_, iterator.is_end_, iterator.is_valid_);
}

template<typename T_Key, typename T_Value>
void Map<T_Key, T_Value>::register_iterator_(MapIterator<T_Key, T_Value>* iterator) noexcept
{
	iterators_.push_back(iterator);
}

template<typename T_Key, typename T_Value>
void Map<T_Key, T_Value>::unregister_iterator_(MapIterator<T_Key, T_Value>* iterator) noexcept
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
void Map<T_Key, T_Value>::register_iterator_(ConstMapIterator<T_Key, T_Value>* iterator) const noexcept
{
	const_iterators_.push_back(iterator);
}

template<typename T_Key, typename T_Value>
void Map<T_Key, T_Value>::unregister_iterator_(ConstMapIterator<T_Key, T_Value>* iterator) const noexcept
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
void Map<T_Key, T_Value>::clear_iterators_() const noexcept
{
	FOR_ITERATORS_(i,
	{
		i->is_valid_ = false;
	})
	iterators_.clear();
	const_iterators_.clear();
}

template<typename T_Key, typename T_Value>
const int Map<T_Key, T_Value>::DEFAULT_SIZE_ = 51;

#undef FOR_ITERATORS_

}