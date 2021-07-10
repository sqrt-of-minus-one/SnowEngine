#include "List.h"

namespace snow
{

template<typename T>
class LinkedList;

template<typename T>
class LinkedListIterator : public ListIterator<T>
{

};

template<typename T>
class LinkedList : public List<T>
{
public:
	T& get_tail();
	const T& get_tail() const;
};

}