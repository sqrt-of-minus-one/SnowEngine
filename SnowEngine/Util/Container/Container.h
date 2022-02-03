    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Container.h                 //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `IContainer` and `IIterator` interfaces
 *	
 *	This file contains the definitions of the `IContainer` and `IIterator` interfaces.
 *	
 *	\~russian
 *	\brief Файл с интерфейсами `IContainer` и `IIterator`
 *	
 *	Этот файл содержит определения интерфейсов `IContainer` и `IIterator`.
 */

namespace snow
{

/**
 *	\~english
 *	\brief The interface that is implemented by SnowEngine containers' iterators
 *	
 *	Any of SnowEngine iterators implements this interface.
 *	\tparam T_Container Type of the container of the iterator.
 *	\tparam T_Element Type of elements in the container.
 *	
 *	\~russian
 *	\brief Интерфейс, реализуемый итераторами контейнеров SnowEngine
 *	
 *	Все итераторы SnowEngine реализуют этот интерфейс.
 *	\tparam T_Container Тип контейнера итератора.
 *	\tparam T_Element Тип элементов контейнера.
*/

template<typename T_Container, typename T_Element>
class IIterator
{
public:
			/* METHODS */


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
	virtual bool is_valid() const noexcept = 0;

	/**
	 *	\~english
	 *	\brief Checks whether the iterator points to a valid element
	 *
	 *	This function returns `false` if the iterator is not valid or points to the end of the
	 *	container (i. e. after the last container element).
	 *	\return `true` if the iterator points to a valid element, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, указывает ли итератор на действительный элемент
	 *
	 *	Эта функция возвращает `false`, если итератор недействителен или указывает на конец
	 *	контейнера (т. е. после последнего элемента контейнера).
	 *	\return `true`, если итератор указывает на действительный элемент, иначе `false`.
	 */
	virtual bool is_element_valid() const noexcept = 0;

	/**
	 *	\~english
	 *	\brief The container of the iterator
	 *
	 *	Allows to get the container that has the element that the iterator points to.
	 *	\return The container of the iterator.
	 *	\throw std::logic_error The iterator is not valid.
	 *
	 *	\~russian
	 *	\brief Контейнер итератора
	 *
	 *	Позволяет получить контейнер, на элемент которого указывает итератор.
	 *	\return Контейнер итератора.
	 *	\throw std::logic_error Итератор недействителен.
	 */
	virtual T_Container& get_container() const = 0;

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
	virtual T_Element& get() const = 0;

	/**
	 *	\~english
	 *	\brief Checks whether the iterator points to the first element of the container
	 *
	 *	The iterator is begin if it points to the first element.
	 *	\return `true` if the iterator points to the first element of the container, `false`
	 *	otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, указывает ли итератор на первый элемент контейнера
	 *
	 *	Проверяет, указывает ли итератор на первый элемент контейнера.
	 *	\return `true`, если итератор указывает на первый элемент контейнера, иначе `false`.
	 */
	virtual bool is_begin() const noexcept = 0;

	/**
	 *	\~english
	 *	\brief Checks whether the iterator points to the last element of the container
	 *
	 *	The iterator is last if it points to the last element.
	 *	\return `true` if the iterator points to the last element of the container,
	 *	`false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, указывает ли итератор на последний элемент контейнера
	 *
	 *	Проверяет, указывает ли итератор на последний элемент контейнера.
	 *	\return `true`, если итератор указывает на последний элемент контейнера, иначе `false`.
	 */
	virtual bool is_last() const noexcept = 0;

	/**
	 *	\~english
	 *	\brief Checks whether the iterator points after the last element of the container
	 *
	 *	The iterator is end if it points to a space that is after the last element. In this case
	 *	`is_element_valid` method returns `false`.
	 *	\return `true` if the iterator points after the last element of the container, `false`
	 *	otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, указывает ли итератор после последнего элемента контейнера
	 *
	 *	Итератор указывает в конец, если он указывает на пространство после последнего элемента
	 *	контейнера. В этом случае метод `is_element_valid` возвращает `false`.
	 *	\return `true`, если итератор указывает после последнего элемента контейнера, иначе
	 *	`false`.
	 */
	virtual bool is_end() const noexcept = 0;

	/**
	 *	\~english
	 *	\brief Moves the iterator forward
	 *
	 *	Increases the iterator index so that it points to the next element. The iterator won't be
	 *	changed if it already points after the last element.
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
	virtual bool next() = 0;

	/**
	 *	\~english
	 *	\brief Moves the iterator forward
	 *
	 *	Decreases the iterator index so that it points to the previous element. The iterator won't
	 *	be changed if it already points to the first element.
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
	virtual bool prev() = 0;

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
	virtual T_Element& operator*() const = 0;

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
	virtual T_Element* operator->() const = 0;
};

/**
 *	\~english
 *	\brief The interface of all of the SnowEngine containers
 *	
 *	All of the SnowEngine containers implement this interface.
 *	\tparam T Type of elements being in the container.
 *	
 *	\~russian
 *	\brief Интерфейс всех контейнеров SnowEngine
 *	
 *	Все контейнеры SnowEngine реализовывают этот интерфейс.
 *	\tparam T Тип элементов контейнера.
 */
template<typename T>
class IContainer
{
public:
			/* METHODS */

	/**
	 *	\~english
	 *	\brief The size of the container
	 *
	 *	Allows to get the number of elements in the container.
	 *	\return The number of elements in the container.
	 *
	 *	\~russian
	 *	\brief Размер контейнера
	 *
	 *	Позволяет получить количество элеменов в контейнере.
	 *	\return Количество элеменов в контейнере.
	 */
	virtual int size() const noexcept = 0;

	/**
	 *	\~english
	 *	\brief Checks whether the container is empty
	 *
	 *	Checks whether the container is empty.
	 *	\return `true` if the container does not contain any element, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, пуст ли контейнер
	 *
	 *	Проверяет, пуст ли контейнер.
	 *	\return `true`, если контейнер не содержит никаких элементов, иначе `false`.
	 */
	virtual bool is_empty() const noexcept = 0;

	/**
	 *	\~english
	 *	\brief Clears the container
	 *
	 *	Removes all of the elements in the container.
	 *
	 *	\~russian
	 *	\brief Очищает контейнер
	 *
	 *	Удаляет все элементы контейнера.
	 */
	virtual void clear() noexcept = 0;

	/**
	 *	\~english
	 *	\brief Removes all elements that are equal to the passed one
	 *	
	 *	Removes all of the elements that are equal to the passed one.
	 *	\param element The object to compare.
	 *	\return Number of elements that have been successfully removed.
	 *
	 *	\~russian
	 *	\brief Удаляет все элементы, равные переданному
	 *
	 *	Удаляет все элементы, равные переданному.
	 *	\param element Объект для сравнения.
	 *	\return Количество успешно удалённых элементов.
	 */
	virtual int remove_all(const T& element) = 0;

	/**
	 *	\~english
	 *	\brief Checks whether the container contains the passed element
	 *	
	 *	If the container contains the passed element, returns `true`.
	 *	\param element The desired element.
	 *	\return `true` if the container contains the passed element, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, содержит ли контейнер переданный элемент
	 *	
	 *	Если контейнер содержит переданный элемент, возвращает `true`.
	 *	\param element Искомый элемент.
	 *	\return `true`, если контейнер содержит переданный элемент, иначе `false`.
	 */
	virtual bool contains(const T& element) const = 0;

	/**
	 *	\~english
	 *	\brief How many elements of the container are equal to the passed one
	 *
	 *	Counts elements that are equal to the passed one.
	 *	\param element The desired element.
	 *	\return Number of matches.
	 *
	 *	\~russian
	 *	\brief Сколько элементов контейнера равны переданному
	 *
	 *	Подсчитывает элементы, равные переданному.
	 *	\param element Требуемый элемент.
	 *	\return Количество совпадений.
	 */
	virtual int count(const T& element) const = 0;
};

}
