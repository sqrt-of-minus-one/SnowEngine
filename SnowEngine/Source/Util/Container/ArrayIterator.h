    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ArrayIterator.h             //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file of array iterator
 *	
 *	This file contains the definitions of the array iterator classes.
 *	
 *	\~russian
 *	\brief Файл итератора массива
 *	
 *	Этот файл содержит определения классов итераторов массива.
 */

#include "../../Object.h"
#include "Container.h"

#include "../Util.h"
#include "../Types/String.h"

namespace snow
{

template<typename T>
class Array;

namespace
{

/**
 *	\~english
 *	\brief The base for array iterators
 *	
 *	This class is used as a template for `ArrayIterator` and `ConstArrayIterator` classes.
 *	\warning Do not use this class directly.
 *	\tparam T_Container Type of the container (`Array` or `const Array`).
 *	\tparam T_Element Type of the array elements (taking into account `const` modifier).
 *	
 *	\~russian
 *	\brief Основа для итераторов массива
 *	
 *	Этот класс используется как шаблон для классов `ArrayIterator` и `ConstArrayIterator`.
 *	\warning Не используйте этот класс напрямую.
 *	\tparam T_Container Тип контейнера (`Array` или `const Array`).
 *	\tparam T_Element Тип элемента массива (с учётом модификатора `const`).
 */
template<typename T_Container, typename T_Element>
class BaseArrayIterator_ :
	public Object,
	public IIterator<T_Container, T_Element>
{
	template<typename T>
	friend class Array;

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
	BaseArrayIterator_(const BaseArrayIterator_<T_Container, T_Element>& iterator) noexcept;

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
	BaseArrayIterator_(BaseArrayIterator_<T_Container, T_Element>&& iterator) noexcept;

	/**
	 *	\~english
	 *	\brief The destructor
	 *	
	 *	The destructor of the array iterator.
	 *	
	 *	\~russian
	 *	\brief Деструктор
	 *	
	 *	Деструктор итератора массива.
	 */
	virtual ~BaseArrayIterator_() noexcept;

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
	 *	array (i. e. after the last array element).
	 *	\return `true` if the iterator points to a valid element, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, указывает ли итератор на действительный элемент
	 *	
	 *	Эта функция возвращает `false`, если итератор недействителен или указывает на конец массива
	 *	(т. е. после последнего элемента массива).
	 *	\return `true`, если итератор указывает на действительный элемент, иначе `false`.
	 */
	virtual bool is_element_valid() const noexcept override;
	
	/**
	 *	\~english
	 *	\brief The container of the iterator
	 *
	 *	Allows to get the array that has the element that the iterator points to.
	 *	\return The container of the iterator.
	 *	\throw std::logic_error The iterator is not valid.
	 *	
	 *	\~russian
	 *	\brief Контейнер итератора
	 *	
	 *	Позволяет получить массив, на элемент которого указывает итератор.
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
	 *	\return Индекс элемента.
	 *	\throw std::logic_error Итератор недействителен.
	 */
	int get_index() const;

	/**
	 *	\~english
	 *	\brief Checks whether the iterator points to the first element of the array
	 *
	 *	The iterator is begin if it points to the first element.
	 *	\return `true` if the iterator points to the first element of the array, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, указывает ли итератор на первый элемент массива
	 *	
	 *	Проверяет, указывает ли итератор на первый элемент массива.
	 *	\return `true`, если итератор указывает на первый элемент массива, иначе `false`.
	 */
	virtual bool is_begin() const noexcept override;

	/**
	 *	\~english
	 *	\brief Checks whether the iterator points to the last element of the array
	 *
	 *	The iterator is last if it points to the last element.
	 *	\return `true` if the iterator points to the last element of the array, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, указывает ли итератор на последний элемент массива
	 *
	 *	Проверяет, указывает ли итератор на последний элемент массива.
	 *	\return `true`, если итератор указывает на последний элемент массива, иначе `false`.
	 */
	virtual bool is_last() const noexcept override;

	/**
	 *	\~english
	 *	\brief Checks whether the iterator points after the last element of the array
	 *
	 *	The iterator is end if it points to a space that is after the last element. In this case
	 *	`is_element_valid` method returns `false`.
	 *	\return `true` if the iterator points after the last element of the array, `false`
	 *	otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, указывает ли итератор после последнего элемента массива
	 *
	 *	Итератор указывает в конец, если он указывает на пространство после последнего элемента
	 *	массива. В этом случае метод `is_element_valid` возвращает `false`.
	 *	\return `true`, если итератор указывает после последнего элемента массива, иначе `false`.
	 */
	virtual bool is_end() const noexcept override;

	/**
	 *	\~english
	 *	\brief Moves the iterator forward
	 *
	 *	Increases the iterator index so that it points to the next element. The iterator won't be
	 *	changed if it is already pointing after the last element.
	 *	\return `true` if the new element of the iterator is valid (is not end), `false` otherwise.
	 *	\throw std::logic_error The iterator is not valid.
	 *	
	 *	\~russian
	 *	\brief Перемещает элемент вперёд
	 *	
	 *	Увеличивает индекс итератора, чтобы он указывал на следующий элемент. Итератор не будет
	 *	изменён, если он уже указывает после последнего элемента.
	 *	\return `true`, если новый элемент итератора действителен (итератор не указывает после
	 *	последнего элемента), иначе `false`.
	 *	\throw std::logic_error Итератор недействителен.
	 */
	virtual bool next() override;

	/**
	 *	\~english
	 *	\brief Moves the iterator backward
	 *
	 *	Decreases the iterator index so that it points to the previous element. The iterator won't
	 *	be changed if it is already pointing to the first element.
	 *	\return `true` if the iterator has been moved, `false` otherwise.
	 *	\throw std::logic_error The iterator is not valid.
	 *	
	 *	\~russian
	 *	\brief Перемещает элемент назад
	 *	
	 *	Уменьшает индекс итератора, чтобы он указывал на предыдущий элемент. Итератор не будет
	 *	изменён, если он уже указывает на первый элемент.
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
	 *	Increases the iterator index so that it points to the next element. The iterator won't be
	 *	changed if it is already pointing after the last element.
	 *	\return The moved iterator.
	 *	\throw std::logic_error The iterator is not valid.
	 *
	 *	\~russian
	 *	\brief Префиксный инкремент итератора
	 *
	 *	Увеличивает индекс итератора, чтобы он указывал на следующий элемент. Итератор не будет
	 *	изменён, если он уже указывает после последнего элемента.
	 *	\return Перемещённый итератор.
	 *	\throw std::logic_error Итератор недействителен.
	 */
	BaseArrayIterator_<T_Container, T_Element> operator++();

	/**
	 *	\brief The prefix decrement of the iterator
	 *
	 *	Decreases the iterator index so that it points to the previous element. The iterator won't
	 *	be changed if it is already pointing after the last element.
	 *	\return The moved iterator.
	 *	\throw std::logic_error The iterator is not valid.
	 *
	 *	\~russian
	 *	\brief Префиксный декремент итератора
	 *
	 *	Уменьшает индекс итератора, чтобы он указывал на предыдущий элемент. Итератор не будет
	 *	изменён, если он уже указывает на первый элемент.
	 *	\return Перемещённый итератор.
	 *	\throw std::logic_error Итератор недействителен.
	 */
	BaseArrayIterator_<T_Container, T_Element> operator--();

	/**
	 *	\~english
	 *	\brief The postfix increment of the iterator
	 *
	 *	Increases the iterator index so that it points to the next element. The iterator won't be
	 *	changed if it is already pointing after the last element.
	 *	\return The iterator before moving.
	 *	\throw std::logic_error The iterator is not valid.
	 *
	 *	\~russian
	 *	\brief Постфиксный инкремент итератора
	 *
	 *	Увеличивает индекс итератора, чтобы он указывал на следующий элемент. Итератор не будет
	 *	изменён, если он уже указывает после последнего элемента.
	 *	\return Итератор до перемещения.
	 *	\throw std::logic_error Итератор недействителен.
	 */
	BaseArrayIterator_<T_Container, T_Element> operator++(int);

	/**
	 *	\brief The postfix decrement of the iterator
	 *
	 *	Decreases the iterator index so that it points to the previous element. The iterator won't
	 *	be changed if it is already pointing after the last element.
	 *	\return The iterator before moving.
	 *	\throw std::logic_error The iterator is not valid.
	 *
	 *	\~russian
	 *	\brief Постфиксный декремент итератора
	 *
	 *	Уменьшает индекс итератора, чтобы он указывал на предыдущий элемент. Итератор не будет
	 *	изменён, если он уже указывает на первый элемент.
	 *	\return Итератор до перемещения.
	 *	\throw std::logic_error Итератор недействителен.
	 */
	BaseArrayIterator_<T_Container, T_Element> operator--(int);

	/**
	 *	\~english
	 *	\brief Checks whether two iterators are equal
	 *
	 *	Two array iterators are equal if they point to the same element of the same array. The
	 *	iterators are also equal if they are both invalid.
	 *	\return `true` if the iterators are equal, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, равны ли два итератора
	 *	
	 *	Два итератора массива равны, если они указывают на один и тот же элемент одного и того же
	 *	массива. Итераторы также равны, если они оба недействительны.
	 *	\return `true`, если итераторы равны, иначе `false`.
	 */
	bool operator==(const BaseArrayIterator_<T_Container, T_Element>& iterator) const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether two iterators are not equal
	 *
	 *	Two array iterators are equal if they point to the same element of the same array. The
	 *	iterators are also equal if they are both invalid.
	 *	\return `true` if the iterators are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, различаются ли два итератора
	 *
	 *	Два итератора массива равны, если они указывают на один и тот же элемент одного и того же
	 *	массива. Итераторы также равны, если они оба недействительны.
	 *	\return `true`, если итераторы не равны, иначе `false`.
	 */
	bool operator!=(const BaseArrayIterator_<T_Container, T_Element>& iterator) const noexcept;
	
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
	BaseArrayIterator_(T_Container& array, int index, bool is_valid = true) noexcept;

	T_Container& container_;
	int index_;
	bool is_valid_;
};

}

/**
 *	\~english
 *	\brief The iterator of a constant array
 *	
 *	This iterator allows to read elements of an array, but doesn't allow to modify them or the
 *	array. Can be created by a constant array (or using `iterator_to_const` method). Information
 *	about members is contained in the documentation of the `BaseArrayIterator_` class.
 *	\tparam T Type of the array elements.
 *	
 *	\~russian
 *	\brief Итератор константного массива
 *	
 *	Этот итератор позволяет читать элементы массива, но не позволяет изменять их или массив. Может
 *	быть создан константным массивом (или методом `iterator_to_const`). Информация о членах
 *	содержится в документации класса `BaseArrayIterator_`.
 *	\tparam T Тип элементов массива.
 */
template<typename T>
using ConstArrayIterator = BaseArrayIterator_<const Array<T>, const T>;

/**
 *	\~english
 *	\brief The iterator of an array
 *	
 *	This iterator allows to access elements of an array (read and modify them). Information about
 *	members is contained in the documentation of the `BaseArrayIterator_` class.
 *	\tparam T Type of the array elements.
 *	
 *	\~russian
 *	\brief Итератор массива
 *	
 *	Этот итератор позволяет получать доступ к элеменам массива (читать и изменять их). Информация
 *	о членах содержится в документации класса `BaseArrayIterator_`.
 *	\tparam T Тип элементов массива.
 */
template<typename T>
using ArrayIterator = BaseArrayIterator_<Array<T>, T>;


		/* DEFINITIONS */

		/* BaseArrayIterator_: public */

template<typename T_Container, typename T_Element>
BaseArrayIterator_<T_Container, T_Element>::BaseArrayIterator_(const BaseArrayIterator_<T_Container, T_Element>& iterator) noexcept :
	container_(iterator.container_),
	index_(iterator.index_),
	is_valid_(iterator.is_valid_)
{
	if (is_valid_)
	{
		container_.register_iterator_(this);
	}
}

template<typename T_Container, typename T_Element>
BaseArrayIterator_<T_Container, T_Element>::BaseArrayIterator_(BaseArrayIterator_<T_Container, T_Element>&& iterator) noexcept :
	container_(iterator.container_),
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

template<typename T_Container, typename T_Element>
BaseArrayIterator_<T_Container, T_Element>::~BaseArrayIterator_() noexcept
{
	if (is_valid_)
	{
		container_.unregister_iterator_(this);
	}
}

template<typename T_Container, typename T_Element>
String BaseArrayIterator_<T_Container, T_Element>::to_string() const noexcept
{
	return util::to_string(get());
}

template<typename T_Container, typename T_Element>
int BaseArrayIterator_<T_Container, T_Element>::hash_code() const noexcept
{
	return util::hash_code(get());
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::is_valid() const noexcept
{
	return is_valid_ && index_ >= 0 && index_ <= container_.size();
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::is_element_valid() const noexcept
{
	return is_valid_ && index_ >= 0 && index_ < container_.size();
}

template<typename T_Container, typename T_Element>
T_Container& BaseArrayIterator_<T_Container, T_Element>::get_container() const
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

template<typename T_Container, typename T_Element>
T_Element& BaseArrayIterator_<T_Container, T_Element>::get() const
{
	if (is_element_valid())
	{
		return container_[index_];
	}
	else
	{
		throw std::logic_error("Attempt to get element of an invalid iterator");
	}
}

template<typename T_Container, typename T_Element>
int BaseArrayIterator_<T_Container, T_Element>::get_index() const
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

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::is_begin() const noexcept
{
	return is_valid_ && index_ == 0;
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::is_last() const noexcept
{
	return is_valid_ && index_ == container_.size() - 1;
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::is_end() const noexcept
{
	return is_valid_ && index_ == container_.size();
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::next()
{
	if (is_valid_)
	{
		return index_ < container_.size() && ++index_ < container_.size();

//		// This do the same:
//		if (is_end())
//		{
//			return false;
//		}
//		else
//		{
//			index_++;
//			return !is_end();
//		}
	}
	else
	{
		throw std::logic_error("Attempt to increment an invalid iterator");
	}
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::prev()
{
	if (is_valid_)
	{
		if (index_ > 0)
		{
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

template<typename T_Container, typename T_Element>
T_Element& BaseArrayIterator_<T_Container, T_Element>::operator*() const
{
	return get();
}

template<typename T_Container, typename T_Element>
BaseArrayIterator_<T_Container, T_Element> BaseArrayIterator_<T_Container, T_Element>::operator++()
{
	next();
	return *this;
}

template<typename T_Container, typename T_Element>
BaseArrayIterator_<T_Container, T_Element> BaseArrayIterator_<T_Container, T_Element>::operator--()
{
	prev();
	return *this;
}

template<typename T_Container, typename T_Element>
BaseArrayIterator_<T_Container, T_Element> BaseArrayIterator_<T_Container, T_Element>::operator++(int)
{
	auto ret = *this;
	next();
	return ret;
}

template<typename T_Container, typename T_Element>
BaseArrayIterator_<T_Container, T_Element> BaseArrayIterator_<T_Container, T_Element>::operator--(int)
{
	auto ret = *this;
	prev();
	return ret;
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::operator==(const BaseArrayIterator_<T_Container, T_Element>& iterator) const noexcept
{
	return !is_valid() && !iterator.is_valid() ||
		&container_ == &iterator.container_ && index_ == iterator.index_;
}

template<typename T_Container, typename T_Element>
bool BaseArrayIterator_<T_Container, T_Element>::operator!=(const BaseArrayIterator_<T_Container, T_Element>& iterator) const noexcept
{
	return !(*this == iterator);
}

template<typename T_Container, typename T_Element>
T_Element* BaseArrayIterator_<T_Container, T_Element>::operator->() const
{
	return &get();
}

		/* BaseArrayIterator_: private */

template<typename T_Container, typename T_Element>
BaseArrayIterator_<T_Container, T_Element>::BaseArrayIterator_(T_Container& array, int index, bool is_valid) noexcept :
	container_(array),
	index_(index),
	is_valid_(is_valid)
{
	if (is_valid_)
	{
		container_.register_iterator_(this);
	}
}

}
