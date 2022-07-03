    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: MapIterator.h               //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file of map iterator
 *	
 *	This file contains the definitions of the map iterator classes.
 *	
 *	\~russian
 *	\brief Файл итератора словаря
 *	
 *	Этот файл содержит определения классов итераторов словаря.
*/

#include "../../Object.h"
#include "Container.h"

#include "../Types/String.h"

namespace snow
{

template<typename T_Key, typename T_Value>
class Map;

namespace
{

/**
 *	\~english
 *	\brief The base for map iterators
 *	
 *	This class is used as a template for `MapIterator` and `ConstMapIterator` classes.
 *	\warning Do not use this class directly.
 *	\tparam T_Container Type of the container (`Map` or `const Map`).
 *	\tparam T_Element Type of the map elements (taking into account `const` modifier).
 *	
 *	\~russian
 *	\brief Основа для итераторов словаря
 *	
 *	Этот класс используется как шаблон для классов `MapIterator` и `MapIterator`.
 *	\warning Не используйте этот класс напрямую.
 *	\tparam T_Container Тип контейнера (`Map` или `const Map`).
 *	\tparam T_Element Тип элемента словаря (с учётом модификатора `const`).
 */
template<typename T_Container, typename T_Key, typename T_Value>
class BaseMapIterator_ :
	public Object,
	public IIterator<T_Container, T_Value>
{
	template<typename T_Key, typename T_Value>
	friend class Map;

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
	BaseMapIterator_(const BaseMapIterator_<T_Container, T_Key, T_Value>& iterator);

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
	BaseMapIterator_(BaseMapIterator_<T_Container, T_Key, T_Value>&& iterator);

	/**
	 *	\~english
	 *	\brief The destructor
	 *
	 *	The destructor of the map iterator.
	 *
	 *	\~russian
	 *	\brief Деструктор
	 *
	 *	Деструктор итератора словаря.
	 */
	virtual ~BaseMapIterator_();

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
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Hash code of the map iterator
	 *
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes. Hash code of an invalid iterator is zero.
	 *	\return Hash code of the object.
	 *
	 *	\~russian
	 *	\brief Хеш-код итератора словаря
	 *
	 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
	 *	также могут иметь одинаковые хеш-коды. Хеш-код недействительного итератора — ноль.
	 *	\return Хеш-код объекта.
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
	 *	This function returns `false` if the iterator is not valid or points to the end of the map
	 *	(i. e. after the last map element).
	 *	\return `true` if the iterator points to a valid element, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, указывает ли итератор на действительный элемент
	 *
	 *	Эта функция возвращает `false`, если итератор недействителен или указывает на конец
	 *	словаря (т. е. после последнего элемента словаря).
	 *	\return `true`, если итератор указывает на действительный элемент, иначе `false`.
	 */
	virtual bool is_element_valid() const noexcept override;

	/**
	 *	\~english
	 *	\brief The container of the iterator
	 *
	 *	Allows to get the map that has the element that the iterator points to.
	 *	\return The container of the iterator.
	 *	\throw std::logic_error The iterator is not valid.
	 *	
	 *	\~russian
	 *	\brief Контейнер итератора
	 *	
	 *	Позволяет получить словарь, на элемент которого указывает итератор.
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
	virtual T_Value& get() const override;

	/**
	 *	\~english
	 *	\brief The key of the element that the iterator points to
	 *	
	 *	Allows to get the key that the iterator element is associated with.
	 *	\return The key of the iterator element.
	 *	\throw std::logic_error The iterator is not valid.
	 *	
	 *	\~russian
	 *	\brief Ключ элемента, на который указывает итератор
	 *	
	 *	Позволяет получить ключ, которому соответствует элемент итератора.
	 *	\return Ключ элемента, на который указывает итератор.
	 *	\throw std::logic_error Итератор недействителен.
	 */
	const T_Key& get_key() const;

	/**
	 *	\~english
	 *	\brief Checks whether the iterator points to the first element of the map
	 *
	 *	The iterator is begin if it points to the first element.
	 *	\return `true` if the iterator points to the first element of the map, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, указывает ли итератор на первый элемент словаря
	 *	
	 *	Проверяет, указывает ли итератор на первый элемент словаря.
	 *	\return `true`, если итератор указывает на первый элемент словаря, иначе `false`.
	 */
	virtual bool is_begin() const override;

	/**
	 *	\~english
	 *	\brief Checks whether the iterator points to the last element of the map
	 *
	 *	The iterator is last if it points to the last element.
	 *	\return `true` if the iterator points to the last element of the map, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, указывает ли итератор на последний элемент словаря
	 *
	 *	Проверяет, указывает ли итератор на последний элемент словаря.
	 *	\return `true`, если итератор указывает на последний элемент словаря, иначе `false`.
	 */
	virtual bool is_last() const override;

	/**
	 *	\~english
	 *	\brief Checks whether the iterator points after the last element of the map
	 *
	 *	The iterator is end if it points to a space that is after the last element. In this case
	 *	`is_element_valid` method returns `false`.
	 *	\return `true` if the iterator points after the last element of the map, `false`
	 *	otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, указывает ли итератор после последнего элемента словаря
	 *
	 *	Итератор указывает в конец, если он указывает на пространство после последнего элемента
	 *	словаря. В этом случае метод `is_element_valid` возвращает `false`.
	 *	\return `true`, если итератор указывает после последнего элемента словаря, иначе `false`.
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
	virtual T_Value& operator*() const override;

	/**
	 *	\~english
	 *	\brief The prefix increment of the iterator
	 *
	 *	Changes the iterator so that it points to the next element. The iterator won't be changed
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
	BaseMapIterator_<T_Container, T_Key, T_Value> operator++();

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
	BaseMapIterator_<T_Container, T_Key, T_Value> operator--();

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
	BaseMapIterator_<T_Container, T_Key, T_Value> operator++(int);

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
	BaseMapIterator_<T_Container, T_Key, T_Value> operator--(int);

	/**
	 *	\~english
	 *	\brief Checks whether two iterators are equal
	 *
	 *	Two map iterators are equal if they point to the same element of the same map. The
	 *	iterators are also equal if they are both invalid.
	 *	\return `true` if the iterators are equal, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, равны ли два итератора
	 *	
	 *	Два итератора словаря равны, если они указывают на один и тот же элемент одного и того же
	 *	словаря. Итераторы также равны, если они оба недействительны.
	 *	\return `true`, если итераторы равны, иначе `false`.
	 */
	bool operator==(const BaseMapIterator_<T_Container, T_Key, T_Value>& iterator) const noexcept(
		noexcept(std::declval<T_Key> == std::declval<T_Key>()));

	/**
	 *	\~english
	 *	\brief Checks whether two iterators are not equal
	 *
	 *	Two map iterators are equal if they point to the same element of the same map. The
	 *	iterators are also equal if they are both invalid.
	 *	\return `true` if the iterators are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, различаются ли два итератора
	 *
	 *	Два итератора словаря равны, если они указывают на один и тот же элемент одного и того же
	 *	словаря. Итераторы также равны, если они оба недействительны.
	 *	\return `true`, если итераторы не равны, иначе `false`.
	 */
	bool operator!=(const BaseMapIterator_<T_Container, T_Key, T_Value>& iterator) const noexcept(
		noexcept(std::declval<T_Key> == std::declval<T_Key>()));

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
	T_Value* operator->() const;

protected:
	// A new iterator can only be created by the container
	BaseMapIterator_(T_Container& map, const T_Key& key, bool is_end, bool is_valid = true);

	T_Container& container_;
	T_Key key_;
	bool is_end_;
	bool is_valid_;
};

}

/**
 *	\~english
 *	\brief The iterator of a constant map
 *
 *	This iterator allows to read elements of a map, but doesn't allow to modify them or the map.
 *	Can be created by a constant map (or using `iterator_to_const` method). Information about
 *	members is contained in the documentation of the `BaseMapIterator_` class. Order of elements is
 *	defined by the map and is the same for all iterators.
 *	\tparam T Type of the map elements.
 *
 *	\~russian
 *	\brief Итератор константного словаря
 *
 *	Этот итератор позволяет читать элементы словаря, но не позволяет изменять их или словарь.
 *	Может быть создан константным словарём (или методом `iterator_to_const`). Информация о членах
 *	содержится в документации класса `BaseMapIterator_`. Порядок элементов определяется словарём и
 *	одинаков для всех итераторов.
 *	\tparam T Тип элементов массива.
 */
template<typename T_Key, typename T_Value>
using ConstMapIterator = BaseMapIterator_<const Map<T_Key, T_Value>, T_Key, const T_Value>;

/**
 *	\~english
 *	\brief The iterator of a map
 *
 *	This iterator allows to access elements of a map (read and modify them). Information about
 *	members is contained in the documentation of the `BaseMapIterator_` class.Order of elements is
 *	defined by the map and is the same for all iterators.
 *	\tparam T Type of the linked list elements.
 *
 *	\~russian
 *	\brief Итератор словаря
 *
 *	Этот итератор позволяет получать доступ к элеменам словаря (читать и изменять их). Информация
 *	о членах содержится в документации класса `BaseMapIterator_`. Порядок элементов определяется
 *	словарём и одинаков для всех итераторов.
 *	\tparam T Тип элементов связного списка.
 */
template<typename T_Key, typename T_Value>
using MapIterator = BaseMapIterator_<Map<T_Key, T_Value>, T_Key, T_Value>;


		/* DEFINITIONS */
		
		/* BaseMapIterator_: public */

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
String BaseMapIterator_<T_Container, T_Key, T_Value>::to_string() const
{
	return util::to_string(get());
}

template<typename T_Container, typename T_Key, typename T_Value>
int BaseMapIterator_<T_Container, T_Key, T_Value>::hash_code() const noexcept
{
	try
	{
		return util::hash_code(get());
	}
	catch (std::logic_error e)
	{
		return 0;
	}
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::is_valid() const noexcept
{
	return is_valid_;
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::is_element_valid() const noexcept
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
		throw std::logic_error("Attempt to get container of an invalid iterator");
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
		throw std::logic_error("Attempt to get element of an invalid iterator");
	}
}

template<typename T_Container, typename T_Key, typename T_Value>
const T_Key& BaseMapIterator_<T_Container, T_Key, T_Value>::get_key() const
{
	if (is_element_valid())
	{
		return key_;
	}
	else
	{
		throw std::logic_error("Attempt to get key of an invalid iterator");
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
bool BaseMapIterator_<T_Container, T_Key, T_Value>::is_end() const noexcept
{
	return is_valid_ && is_end_;
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::next()
{
	if (is_valid_)
	{
		if (!is_end_)
		{
			if (container_.map_[container_.last_filled_].get_last().get_first() != key_)
			{
				int hash = math::abs(util::hash_code(key_) % container_.internal_size_);
				auto& list = container_.map_[hash];
				auto itr = list.begin();
				while (itr.get().get_first() != key_ && itr.next());
				if (itr.is_last())
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
	else
	{
		throw std::logic_error("Attempt to increment an invalid iterator");
	}
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::prev()
{
	if (is_valid_)
	{
		if (container_.map_[container_.first_filled_].get_begin().get_first() != key_)
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
	else
	{
		throw std::logic_error("Attempt to decrement an invalid iterator");
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
bool BaseMapIterator_<T_Container, T_Key, T_Value>::operator==(const BaseMapIterator_<T_Container, T_Key, T_Value>& iterator) const noexcept(
	noexcept(std::declval<T_Key> == std::declval<T_Key>()))
{
	return !is_valid() && !iterator.is_valid() ||
		&container_ == &iterator.container_ &&
		(is_end_ && iterator.is_end_ || !is_end_ && !iterator.is_end_ && key_ == iterator.key_);
}

template<typename T_Container, typename T_Key, typename T_Value>
bool BaseMapIterator_<T_Container, T_Key, T_Value>::operator!=(const BaseMapIterator_<T_Container, T_Key, T_Value>& iterator) const noexcept(
	noexcept(std::declval<T_Key> == std::declval<T_Key>()))
{
	return !(*this == iterator);
}

template<typename T_Container, typename T_Key, typename T_Value>
T_Value* BaseMapIterator_<T_Container, T_Key, T_Value>::operator->() const
{
	return &get();
}
		
		/* BaseMapIterator_: private */

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