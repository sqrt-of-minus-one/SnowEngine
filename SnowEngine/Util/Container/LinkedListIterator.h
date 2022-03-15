    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: LinkedListIterator.h        //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file of linked list iterator
 *	
 *	This file contains the definitions of the linked list iterator classes.
 *	
 *	\~russian
 *	\brief Файл итератора связного списка
 *	
 *	Этот файл содержит определения классов итераторов связного списка.
*/

#include "../../Object.h"
#include "Container.h"

#include "../Util.h"
#include "../Types/String.h"

namespace snow
{

template<typename T>
class LinkedList;

namespace
{

template<typename T>
struct LinkedListNode_;

/**
 *	\~english
 *	\brief The base for linked list iterators
 *	
 *	This class is used as a template for `LinkedListIterator` and `ConstLinkedListIterator`
 *	classes.
 *	\warning Do not use this class directly.
 *	\tparam T_Container Type of the container (`LinkedList` or `const LinkedList`).
 *	\tparam T_Element Type of the array elements (taking into account `const` modifier).
 *	
 *	\~russian
 *	\brief Основа для итераторов связного списка
 *	
 *	Этот класс используется как шаблон для классов `LinkedListIterator` и `ConstLinkedListIterator`.
 *	\warning Не используйте этот класс напрямую.
 *	\tparam T_Container Тип контейнера (`LinkedListIterator` или `ConstLinkedListIterator`).
 *	\tparam T_Element Тип элемента массива (с учётом модификатора `const`).
 */
template<typename T_Container, typename T_Element, typename T_Node>
class BaseLinkedListIterator_ :
	public Object,
	public IIterator<T_Container, T_Element>
{
	template<typename T>
	friend class LinkedList;

public:

			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *	
	 *	Creates a copy of the passed iterator.
	 *	\param iterator The iterator that will be copied.
	 *	
	 *	\~russian
	 *	\brief Конструктор копирования
	 *	
	 *	Создаёт копию переданного итератора.
	 *	\param iterator Итератор, который будет скопирован.
	 */
	BaseLinkedListIterator_(const BaseLinkedListIterator_<T_Container, T_Element, T_Node>& iterator) noexcept;

	/**
	 *	\~english
	 *	\brief The move constructor
	 *	
	 *	Creates a new iterator by moving the passed one.
	 *	\param iterator The iterator that will be moved.
	 *	
	 *	\~russian
	 *	\brief Конструктор перемещения
	 *	
	 *	Создаёт новый итератор путём перемещения переданного.
	 *	\param iterator Итератор, который будет перемещён.
	 */
	BaseLinkedListIterator_(BaseLinkedListIterator_<T_Container, T_Element, T_Node>&& iterator) noexcept;

	/**
	 *	\~english
	 *	\brief The destructor
	 *	
	 *	The destructor of the linked list iterator.
	 *	
	 *	\~russian
	 *	\brief Деструктор
	 *	
	 *	Деструктор итератора связного списка.
	 */
	~BaseLinkedListIterator_() noexcept;

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts an element of the iterator to string
	 *	
	 *	Gets the element that the iterator points to and converts it to string using
	 *	`util::to_string()` function.
	 *	\code
	 *		// These two strings do the same:
	 *		iterator.to_string();
	 *		util::to_string(iterator.get());
	 *	\endcode
	 *	\return A result string.
	 *
	 *	\~russian
	 *	\brief Конвертирует элемент итератора в строку
	 *
	 *	Получает элемент, на который указывает итератор, и конвертирует его в строку, используя
	 *	функцию `util::to_string()`.
	 *	\code
	 *		// Эти две строки делают одно и то же:
	 *		iterator.to_string();
	 *		util::to_string(iterator.get());
	 *	\endcode
	 *	\return Полученная строка.
	 */
	virtual String to_string() const noexcept override;

	/**
	 *	\~english
	 *	\brief Hash code of an element of the iterator
	 *
	 *	Gets the element that the iterator points to and calculates its hash code using
	 *	`util::hash_code()` function.
	 *	\code
	 *		// These two strings do the same:
	 *		iterator.hash_code();
	 *		util::hash_code(iterator.get());
	 *	\endcode
	 *	\return Hash code of the element.
	 *
	 *	\~russian
	 *	\brief Хеш-код элемента итератора
	 *
	 *	Получает элемент, на который указыват итератор, и вычисляет его хеш-код, используя
	 *	функцию `util::hash_code()`.
	 *	\code
	 *		// Эти две строки делают одно и то же:
	 *		iterator.hash_code();
	 *		util::hash_code(iterator.get());
	 *	\endcode
	 *	\return Хеш-код элемента.
	 */
	virtual int hash_code() const noexcept override;

			/* METHODS FROM IIterator &
				METHODS */

	/**
	 *	\~english
	 *	\brief Checks whether the iterator is valid
	 *
	 *	The iterator may be invalid if its container has been destroyed.
	 *	\return `true` if the iterator is valid, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, действителен ли итератор
	 *	
	 *	Итератор может быть недействительным, если его контейнер был разрушен.
	 *	\return `true`, если итератор действителен, иначе `false`.
	*/
	virtual bool is_valid() const noexcept override;

	/**
	 *	\~english
	 *	\brief Checks whether the iterator points to a valid element
	 *
	 *	This function returns `false` if the iterator is not valid or points to the end of the
	 *	linked list (i. e. after the last linked list element).
	 *	\return `true` if the iterator points to a valid element, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, указывает ли итератор на действительный элемент
	 *	
	 *	Эта функция возвращает `false`, если итератор недействителен или указывает на конец
	 *	связного списка (т. е. после последнего элемента связного списка).
	 *	\return `true`, если итератор указывает на действительный элемент, иначе `false`.
	 */
	virtual bool is_element_valid() const noexcept override;

	/**
	 *	\~english
	 *	\brief The container of the iterator
	 *
	 *	Allows to get the linked list that has the element that the iterator points to.
	 *	\return The container of the iterator.
	 *	\throw std::logic_error The iterator is not valid.
	 *	
	 *	\~russian
	 *	\brief Контейнер итератора
	 *	
	 *	Позволяет получить связный список, на элемент которого указывает итератор.
	 *	\return Контейнер итератора.
	 *	\throw std::logic_error Итератор недействителен.
	 */
	virtual T_Container& get_container() const override;

	/**
	 *	\~english
	 *	\brief The element that the iterator points to
	 *
	 *	Allows to get the element that the iterator points to.
	 *	\return The element that the iterator points to.
	 *	\throw std::logic_error The element is not valid (`is_element_valid` method returns
	 *	`false`).
	 *	
	 *	\~russian
	 *	\brief Элемент, на который указывает итератор
	 *	
	 *	Позволяет получить элемент, на который указывает итератор.
	 *	\return Элемент, на который указывает итератор.
	 *	\throw std::logic_error Элемент недействителен (метод `is_element_valid` возвращает
	 *	`false`).
	 */
	virtual T_Element& get() const override;

	/**
	 *	\~english
	 *	\brief The index of the element that the iterator points to
	 *	
	 *	Allows to get the index of the element that the iterator points to.
	 *	\return The index of the element.
	 *	\throw std::logic_error The iterator is not valid.
	 *	
	 *	\~russian
	 *	\brief Индекс элемента, на который указывает итератор
	 *	
	 *	Позволяет получить индекс элемента, на который указывает итератор.
	 *	\return Индекс элемента, на который указывает итератор.
	 *	\throw std::logic_error Итератор недействителен.
	 */
	int get_index() const;

	/**
	 *	\~english
	 *	\brief Checks whether the iterator points to the first element of the linked list
	 *
	 *	The iterator is begin if it points to the first element.
	 *	\return `true` if the iterator points to the first element of the linked list, `false`
	 *	otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, указывает ли итератор на первый элемент связного списка
	 *	
	 *	Проверяет, указывает ли итератор на первый элемент связного списка.
	 *	\return `true`, если итератор указывает на первый элемент связного списка, иначе `false`.
	 */
	virtual bool is_begin() const noexcept override;

	/**
	 *	\~english
	 *	\brief Checks whether the iterator points to the last element of the linked list
	 *
	 *	The iterator is last if it points to the last element.
	 *	\return `true` if the iterator points to the last element of the linked list, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, указывает ли итератор на последний элемент связного списка
	 *
	 *	Проверяет, указывает ли итератор на последний элемент связного списка.
	 *	\return `true`, если итератор указывает на последний элемент связного списка, иначе `false`.
	 */
	virtual bool is_last() const noexcept override;

	/**
	 *	\~english
	 *	\brief Checks whether the iterator points after the last element of the linked list
	 *
	 *	The iterator is end if it points to a space that is after the last element. In this case
	 *	`is_element_valid` method returns `false`.
	 *	\return `true` if the iterator points after the last element of the linked list, `false`
	 *	otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, указывает ли итератор после последнего элемента связного списка
	 *
	 *	Итератор указывает в конец, если он указывает на пространство после последнего элемента
	 *	связного списка. В этом случае метод `is_element_valid` возвращает `false`.
	 *	\return `true`, если итератор указывает после последнего элемента связного списка, иначе `false`.
	 */
	virtual bool is_end() const noexcept override;

	/**
	 *	\~english
	 *	\brief Moves the iterator forward
	 *
	 *	Changes the iterator so that it points to the next element. The iterator won't be changed
	 *	if it is already pointing after the last element.
	 *	\return `true` if the new element of the iterator is valid (is not end), `false` otherwise.
	 *	\throw std::logic_error The iterator is not valid.
	 *	
	 *	\~russian
	 *	\brief Перемещает элемент вперёд
	 *	
	 *	Изменяет итератор так, чтобы он указывал на следующий элемент. Итератор не будет изменён,
	 *	если он уже указывает после последнего элемента.
	 *	\return `true`, если новый элемент итератора действителен (итератор не указывает после
	 *	последнего элемента), иначе `false`.
	 *	\throw std::logic_error Итератор недействителен.
	 */
	virtual bool next() override;

	/**
	 *	\~english
	 *	\brief Moves the iterator backward
	 *
	 *	Changes the iterator so that it points to the previous element. The iterator won't be
	 *	changed if it is already pointing to the first element.
	 *	\return `true` if the iterator has been moved, `false` otherwise.
	 *	\throw std::logic_error The iterator is not valid.
	 *	
	 *	\~russian
	 *	\brief Перемещает элемент назад
	 *	
	 *	Изменяет итератор так, чтобы он указывал на предыдущий элемент. Итератор не будет изменён,
	 *	если он уже указывает на первый элемент.
	 *	\return `true`, итератор был перемещён, иначе `false`.
	 *	\throw std::logic_error Итератор недействителен.
	 */
	virtual bool prev() override;

			/* OPERATORS */

	/**
	 *	\~english
	 *	\brief The element that the iterator points to
	 *
	 *	This operator is equivalent to the `get` method.
	 *	\return The element that the iterator points to.
	 *	\throw std::logic_error The element is not valid (`is_element_valid` method returns
	 *	`false`).
	 *	
	 *	\~russian
	 *	\brief Элемент, на который указывает итератор
	 *
	 *	Этот оператор эквивалентен методу `get`.
	 *	\return Элемент, на который указывает итератор.
	 *	\throw std::logic_error Элемент недействителен (метод `is_element_valid` возвращает
	 *	`false`).
	 */
	virtual T_Element& operator*() const override;

	/**
	 *	\~english
	 *	\brief The prefix increment of the iterator
	 *
	 *	Changed the iterator so that it points to the next element. The iterator won't be changed
	 *	if it is already pointing after the last element.
	 *	\return The moved iterator.
	 *	\throw std::logic_error The iterator is not valid.
	 *
	 *	\~russian
	 *	\brief Префиксный инкремент итератора
	 *
	 *	Изменяет итератор так, чтобы он указывал на следующий элемент. Итератор не будет изменён,
	 *	если он уже указывает после последнего элемента.
	 *	\return Перемещённый итератор.
	 *	\throw std::logic_error Итератор недействителен.
	 */
	BaseLinkedListIterator_<T_Container, T_Element, T_Node> operator++();

	/**
	 *	\brief The prefix decrement of the iterator
	 *
	 *	Changes the iterator so that it points to the previous element. The iterator won't be
	 *	changed if it is already pointing to the first element.
	 *	\return The moved iterator.
	 *	\throw std::logic_error The iterator is not valid.
	 *
	 *	\~russian
	 *	\brief Префиксный декремент итератора
	 *
	 *	Изменяет итератор так, чтобы он указывал на предыдущий элемент. Итератор не будет изменён,
	 *	если он уже указывает на первый элемент.
	 *	\return Перемещённый итератор.
	 *	\throw std::logic_error Итератор недействителен.
	 */
	BaseLinkedListIterator_<T_Container, T_Element, T_Node> operator--();

	/**
	 *	\~english
	 *	\brief The postfix increment of the iterator
	 *
	 *	Changes the iterator so that it points to the next element. The iterator won't be changed
	 *	if it is already pointing after the last element.
	 *	\return The iterator before moving.
	 *	\throw std::logic_error The iterator is not valid.
	 *
	 *	\~russian
	 *	\brief Постфиксный инкремент итератора
	 *
	 *	Изменяет итератор так, чтобы он указывал на следующий элемент. Итератор не будет изменён,
	 *	если он уже указывает после последнего элемента.
	 *	\return Итератор до перемещения.
	 *	\throw std::logic_error Итератор недействителен.
	 */
	BaseLinkedListIterator_<T_Container, T_Element, T_Node> operator++(int);

	/**
	 *	\brief The postfix decrement of the iterator
	 *
	 *	Changes the iterator so that it points to the previous element. The iterator won't be
	 *	changed if it is already pointing to the first element.
	 *	\return The iterator before moving.
	 *	\throw std::logic_error The iterator is not valid.
	 *
	 *	\~russian
	 *	\brief Постфиксный декремент итератора
	 *
	 *	Изменяет итератор так, чтобы он указывал на предыдущий элемент. Итератор не будет изменён,
	 *	если он уже указывает на первый элемент.
	 *	\return Итератор до перемещения.
	 *	\throw std::logic_error Итератор недействителен.
	 */
	BaseLinkedListIterator_<T_Container, T_Element, T_Node> operator--(int);

	/**
	 *	\~english
	 *	\brief Checks whether two iterators are equal
	 *
	 *	Two linked list iterators are equal if they point to the same element of the same linked
	 *	list. The iterators are also equal if they are both invalid.
	 *	\return `true` if the iterators are equal, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, равны ли два итератора
	 *	
	 *	Два итератора связного списка равны, если они указывают на один и тот же элемент одного и
	 *	того же связного списка. Итераторы также равны, если они оба недействительны.
	 *	\return `true`, если итераторы равны, иначе `false`.
	 */
	bool operator==(const BaseLinkedListIterator_<T_Container, T_Element, T_Node>& iterator) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether two iterators are not equal
	 *
	 *	Two linked list iterators are equal if they point to the same element of the same linked
	 *	list. The iterators are also equal if they are both invalid.
	 *	\return `true` if the iterators are not equal, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, различаются ли два итератора
	 *	
	 *	Два итератора связного списка равны, если они указывают на один и тот же элемент одного и
	 *	того же связного списка. Итераторы также равны, если они оба недействительны.
	 *	\return `true`, если итераторы не равны, иначе `false`.
	 */
	bool operator!=(const BaseLinkedListIterator_<T_Container, T_Element, T_Node>& iterator) const noexcept;

	/**
	 *	\~english
	 *	\brief Access to the element that the iterator points to
	 *
	 *	This operator allows to get access to members of the element that the iterator points to.
	 *	\return The pointer to the element of the iterator.
	 *	\throw std::logic_error The element is not valid (`is_element_valid` method returns
	 *	`false`).
	 *
	 *	\~russian
	 *	\brief Доступ к элементу, на который указывает итератор
	 *
	 *	Этот оператор позволяет получить доступ к членам элемента, на который указывает итератор.
	 *	\return Указатель на элемент итератора.
	 *	\throw std::logic_error Элемент недействителен (метод `is_element_valid` возвращает
	 *	`false`).
	 */
	virtual T_Element* operator->() const override;

private:
	// A new iterator can only be created by the container
	BaseLinkedListIterator_(T_Container& linked_list, int index, std::shared_ptr<T_Node> node = nullptr, bool is_valid = true) noexcept;

	T_Container& container_;
	std::weak_ptr<T_Node> node_;
	int index_;
	bool is_valid_;
};

}

/**
 *	\~english
 *	\brief The iterator of a constant linked list
 *	
 *	This iterator allows to read elements of a linked list, but doesn't allow to modify them or the
 *	linked list. Can be created by a constant linked list (or using `iterator_to_const` method).
 *	\tparam T Type of the linked list elements.
 *	
 *	\~russian
 *	\brief Итератор константного связного списка
 *	
 *	Этот итератор позволяет читать элементы связного списка, но не позволяет изменять их или
 *	связный список. Может быть создан константным связным списком (или методом `iterator_to_const`).
 *	\tparam T Тип элементов массива.
 */
template<typename T>
using ConstLinkedListIterator = BaseLinkedListIterator_<const LinkedList<T>, const T, LinkedListNode_<T>>;

/**
 *	\~english
 *	\brief The iterator of a linked list
 *	
 *	This iterator allows to access elements of a linked list (read and modify them).
 *	\tparam T Type of the linked list elements.
 *	
 *	\~russian
 *	\brief Итератор связного списка
 *	
 *	Этот итератор позволяет получать доступ к элеменам связного списка (читать и изменять их).
 *	\tparam T Тип элементов связного списка.
 */
template<typename T>
using LinkedListIterator = BaseLinkedListIterator_<LinkedList<T>, T, LinkedListNode_<T>>;


		/* DEFINITIONS */

template<typename T_Container, typename T_Element, typename T_Node>
BaseLinkedListIterator_<T_Container, T_Element, T_Node>::BaseLinkedListIterator_(const BaseLinkedListIterator_<T_Container, T_Element, T_Node>& iterator) noexcept :
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
BaseLinkedListIterator_<T_Container, T_Element, T_Node>::BaseLinkedListIterator_(BaseLinkedListIterator_<T_Container, T_Element, T_Node>&& iterator) noexcept :
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
BaseLinkedListIterator_<T_Container, T_Element, T_Node>::~BaseLinkedListIterator_() noexcept
{
	if (is_valid_)
	{
		container_.unregister_iterator_(this);
	}
}

template<typename T_Container, typename T_Element, typename T_Node>
String BaseLinkedListIterator_<T_Container, T_Element, T_Node>::to_string() const noexcept
{
	return util::to_string(get());
}

template<typename T_Container, typename T_Element, typename T_Node>
int BaseLinkedListIterator_<T_Container, T_Element, T_Node>::hash_code() const noexcept
{
	return util::hash_code(get());
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::is_valid() const noexcept
{
	return is_valid_ && index_ >= 0 && index_ <= container_.size();
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::is_element_valid() const noexcept
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
		throw std::logic_error("Attempt to get container of an invalid iterator");
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
		throw std::logic_error("Attempt to get element of an invalid iterator");
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
		throw std::logic_error("Attempt to get index of an invalid iterator");
	}
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::is_begin() const noexcept
{
	return is_valid_ && index_ == 0;
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::is_last() const noexcept
{
	return is_valid_ && index_ == container_.size() - 1;
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::is_end() const noexcept
{
	return is_valid_ && index_ == container_.size();
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::next()
{
	if (is_valid_)
	{
		if (index_ < container_.size())
		{
			node_ = node_.lock()->next;
			return ++index_ < container_.size();
		}
		else
		{
			return false;
		}
	}
	else
	{
		throw std::logic_error("Attempt to increment an invalid iterator");
	}
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::prev()
{
	if (is_valid_)
	{
		if (index_ > 0)
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
	else
	{
		throw std::logic_error("Attempt to decrement an invalid iterator");
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
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::operator==(const BaseLinkedListIterator_<T_Container, T_Element, T_Node>& iterator) const noexcept
{
	return !is_valid_ && !iterator.is_valid_ ||
		&container_ == &iterator.container_ && index_ == iterator.index_;
}

template<typename T_Container, typename T_Element, typename T_Node>
bool BaseLinkedListIterator_<T_Container, T_Element, T_Node>::operator!=(const BaseLinkedListIterator_<T_Container, T_Element, T_Node>& iterator) const noexcept
{
	return !(*this == iterator);
}

template<typename T_Container, typename T_Element, typename T_Node>
T_Element* BaseLinkedListIterator_<T_Container, T_Element, T_Node>::operator->() const
{
	return &get();
}

template<typename T_Container, typename T_Element, typename T_Node>
BaseLinkedListIterator_<T_Container, T_Element, T_Node>::BaseLinkedListIterator_(T_Container& linked_list, int index, std::shared_ptr<T_Node> node, bool is_valid) noexcept :
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
