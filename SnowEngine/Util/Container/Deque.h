    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Deque.h                     //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `Deque` class
 *	
 *	This file contains the definition of the `Deque` class.
 *	
 *	\~russian
 *	\brief Файл с классом `Deque`
 *	
 *	Этот файл содержит определение класса `Deque`.
 */

#include "LinkedList.h"

namespace snow
{

/**
 *	\~english
 *	\brief The class of deque
 *	
 *	This deque is based on linked list (the `LinkedList` class). It allows you to push elements into
 *	its beginning and its end, and pop elements from the beginning and the end.
 *	\tparam T Type of the deque elements. This type must meet the same conditions as the template
 *	of the `LinkedList` class.
 *	
 *	\~russian
 *	\breif Класс двусторонней очереди
 *	
 *	Эта двусторонняя очередь основана на связном списке (класс `LinkedList`). Она позволяет
 *	добавлять элементы в начало и конец, а также удалять элементы с начала и конца.
 *	\tparam T Тип элементов двусторонней очереди. Этот тип должен удовлетворять тем же условиям,
 *	что и шаблон класса `LinkedList`.
 */
template<typename T>
class Deque :
	public Object,
	public IContainer<T>
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates an empty deque.
	 *	
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *	
	 *	Создаёт пустую двустороннюю очередь.
	 */
	Deque() noexcept;

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *	
	 *	Copies the deque.
	 *	\param deque The deque that will be copied.
	 *	
	 *	\~russian
	 *	\brief Конструктор копирования
	 *	
	 *	Копирует двустороннюю очередь.
	 *	\param deque Двусторонняя очередь, которая будет скопирован.
	 */
	Deque(const Deque<T>& deque) noexcept;

	/**
	 *	\~english
	 *	\brief The move constructor
	 *	
	 *	Moves elements to a new deque from the passed one.
	 *	\param deque The deque whose elements will be moved.
	 *	
	 *	\~russian
	 *	\brief Конструктор перемещения
	 *	
	 *	Перемещает элементы в новую двустороннюю очередь из переданной.
	 *	\param deque Двусторонняя очередь, чьи элементы будут перемещены.
	 */
	Deque(Deque<T>&& deque) noexcept;
	
			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the deque into a string
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
	 *	\brief Hash code of the deque
	 *	
	 *	Hash code of the deque is hash code of the internal linked list.
	 *	\return Hash code of the deque.
	 *	
	 *	\~russian
	 *	\brief Хеш-код двусторонней очереди
	 *	
	 *	Хеш-код двусторонней очереди — это хеш-код внутреннего связного списка.
	 *	\return Хеш-код двусторонней очереди.
	 */
	virtual int hash_code() const noexcept override;

			/* METHODS FROM IContainer &
				METHODS */
	
	/**
	 *	\~english
	 *	\brief The size of the deque
	 *
	 *	Allows to get the number of elements in the deque.
	 *	\return The number of elements in the deque.
	 *
	 *	\~russian
	 *	\brief Размер двусторонней очереди
	 *
	 *	Позволяет получить количество элеменов в двусторонней очереди.
	 *	\return Количество элеменов в двусторонней очереди.
	 */
	virtual int size() const noexcept override;

	/**
	 *	\~english
	 *	\brief Checks whether the deque is empty
	 *
	 *	Checks whether the deque is empty.
	 *	\return `true` if the deque does not contain any element, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, пуста ли односторонняя очередь
	 *
	 *	Проверяет, пуста ли односторонняя очередь.
	 *	\return `true`, если односторонняя очередь не содержит никаких элементов, иначе `false`.
	 */
	virtual bool is_empty() const noexcept override;

	/**
	 *	\~english
	 *	\brief Clears the deque
	 *
	 *	Removes all of the elements in the deque.
	 *	
	 *	\~russian
	 *	\brief Очищает двустороннюю очередь
	 *
	 *	Удаляет все элементы двусторонней очереди.
	 */
	virtual void clear() noexcept override;
	
	/**
	 *	\~english
	 *	\brief The first element of the deque
	 *	
	 *	Allows to access the first element of the deque.
	 *	\return A reference to the first element.
	 *	\throw std::out_of_range The deque is empty.
	 *	
	 *	\~russian
	 *	\brief Первый элемент двусторонней очереди
	 *	
	 *	Позволяет получить доступ к первому элементу двусторонней очереди.
	 *	\return Ссылка на первый элемент.
	 *	\throw std::out_of_range Двусторонняя очередь пуста.
	 */
	T& get_begin();
	
	/**
	 *	\~english
	 *	\brief The last element of the deque
	 *	
	 *	Allows to access the last element of the deque.
	 *	\return A reference to the last element.
	 *	\throw std::out_of_range The deque is empty.
	 *	
	 *	\~russian
	 *	\brief Последний элемент двусторонней очереди
	 *	
	 *	Позволяет получить доступ к последнему элементу двусторонней очереди.
	 *	\return Ссылка на последний элемент.
	 *	\throw std::out_of_range Двусторонняя очередь пуста.
	 */
	T& get_last();
	
	/**
	 *	\~english
	 *	\brief The first element of the deque
	 *	
	 *	Allows to read the first element of the deque.
	 *	\return A constant reference to the first element.
	 *	\throw std::out_of_range The deque is empty.
	 *	
	 *	\~russian
	 *	\brief Первый элемент двусторонней очереди
	 *	
	 *	Позволяет прочитать первый элемент двусторонней очереди.
	 *	\return Константная ссылка на первый элемент.
	 *	\throw std::out_of_range Двусторонняя очередь пуста.
	 */
	const T& get_begin() const;
	
	/**
	 *	\~english
	 *	\brief The last element of the deque
	 *	
	 *	Allows to read the last element of the deque.
	 *	\return A constant reference to the last element.
	 *	\throw std::out_of_range The deque is empty.
	 *	
	 *	\~russian
	 *	\brief Последний элемент двусторонней очереди
	 *	
	 *	Позволяет прочитать последний элемент двусторонней очереди.
	 *	\return Константная ссылка на последний элемент.
	 *	\throw std::out_of_range Двусторонняя очередь пуста.
	 */
	const T& get_last() const;
	
	/**
	 *	\~english
	 *	\brief Removes the first element of the deque and returns it
	 *	
	 *	Removes the first element of the deque and returns its value.
	 *	\return The value of the removed element.
	 *	\throw std::out_of_range The deque is empty.
	 *	
	 *	\~russian
	 *	\brief Удаляет первый элемент двусторонней очереди и возвращает его
	 *	
	 *	Удаляет первый элемент двусторонней очереди и возвращает его значение.
	 *	\return Значение удалённого элемента.
	 *	\throw std::out_of_range Двусторонняя очередь пуста.
	 */
	T pop_begin();
	
	/**
	 *	\~english
	 *	\brief Removes the last element of the deque and returns it
	 *	
	 *	Removes the last element of the deque and returns its value.
	 *	\return The value of the removed element.
	 *	\throw std::out_of_range The deque is empty.
	 *	
	 *	\~russian
	 *	\brief Удаляет последний элемент двусторонней очереди и возвращает его
	 *	
	 *	Удаляет последний элемент двусторонней очереди и возвращает его значение.
	 *	\return Значение удалённого элемента.
	 *	\throw std::out_of_range Двусторонняя очередь пуста.
	 */
	T pop_last();

	/**
	 *	\~english
	 *	\brief Inserts the element into the beginning of the deque
	 *	
	 *	Inserts the passed element into the beginning of the deque.
	 *	\param element The element that will be inserted.
	 *	
	 *	\~russian
	 *	\brief Вставляет элемент в начало двусторонней очереди
	 *	
	 *	Вставляет переданный элемент в начало двусторонней очереди.
	 *	\param element Элемент, который будет добавлен.
	 */
	bool push_begin(const T& element);

	/**
	 *	\~english
	 *	\brief Inserts the element into the end of the deque
	 *	
	 *	Inserts the passed element into the end of the deque.
	 *	\param element The element that will be inserted.
	 *	
	 *	\~russian
	 *	\brief Вставляет элемент в конец двусторонней очереди
	 *	
	 *	Вставляет переданный элемент в конец двусторонней очереди.
	 *	\param element Элемент, который будет добавлен.
	 */
	bool push_last(const T& element);

	/**
	 *	\~english
	 *	\brief Inserts the element into the beginning of the deque
	 *	
	 *	Inserts the passed element into the beginning of the deque.
	 *	\param element The element that will be inserted.
	 *	
	 *	\~russian
	 *	\brief Вставляет элемент в начало двусторонней очереди
	 *	
	 *	Вставляет переданный элемент в начало двусторонней очереди.
	 *	\param element Элемент, который будет добавлен.
	 */
	bool push_begin(T&& element);

	/**
	 *	\~english
	 *	\brief Inserts the element into the end of the deque
	 *	
	 *	Inserts the passed element into the end of the deque.
	 *	\param element The element that will be inserted.
	 *	
	 *	\~russian
	 *	\brief Вставляет элемент в конец двусторонней очереди
	 *	
	 *	Вставляет переданный элемент в конец двусторонней очереди.
	 *	\param element Элемент, который будет добавлен.
	 */
	bool push_last(T&& element);
	
	/**
	 *	\~english
	 *	\brief Removes all elements that are equal to the passed one
	 *	
	 *	Compares every element of the deque with the passed one and removes all matches.
	 *	\param element The object to compare.
	 *	\return Number of elements that have been successfully removed.
	 *
	 *	\~russian
	 *	\brief Удаляет все элементы, равные переданному
	 *
	 *	Сравнивает каждый элемент двусторонней очереди с переданным и удаляет все совпадения.
	 *	\param element Объект для сравнения.
	 *	\return Количество успешно удалённых элементов.
	 */
	virtual int remove_all(const T& element) override;
	
	/**
	 *	\~english
	 *	\brief Checks whether the deque contains the passed element
	 *
	 *	Checks whether the deque has an element that is equal to the passed one.
	 *	\param element The desired element.
	 *	\return `true` if the deque contains the passed element, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, содержит ли двусторонняя очередь переданный элемент
	 *	
	 *	Проверяет, содержит ли двусторонняя очередь элемент, равный переданному.
	 *	\param element Искомый элемент.
	 *	\return `true`, если двусторонняя очередь содержит переданный элемент, иначе `false`.
	 */
	virtual bool contains(const T& element) const override;
	
	/**
	 *	\~english
	 *	\brief How many elements of the deque are equal to the passed one
	 *	
	 *	Counts elements that are equal to the passed one.
	 *	\param element The desired element.
	 *	\return Number of matches.
	 *	
	 *	\~russian
	 *	\brief Сколько элементов двусторонней очередь равны переданному
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
	 *	Clears the deque and inserts into it copies of elements of the passed deque.
	 *	\param deque The deque to assign.
	 *	\return A reference to itself.
	 *	
	 *	\~russian
	 *	\brief Оператор присваивания копированием
	 *	
	 *	Очищает двустороннюю очередь и вставляет в неё копии элементов переданной очереди.
	 *	\param deque Двусторонняя очередь для присваивания.
	 *	\return Ссылка на себя.
	 */
	Deque<T>& operator=(const Deque<T>& deque);

	/**
	 *	\~english
	 *	\brief The move assignment operator
	 *	
	 *	Clears the deque and moves into it elements of the passed deque.
	 *	\param deque The deque to assign.
	 *	\return A reference to itself.
	 *	
	 *	\~russian
	 *	\brief Оператор присваивания перемещением
	 *	
	 *	Очищает двустороннюю очередь и перемещает в неё элементы переданной очереди.
	 *	\param deque Двусторонняя очередь для присваивания.
	 *	\return Ссылка на себя.
	 */
	Deque<T>& operator=(Deque<T>&& deque);
	
	/**
	 *	\~english
	 *	\brief Checks whether two deques are equal
	 *	
	 *	Two deques are equal if all of their elements are equal and have the same order.
	 *	\param deque The deque to compare.
	 *	\return `true` if two deques are equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, равны ли две двусторонние очереди
	 *
	 *	Две двусторонние очереди равны, если их элементы равны и находятся в одинаковом порядке.
	 *	\param deque Двусторонняя очередь для сравнения.
	 *	\return `true`, если две двусторонние очереди равны, иначе `false`.
	 */
	bool operator==(const Deque<T>& deque) const;
	
	/**
	 *	\~english
	 *	\brief Checks whether two deques are not equal
	 *	
	 *	Two deques are equal if all of their elements are equal and have the same order.
	 *	\param deque The deque to compare.
	 *	\return `true` if two deques are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, различаются ли две двусторонние очереди
	 *
	 *	Две двусторонние очереди равны, если их элементы равны и находятся в одинаковом порядке.
	 *	\param deque Двусторонняя очередь для сравнения.
	 *	\return `true`, если две двусторонние очереди не равны, иначе `false`.
	 */
	bool operator!=(const Deque<T>& deque) const;

private:
	LinkedList<T> list;
};


		/* DEFINITIONS */

template<typename T>
Deque<T>::Deque() noexcept :
	list()
{}

template<typename T>
Deque<T>::Deque(const Deque<T>& deque) noexcept :
	list(deque.list)
{}

template<typename T>
Deque<T>::Deque(Deque<T>&& deque) noexcept :
	list(std::move(deque.list))
{}

template<typename T>
String Deque<T>::to_string() const noexcept
{
	return list.to_string();
}

template<typename T>
int Deque<T>::hash_code() const noexcept
{
	return list.hash_code();
}

template<typename T>
int Deque<T>::size() const noexcept
{
	return list.size();
}

template<typename T>
bool Deque<T>::is_empty() const noexcept
{
	return list.is_empty();
}

template<typename T>
void Deque<T>::clear() noexcept
{
	return list.clear();
}

template<typename T>
T& Deque<T>::get_begin()
{
	return list.get_begin();
}

template<typename T>
T& Deque<T>::get_last()
{
	return list.get_last();
}

template<typename T>
const T& Deque<T>::get_begin() const
{
	return list.get_begin();
}

template<typename T>
const T& Deque<T>::get_last() const
{
	return list.get_last();
}

template<typename T>
T Deque<T>::pop_begin()
{
	T ret = list.get_begin();
	list.remove(list.begin());
	return ret;
}

template<typename T>
T Deque<T>::pop_last()
{
	T ret = list.get_last();
	list.remove(list.last());
	return ret;
}

template<typename T>
bool Deque<T>::push_begin(const T& element)
{
	return list.add_to_begin(element);
}

template<typename T>
bool Deque<T>::push_last(const T& element)
{
	return list.add(element);
}

template<typename T>
bool Deque<T>::push_begin(T&& element)
{
	return list.add_to_begin(std::forward<T>(element));
}

template<typename T>
bool Deque<T>::push_last(T&& element)
{
	return list.add(std::forward<T>(element));
}

template<typename T>
int Deque<T>::remove_all(const T& element)
{
	return list.remove_all(element);
}

template<typename T>
bool Deque<T>::contains(const T& element) const
{
	return list.contains(element);
}

template<typename T>
int Deque<T>::count(const T& element) const
{
	return list.count(element);
}

template<typename T>
Deque<T>& Deque<T>::operator=(const Deque<T>& deque)
{
	list = deque.list;
	return *this;
}

template<typename T>
Deque<T>& Deque<T>::operator=(Deque<T>&& deque)
{
	list = std::move(deque.list);
	return *this;
}

template<typename T>
bool Deque<T>::operator==(const Deque<T>& deque) const
{
	return list == deque.list;
}

template<typename T>
bool Deque<T>::operator!=(const Deque<T>& deque) const
{
	return list != deque.list;
}

}
