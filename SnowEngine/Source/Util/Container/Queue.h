    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Queue.h                     //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `Queue` class
 *	
 *	This file contains the definition of the `Queue` class.
 *	
 *	\~russian
 *	\brief Файл с классом `Queue`
 *	
 *	Этот файл содержит определение класса `Queue`.
 */

#include "LinkedList.h"

namespace snow
{

/**
 *	\~english
 *	\brief The class of queue
 *	
 *	This queue is based on linked list (the `LinkedList` class). It allows you to push elements
 *	only into its end, and pop elements only from the beginning.
 *	\warning If the queue contains `unique_ptr`'s, methods that copy the queue elements (for
 *	example, the copy constructor) must not be called (`std::logic_error` exception can be thrown).
 *	\tparam T Type of the queue elements. This type must meet the same conditions as the template
 *	of the `LinkedList` class.
 *	
 *	\~russian
 *	\breif Класс очереди
 *	
 *	Эта очередь основана на связном списке (класс `LinkedList`). Она позволяет добавлять элементы
 *	только в её конец, а также удалять элементы только с начала.
 *	\warning Если очередь содержит `unique_ptr`ы, то методы, копирующие элементы очереди,
 *	(например, конструктор копирования) не должны вызываться (может быть выброшено исключение
 *	`std::logic_error`).
 *	\tparam T Тип элементов очереди. Этот тип должен удовлетворять тем же условиям, что и шаблон
 *	класса `LinkedList`.
 */
template<typename T>
class Queue :
	public Object,
	public IContainer<T>
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates an empty queue.
	 *	
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *	
	 *	Создаёт пустую очередь.
	 */
	Queue() noexcept;

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *
	 *	Copies the queue.
	 *	\warning This constructor must not be used if the queue contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param queue The queue that will be copied.
	 *
	 *	\~russian
	 *	\brief Конструктор копирования
	 *
	 *	Копирует очередь.
	 *	\warning Этот конструктор не должен быть использован, если очередь содержит `unique_ptr`ы
	 *	(может быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param queue Очередь, которая будет скопирован.
	 */
	Queue(const Queue<T>& queue) noexcept;

	/**
	 *	\~english
	 *	\brief The move constructor
	 *
	 *	Moves elements to a new queue from the passed one.
	 *	\param queue The queue whose elements will be moved.
	 *
	 *	\~russian
	 *	\brief Конструктор перемещения
	 *
	 *	Перемещает элементы в новую очередь из переданной.
	 *	\param queue Очередь, чьи элементы будут перемещены.
	 */
	Queue(Queue<T>&& queue) noexcept;
	
			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the queue into a string
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
	 *	\brief Hash code of the queue
	 *
	 *	Hash code of the queue is hash code of the internal linked list.
	 *	\return Hash code of the queue.
	 *
	 *	\~russian
	 *	\brief Хеш-код очереди
	 *
	 *	Хеш-код очереди — это хеш-код внутреннего связного списка.
	 *	\return Хеш-код очереди.
	 */
	virtual int hash_code() const noexcept override;

			/* METHODS FROM IContainer &
				METHODS */
	
	/**
	 *	\~english
	 *	\brief The size of the queue
	 *
	 *	Allows to get the number of elements in the queue.
	 *	\return The number of elements in the queue.
	 *
	 *	\~russian
	 *	\brief Размер очереди
	 *
	 *	Позволяет получить количество элеменов в очереди.
	 *	\return Количество элеменов в очереди.
	 */
	virtual int size() const noexcept override;

	/**
	 *	\~english
	 *	\brief Checks whether the queue is empty
	 *
	 *	Checks whether the queue is empty.
	 *	\return `true` if the queue does not contain any element, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, пуста ли очередь
	 *
	 *	Проверяет, пуста ли очередь.
	 *	\return `true`, если очередь не содержит никаких элементов, иначе `false`.
	 */
	virtual bool is_empty() const noexcept override;

	/**
	 *	\~english
	 *	\brief Clears the queue
	 *
	 *	Removes all of the elements in the queue.
	 *
	 *	\~russian
	 *	\brief Очищает очередь
	 *
	 *	Удаляет все элементы очереди.
	 */
	virtual void clear() noexcept override;

	/**
	 *	\~english
	 *	\brief The next element of the queue
	 *
	 *	Allows to access the next element of the queue.
	 *	\return A reference to the next element.
	 *	\throw std::out_of_range The queue is empty.
	 *
	 *	\~russian
	 *	\brief Следующий элемент очереди
	 *
	 *	Позволяет получить доступ к следующему элементу очереди.
	 *	\return Ссылка на следующий элемент.
	 *	\throw std::out_of_range Очередь пуста.
	 */
	T& get();

	/**
	 *	\~english
	 *	\brief The next element of the queue
	 *
	 *	Allows to read the next element of the queue.
	 *	\return A constant reference to the next element.
	 *	\throw std::out_of_range The queue is empty.
	 *
	 *	\~russian
	 *	\brief Следующий элемент очереди
	 *
	 *	Позволяет прочитать следующий элемент очереди.
	 *	\return Константная ссылка на следующий элемент.
	 *	\throw std::out_of_range Очередь пуста.
	 */
	const T& get() const;

	/**
	 *	\~english
	 *	\brief Removes the next element of the queue and returns it
	 *
	 *	Removes the next element of the queue and returns its value.
	 *	\return The value of the removed element.
	 *	\throw std::out_of_range The queue is empty.
	 *
	 *	\~russian
	 *	\brief Удаляет следующий элемент очереди и возвращает его
	 *
	 *	Удаляет следующий элемент очереди и возвращает его значение.
	 *	\return Значение удалённого элемента.
	 *	\throw std::out_of_range Очередь пуста.
	 */
	T&& pop();

	/**
	 *	\~english
	 *	\brief Inserts the element in the queue
	 *
	 *	Inserts the passed element in the queue.
	 *	\warning This method must not be used if the queue contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param element The element that will be inserted.
	 *
	 *	\~russian
	 *	\brief Вставляет элемент в очередь
	 *
	 *	Вставляет переданный элемент в очередь.
	 *	\warning Этот метод не должен быть использован, если очередь содержит `unique_ptr`ы (может
	 *	быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param element Элемент, который будет добавлен.
	 */
	bool push(const T& element);

	/**
	 *	\~english
	 *	\brief Inserts the element in the queue
	 *
	 *	Inserts the passed element in the queue.
	 *	\param element The element that will be inserted.
	 *
	 *	\~russian
	 *	\brief Вставляет элемент в очередь
	 *
	 *	Вставляет переданный элемент в очередь.
	 *	\param element Элемент, который будет добавлен.
	 */
	bool push(T&& element);

	/**
	 *	\~english
	 *	\brief Removes all elements that are equal to the passed one
	 *
	 *	Compares every element of the queue with the passed one and removes all matches.
	 *	\param element The object to compare.
	 *	\return Number of elements that have been successfully removed.
	 *
	 *	\~russian
	 *	\brief Удаляет все элементы, равные переданному
	 *
	 *	Сравнивает каждый элемент очереди с переданным и удаляет все совпадения.
	 *	\param element Объект для сравнения.
	 *	\return Количество успешно удалённых элементов.
	 */
	virtual int remove_all(const T& element) override;

	/**
	 *	\~english
	 *	\brief Checks whether the queue contains the passed element
	 *
	 *	Checks whether the queue has an element that is equal to the passed one.
	 *	\param element The desired element.
	 *	\return `true` if the queue contains the passed element, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, содержит ли очередь переданный элемент
	 *
	 *	Проверяет, содержит ли очередь элемент, равный переданному.
	 *	\param element Искомый элемент.
	 *	\return `true`, если очередь содержит переданный элемент, иначе `false`.
	 */
	virtual bool contains(const T& element) const override;

	/**
	 *	\~english
	 *	\brief How many elements of the queue are equal to the passed one
	 *
	 *	Counts elements that are equal to the passed one.
	 *	\param element The desired element.
	 *	\return Number of matches.
	 *
	 *	\~russian
	 *	\brief Сколько элементов очереди равны переданному
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
	 *	Clears the queue and inserts into it copies of elements of the passed queue.
	 *	\warning This operator must not be used if the queue contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param queue The queue to assign.
	 *	\return A reference to itself.
	 *	
	 *	\~russian
	 *	\brief Оператор присваивания копированием
	 *	
	 *	Очищает очередь и вставляет в неё копии элементов переданной очереди.
	 *	\warning Этот оператор не должен быть использован, если очередь содержит `unique_ptr`ы
	 *	(может быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param queue Очередь для присваивания.
	 *	\return Ссылка на себя.
	 */
	Queue<T>& operator=(const Queue<T>& queue);

	/**
	 *	\~english
	 *	\brief The move assignment operator
	 *
	 *	Clears the queue and moves into it elements of the passed queue.
	 *	\param queue The queue to assign.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Оператор присваивания перемещением
	 *
	 *	Очищает очередь и перемещает в неё элементы переданной очереди.
	 *	\param queue Очередь для присваивания.
	 *	\return Ссылка на себя.
	 */
	Queue<T>& operator=(Queue<T>&& queue);

	/**
	 *	\~english
	 *	\brief Checks whether two queues are equal
	 *
	 *	Two queues are equal if all of their elements are equal and have the same order.
	 *	\param queue The queue to compare.
	 *	\return `true` if two queues are equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, равны ли две очереди
	 *
	 *	Две очереди равны, если их элементы равны и находятся в одинаковом порядке.
	 *	\param queue Очередь для сравнения.
	 *	\return `true`, если две очереди равны, иначе `false`.
	 */
	bool operator==(const Queue<T>& queue) const;

	/**
	 *	\~english
	 *	\brief Checks whether two queues are not equal
	 *
	 *	Two queues are equal if all of their elements are equal and have the same order.
	 *	\param queue The queue to compare.
	 *	\return `true` if two queues are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, различаются ли две очереди
	 *
	 *	Две очереди равны, если их элементы равны и находятся в одинаковом порядке.
	 *	\param queue Очередь для сравнения.
	 *	\return `true`, если две очереди не равны, иначе `false`.
	 */
	bool operator!=(const Queue<T>& queue) const;

private:
	LinkedList<T> list;
};


		/* DEFINITIONS */

template<typename T>
Queue<T>::Queue() noexcept :
	list()
{}

template<typename T>
Queue<T>::Queue(const Queue<T>& queue) noexcept :
	list(queue.list)
{}

template<typename T>
Queue<T>::Queue(Queue<T>&& queue) noexcept :
	list(std::move(queue.list))
{}

template<typename T>
String Queue<T>::to_string() const noexcept
{
	return list.to_string();
}

template<typename T>
int Queue<T>::hash_code() const noexcept
{
	return list.hash_code();
}

template<typename T>
int Queue<T>::size() const noexcept
{
	return list.size();
}

template<typename T>
bool Queue<T>::is_empty() const noexcept
{
	return list.is_empty();
}

template<typename T>
void Queue<T>::clear() noexcept
{
	return list.clear();
}

template<typename T>
T& Queue<T>::get()
{
	return list.get_begin();
}

template<typename T>
const T& Queue<T>::get() const
{
	return list.get_begin();
}

template<typename T>
T&& Queue<T>::pop()
{
	T ret = list.get_begin();
	list.remove(list.begin());
	return ret;
}

template<typename T>
bool Queue<T>::push(const T& element)
{
	return list.add(element);
}

template<typename T>
bool Queue<T>::push(T&& element)
{
	return list.add(std::forward<T>(element));
}

template<typename T>
int Queue<T>::remove_all(const T& element)
{
	return list.remove_all(element);
}

template<typename T>
bool Queue<T>::contains(const T& element) const
{
	return list.contains(element);
}

template<typename T>
int Queue<T>::count(const T& element) const
{
	return list.count(element);
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& queue)
{
	list = queue.list;
	return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& queue)
{
	list = std::move(queue.list);
	return *this;
}

template<typename T>
bool Queue<T>::operator==(const Queue<T>& queue) const
{
	return list == queue.list;
}

template<typename T>
bool Queue<T>::operator!=(const Queue<T>& queue) const
{
	return list != queue.list;
}

}
