    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: LinkedList.h                //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `LinkedList` class
 *	
 *	This file contains the definition of the `LinkedList` class.
 *	
 *	\~russian
 *	\brief Файл с классом `LinkedList`
 *	
 *	Этот файл содержит определение класса `LinkedList`.
 */

#include "LinkedListIterator.h"

#include <list>

namespace snow
{

template<typename T>
class LinkedList;

namespace
{

// Do not use this structure directly
template<typename T>
struct LinkedListNode_
{
public:
	LinkedListNode_(const LinkedListNode_<T>&) noexcept = default;
	LinkedListNode_(LinkedListNode_<T>&&) noexcept = default;
	LinkedListNode_(const T& val) noexcept;
	LinkedListNode_(T&& val) noexcept;

	T value;
	std::weak_ptr<LinkedListNode_<T>> prev;
	std::shared_ptr<LinkedListNode_<T>> next;
};

template<typename T>
struct LinkedListNode_<std::unique_ptr<T>>
{
public:
	LinkedListNode_(const LinkedListNode_<std::unique_ptr<T>>&) noexcept;
	LinkedListNode_(LinkedListNode_<std::unique_ptr<T>>&&) noexcept = default;
	LinkedListNode_(const std::unique_ptr<T>& val) noexcept;
	LinkedListNode_(std::unique_ptr<T>&& val) noexcept;

	T value;
	std::weak_ptr<LinkedListNode_<std::unique_ptr<T>>> prev;
	std::shared_ptr<LinkedListNode_<std::unique_ptr<T>>> next;
};

}

/**
 *	\~english
 *	\brief The class of linked list
 *	
 *	This class is used as the linked list. It should be used it if you don't need a fast access to
 *	an arbitrary element. On the other hand, the linked list provides a quick insertion and removal
 *	of any element. Linked lists take up more space than arrays. This class has methods that allow
 *	to work with the list using indexes of elements, but they can be significantly slower than
 *	those that use iterators.
 *	\warning If the linked list contains `unique_ptr`'s, methods that copy the linked list elements
 *	(for example, the copy constructor) must not be called (`std::logic_error` exception can be
 *	thrown).
 *	\tparam T Type of the linked list elements. If you need to store objects of some class in the
 *	linked list, it is highly recommended to store pointers to them. If `T` is not a primitive
 *	type, `to_string` and `hash_code` methods must be defined for it (any `snow::Object` has them).
 *	If `T` is not a pointer, it also must have a default constructor, an assignment operator (`=`)
 *	and an equality operator (`==`). The default and copy constructors are assumed not to throw any
 *	exceptions.
 *	
 *	\~russian
 *	Этот класс используется в качестве связного списка. Его следует использовать, если нет
 *	необходимости в быстром доступе к произвольному элементу. С другой стороны, связный список
 *	обеспечивает быструю вставку и удаление любого элемента. Связный список занимает больше места,
 *	чем массив. У этого класса есть методы, позволяющие работать со списком, используя индексы
 *	элементов, однако они могут быть значительно медленнее тех, что используют итераторы.
 *	\warning Если связный список содержит `unique_ptr`ы, то методы, копирующие элементы связного,
 *	списка (например, конструктор копирования) не должны вызываться (может быть выброшено
 *	исключение `std::logic_error`).
 *	\tparam T Тип элементов связного списка. Если вам нужно хранить в связном списке объекты
 *	некоторого класса, настоятельно рекомендуется хранить указатели на них. Если `T` не
 *	примитивный тип, для него должны быть определены методы `to_string` и `hash_code` (у любого
 *	`snow::Object` они есть). Если `T` не указатель, у него также должны быть определёны
 *	конструктор по умолчанию, оператор присваивания (`=`) и оператор равенства (`==`).
 *	Предполагается, что конструктор по умолчанию и конструктор копирования не выбрасывают никаких
 *	исключений.
 */
template<typename T>
class LinkedList :
	public Object,
	public IContainer<T>
{
	template<typename T_Container, typename T_Element, typename T_Node>
	friend class BaseLinkedListIterator_;

public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates an empty linked list.
	 *	
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *	
	 *	Создаёт пустой связный список.
	 */
	LinkedList() noexcept;

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *	
	 *	Copies the linked list.
	 *	\warning This constructor must not be used if the linked list contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param list The linked list that will be copied.
	 *	
	 *	\~russian
	 *	\brief Конструктор копирования
	 *	
	 *	Копирует связный список.
	 *	\warning Этот конструктор не должен быть использован, если связный список содержит
	 *	`unique_ptr`ы (может быть выброшено исключение `std::logic_error`). Вместо этого
	 *	используйте семантику перемещения.
	 *	\param list Связный список, который будет скопирован.
	 */
	LinkedList(const LinkedList<T>& list) noexcept;

	/**
	 *	\~english
	 *	\brief The move constructor
	 *	
	 *	Moves elements to a new linked list from the passed one.
	 *	\param list The linked list whose elements will be moved.
	 *	
	 *	\~russian
	 *	\brief Конструктор перемещения
	 *	
	 *	Перемещает элементы в новый связный список из переданного.
	 *	\param list Связный список, чьи элементы будут перемещены.
	 */
	LinkedList(LinkedList<T>&& list) noexcept;

	/**
	 *	\~english
	 *	\brief The destructor
	 *	
	 *	The destructor is used to invalidate all iterators.
	 *	
	 *	\~russian
	 *	\brief Деструктор
	 *	
	 *	Деструктор используется для аннулирования всех итераторов.
	 */
	virtual ~LinkedList() noexcept;

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the linked list into a string
	 *	
	 *	Creates a string representing the list of all elements. `util::to_string` is used to
	 *	convert elements to string.
	 *	\return A result string in the format `{ x, x, ..., x }`. `{ }` if the linked list is
	 *	empty.
	 *	
	 *	\~russian
	 *	\brief Конвертирует связный список в строку
	 *
	 *	Создаёт строку, представляющую из себя список всех элементов. Для конвертации элементов
	 *	в строку используется `util::to_string`.
	 *	\return Итоговая строка в формате `{ x, x, ..., x }`. `{ }`, если связный список пуст.
	 */
	virtual String to_string() const noexcept override;

	/**
	 *	\~english
	 *	\brief Hash code of the linked list
	 *	
	 *	Hash code is calculated using `util::hash_code` function and formula:
	 *	\f[
	 *		\sum^{n}_{i = 0} ((-1)^i \cdot a[i]) = a[0] - a[1] + a[2] - ...
	 *	\f]
	 *	\f$n\f$ is the linked list size, \f$a[i]\f$ is the hash code of i-th element of the linked
	 *	list.
	 *	\return Hash code of the linked list.
	 *	
	 *	\~russian
	 *	\brief Хеш-код связного списка
	 *
	 *	Хеш-код вычисляется с использованием `util::hash_code` по формуле:
	 *	\f[
	 *		\sum^{n}_{i = 0} ((-1)^i \cdot (a[i]) = a[0] - a[1] + a[2] - ...
	 *	\f]
	 *	\f$n\f$ — размер связного списка, \f$a[i]\f$ — хеш-код i-го элемента связного списка.
	 *	\return Хеш-код связного списка.
	 */
	virtual int hash_code() const noexcept override;
	
			/* METHODS FROM IContainer &
				METHODS */

	/**
	 *	\~english
	 *	\brief The size of the linked list
	 *
	 *	Allows to get the number of elements in the linked list.
	 *	\return The number of elements in the linked list.
	 *
	 *	\~russian
	 *	\brief Размер связного списка
	 *
	 *	Позволяет получить количество элеменов в связном списке.
	 *	\return Количество элеменов в связном списке.
	 */
	virtual int size() const noexcept override;

	/**
	 *	\~english
	 *	\brief Checks whether the linked list is empty
	 *
	 *	Checks whether the linked list is empty.
	 *	\return `true` if the linked list does not contain any element, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, пуст ли связный список
	 *
	 *	Проверяет, пуст ли связный список.
	 *	\return `true`, если связный список не содержит никаких элементов, иначе `false`.
	 */
	virtual bool is_empty() const noexcept override;

	/**
	 *	\~english
	 *	\brief Clears the linked list
	 *
	 *	Removes all of the elements in the linked list.
	 *	
	 *	\~russian
	 *	\brief Очищает связный список
	 *
	 *	Удаляет все элементы связного списка.
	 */
	virtual void clear() noexcept override;

	/**
	 *	\~english
	 *	\brief The first element of the linked list
	 *	
	 *	Allows to access the first element of the linked list.
	 *	\return A reference to the first element.
	 *	\throw std::out_of_range The linked list is empty.
	 *	
	 *	\~russian
	 *	\brief Первый элемент связного списка
	 *	
	 *	Позволяет получить доступ к первому элементу связного списка.
	 *	\return Ссылка на первый элемент.
	 *	\throw std::out_of_range Связный список пуст.
	 */
	T& get_begin();
	
	/**
	 *	\~english
	 *	\brief The last element of the linked list
	 *	
	 *	Allows to access the last element of the linked list.
	 *	\return A reference to the last element.
	 *	\throw std::out_of_range The deque is empty.
	 *	
	 *	\~russian
	 *	\brief Последний элемент связного списка
	 *	
	 *	Позволяет получить доступ к последнему элементу связного списка.
	 *	\return Ссылка на последний элемент.
	 *	\throw std::out_of_range Связный список пуст.
	 */
	T& get_last();

	/**
	 *	\~english
	 *	\brief The first element of the linked list
	 *	
	 *	Allows to read the first element of the linked list.
	 *	\return A constant reference to the first element.
	 *	\throw std::out_of_range The linked list is empty.
	 *	
	 *	\~russian
	 *	\brief Первый элемент связного списка
	 *	
	 *	Позволяет прочитать первый элемент связного списка.
	 *	\return Константная ссылка на первый элемент.
	 *	\throw std::out_of_range Связный список пуст.
	 */
	const T& get_begin() const;
	
	/**
	 *	\~english
	 *	\brief The last element of the linked list
	 *	
	 *	Allows to read the last element of the linked list.
	 *	\return A constant reference to the last element.
	 *	\throw std::out_of_range The deque is empty.
	 *	
	 *	\~russian
	 *	\brief Последний элемент связного списка
	 *	
	 *	Позволяет прочитать последний элемент связного списка.
	 *	\return Константная ссылка на последний элемент.
	 *	\throw std::out_of_range Связный список пуст.
	 */
	const T& get_last() const;

	/**
	 *	\~english
	 *	\brief Adds a new element
	 *	
	 *	Inserts a new element into the end of the linked list. If there are iterators that point to
	 *	the end (`is_end` is true), they will continue to be end after executing this method.
	 *	\warning This method must not be used if the linked list contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param element The element that will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Добавляет новый элемент
	 *	
	 *	Вставляет новый элемент в конец связного списка. Если есть итераторы, указывающие на конец 
	 *	(`is_end` истинно), после выполнения метода они продолжат указывать на конец.
	 *	\warning Этот метод не должен быть использован, если связный список содержит `unique_ptr`ы
	 *	(может быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param element Элемент, который будет добавлен.
	 *	\return `true`, если элемент был успешно добавлен, иначе `false`.
	 */
	virtual bool add(const T& element);

	/**
	 *	\~english
	 *	\brief Adds a new element
	 *	
	 *	Inserts a new element into the end of the linked list. If there are iterators that point to
	 *	the end (`is_end` is true), they will continue to be end after executing this method.
	 *	\param element The element that will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Добавляет новый элемент
	 *	
	 *	Вставляет новый элемент в конец связного списка. Если есть итераторы, указывающие на конец 
	 *	(`is_end` истинно), после выполнения метода они продолжат указывать на конец.
	 *	\param element Элемент, который будет добавлен.
	 *	\return `true`, если элемент был успешно добавлен, иначе `false`.
	 */
	virtual bool add(T&& element);

	/**
	 *	\~english
	 *	\brief Adds a new element with the specified index
	 *	
	 *	Inserts a new element into the linked list. The new element will have the passed index. 
	 *	All iterators will continue to point to their elements. This method is pretty slow, it is
	 *	faster to put the element using an iterator if you have one.
	 *	\warning This method must not be used if the linked list contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param element The element that will be added.
	 *	\param index The index that the new element will have.
	 *	\return `true` if the element has been successfully added, `false` otherwise (i. g. if the
	 *	index is out of the linked list bounds).
	 *	
	 *	\~russian
	 *	\brief Добавляет новый элемент с заданным индексом
	 *	
	 *	Вставляет новый элемент в связный список. Новый элемент будет иметь переданный индекс.
	 *	Все итераторы продолжат указывать на свои элементы. Этот метод довольно медленный, быстрее
	 *	вставить элемент с использованием итератора, если таковой имеется.
	 *	\warning Этот метод не должен быть использован, если связный список содержит `unique_ptr`ы
	 *	(может быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param element Элемент, который будет добавлен.
	 *	\param index Индекс, который новый элемент будет иметь.
	 *	\return `true`, если элемент был успешно добавлен, иначе `false` (например, если индекс
	 *	выходит за границы связного списка).
	 */
	virtual bool add(const T& element, int index);

	/**
	 *	\~english
	 *	\brief Adds a new element with the specified index
	 *	
	 *	Inserts a new element into the linked list. The new element will have the passed index. 
	 *	All iterators will continue to point to their elements. This method is pretty slow, it is
	 *	faster to put the element using an iterator if you have one.
	 *	\param element The element that will be added.
	 *	\param index The index that the new element will have.
	 *	\return `true` if the element has been successfully added, `false` otherwise (i. g. if the
	 *	index is out of the linked list bounds).
	 *	
	 *	\~russian
	 *	\brief Добавляет новый элемент с заданным индексом
	 *	
	 *	Вставляет новый элемент в связный список. Новый элемент будет иметь переданный индекс.
	 *	Все итераторы продолжат указывать на свои элементы. Этот метод довольно медленный, быстрее
	 *	вставить элемент с использованием итератора, если таковой имеется.
	 *	\param element Элемент, который будет добавлен.
	 *	\param index Индекс, который новый элемент будет иметь.
	 *	\return `true`, если элемент был успешно добавлен, иначе `false` (например, если индекс
	 *	выходит за границы связного списка).
	 */
	virtual bool add(T&& element, int index);

	/**
	 *	\~english
	 *	\brief Adds into the linked list copies of elements of the passed linked list
	 *	
	 *	Inserts into the end of the linked list copies of elements of the passed linked list. If
	 *	there are iterators that points to the end (`is_end` is true), they will continue to be end
	 *	after executing this method.
	 *	\warning This method must not be used if the linked list contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param list The linked list whose elements will be added.
	 *	\return The number of elements that have been successfully added.
	 *	
	 *	\~russian
	 *	\brief Добавляет в связный список копии элементов переданного связного списка
	 *	
	 *	Вставляет в конец связного списка копии элементов переданного связного списка. Если есть
	 *	итераторы, указывающие на конец (`is_end` истинно), после выполнения метода они продолжат
	 *	указывать на конец.
	 *	\warning Этот метод не должен быть использован, если связный список содержит `unique_ptr`ы
	 *	(может быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param list Связный список, чьи элементы будут добавлены.
	 *	\return Количество успешно добавленных элементов.
	 */
	virtual int add(const LinkedList<T>& list);

	/**
	 *	\~english
	 *	\brief Moves into the linked list elements of the passed linked list
	 *
	 *	Moves into the end of the linked list elements of the passed linked list. If there are
	 *	iterators that points to the end (`is_end` is true), they will continue to be end after
	 *	executing this method.
	 *	\param list The linked list whose elements will be moved.
	 *	\return The number of elements that have been successfully added.
	 *	
	 *	\~russian
	 *	\brief Перемещает в связный список элементы из переданного связного списка
	 *	
	 *	Перемещает в конец связного списка элементы из переданного связного списка. Если есть
	 *	итераторы, указывающие на конец (`is_end` истинно), после выполнения метода они продолжат
	 *	указывать на конец.
	 *	\param list Связный список, чьи элементы будут перемещены.
	 *	\return Количество успешно добавленных элементов.
	 */
	virtual int add(LinkedList<T>&& list);

	/**
	 *	\~english
	 *	\brief Adds a new element before the passed one
	 *	
	 *	Inserts a new element before the one that the passed iterator points to. If there are
	 *	iterators that point to the end (`is_end` is true), they will continue to be end after
	 *	executing this method.
	 *	\warning This method must not be used if the linked list contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param element The element that will be added.
	 *	\param iterator The iterator pointing to an element before which the new one will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Добавляет новый элемент перед переданным
	 *	
	 *	Вставляет новый элемент перед тем, на который указывает переданный итератор. Если есть
	 *	итераторы, указывающие на конец (`is_end` истинно), после выполнения метода они продолжат
	 *	указывать на конец.
	 *	\warning Этот метод не должен быть использован, если связный список содержит `unique_ptr`ы
	 *	(может быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param element Элемент, который будет добавлен.
	 *	\param iterator Итератор, указывающий на элемент, перед которым будет вставлен новый.
	 *	\return `true`, если элемент был успешно добавлен, иначе `false`.
	 */
	virtual bool add_before(const T& element, const LinkedListIterator<T>& iterator);

	/**
	 *	\~english
	 *	\brief Adds a new element before the passed one
	 *	
	 *	Inserts a new element before the one that the passed iterator points to. If there are
	 *	iterators that point to the end (`is_end` is true), they will continue to be end after
	 *	executing this method.
	 *	\param element The element that will be added.
	 *	\param iterator The iterator pointing to an element before which the new one will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Добавляет новый элемент перед переданным
	 *	
	 *	Вставляет новый элемент перед тем, на который указывает переданный итератор. Если есть
	 *	итераторы, указывающие на конец  (`is_end` истинно), после выполнения метода они продолжат
	 *	указывать на конец.
	 *	\param element Элемент, который будет добавлен.
	 *	\param iterator Итератор, указывающий на элемент, перед которым будет вставлен новый.
	 *	\return `true`, если элемент был успешно добавлен, иначе `false`.
	 */
	virtual bool add_before(T&& element, const LinkedListIterator<T>& iterator);

	/**
	 *	\~english
	 *	\brief Adds a new element before the passed one
	 *	
	 *	Inserts a new element before the one that the passed iterator points to. If there are
	 *	iterators that point to the end (`is_end` is true), they will continue to be end after
	 *	executing this method.
	 *	\warning This method must not be used if the linked list contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param element The element that will be added.
	 *	\param iterator The iterator pointing to an element before which the new one will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Добавляет новый элемент перед переданным
	 *	
	 *	Вставляет новый элемент перед тем, на который указывает переданный итератор. Если есть
	 *	итераторы, указывающие на конец (`is_end` истинно), после выполнения метода они продолжат
	 *	указывать на конец.
	 *	\warning Этот метод не должен быть использован, если связный список содержит `unique_ptr`ы
	 *	(может быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param element Элемент, который будет добавлен.
	 *	\param iterator Итератор, указывающий на элемент, перед которым будет вставлен новый.
	 *	\return `true`, если элемент был успешно добавлен, иначе `false`.
	 */
	virtual bool add_before(const T& element, const ConstLinkedListIterator<T>& iterator);

	/**
	 *	\~english
	 *	\brief Adds a new element before the passed one
	 *	
	 *	Inserts a new element before the one that the passed iterator points to. If there are
	 *	iterators that point to the end (`is_end` is true), they will continue to be end after
	 *	executing this method.
	 *	\param element The element that will be added.
	 *	\param iterator The iterator pointing to an element before which the new one will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Добавляет новый элемент перед переданным
	 *	
	 *	Вставляет новый элемент перед тем, на который указывает переданный итератор. Если есть
	 *	итераторы, указывающие на конец (`is_end` истинно), после выполнения метода они продолжат
	 *	указывать на конец.
	 *	\param element Элемент, который будет добавлен.
	 *	\param iterator Итератор, указывающий на элемент, перед которым будет вставлен новый.
	 *	\return `true`, если элемент был успешно добавлен, иначе `false`.
	 */
	virtual bool add_before(T&& element, const ConstLinkedListIterator<T>& iterator);

	/**
	 *	\~english
	 *	\brief Adds the element into the beginning of the linked list
	 *	
	 *	Inserts the passed element into the beginning of the linked list. If there are iterators
	 *	that point to the end (`is_end` is true), they will continue to be end after executing this
	 *	method.
	 *	\warning This method must not be used if the linked list contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param element The element that will be inserted.
	 *	
	 *	\~russian
	 *	\brief Добавляет элемент в начало связного списка
	 *	
	 *	Вставляет переданный элемент в начало связного списка. Если есть итераторы, указывающие на
	 *	конец (`is_end` истинно), после выполнения метода они продолжат указывать на конец.
	 *	\warning Этот метод не должен быть использован, если связный список содержит `unique_ptr`ы
	 *	(может быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param element Элемент, который будет добавлен.
	 */
	virtual bool add_to_begin(const T& element);

	/**
	 *	\~english
	 *	\brief Adds the element into the beginning of the linked list
	 *	
	 *	Inserts the passed element into the beginning of the linked list. If there are iterators
	 *	that point to the end (`is_end` is true), they will continue to be end after executing this 
	 *	method.
	 *	\param element The element that will be inserted.
	 *	
	 *	\~russian
	 *	\brief Добавляет элемент в начало связного списка
	 *	
	 *	Вставляет переданный элемент в начало связного списка. Если есть итераторы, указывающие на
	 *	конец (`is_end` истинно), после выполнения метода они продолжат указывать на конец.
	 *	\param element Элемент, который будет добавлен.
	 */
	virtual bool add_to_begin(T&& element);

	/**
	 *	\~english
	 *	\brief Removes an element with the specified index
	 *	
	 *	Removes an element that has the specified index.
	 *	All iterators will continue to point to their elements. Iterators that pointed to the
	 *	removed element will point to the next element after executing this method. This method is
	 *	pretty slow, it is faster to remove the element using an iterator if you have one.
	 *	\param index The index of the element that will be removed.
	 *	\return `true` if the element has been successfully removed, `false` otherwise (i. g. if
	 *	the index is out of the linked list bounds).
	 *	
	 *	\~russian
	 *	\brief Удаляет элемент с заданным индексом
	 *	
	 *	Удаляет элемент, который имеет заданный индекс.
	 *	Все итераторы продолжат указывать на свои элементы.
	 *	Итераторы, указывавшие на удалённый элемент, после выполнения метода будут указывать на
	 *	следующий. Этот метод довольно медленный, быстрее удалить элемент с использованием
	 *	итератора, если таковой имеется.
	 *	\param index Индекс элемента, который будет удалён.
	 *	\return `true`, если элемент был успешно удалён, иначе `false` (например, если индекс
	 *	выходит за границы связного списка).
	 */
	virtual bool remove(int index);

	/**
	 *	\~english
	 *	\brief Removes an element by iterator
	 *	
	 *	Removes an element that the passed iterator points to. All iterators will continue to point
	 *	to their elements. Iterators that pointed to the removed element (including the passed one)
	 *	will point to the next element after executing this method.
	 *	\param element The iterator pointing to the element that will be removed.
	 *	\return `true` if the element has been successfully removed, `false` otherwise (i. g. if
	 *	the iterator points to an element of other linked list).
	 *	
	 *	\~russian
	 *	\brief Удаляет элемент по итератору
	 *	
	 *	Удаляет элемент, на который указывает переданный итератор. Все итераторы продолжат
	 *	указывать на свои элементы. Итераторы, указывавшие на удалённый элемент (включая
	 *	переданный), после выполнения метода будут указывать на следующий.
	 *	\param element Итератор, указывающий на элемент, который будет удалён.
	 *	\return `true`, если элемент был успешно удалён, иначе `false` (например, если итератор
	 *	указывает на элемент другого связного списка).
	 */
	virtual bool remove(const LinkedListIterator<T>& element);

	/**
	 *	\~english
	 *	\brief Removes an element by iterator
	 *	
	 *	Removes an element that the passed iterator points to. All iterators will continue to point
	 *	to their elements. Iterators that pointed to the removed element (including the passed one)
	 *	will point to the next element after executing this method.
	 *	\param element The iterator pointing to the element that will be removed.
	 *	\return `true` if the element has been successfully removed, `false` otherwise (i. g. if
	 *	the iterator points to an element of other linked list).
	 *	
	 *	\~russian
	 *	\brief Удаляет элемент по итератору
	 *	
	 *	Удаляет элемент, на который указывает переданный итератор. Все итераторы продолжат
	 *	указывать на свои элементы. Итераторы, указывавшие на удалённый элемент (включая
	 *	переданный), после выполнения метода будут указывать на следующий.
	 *	\param element Итератор, указывающий на элемент, который будет удалён.
	 *	\return `true`, если элемент был успешно удалён, иначе `false` (например, если итератор
	 *	указывает на элемент другого связного списка).
	 */
	virtual bool remove(const ConstLinkedListIterator<T>& element);

	/**
	 *	\brief Remove elements in the passed range
	 *
	 *	Removes elements that are in the passed range. The subsequent elements are moved and fill a
	 *	formed space. All iterators will continue to point to their elements. Iterators that
	 *	pointed to the removed elements will point to the next element after executing this method.
	 *	It is faster to do this using iterators if you have them.
	 *	\param from The beginning of range that will be removed.
	 *	\param to The index of an element after the last element in the range that will be removed.
	 *	This element won't be removed.
	 *	\return The number of elements that have been successfully removed.
	 */

	/**
	 *	\~english
	 *	\brief Removes elements in the specified range
	 *	
	 *	Removes elements that are in the specified range.
	 *	All iterators will continue to point to their elements. Iterators that
	 *	pointed to one of the removed elements will point to the first element after the removed
	 *	range after executing this method. This method is pretty slow, it is faster to remove the
	 *	elements using iterators if you have one.
	 *	\param from The beginning of the range that will be removed.
	 *	\param to The end of the range that will be removed. An element with this index won't be
	 *	removed, but the previous one will.
	 *	\return The number of elements that have been successfully removed.
	 *	
	 *	\~russian
	 *	\brief Удаляет элементы в заданном диапазоне
	 *	
	 *	Удаляет элементы, которых входят в заданный диапазон. Все итераторы продолжат указывать на
	 *	свои элементы. Итераторы, указывавшие на один из удалённых элементов, после выполнения
	 *	метода будут указывать на первый элемент после удалённого диапазона. Этот метод довольно
	 *	медленный, быстрее удалить элементы с использованием итераторов, если таковой имеется.
	 *	\param from Начало диапазона, который будет удалён.
	 *	\param to Конец диапазона, который будет удалён. Элемент с этим индектом удалён не будет, а
	 *	предыдущий — будет.
	 *	\return Количество успешно удалённых элементов.
	 */
	virtual int remove(int from, int to);

	/**
	 *	\~english
	 *	\brief Removes elements in the specified range
	 *
	 *	Removes elements that are in the specified range. All iterators will continue to point to
	 *	their elements. Iterators that pointed to one of the removed elements will point to the
	 *	first element after the removed range after executing this method.
	 *	\param from The iterator pointing to the first element in the range that will be removed.
	 *	\param to The iterator pointing after the last element in the range that will be removed.
	 *	This element won't be removed.
	 *	\return The number of elements that have been successfully removed.
	 *
	 *	\~russian
	 *	\brief Удаляет элементы в заданном диапазоне
	 *
	 *	Удаляет элементы, которых входят в заданный диапазон. Все итераторы продолжат указывать на
	 *	свои элементы. Итераторы, указывавшие на один из удалённых элементов, после выполнения
	 *	метода будут указывать на первый элемент после удалённого диапазона.
	 *	\param from Итератор, указывающий на первый элемент диапазона, который будет удалён.
	 *	\param to Итератор, указывающий после последнего элемента диапазона, который будет удалён.
	 *	Этот элемент не будет удалён.
	 *	\return Количество успешно удалённых элементов.
	 */
	virtual int remove(const LinkedListIterator<T>& from, const LinkedListIterator<T>& to);

	/**
	 *	\~english
	 *	\brief Removes elements in the specified range
	 *
	 *	Removes elements that are in the specified range. All iterators will continue to point to
	 *	their elements. Iterators that pointed to one of the removed elements will point to the
	 *	first element after the removed range after executing this method.
	 *	\param from The iterator pointing to the first element in the range that will be removed.
	 *	\param to The iterator pointing after the last element in the range that will be removed.
	 *	This element won't be removed.
	 *	\return The number of elements that have been successfully removed.
	 *
	 *	\~russian
	 *	\brief Удаляет элементы в заданном диапазоне
	 *
	 *	Удаляет элементы, которых входят в заданный диапазон. Все итераторы продолжат указывать на
	 *	свои элементы. Итераторы, указывавшие на один из удалённых элементов, после выполнения
	 *	метода будут указывать на первый элемент после удалённого диапазона.
	 *	\param from Итератор, указывающий на первый элемент диапазона, который будет удалён.
	 *	\param to Итератор, указывающий после последнего элемента диапазона, который будет удалён.
	 *	Этот элемент не будет удалён.
	 *	\return Количество успешно удалённых элементов.
	 */
	virtual int remove(const ConstLinkedListIterator<T>& from, const ConstLinkedListIterator<T>& to);

	/**
	 *	\~english
	 *	\brief Removes the first element that is equal to the passed one
	 *	
	 *	Compares elements of the linked list with the passed one starting from the beginning and
	 *	removes the first match. All iterators will continue to point to their elements. Iterators
	 *	that pointed to the removed element will point to the next element after executing this
	 *	method.
	 *	\param element The object to compare.
	 *	\return `true` if an element has been successfully removed, `false` otherwise (i. g. if the
	 *	linked list doesn't contain the passed object).
	 *	
	 *	\~russian
	 *	\brief Удаляет первый элемент, равный переданному
	 *
	 *	Сравнивает элементы связного списка с переданным, начиная с начала, и удаляет первое
	 *	совпадение. Все итераторы продолжат указывать на свои элементы. Итераторы, указывавшие на
	 *	удалённый элемент, после выполнения метода будут указывать на следующий.
	 *	\param element Объект для сравнения.
	 *	\return `true`, если элемент был успешно удалён, иначе `false` (например, если связный
	 *	список не содержит переданный объект).
	 */
	virtual bool remove_first(const T& element);

	/**
	 *	\~english
	 *	\brief Removes the last element that is equal to the passed one
	 *
	 *	Compares elements of the linked list with the passed one starting from the end and removes
	 *	the first match. All iterators will continue to point to their elements. Iterators that
	 *	pointed to the removed element will point to the next element after executing this method.
	 *	\param element The object to compare.
	 *	\return `true` if an element has been successfully removed, `false` otherwise (i. g. if the
	 *	linked list doesn't contain the passed object).
	 *
	 *	\~russian
	 *	\brief Удаляет последний элемент, равный переданному
	 *
	 *	Сравнивает элементы связного списка с переданным, начиная с конца, и удаляет первое
	 *	совпадение. Все итераторы продолжат указывать на свои элементы. Итераторы, указывавшие на
	 *	удалённый элемент, после выполнения метода будут указывать на следующий.
	 *	\param element Объект для сравнения.
	 *	\return `true`, если элемент был успешно удалён, иначе `false` (например, если связный
	 *	список не содержит переданный объект).
	 */
	virtual bool remove_last(const T& element);

	/**
	 *	\~english
	 *	\brief Removes all elements that are equal to the passed one
	 *	
	 *	Compares every element of the linked list with the passed one and removes all matches. All
	 *	iterators will continue to point to their elements. Iterators that pointed to one of the
	 *	removed elements will point to the next element after executing this method.
	 *	\param element The object to compare.
	 *	\return Number of elements that have been successfully removed.
	 *
	 *	\~russian
	 *	\brief Удаляет все элементы, равные переданному
	 *
	 *	Сравнивает каждый элемент связного списка с переданным и удаляет все совпадения. Все
	 *	итераторы продолжат указывать на свои элементы. Итераторы, указывавшие на один из удалённых
	 *	элементов, после выполнения метода будут указывать на следующий.
	 *	\param element Объект для сравнения.
	 *	\return Количество успешно удалённых элементов.
	 */
	virtual int remove_all(const T& element) override;

	/**
	 *	\~english
	 *	\brief Finds the first element that is equal to the passed one
	 *	
	 *	Compares elements of the linked list with the passed one starting from the beginning. If a
	 *	match is found, returns its index. In most cases it's better to use
	 *	`find_first_by_iterator`.
	 *	\param element The desired element.
	 *	\return An index of the first match; a negative value if no match has been found.
	 *	
	 *	\~russian
	 *	\brief Находит первый элемент, который равен переданному
	 *	
	 *	Сравнивает элементы связного списка с переданным, начиная с начала. Если совпадение
	 *	найдено, возвращает его индекс. В большинстве случаев лучше использовать
	 *	`find_first_by_iterator`.
	 *	\param element Искомый элемент.
	 *	\return Индекс первого совпадения; отрицательное значение, если совпадения найдено не было.
	 */
	virtual int find_first_by_index(const T& element) const;

	/**
	 *	\~english
	 *	\brief Finds the last element that is equal to the passed one
	 *	
	 *	Compares elements of the linked list with the passed one starting from the end. If a match
	 *	is found, returns its index. In most cases it's better to use `find_last_by_iterator`.
	 *	\param element The desired element.
	 *	\return An index of the last match; a negative value if no match has been found.
	 *	
	 *	\~russian
	 *	\brief Находит последний элемент, который равен переданному
	 *	
	 *	Сравнивает элементы связного списка с переданным, начиная с конца. Если совпадение найдено,
	 *	возвращает его индекс. В большинстве случаев лучше использовать `find_last_by_iterator`.
	 *	\param element Искомый элемент.
	 *	\return Индекс последнего совпадения; отрицательное значение, если совпадения найдено не
	 *	было.
	 */
	virtual int find_last_by_index(const T& element) const;

	/**
	 *	\~english
	 *	\brief Finds the first element that is equal to the passed one
	 *	
	 *	Compares elements of the linked list with the passed one starting from the beginning. If a
	 *	match is found, returns an iterator to the found element.
	 *	\param element The desired element.
	 *	\return The iterator to the found element or the end iterator if no match has been found.
	 *	
	 *	\~russian
	 *	\brief Находит первый элемент, который равен переданному
	 *	
	 *	Сравнивает элементы связного списка с переданным, начиная с начала. Если совпадение
	 *	найдено, возвращает итератор на найденный элемент.
	 *	\param element Искомый элемент.
	 *	\return Итератор на найденный элемент или итератор на конец, если совпадения найдено не
	 *	было.
	 */
	virtual LinkedListIterator<T> find_first_by_iterator(const T& element);

	/**
	 *	\~english
	 *	\brief Finds the last element that is equal to the passed one
	 *	
	 *	Compares elements of the linked list with the passed one starting from the end. If a match
	 *	is found, returns an iterator to the found element.
	 *	\param element The desired element.
	 *	\return The iterator to the found element or the end iterator if no match has been found.
	 *	
	 *	\~russian
	 *	\brief Находит последний элемент, который равен переданному
	 *	
	 *	Сравнивает элементы связного списка с переданным, начиная с конца. Если совпадение найдено,
	 *	возвращает итератор на найденный элемент.
	 *	\param element Искомый элемент.
	 *	\return Итератор на найденный элемент или итератор на конец, если совпадения найдено не
	 *	было.
	 */
	virtual LinkedListIterator<T> find_last_by_iterator(const T& element);

	/**
	 *	\~english
	 *	\brief Finds the first element that is equal to the passed one
	 *	
	 *	Compares elements of the linked list with the passed one starting from the beginning. If a
	 *	match is found, returns an iterator to the found element.
	 *	\param element The desired element.
	 *	\return The iterator to the found element or the end iterator if no match has been found.
	 *	
	 *	\~russian
	 *	\brief Находит первый элемент, который равен переданному
	 *	
	 *	Сравнивает элементы связного списка с переданным, начиная с начала. Если совпадение
	 *	найдено, возвращает итератор на найденный элемент.
	 *	\param element Искомый элемент.
	 *	\return Итератор на найденный элемент или итератор на конец, если совпадения найдено не
	 *	было.
	 */
	virtual ConstLinkedListIterator<T> find_first_by_iterator(const T& element) const;

	/**
	 *	\~english
	 *	\brief Finds the last element that is equal to the passed one
	 *	
	 *	Compares elements of the linked list with the passed one starting from the end. If a match
	 *	is found, returns an iterator to the found element.
	 *	\param element The desired element.
	 *	\return The iterator to the found element or the end iterator if no match has been found.
	 *	
	 *	\~russian
	 *	\brief Находит последний элемент, который равен переданному
	 *	
	 *	Сравнивает элементы связного списка с переданным, начиная с конца. Если совпадение найдено,
	 *	возвращает итератор на найденный элемент.
	 *	\param element Искомый элемент.
	 *	\return Итератор на найденный элемент или итератор на конец, если совпадения найдено не
	 *	было.
	 */
	virtual ConstLinkedListIterator<T> find_last_by_iterator(const T& element) const;

	/**
	 *	\brief Whether the linked list contains the passed element
	 *
	 *	Checks whether the linked list has an element that is equal to the passed one.
	 *	\param element The desired element.
	 *	\return `true` if the linked list contains the passed element, `false` otherwise.
	 */
	/**
	 *	\~english
	 *	\brief Checks whether the linked list contains the passed element
	 *
	 *	Checks whether the linked list has an element that is equal to the passed one.
	 *	\param element The desired element.
	 *	\return `true` if the linked list contains the passed element, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, содержит ли связный список переданный элемент
	 *	
	 *	Проверяет, содержит ли связный список элемент, равный переданному.
	 *	\param element Искомый элемент.
	 *	\return `true`, если связный список содержит переданный элемент, иначе `false`.
	 */
	virtual bool contains(const T& element) const override;

	/**
	 *	\~english
	 *	\brief How many elements of the linked list are equal to the passed one
	 *	
	 *	Counts elements that are equal to the passed one.
	 *	\param element The desired element.
	 *	\return Number of matches.
	 *	
	 *	\~russian
	 *	\brief Сколько элементов связного списка равны переданному
	 *	
	 *	Подсчитывает элементы, равные переданному.
	 *	\param element Требуемый элемент.
	 *	\return Количество совпадений.
	 */
	virtual int count(const T& element) const override;

	/**
	 *	\~english
	 *	\brief Creates an iterator to the first element
	 *	
	 *	Creates an iterator that points to the first element of the linked list. If the linked list
	 *	is empty, the created iterator is end (`is_end` is true).
	 *	\return The iterator to the first element of the linked list.
	 *	
	 *	\~russian
	 *	\brief Создаёт итератор на первый элемент
	 *	
	 *	Создаёт итератор, который указывает на первый элемент связного списка. Если связный список
	 *	пуст, созданный итератор будет указывать на конец (`is_end` истинно).
	 *	\return Итератор на первый элемент связного списка.
	 */
	LinkedListIterator<T> begin() noexcept;

	/**
	 *	\~english
	 *	\brief Creates an iterator to the last element
	 *
	 *	Creates an iterator that points to the last element of the linked list. If the linked list
	 *	is empty, the created iterator is end (`is_end` is true).
	 *	\return The iterator to the last element of the linked list.
	 *
	 *	\~russian
	 *	\brief Создаёт итератор на последний элемент
	 *
	 *	Создаёт итератор, который указывает на последний элемент связного списка. Если связный
	 *	список пуст, созданный итератор будет указывать на конец (`is_end` истинно).
	 *	\return Итератор на последний элемент связного списка.
	 */
	LinkedListIterator<T> last() noexcept;

	/**
	 *	\~english
	 *	\brief Creates an iterator pointing after the last element
	 *
	 *	Creates an iterator that points to a space after the last element of the linked list (this
	 *	iterator is end: `is_end` is true).
	 *	\return The end iterator.
	 *	
	 *	\~russian
	 *	\brief Создаёт итератор, указывающий после последнего элемента
	 *	
	 *	Создаёт итератор, который указывает на пространство после последнего элемента связного
	 *	списка (этот итератор указывает в конец: `is_end` истинно).
	 *	\return Итератор на конец.
	 */
	LinkedListIterator<T> end() noexcept;

	/**
	 *	\~english
	 *	\brief Creates an iterator pointing to the specified element
	 *	
	 *	Creates an iterator that points to an element with the passed index.
	 *	\param index The index of an element that the iterator will points to.
	 *	\return The iterator pointing to the specified element.
	 *	\throw std::out_of_range The index is out of the linked list bounds.
	 *	
	 *	\~russian
	 *	\brief Создаёт итератор, указывающий на заданный элемент
	 *	
	 *	Создаёт итератор, который указывает на элемент с переданным индексом.
	 *	\param index Индекс элемента, на который будет указывать итератор.
	 *	\return Итератор, указывающий на заданный элемент.
	 *	\throw std::out_of_range Индекс выходит за границы связного списка.
	 */
	LinkedListIterator<T> create_iterator(int index);

	/**
	 *	\~english
	 *	\brief Creates a constant iterator to the first element
	 *	
	 *	Creates a constant iterator that points to the first element of the linked list. If the
	 *	linked list is empty, the created iterator is end (`is_end` is true).
	 *	\return The constant iterator to the first element of the linked list.
	 *	
	 *	\~russian
	 *	\brief Создаёт константный итератор на первый элемент
	 *	
	 *	Создаёт константный итератор, который указывает на первый элемент связного списка. Если
	 *	связный список пуст, созданный итератор будет указывать на конец (`is_end` истинно).
	 *	\return Константный итератор на первый элемент связного списка.
	 */
	ConstLinkedListIterator<T> begin() const noexcept;

	/**
	 *	\~english
	 *	\brief Creates a constant iterator to the last element
	 *
	 *	Creates a constant iterator that points to the last element of the linked list. If the
	 *	linked list is empty, the created iterator is end (`is_end` is true).
	 *	\return The constant iterator to the last element of the linked list.
	 *
	 *	\~russian
	 *	\brief Создаёт константный итератор на последний элемент
	 *
	 *	Создаёт константный итератор, который указывает на последний элемент связного списка. Если
	 *	связный список пуст, созданный итератор будет указывать на конец (`is_end` истинно).
	 *	\return Константный итератор на последний элемент связного списка.
	 */
	ConstLinkedListIterator<T> last() const noexcept;

	/**
	 *	\~english
	 *	\brief Creates a constant iterator pointing after the last element
	 *
	 *	Creates a constant iterator that points to a space after the last element of the linked
	 *	list (this iterator is end: `is_end` is true).
	 *	\return The constant end iterator.
	 *	
	 *	\~russian
	 *	\brief Создаёт константный итератор, указывающий после последнего элемента
	 *	
	 *	Создаёт константный итератор, который указывает на пространство после последнего элемента
	 *	связного списка (этот итератор указывает в конец: `is_end` истинно).
	 *	\return Константный итератор на конец.
	 */
	ConstLinkedListIterator<T> end() const noexcept;

	/**
	 *	\~english
	 *	\brief Creates a constant iterator pointing to the specified element
	 *	
	 *	Creates a constant iterator that points to an element with the passed index.
	 *	\param index The index of an element that the iterator will points to.
	 *	\return The constnat iterator pointing to the specified element.
	 *	\throw std::out_of_range The index is out of the linked list bounds.
	 *	
	 *	\~russian
	 *	\brief Создаёт константый итератор, указывающий на заданный элемент
	 *	
	 *	Создаёт константый итератор, который указывает на элемент с переданным индексом.
	 *	\param index Индекс элемента, на который будет указывать итератор.
	 *	\return Константный итератор, указывающий на заданный элемент.
	 *	\throw std::out_of_range Индекс выходит за границы связного списка.
	 */
	ConstLinkedListIterator<T> create_iterator(int index) const;

	/**
	 *	\~english
	 *	\brief Converts `LinkedListIterator` to `ConstLinkedListIterator`
	 *
	 *	Converts the passed linked list iterator to constant linked list iterator that points to
	 *	the same element of the same linked list.
	 *	\param iterator The linked list iterator that will be converted.
	 *	\return A result constant linked list iterator.
	 *
	 *	\~russian
	 *	\brief Конвертирует `LinkedListIterator` в `ConstLinkedListIterator`
	 *
	 *	Конвертирует переданный итератор связного списка в константный итератор связного списка,
	 *	указывающий на тот же элемент того же связного списка.
	 *	\param iterator Итератор, который будет сконвертирован.
	 *	\return Полученный константный итератор.
	 */
	static ConstLinkedListIterator<T> iterator_to_const(const LinkedListIterator<T> iterator) noexcept;
	
			/* OPERATORS */
	
	/**
	 *	\~english
	 *	\brief The copy assignment operator
	 *	
	 *	Clears the linked list and inserts into it copies of elements of the passed linked list.
	 *	Invalidates all iterators.
	 *	\warning This operator must not be used if the linked list contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param list The linked list to assign.
	 *	\return A reference to itself.
	 *	
	 *	\~russian
	 *	\brief Оператор присваивания копированием
	 *	
	 *	Очищает связный список и вставляет в него копии элементов переданного связного списка.
	 *	Аннулирует все итераторы.
	 *	\warning Этот оператор не должен быть использован, если связный список содержит
	 *	`unique_ptr`ы (может быть выброшено исключение `std::logic_error`). Вместо этого
	 *	используйте семантику перемещения.
	 *	\param list Связный список для присваивания.
	 *	\return Ссылка на себя.
	 */
	virtual LinkedList<T>& operator=(const LinkedList<T>& list);

	/**
	 *	\~english
	 *	\brief The move assignment operator
	 *
	 *	Clears the linked list and moves into it elements of the passed linked list. Invalidates
	 *	all iterators.
	 *	\param list The linked list to move.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Оператор присваивания перемещением
	 *
	 *	Очищает связный список и перемещает в него элементы переданного связного списка. Аннулирует
	 *	все итераторы.
	 *	\param list Связный список для перемещения.
	 *	\return Ссылка на себя.
	 */
	virtual LinkedList<T>& operator=(LinkedList<T>&& list);

	/**
	 *	\~english
	 *	\brief Checks whether two linked lists are equal
	 *	
	 *	Two linked lists are equal if all of their elements are equal and have the same order.
	 *	\param list The linked list to compare.
	 *	\return `true` if two linked lists are equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, равны ли два связных списка
	 *
	 *	Два связных списка равны, если их элементы равны и находятся в одинаковом порядке.
	 *	\param list Связный список для сравнения.
	 *	\return `true`, если два связных списка равны, иначе `false`.
	 */
	bool operator==(const LinkedList<T>& list) const;

	/**
	 *	\~english
	 *	\brief Checks whether two linked lists are not equal
	 *
	 *	Two linked lists are equal if all of their elements are equal and have the same order.
	 *	\param list The linked list to compare.
	 *	\return `true` if two linked lists are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, различаются ли два связных списка
	 *
	 *	Два связных списка равны, если их элементы равны и находятся в одинаковом порядке.
	 *	\param list Связный список для сравнения.
	 *	\return `true`, если два связных списка не равны, иначе `false`.
	 */
	bool operator!=(const LinkedList<T>& list) const;

	/**
	 *	\~english
	 *	\brief Returns the specifies element
	 *	
	 *	Allows to access an element with the specified index. Access to an arbitrary element of a
	 *	linked list can be slow.
	 *	\param index The index of the element.
	 *	\return A reference to the desired element.
	 *	\throw std::out_of_range The index is out of the linked list bounds.
	 *
	 *	\~russian
	 *	\brief Возвращает заданный элемент
	 *
	 *	Позволяет получить доступ к элементу с заданным индексом. Доступ к произвольному элементу
	 *	связного списка может быть медленным.
	 *	\param index Индекс элемента.
	 *	\return Ссылка на требуемый элемент.
	 *	\throw std::out_of_range Индекс выходит за границы связного списка.
	 */
	T& operator[](int index);

	/**
	 *	\~english
	 *	\brief Returns the specifies element
	 *
	 *	Allows to read an element with the specified index. Access to an arbitrary element of a
	 *	linked list can be slow.
	 *	\param index The index of the element.
	 *	\return A constant reference to the desired element.
	 *	\throw std::out_of_range The index is out of the linked list bounds.
	 *
	 *	\~russian
	 *	\brief Возвращает заданный элемент
	 *
	 *	Позволяет прочитать элемент с заданным индексом. Доступ к произвольному элементу
	 *	связного списка может быть медленным.
	 *	\param index Индекс элемента.
	 *	\return Константная ссылка на требуемый элемент.
	 *	\throw std::out_of_range Индекс выходит за границы связного списка.
	 */
	const T& operator[](int index) const;

private:
	std::shared_ptr<LinkedListNode_<T>> begin_;
	std::shared_ptr<LinkedListNode_<T>> end_;
	int size_;

	std::shared_ptr<LinkedListNode_<T>> get_last_node_() const noexcept;

	mutable std::list<LinkedListIterator<T>*> iterators_;
	mutable std::list<ConstLinkedListIterator<T>*> const_iterators_;
	void register_iterator_(LinkedListIterator<T>* iterator) noexcept;
	void unregister_iterator_(LinkedListIterator<T>* iterator) noexcept;
	void register_iterator_(ConstLinkedListIterator<T>* iterator) const noexcept;
	void unregister_iterator_(ConstLinkedListIterator<T>* iterator) const noexcept;
	void clear_iterators_() const noexcept;
};


		/* DEFINITIONS of LinkedListNode_ */

template<typename T>
LinkedListNode_<T>::LinkedListNode_(const T& val) noexcept :
	value(val),
	prev(),
	next()
{}

template<typename T>
LinkedListNode_<T>::LinkedListNode_(T&& val) noexcept :
	value(std::move(val)),
	prev(),
	next()
{}

template<typename T>
LinkedListNode_<std::unique_ptr<T>>::LinkedListNode_(const LinkedListNode_<std::unique_ptr<T>>& val) noexcept :
	value(),
	prev(),
	next()
{
	throw std::logic_error("Using of this method is not allowed for containers of unique_ptr's");
}

template<typename T>
LinkedListNode_<std::unique_ptr<T>>::LinkedListNode_(const std::unique_ptr<T>& val) noexcept :
	value(),
	prev(),
	next()
{
	throw std::logic_error("Using of this method is not allowed for containers of unique_ptr's");
}

template<typename T>
LinkedListNode_<std::unique_ptr<T>>::LinkedListNode_(std::unique_ptr<T>&& val) noexcept :
	value(std::move(val)),
	prev(),
	next()
{}

		/* DEFINITIONS of LinkedList */

#define FOR_ITERATORS_(i, arg) \
	for (auto i : iterators_) arg \
	for (auto i : const_iterators_) arg

template<typename T>
LinkedList<T>::LinkedList() noexcept :
	begin_(nullptr),
	end_(nullptr),
	size_(0)
{}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& linked_list) noexcept :
	LinkedList()
{
	for (const T& i : linked_list)
	{
		add(i);
	}
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& linked_list) noexcept :
	begin_(std::move(linked_list.begin_)),
	end_(std::move(linked_list.end_)),
	size_(std::move(linked_list.size_))
{}

template<typename T>
LinkedList<T>::~LinkedList() noexcept
{
	clear_iterators_();
}

template<typename T>
String LinkedList<T>::to_string() const noexcept
{
	if (is_empty())
	{
		return L"{ }"_s;
	}
	else
	{
		String str = L"{ "_s;
		for (auto p = begin(); !p.is_last(); p.next())
		{
			str += p.to_string() + L", "_s;
		}
		return str + util::to_string(get_last()) + L" }"_s;
	}
}

template<typename T>
int LinkedList<T>::hash_code() const noexcept
{
	if (is_empty())
	{
		return 0;
	}
	else
	{
		int hash = 0, one = 1;
		for (const T& i : *this)
		{
			hash += one * util::hash_code(i);
			one = -one;
		}
		return hash;
	}
}

template<typename T>
int LinkedList<T>::size() const noexcept
{
	return size_;
}

template<typename T>
bool LinkedList<T>::is_empty() const noexcept
{
	return size_ == 0;
}

template<typename T>
void LinkedList<T>::clear() noexcept
{
	begin_.reset();
	end_.reset();
	size_ = 0;

	FOR_ITERATORS_(i,
	{
		i->index_ = 0;
		i->node_.reset();
	})
}

template<typename T>
T& LinkedList<T>::get_begin()
{
	if (size_ > 0)
	{
		return begin_->value;
	}
	else
	{
		throw std::out_of_range("Attempt to access an element of empty linked list");
	}
}

template<typename T>
T& LinkedList<T>::get_last()
{
	if (size_ > 0)
	{
		return end_->value;
	}
	else
	{
		throw std::out_of_range("Attempt to access an element of empty linked list");
	}
}

template<typename T>
const T& LinkedList<T>::get_begin() const
{
	if (size_ > 0)
	{
		return begin_->value;
	}
	else
	{
		throw std::out_of_range("Attempt to access an element of empty linked list");
	}
}

template<typename T>
const T& LinkedList<T>::get_last() const
{
	if (size_ > 0)
	{
		return end_->value;
	}
	else
	{
		throw std::out_of_range("Attempt to access an element of empty linked list");
	}
}

template<typename T>
bool LinkedList<T>::add(const T& element)
{
	if (size_ == 0)
	{
		begin_.reset(new LinkedListNode_<T>(element));
		end_ = begin_;
	}
	else
	{
		end_->next.reset(new LinkedListNode_<T>(element));
		end_->next->prev = end_;
		end_ = end_->next;
	}
	
	FOR_ITERATORS_(i,
	{
		if (i->index_ >= size_)
		{
			i->index_++;
		}
	})

	size_++;
	return true;
}

template<typename T>
bool LinkedList<T>::add(T&& element)
{
	if (size_ == 0)
	{
		begin_.reset(new LinkedListNode_<T>(std::forward<T>(element)));
		end_ = begin_;
	}
	else
	{
		end_->next.reset(new LinkedListNode_<T>(std::forward<T>(element)));
		end_->next->prev = end_;
		end_ = end_->next;
	}
	
	FOR_ITERATORS_(i,
	{
		if (i->index_ >= size_)
		{
			i->index_++;
		}
	})

	size_++;
	return true;
}

template<typename T>
bool LinkedList<T>::add(const T& element, int index)
{
	if (index >= 0 && index <= size_)
	{
		return add_before(element, create_iterator(index));
	}
	else
	{
		return false;
	}
}

template<typename T>
bool LinkedList<T>::add(T&& element, int index)
{
	if (index >= 0 && index <= size_)
	{
		return add_before(std::forward<T>(element), create_iterator(index));
	}
	else
	{
		return false;
	}
}

template<typename T>
int LinkedList<T>::add(const LinkedList<T>& list)
{
	int ret = 0;
	for (const T& i : list)
	{
		ret += static_cast<int>(add(i));
	}
	return ret;
}

template<typename T>
int LinkedList<T>::add(LinkedList<T>&& list)
{
	int ret = list.size_;
	if (!list.is_empty())
	{
		end_->next = list.begin_;
		list.begin_->prev = end_;
		end_ = list.end_;

		FOR_ITERATORS_(i,
		{
			if (i->index_ >= size_)
			{
				i->index_ += ret;
			}
		})

		size_ += list.size_;
	}
	return ret;
}

template<typename T>
bool LinkedList<T>::add_before(const T& element, const LinkedListIterator<T>& iterator)
{
	return add_before(element, iterator_to_const(iterator));
}

template<typename T>
bool LinkedList<T>::add_before(T&& element, const LinkedListIterator<T>& iterator)
{
	return add_before(std::forward<T>(element), iterator_to_const(iterator));
}

template<typename T>
bool LinkedList<T>::add_before(const T& element, const ConstLinkedListIterator<T>& iterator)
{
	if (iterator.is_valid() && &iterator.get_container() == this)
	{
		if (iterator.is_end())
		{
			return add(element);
		}
		else
		{
			std::shared_ptr<LinkedListNode_<T>> node = iterator.node_.lock();
			std::shared_ptr<LinkedListNode_<T>> new_node = std::make_shared<LinkedListNode_<T>>(element);
			new_node->next = node;
			new_node->prev = node->prev;
			node->prev = new_node;
			if (new_node->prev.lock())
			{
				new_node->prev.lock()->next = new_node;
			}
			size_++;

			int index = iterator.index_;
			FOR_ITERATORS_(i,
			{
				if (i->index_ >= index)
				{
					i->index_++;
				}
			})

			return true;
		}
	}
	else
	{
		return false;
	}
}

template<typename T>
bool LinkedList<T>::add_before(T&& element, const ConstLinkedListIterator<T>& iterator)
{
	if (iterator.is_valid() && &iterator.get_container() == this)
	{
		if (iterator.is_end())
		{
			return add(element);
		}
		else
		{
			std::shared_ptr<LinkedListNode_<T>> node = iterator.node_.lock();
			std::shared_ptr<LinkedListNode_<T>> new_node = std::make_shared<LinkedListNode_<T>>(std::forward<T>(element));
			new_node->next = node;
			new_node->prev = node->prev;
			node->prev = new_node;
			if (new_node->prev.lock())
			{
				new_node->prev.lock()->next = new_node;
			}
			size_++;

			int index = iterator.index_;
			FOR_ITERATORS_(i,
			{
				if (i->index_ >= index)
				{
					i->index_++;
				}
			})

			return true;
		}
	}
	else
	{
		return false;
	}
}

template<typename T>
bool LinkedList<T>::add_to_begin(const T& element)
{
	if (size_ > 0)
	{
		std::shared_ptr<LinkedListNode_<T>> new_node = std::make_shared<LinkedListNode_<T>>(element);
		new_node->next = begin_;
		begin_->prev = new_node;
		begin_ = new_node;
		size_++;

		FOR_ITERATORS_(i,
		{
			i->index_++;
		})

		return true;
	}
	else
	{
		return add(element);
	}
}

template<typename T>
bool LinkedList<T>::add_to_begin(T&& element)
{
	if (size_ > 0)
	{
		std::shared_ptr<LinkedListNode_<T>> new_node = std::make_shared<LinkedListNode_<T>>(std::move(element));
		new_node->next = begin_;
		begin_->prev = new_node;
		begin_ = new_node;
		size_++;

		FOR_ITERATORS_(i,
		{
			i->index_++;
		})

		return true;
	}
	else
	{
		return add(std::forward<T>(element));
	}
}

template<typename T>
bool LinkedList<T>::remove(int index)
{
	return remove(create_iterator(index));
}

template<typename T>
bool LinkedList<T>::remove(const LinkedListIterator<T>& element)
{
	return remove(iterator_to_const(element));
}

template<typename T>
bool LinkedList<T>::remove(const ConstLinkedListIterator<T>& element)
{
	if (element.is_element_valid() && &element.get_container() == this)
	{
		int index = element.index_;

		std::shared_ptr<LinkedListNode_<T>> node = element.node_.lock();
		if (!element.is_begin())
		{
			node->prev.lock()->next = node->next;
		}
		else
		{
			begin_ = node->next;
		}

		if (!element.is_last())
		{
			node->next->prev = node->prev;
		}
		else
		{
			end_ = node->prev.lock();
		}
		size_--;

		FOR_ITERATORS_(i,
		{
			if (i->index_ > index)
			{
				i->index_--;
			}
		})
		
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
int LinkedList<T>::remove(int from, int to)
{
	if (from < to && from >= 0 && to <= size_)
	{
		int index = 0;
		std::shared_ptr<LinkedListNode_<T>> i = begin_;
		for ( ; index < from; i = i->next, index++);
		LinkedListIterator<T> from_itr(*this, index, i);
		for ( ; index < to; i = i->next, index++);
		LinkedListIterator<T> to_itr(*this, index, i);
		return remove(from_itr, to_itr);
	}
	else
	{
		return false;
	}
}

template<typename T>
int LinkedList<T>::remove(const LinkedListIterator<T>& from, const LinkedListIterator<T>& to)
{
	return remove(iterator_to_const(from), iterator_to_const(to));
}

template<typename T>
int LinkedList<T>::remove(const ConstLinkedListIterator<T>& from, const ConstLinkedListIterator<T>& to)
{
	if (from.is_element_valid() && to.is_valid() &&
		&from.get_container() == this && &to.get_container() == this &&
		from.get_index() < to.get_index())
	{
		int from_index = from.index_;
		int to_index = to.index_;
		std::shared_ptr<LinkedListNode_<T>> from_node = from.node_.lock();
		std::shared_ptr<LinkedListNode_<T>> to_node = to.is_end() ? end_ : to.node_.lock()->prev.lock();

		if (!from.is_begin())
		{
			from_node->prev.lock()->next = to_node->next;
		}
		else
		{
			begin_ = to_node->next;
		}
		
		if (!to.is_end())
		{
			to_node->next->prev = from_node->prev;
		}
		else
		{
			end_ = from_node->prev.lock();
		}
		
		size_ -= to_index - from_index;
		
		FOR_ITERATORS_(i,
		{
			if (i->index_ > from_index && i->index_ < to_index)
			{
				i->index_ = from_index;
			}
			else if (i->index_ >= to_index)
			{
				i->index_ -= to_index - from_index;
			}
		})
		
		return to_index - from_index;
	}
	else
	{
		return false;
	}
}

template<typename T>
bool LinkedList<T>::remove_first(const T& element)
{
	return remove(find_first_by_iterator(element));
}

template<typename T>
bool LinkedList<T>::remove_last(const T& element)
{
	return remove(find_last_by_iterator(element));
}

template<typename T>
int LinkedList<T>::remove_all(const T& element)
{
	if (!is_empty())
	{
		int ret = 0;
		while (get_begin() == element)
		{
			ret += static_cast<int>(remove(begin()));
		}
		auto i = begin();
		while (i.next())
		{
			if (i.get() == element)
			{
				ret += static_cast<int>(remove(i--));
			}
		}
		return ret;
	}
	else
	{
		return 0;
	}
}

template<typename T>
int LinkedList<T>::find_first_by_index(const T& element) const
{
	int index = 0;
	for (std::shared_ptr<LinkedListNode_<T>> i = begin_; i; i = i->next, index++)
	{
		if (i->value == element)
		{
			return index;
		}
	}
	return -1;
}

template<typename T>
int LinkedList<T>::find_last_by_index(const T& element) const
{
	int index = size_ - 1;
	for (std::shared_ptr<LinkedListNode_<T>> i = end_; i; i = i->prev.lock(), index--)
	{
		if (i->value == element)
		{
			return index;
		}
	}
	return -1;
}

template<typename T>
LinkedListIterator<T> LinkedList<T>::find_first_by_iterator(const T& element)
{
	int index = 0;
	for (std::shared_ptr<LinkedListNode_<T>> i = begin_; i; i = i->next, index++)
	{
		if (i->value == element)
		{
			return LinkedListIterator<T>(*this, index, i);
		}
	}
	return end();
}

template<typename T>
LinkedListIterator<T> LinkedList<T>::find_last_by_iterator(const T& element)
{
	int index = size_ - 1;
	for (std::shared_ptr<LinkedListNode_<T>> i = end_; i; i = i->prev.lock(), index--)
	{
		if (i->value == element)
		{
			return LinkedListIterator<T>(*this, index, i);
		}
	}
	return end();
}

template<typename T>
ConstLinkedListIterator<T> LinkedList<T>::find_first_by_iterator(const T& element) const
{
	int index = 0;
	for (std::shared_ptr<LinkedListNode_<T>> i = begin_; i; i = i->next, index++)
	{
		if (i->value == element)
		{
			return ConstLinkedListIterator<T>(*this, index, i);
		}
	}
	return end();
}

template<typename T>
ConstLinkedListIterator<T> LinkedList<T>::find_last_by_iterator(const T& element) const
{
	int index = size_ - 1;
	for (std::shared_ptr<LinkedListNode_<T>> i = end_; i; i = i->prev.lock(), index--)
	{
		if (i->value == element)
		{
			return ConstLinkedListIterator<T>(*this, index, i);
		}
	}
	return end();
}

template<typename T>
bool LinkedList<T>::contains(const T& element) const
{
	for (std::shared_ptr<LinkedListNode_<T>> i = begin_; i; i = i->next)
	{
		if (i->value == element)
		{
			return true;
		}
	}
	return false;
}

template<typename T>
int LinkedList<T>::count(const T& element) const
{
	int result = 0;
	for (std::shared_ptr<LinkedListNode_<T>> i = begin_; i; i = i->next)
	{
		if (i->value == element)
		{
			result++;
		}
	}
	return result;
}

template<typename T>
LinkedListIterator<T> LinkedList<T>::begin() noexcept
{
	return LinkedListIterator<T>(*this, 0, begin_);
}

template<typename T>
LinkedListIterator<T> LinkedList<T>::last() noexcept
{
	return LinkedListIterator<T>(*this, size_ - 1, end_);
}

template<typename T>
LinkedListIterator<T> LinkedList<T>::end() noexcept
{
	return LinkedListIterator<T>(*this, size_);
}

template<typename T>
LinkedListIterator<T> LinkedList<T>::create_iterator(int index)
{
	if (index >= 0 && index <= size_)
	{
		if (index < size_ / 2)
		{
			auto ret = begin();
			for (int i = 0; i < index; i++)
			{
				ret.next();
			}
			return ret;
		}
		else
		{
			auto ret = last();
			for (int i = size_ - 1; i > index; i--)
			{
				ret.prev();
			}
			return ret;
		}
	}
	else
	{
		throw std::out_of_range("Index is out of linked list bounds");
	}
}

template<typename T>
ConstLinkedListIterator<T> LinkedList<T>::begin() const noexcept
{
	return ConstLinkedListIterator<T>(*this, 0, begin_);
}

template<typename T>
ConstLinkedListIterator<T> LinkedList<T>::last() const noexcept
{
	return ConstLinkedListIterator<T>(*this, size_ - 1, end_);
}

template<typename T>
ConstLinkedListIterator<T> LinkedList<T>::end() const noexcept
{
	return ConstLinkedListIterator<T>(*this, size_);
}

template<typename T>
ConstLinkedListIterator<T> LinkedList<T>::create_iterator(int index) const
{
	if (index >= 0 && index <= size_)
	{
		if (index < size_ / 2)
		{
			auto ret = begin();
			for (int i = 0; i < index; i++)
			{
				ret.next();
			}
			return ret;
		}
		else
		{
			auto ret = last();
			for (int i = size_ - 1; i > index; i--)
			{
				ret.prev();
			}
			return ret;
		}
	}
	else
	{
		throw std::out_of_range("Index is out of linked list bounds");
	}
}

template<typename T>
ConstLinkedListIterator<T> LinkedList<T>::iterator_to_const(const LinkedListIterator<T> iterator) noexcept
{
	return ConstLinkedListIterator<T>(iterator.container_, iterator.index_, iterator.node_.lock(), iterator.is_valid_);
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& linked_list)
{
	clear();
	for (const T& i : linked_list)
	{
		add(i);
	}
	return *this;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& linked_list)
{
	clear_iterators_();
	begin_ = std::move(linked_list.begin_);
	end_ = std::move(linked_list.end_);
	size_ = std::move(linked_list.size_);
	return *this;
}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& linked_list) const
{
	if (size_ == linked_list.size_)
	{
		auto this_iter = begin();
		auto other_iter = linked_list.begin();
		do 
		{
			if (!(this_iter.get() == other_iter.get()))
			{
				return false;
			}
		} while (this_iter.next() && other_iter.next());
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
bool LinkedList<T>::operator!=(const LinkedList<T>& linked_list) const
{
	return !(*this == linked_list);
}

template<typename T>
T& LinkedList<T>::operator[](int index)
{
	if (index >= 0 && index < size_)
	{
		return create_iterator(index).get();
	}
	else
	{
		throw std::out_of_range("Index is out of linked list bounds");
	}
}

template<typename T>
const T& LinkedList<T>::operator[](int index) const
{
	if (index >= 0 && index < size_)
	{
		return create_iterator(index).get();
	}
	else
	{
		throw std::out_of_range("Index is out of linked list bounds");
	}
}

template<typename T>
std::shared_ptr<LinkedListNode_<T>> LinkedList<T>::get_last_node_() const noexcept
{
	return end_;
}

template<typename T>
void LinkedList<T>::register_iterator_(LinkedListIterator<T>* iterator) noexcept
{
	iterators_.push_back(iterator);
}

template<typename T>
void LinkedList<T>::unregister_iterator_(LinkedListIterator<T>* iterator) noexcept
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

template<typename T>
void LinkedList<T>::register_iterator_(ConstLinkedListIterator<T>* iterator) const noexcept
{
	const_iterators_.push_back(iterator);
}

template<typename T>
void LinkedList<T>::unregister_iterator_(ConstLinkedListIterator<T>* iterator) const noexcept
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

template<typename T>
void LinkedList<T>::clear_iterators_() const noexcept
{
	FOR_ITERATORS_(i,
	{
		i->is_valid_ = false;
	})
	iterators_.clear();
	const_iterators_.clear();
}

#undef FOR_ITERATORS_

}
