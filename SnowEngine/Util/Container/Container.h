    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Container.h                 //
////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include "../Util.h"

namespace snow
{

template<typename T_Container, typename T_Element>
class IIterator
{
public:
	virtual bool is_valid() const = 0;

	virtual T_Container& get_container() const = 0;
	virtual T_Element& get() const = 0;

	virtual bool is_begin() const = 0;
	virtual bool is_end() const = 0;
	virtual bool next() = 0;
	virtual bool prev() = 0;

	virtual T_Element& operator*() const = 0;
	virtual bool operator++() = 0;
	virtual bool operator--() = 0;
	virtual bool operator++(int) = 0;
	virtual bool operator--(int) = 0;

	virtual bool operator==(const IIterator<T_Container, T_Element>& iterator) const = 0;
	virtual bool operator!=(const IIterator<T_Container, T_Element>& iterator) const = 0;
};

template<typename T>
class IContainer
{
public:
	virtual int size() const = 0;
	virtual bool is_empty() const = 0;
	virtual void clear() = 0;

	virtual bool add(const T& element) = 0;
	virtual bool add(T&& element) = 0;

	virtual bool remove_all(const T& element) = 0;

	virtual bool contains(const T& element) const = 0;
	virtual int count(const T& element) const = 0;
};

}
