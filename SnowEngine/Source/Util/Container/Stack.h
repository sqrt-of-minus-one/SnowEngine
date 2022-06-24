    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Stack.h                     //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `Stack` class
 *
 *	This file contains the definition of the `Stack` class.
 *
 *	\~russian
 *	\brief Файл с классом `Stack`
 *
 *	Этот файл содержит определение класса `Stack`.
 */

#include "LinkedList.h"
		// + Object
		// + IContainer

namespace snow
{

/**
 *	\brief The class of the SnowEngine stack
 *	
 *	This stack is based on linked list (the LinkedList class). It allows you to push elements only
 *	into its end, and pop elements only from its the end.
 *	\tparam T The type of elements that are contained in the stack. This type must meet the same
 *	conditions as the template of the LinkedList class.
 */
/**
 *	\~english
 *	\brief The class of stack
 *	
 *	This stack is based on linked list (the `LinkedList` class). It allows you to push elements
 *	only into its end, and pop elements only from the end.
 *	\warning If the stack contains `unique_ptr`'s, methods that copy the stack elements (for
 *	example, the copy constructor) must not be called (`std::logic_error` exception can be thrown).
 *	\tparam T Type of the stack elements. This type must meet the same conditions as the template
 *	of the `LinkedList` class.
 *	
 *	\~russian
 *	\brief Класс стека
 *	
 *	Этот стек основан на связном списке (класс `LinkedList`). Он позволяет добавлять элементы
 *	только в его конец, а также удалять элементы только с конца.
 *	\warning Если стек содержит `unique_ptr`ы, то методы, копирующие элементы стека, (например,
 *	конструктор копирования) не должны вызываться (может быть выброшено исключение
 *	`std::logic_error`).
 *	\tparam T Тип элементов стека. Этот тип должен удовлетворять тем же условиям, что и шаблон
 *	класса `LinkedList`.
 */
template<typename T>
class Stack :
	public Object,
	public IContainer<T>
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates an empty stack.
	 *	
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *	
	 *	Создаёт пустой стек.
	 */
	Stack() noexcept;

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *
	 *	Copies the stack.
	 *	\warning This constructor must not be used if the stack contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param stack The stack that will be copied.
	 *
	 *	\~russian
	 *	\brief Конструктор копирования
	 *
	 *	Копирует стек.
	 *	\warning Этот конструктор не должен быть использован, если стек содержит `unique_ptr`ы
	 *	(может быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param stack Стек, которая будет скопирован.
	 */
	Stack(const Stack<T>& stack) noexcept;

	/**
	 *	\~english
	 *	\brief The move constructor
	 *
	 *	Moves elements to a new stack from the passed one.
	 *	\param stack The stack whose elements will be moved.
	 *
	 *	\~russian
	 *	\brief Конструктор перемещения
	 *
	 *	Перемещает элементы в новый стек из переданного.
	 *	\param stack Стек, чьи элементы будут перемещены.
	 */
	Stack(Stack<T>&& stack) noexcept;
	
			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the stack into a string
	 *	
	 *	Uses the `to_string` method of the internal linked list to convert itself to a string.
	 *	\return A result string.
	 *	
	 *	\~russian
	 *	\brief Конвертирует массив в строку
	 *
	 *	Использует метод `to_string` внутреннего связного списка, чтобы сконвертировать себя в
	 *	строку.
	 *	\return Итоговая строка.
	 */
	virtual String to_string() const noexcept override;

	/**
	 *	\~english
	 *	\brief Hash code of the stack
	 *
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes. Hash code of an stack array is zero.
	 *	\return Hash code of the object.
	 *
	 *	\~russian
	 *	\brief Хеш-код стека
	 *
	 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
	 *	также могут иметь одинаковые хеш-коды. Хеш-код пустого стека — ноль.
	 *	\return Хеш-код объекта.
	 */
	virtual int hash_code() const noexcept override;
	
			/* METHODS FROM IContainer &
				METHODS */
	
	/**
	 *	\~english
	 *	\brief The size of the stack
	 *
	 *	Allows to get the number of elements in the stack.
	 *	\return The number of elements in the stack.
	 *
	 *	\~russian
	 *	\brief Размер стека
	 *
	 *	Позволяет получить количество элеменов в стека.
	 *	\return Количество элеменов в стека.
	 */
	virtual int size() const noexcept override;

	/**
	 *	\~english
	 *	\brief Checks whether the stack is empty
	 *
	 *	Checks whether the stack is empty.
	 *	\return `true` if the stack does not contain any element, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, пуст ли стек
	 *
	 *	Проверяет, пуст ли стек.
	 *	\return `true`, если стек не содержит никаких элементов, иначе `false`.
	 */
	virtual bool is_empty() const noexcept override;

	/**
	 *	\~english
	 *	\brief Clears the stack
	 *
	 *	Removes all of the elements in the stack.
	 *
	 *	\~russian
	 *	\brief Очищает стек
	 *
	 *	Удаляет все элементы стека.
	 */
	virtual void clear() noexcept override;

	/**
	 *	\~english
	 *	\brief The next element of the stack
	 *
	 *	Allows to access the next element of the stack.
	 *	\return A reference to the next element.
	 *	\throw std::out_of_range The stack is empty.
	 *
	 *	\~russian
	 *	\brief Следующий элемент стека
	 *
	 *	Позволяет получить доступ к следующему элементу стека.
	 *	\return Ссылка на следующий элемент.
	 *	\throw std::out_of_range Стек пуста.
	 */
	T& get();

	/**
	 *	\~english
	 *	\brief The next element of the stack
	 *
	 *	Allows to read the next element of the stack.
	 *	\return A constant reference to the next element.
	 *	\throw std::out_of_range The stack is empty.
	 *
	 *	\~russian
	 *	\brief Следующий элемент стека
	 *
	 *	Позволяет прочитать следующий элемент стека.
	 *	\return Константная ссылка на следующий элемент.
	 *	\throw std::out_of_range Стек пуста.
	 */
	const T& get() const;

	/**
	 *	\~english
	 *	\brief Removes the next element of the stack and returns it
	 *
	 *	Removes the next element of the stack and returns its value.
	 *	\return The value of the removed element.
	 *	\throw std::out_of_range The stack is empty.
	 *
	 *	\~russian
	 *	\brief Удаляет следующий элемент стека и возвращает его
	 *
	 *	Удаляет следующий элемент стека и возвращает его значение.
	 *	\return Значение удалённого элемента.
	 *	\throw std::out_of_range Стек пуста.
	 */
	T&& pop();

	/**
	 *	\~english
	 *	\brief Inserts the element in the stack
	 *
	 *	Inserts the passed element in the stack.
	 *	\warning This method must not be used if the stack contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param element The element that will be inserted.
	 *
	 *	\~russian
	 *	\brief Вставляет элемент в стек
	 *
	 *	Вставляет переданный элемент в стек.
	 *	\warning Этот метод не должен быть использован, если стек содержит `unique_ptr`ы (может
	 *	быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param element Элемент, который будет добавлен.
	 */
	bool push(const T& element);

	/**
	 *	\~english
	 *	\brief Inserts the element in the stack
	 *
	 *	Inserts the passed element in the stack.
	 *	\param element The element that will be inserted.
	 *
	 *	\~russian
	 *	\brief Вставляет элемент в стек
	 *
	 *	Вставляет переданный элемент в стек.
	 *	\param element Элемент, который будет добавлен.
	 */
	bool push(T&& element);

	/**
	 *	\~english
	 *	\brief Removes all elements that are equal to the passed one
	 *
	 *	Compares every element of the stack with the passed one and removes all matches.
	 *	\param element The object to compare.
	 *	\return Number of elements that have been successfully removed.
	 *
	 *	\~russian
	 *	\brief Удаляет все элементы, равные переданному
	 *
	 *	Сравнивает каждый элемент стека с переданным и удаляет все совпадения.
	 *	\param element Объект для сравнения.
	 *	\return Количество успешно удалённых элементов.
	 */
	virtual int remove_all(const T& element) override;

	/**
	 *	\~english
	 *	\brief Checks whether the stack contains the passed element
	 *
	 *	Checks whether the stack has an element that is equal to the passed one.
	 *	\param element The desired element.
	 *	\return `true` if the stack contains the passed element, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, содержит ли стек переданный элемент
	 *
	 *	Проверяет, содержит ли стек элемент, равный переданному.
	 *	\param element Искомый элемент.
	 *	\return `true`, если стек содержит переданный элемент, иначе `false`.
	 */
	virtual bool contains(const T& element) const override;

	/**
	 *	\~english
	 *	\brief How many elements of the stack are equal to the passed one
	 *
	 *	Counts elements that are equal to the passed one.
	 *	\param element The desired element.
	 *	\return Number of matches.
	 *
	 *	\~russian
	 *	\brief Сколько элементов стека равны переданному
	 *
	 *	Подсчитывает элементы, равные переданному.
	 *	\param element Требуемый элемент.
	 *	\return Количество совпадений.
	 */
	virtual int count(const T& element) const override;
	
			/* OPERATORS */

	/**
	 *	\~english
	 *	\brief The copy assignment operator
	 *	
	 *	Clears the stack and inserts into it copies of elements of the passed stack.
	 *	\warning This operator must not be used if the stack contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param stack The stack to assign.
	 *	\return A reference to itself.
	 *	
	 *	\~russian
	 *	\brief Оператор присваивания копированием
	 *	
	 *	Очищает стек и вставляет в неё копии элементов переданного стека.
	 *	\warning Этот оператор не должен быть использован, если стек содержит `unique_ptr`ы
	 *	(может быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param stack Стек для присваивания.
	 *	\return Ссылка на себя.
	 */
	Stack<T>& operator=(const Stack<T>& stack);

	/**
	 *	\~english
	 *	\brief The move assignment operator
	 *
	 *	Clears the stack and moves into it elements of the passed stack.
	 *	\param stack The stack to assign.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Оператор присваивания перемещением
	 *
	 *	Очищает стек и перемещает в неё элементы переданного стека.
	 *	\param stack Стек для присваивания.
	 *	\return Ссылка на себя.
	 */
	Stack<T>& operator=(Stack<T>&& stack);

	/**
	 *	\~english
	 *	\brief Checks whether two stacks are equal
	 *
	 *	Two stacks are equal if all of their elements are equal and have the same order.
	 *	\param stack The stack to compare.
	 *	\return `true` if two stacks are equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, равны ли два стека
	 *
	 *	Два стека равны, если их элементы равны и находятся в одинаковом порядке.
	 *	\param stack Стек для сравнения.
	 *	\return `true`, если два стека равны, иначе `false`.
	 */
	bool operator==(const Stack<T>& stack) const;

	/**
	 *	\~english
	 *	\brief Checks whether two stacks are not equal
	 *
	 *	Two stacks are equal if all of their elements are equal and have the same order.
	 *	\param stack The stack to compare.
	 *	\return `true` if two stacks are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, различаются ли два стека
	 *
	 *	Два стека равны, если их элементы равны и находятся в одинаковом порядке.
	 *	\param stack Стек для сравнения.
	 *	\return `true`, если два стека не равны, иначе `false`.
	 */
	bool operator!=(const Stack<T>& stack) const;

private:
	LinkedList<T> list;
};


		/* DEFINITIONS */
		
		/* Stack: public */

template<typename T>
Stack<T>::Stack() noexcept :
	list()
{}

template<typename T>
Stack<T>::Stack(const Stack<T>& stack) noexcept :
	list(stack.list)
{}

template<typename T>
Stack<T>::Stack(Stack<T>&& stack) noexcept :
	list(std::move(stack.list))
{}

template<typename T>
String Stack<T>::to_string() const noexcept
{
	return list.to_string();
}

template<typename T>
int Stack<T>::hash_code() const noexcept
{
	return list.hash_code();
}

template<typename T>
int Stack<T>::size() const noexcept
{
	return list.size();
}

template<typename T>
bool Stack<T>::is_empty() const noexcept
{
	return list.is_empty();
}

template<typename T>
void Stack<T>::clear() noexcept
{
	return list.clear();
}

template<typename T>
T& Stack<T>::get()
{
	return list.get_last();
}

template<typename T>
const T& Stack<T>::get() const
{
	return list.get_last();
}

template<typename T>
T&& Stack<T>::pop()
{
	T ret = list.get_last();
	list.remove(list.last());
	return ret;
}

template<typename T>
bool Stack<T>::push(const T& element)
{
	return list.add(element);
}

template<typename T>
bool Stack<T>::push(T&& element)
{
	return list.add(std::forward<T>(element));
}

template<typename T>
int Stack<T>::remove_all(const T& element)
{
	return list.remove_all(element);
}

template<typename T>
bool Stack<T>::contains(const T& element) const
{
	return list.contains(element);
}

template<typename T>
int Stack<T>::count(const T& element) const
{
	return list.count(element);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& stack)
{
	list = stack.list;
	return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& stack)
{
	list = std::move(stack.list);
	return *this;
}

template<typename T>
bool Stack<T>::operator==(const Stack<T>& stack) const
{
	return list == stack.list;
}

template<typename T>
bool Stack<T>::operator!=(const Stack<T>& stack) const
{
	return list != stack.list;
}

}
