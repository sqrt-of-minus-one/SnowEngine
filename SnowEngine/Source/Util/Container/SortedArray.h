    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SortedArray.h               //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `SortedArray` class
 *
 *	This file contains the definition of the `SortedArray` class.
 *
 *	\~russian
 *	\brief Файл с классом `SortedArray`
 *
 *	Этот файл содержит определение класса `SortedArray`.
 */

#include "Array.h"

#include "../Function/Delegate.h"

namespace snow
{

/**
 *	\~english
 *	\brief The class of the array that is always sorted
 *	
 *	This class is identical to an ordinary array, but is always sorted. Sorting is performed using
 *	a custom comparator function. Default comparator function performs sorting in non-descending
 *	order of hash codes (in non-descending order of values for `float` type).
 *	\warning If the array contains `unique_ptr`'s, methods that copy the array elements (for
 *	example, the copy constructor) must not be called (`std::logic_error` exception can be thrown).
 *	\tparam T Type of the array elements. The requirements are the same as the `Array` class.
 *	
 *	\~russian
 *	\brief Класс массива, который вседа отсортирован
 *	
 *	Этот класс идентичен обычному массиву, но всегда отсортирован. Сортировка производится с
 *	помощью пользовательской сравнивающей функции. Сравнивающая функция по умолчанию производит
 *	сортировку по неубыванию хеш-кодов (по неубыванию значений для типа `float`).
 *	\warning Если массив содержит `unique_ptr`ы, то методы, копирующие элементы массива,
 *	(например, конструктор копирования) не должны вызываться (может быть выброшено исключение
 *	`std::logic_error`).
 *	\tparam T Тип элементов массива. Требования те же, что и для класса `Array`.
 */
template<typename T>
class SortedArray : public Array<T>
{
public:
			/* CONSTRUCTORS */
	
	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates an empty array with default comparator function.
	 *	
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *	
	 *	Создаёт пустой массив со сравнивающей функцией по умолчанию.
	 */
	SortedArray() noexcept;

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *
	 *	Copies the array with its comparator function.
	 *	\warning This constructor must not be used if the array contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param array The array that will be copied.
	 *
	 *	\~russian
	 *	\brief Конструктор копирования
	 *
	 *	Копирует массив вместе с его сравнивающей функцией.
	 *	\warning Этот конструктор не должен быть использован, если массив содержит `unique_ptr`ы
	 *	(может быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param array Массив, который будет скопирован.
	 */
	SortedArray(const SortedArray<T>& array) noexcept;

	/**
	 *	\~english
	 *	\brief The move constructor
	 *
	 *	Moves elements to a new array from the passed one saving its comparator function.
	 *	\param array The array whose elements will be moved.
	 *
	 *	\~russian
	 *	\brief Конструктор перемещения
	 *
	 *	Перемещает элементы в новый массив из переданного, сохраняя его сравнивающую функцию.
	 *	\param array Массив, чьи элементы будут перемещены.
	 */
	SortedArray(SortedArray<T>&& array) noexcept;

	/**
	 *	\~english
	 *	\brief Creates a sorted array of the specified size
	 *
	 *	Creates an array of the specified size and fills it with default elements. If the array
	 *	stores pointers, `nullptr`s are added. Otherwise inserted elements are created using a
	 *	default constructor. The default comparator function is used.
	 *	\param size The size of the array.
	 *
	 *	\~russian
	 *	\brief Создаёт отсортированный массив заданного размера
	 *
	 *	Создаёт массив заданного размера и заполняет его элементами по умолчанию. Если массив
	 *	хранит указатели, добавляются `nullptr`. Иначе вставляемые элементы будут создаваться с
	 *	использованием конструктора по умолчанию. Используется сравнивающая функция по умолчанию.
	 *	\param size Размер массива.
	 */
	SortedArray(int size);

			/* METHODS FROM IContainer &
				METHODS FROM Array */

	/**
	 *	\~english
	 *	\brief Adds a new element
	 *
	 *	Inserts a new element into the array in a correct place so that the array remains sorted.
	 *	Moves the subsequent elements towards the end of the array. The iterators will also be
	 *	moved and continue to point to their elements.
	 *	\warning This method must not be used if the array contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param element The element that will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Добавляет новый элемент
	 *
	 *	Вставляет новый элемент в массив на соответствующее место, таким образом, чтобы массив
	 *	оставался отсортированным. Передвигает последующие элементы к концу массива. Итераторы
	 *	также будут передвинуты и продолжат указывать на свои элементы.
	 *	\warning Этот метод не должен быть использован, если массив содержит `unique_ptr`ы (может
	 *	быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param element Элемент, который будет добавлен.
	 *	\return `true`, если элемент был успешно добавлен, иначе `false`.
	 */
	virtual bool add(const T& element) override;

	/**
	 *	\~english
	 *	\brief Adds a new element
	 *
	 *	Inserts a new element into the array in a correct place so that the array remains sorted.
	 *	Moves the subsequent elements towards the end of the array. The iterators will also be
	 *	moved and continue to point to their elements.
	 *	\param element The element that will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Добавляет новый элемент
	 *
	 *	Вставляет новый элемент в массив на соответствующее место, таким образом, чтобы массив
	 *	оставался отсортированным. Передвигает последующие элементы к концу массива. Итераторы
	 *	также будут передвинуты и продолжат указывать на свои элементы.
	 *	\param element Элемент, который будет добавлен.
	 *	\return `true`, если элемент был успешно добавлен, иначе `false`.
	 */
	virtual bool add(T&& element) override;

	/**
	 *	\~english
	 *	\brief Adds a new element
	 *
	 *	Inserts a new element into the array in a correct place so that the array remains sorted.
	 *	Moves the subsequent elements towards the end of the array. The iterators will also be
	 *	moved and continue to point to their elements.
	 *	\warning This method must not be used if the array contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param element The element that will be added.
	 *	\param index This parameter is ignored.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Добавляет новый элемент
	 *
	 *	Вставляет новый элемент в массив на соответствующее место, таким образом, чтобы массив
	 *	оставался отсортированным. Передвигает последующие элементы к концу массива. Итераторы
	 *	также будут передвинуты и продолжат указывать на свои элементы.
	 *	\warning Этот метод не должен быть использован, если массив содержит `unique_ptr`ы (может
	 *	быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param element Элемент, который будет добавлен.
	 *	\param index Этот параметр игнорируется.
	 *	\return `true`, если элемент был успешно добавлен, иначе `false`.
	 */
	virtual bool add(const T& element, int index) override;

	/**
	 *	\~english
	 *	\brief Adds a new element
	 *
	 *	Inserts a new element into the array in a correct place so that the array remains sorted.
	 *	Moves the subsequent elements towards the end of the array. The iterators will also be
	 *	moved and continue to point to their elements.
	 *	\param element The element that will be added.
	 *	\param index This parameter is ignored.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Добавляет новый элемент
	 *
	 *	Вставляет новый элемент в массив на соответствующее место, таким образом, чтобы массив
	 *	оставался отсортированным. Передвигает последующие элементы к концу массива. Итераторы
	 *	также будут передвинуты и продолжат указывать на свои элементы.
	 *	\param element Элемент, который будет добавлен.
	 *	\param index Этот параметр игнорируется.
	 *	\return `true`, если элемент был успешно добавлен, иначе `false`.
	 */
	virtual bool add(T&& element, int index) override;

	/**
	 *	\~english
	 *	\brief Adds into the array copies of elements of the passed array
	 *	
	 *	Inserts into the array copies of elements of the passed array in correct places so that the
	 *	array remains sorted. Moves the subsequent elements towards the end of the array. The
	 *	iterators will also be moved and continue to point to their elements.
	 *	\warning This method must not be used if the array contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param array The array whose elements will be added.
	 *	\return The number of elements that have been successfully added.
	 *	
	 *	\~russian
	 *	\brief Добавляет в массив копии элементов переданного массива
	 *	
	 *	Вставляет в массив копии элементов переданного массива на соответствующие места, таким
	 *	образом, чтобы массив оставался отсортированным. Передвигает последующие элементы к концу
	 *	массива. Итераторы также будут передвинуты и продолжат указывать на свои элементы.
	 *	\warning Этот метод не должен быть использован, если массив содержит `unique_ptr`ы (может
	 *	быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param array Массив, чьи элементы будут добавлены.
	 *	\return Количество успешно добавленных элементов.
	 */
	virtual int add(const Array<T>& array) override;

	/**
	 *	\~english
	 *	\brief Moves into the array elements of the passed array
	 *
	 *	Moves into the array elements of the passed array in correct places so that the array
	 *	remains sorted. Moves the subsequent elements towards the end of the array. The iterators
	 *	will also be moved and continue to point to their elements.
	 *	\param array The array whose elements will be moved.
	 *	\return The number of elements that have been successfully added.
	 *
	 *	\~russian
	 *	\brief Перемещает в массив элементы из переданного массива
	 *
	 *	Перемещает в массив элементы из переданного массива на соответствующие места, таким
	 *	образом, чтобы массив оставался отсортированным. Передвигает последующие элементы к концу
	 *	массива. Итераторы также будут передвинуты и продолжат указывать на свои элементы.
	 *	\param array Массив, чьи элементы будут перемещены.
	 *	\return Количество успешно добавленных элементов.
	 */
	virtual int add(Array<T>&& array) override;

	/**
	 *	\~english
	 *	\brief Removes all elements that are equal to the passed one
	 *
	 *	Compares every element of the array with the passed one and removes all matches. All
	 *	iterators will continue to point to their elements. Iterators that pointed to one of the
	 *	removed elements will point to the next element after executing this method.
	 *	\param element The object to compare.
	 *	\return Number of elements that have been successfully removed.
	 *
	 *	\~russian
	 *	\brief Удаляет все элементы, равные переданному
	 *
	 *	Сравнивает каждый элемент массива с переданным и удаляет все совпадения. Все итераторы
	 *	продолжат указывать на свои элементы. Итераторы, указывавшие на один из удалённых
	 *	элементов, после выполнения метода будут указывать на следующий.
	 *	\param element Объект для сравнения.
	 *	\return Количество успешно удалённых элементов.
	 */
	virtual int remove_all(const T& element) override;
	
	/**
	 *	\~english
	 *	\brief Finds any element that is equal to the passed one
	 *	
	 *	Compares elements of the array with the passed one. If a match is found, returns its index.
	 *	\param element The desired element.
	 *	\return An index of a match; a negative value if no match has been found.
	 *	
	 *	\~russian
	 *	\brief Находит любой элемент, который равен переданному
	 *	
	 *	Сравнивает элементы массива с переданным. Если совпадение найдено, возвращает его индекс.
	 *	\param element Искомый элемент.
	 *	\return Индекс совпадения; отрицательное значение, если совпадения найдено не было.
	 */
	virtual int find_any(const T& element) const override;

	/**
	 *	\~english
	 *	\brief Finds the first element that is equal to the passed one
	 *
	 *	Compares elements of the array with the passed one starting from the beginning. If a match
	 *	is found, returns its index.
	 *	\param element The desired element.
	 *	\return An index of the first match; a negative value if no match has been found.
	 *
	 *	\~russian
	 *	\brief Находит первый элемент, который равен переданному
	 *
	 *	Сравнивает элементы массива с переданным, начиная с начала. Если совпадение найдено,
	 *	возвращает его индекс.
	 *	\param element Искомый элемент.
	 *	\return Индекс первого совпадения; отрицательное значение, если совпадения найдено не было.
	 */
	virtual int find_first(const T& element) const override;

	/**
	 *	\~english
	 *	\brief Finds the last element that is equal to the passed one
	 *
	 *	Compares elements of the array with the passed one starting from the end. If a match is
	 *	found, returns its index.
	 *	\param element The desired element.
	 *	\return An index of the last match; a negative value if no match has been found.
	 *
	 *	\~russian
	 *	\brief Находит последний элемент, который равен переданному
	 *
	 *	Сравнивает элементы массива с переданным, начиная с конца. Если совпадение найдено,
	 *	возвращает его индекс.
	 *	\param element Искомый элемент.
	 *	\return Индекс последнего совпадения; отрицательное значение, если совпадения найдено не
	 *	было.
	 */
	virtual int find_last(const T& element) const override;

	/**
	 *	\~english
	 *	\brief Checks whether the array contains the passed element
	 *
	 *	Checks whether the array has an element that is equal to the passed one.
	 *	\param element The desired element.
	 *	\return `true` if the array contains the passed element, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, содержит ли массив переданный элемент
	 *
	 *	Проверяет, содержит ли массив элемент, равный переданному.
	 *	\param element Искомый элемент.
	 *	\return `true`, если массив содержит переданный элемент, иначе `false`.
	 */
	virtual bool contains(const T& element) const override;

	/**
	 *	\~english
	 *	\brief How many elements of the array are equal to the passed one
	 *
	 *	Counts elements that are equal to the passed one.
	 *	\param element The desired element.
	 *	\return Number of matches.
	 *
	 *	\~russian
	 *	\brief Сколько элементов массива равны переданному
	 *
	 *	Подсчитывает элементы, равные переданному.
	 *	\param element Требуемый элемент.
	 *	\return Количество совпадений.
	 */
	virtual int count(const T& element) const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Sets the comparator function
	 *
	 *	Allows to set the comparator function, which will be used to sort the array. The comparator
	 *	function must return:
	 *	- a *positive value* if the first element should be after the second one;
	 *	- a *negative value* if the first element should be before the second one;
	 *	- *zero* if the elements are equal.
	 *	If the comparator function is no longer available, it will be replaced by the default
	 *	comparator function.
	 *	\param comparator The reference to the comparator function.
	 *
	 *	\~russian
	 *	\brief Устанавливает сравнивающую функцию
	 *
	 *	Позволяет установить сравнивающую функцию, которая будет использоваться для сортировки
	 *	массива. Сравнивающая функция должна возвращать:
	 *	- *положительное значение*, если первый элемент должен быть после второго;
	 *	- *отрицательное значение*, если первый элемент должен быть перед вторым;
	 *	- *ноль*, если элементы равны.
	 *	Если сравнивающая функция перестаёт быть доступной, она заменяется на сравнивающую функцию
	 *	по умолчанию.
	 *	\param comparator Ссылка на сравнивающую функцию.
	 */
	void set_comparator(const std::function<int(const T&, const T&)>& comparator);

	/**
	 *	\~english
	 *	\brief Sets the comparator function
	 *
	 *	Allows to set the comparator function, which will be used to sort the array. The comparator
	 *	function must return:
	 *	- a *positive value* if the first element should be after the second one;
	 *	- a *negative value* if the first element should be before the second one;
	 *	- *zero* if the elements are equal.
	 *	If the comparator function is no longer available, it will be replaced by the default
	 *	comparator function.
	 *	\param comparator The delegate to the comparator function.
	 *
	 *	\~russian
	 *	\brief Устанавливает сравнивающую функцию
	 *
	 *	Позволяет установить сравнивающую функцию, которая будет использоваться для сортировки
	 *	массива. Сравнивающая функция должна возвращать:
	 *	- *положительное значение*, если первый элемент должен быть после второго;
	 *	- *отрицательное значение*, если первый элемент должен быть перед вторым;
	 *	- *ноль*, если элементы равны.
	 *	Если сравнивающая функция перестаёт быть доступной, она заменяется на сравнивающую функцию
	 *	по умолчанию.
	 *	\param comparator Делегат на сравнивающую функцию.
	 */
	void set_comparator(const Delegate<int, const T&, const T&>& comparator);

	/**
	 *	\~english
	 *	\brief Sets the comparator function
	 *
	 *	Allows to set a method as comparator function, which will be used to sort the array. The
	 *	comparator function must return:
	 *	- a *positive value* if the first element should be after the second one;
	 *	- a *negative value* if the first element should be before the second one;
	 *	- *zero* if the elements are equal.
	 *	If the comparator function is no longer available, it will be replaced by the default
	 *	comparator function.
	 *	\tparam T_Class The class of the object whose method will be used as comparator function.
	 *	You're allowed to use the `const` modifier here.
	 *	\param object The object whose method will be used as comparator function.
	 *	\param comparator The reference to the comparator function.
	 *
	 *	\~russian
	 *	\brief Устанавливает сравнивающую функцию
	 *
	 *	Позволяет установить метод в качестве сравнивающей функции, которая будет использоваться
	 *	для сортировки массива. Сравнивающая функция должна возвращать:
	 *	- *положительное значение*, если первый элемент должен быть после второго;
	 *	- *отрицательное значение*, если первый элемент должен быть перед вторым;
	 *	- *ноль*, если элементы равны.
	 *	Если сравнивающая функция перестаёт быть доступной, она заменяется на сравнивающую функцию
	 *	по умолчанию.
	 *	\tparam T_Class Класс объекта, чей метод будет использоваться в качестве сравнивающей
	 *	функции. Вы можете использовать здесь модификатор `const`.
	 *	\param object Объект, чей метод будет использоваться в качестве сравнивающей функции.
	 *	\param comparator Ссылка на сравнивающую функцию.
	 */
	template<typename T_Class>
	void set_comparator(T_Class& object, const std::function<int(T_Class&, const T&, const T&)>& comparator);
	
	/**
	 *	\~english
	 *	\brief Compares two values using the comparator function
	 *	
	 *	Uses the comparator function to compare two values.
	 *	\param first The first value.
	 *	\param second The second value.
	 *	\return A positive number if the first value should be after the second one; a negative
	 *	number if the first value should be before the second one; zero if the values are equal.
	 *	
	 *	\~russian
	 *	\brief Сравнивает два значения с помощью сравнивающей функции
	 *	
	 *	Использует сравнивающую функцию для сравнения двух значений.
	 *	\param first Первое значение.
	 *	\param second Второе значение.
	 *	\return Положительное число, если первое значение должно быть после второго; отрицательное
	 *	число, если первое значение должно быть перед вторый; ноль, если значения равны.
	 */
	int compare(const T& first, const T& second) const;

	/**
	 *	\~english
	 *	\brief Compares two array elements using the comparator function
	 *
	 *	Uses the comparator function to compare two array elements.
	 *	\param first The index of the first value.
	 *	\param second The index of the second value.
	 *	\return A positive number if the first value should be after the second one; a negative
	 *	number if the first value should be before the second one; zero if the values are equal.
	 *
	 *	\~russian
	 *	\brief Сравнивает два элемента массива с помощью сравнивающей функции
	 *
	 *	Использует сравнивающую функцию для сравнения двух элементов массива.
	 *	\param first Индекс первого значения.
	 *	\param second Индекс второго значения.
	 *	\return Положительное число, если первое значение должно быть после второго; отрицательное
	 *	число, если первое значение должно быть перед вторый; ноль, если значения равны.
	 */
	int compare_by_index(int first, int second) const;

			/* OPERATORS */

	/**
	 *	\~english
	 *	\brief The copy assignment operator
	 *	
	 *	Clears the array and inserts into it copies of elements of the passed array. Invalidates
	 *	all iterators. Sorts the array.
	 *	\warning This operator must not be used if the array contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param array The array to assign.
	 *	\return A reference to itself.
	 *	
	 *	\~russian
	 *	\brief Оператор присваивания копированием
	 *	
	 *	Очищает массив и вставляет в него копии элементов переданного массива. Аннулирует все
	 *	итераторы. Сортирует массив.
	 *	\warning Этот оператор не должен быть использован, если массив содержит `unique_ptr`ы
	 *	(может быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param array Массив для присваивания.
	 *	\return Ссылка на себя.
	 */
	virtual SortedArray<T>& operator=(const Array<T>& array) override;

	/**
	 *	\~english
	 *	\brief The move assignment operator
	 *
	 *	Clears the array and moves into it elements of the passed array. Invalidates all iterators.
	 *	Sorts the array.
	 *	\param array The array to move.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Оператор присваивания перемещением
	 *
	 *	Очищает массив и перемещает в него элементы переданного массива. Аннулирует все итераторы.
	 *	Сортирует массив.
	 *	\param array Массив для перемещения.
	 *	\return Ссылка на себя.
	 */
	virtual SortedArray<T>& operator=(Array<T>&& array) override;
	
private:
	mutable Delegate<int, const T&, const T&> comparator_;
	int get_index_to_add_(const T& element) const;
	int get_index_to_add_(const T& element, int from, int to) const;
	void sort_();

	void quick_sort_(int left, int right);
	void insertion_sort_(int left, int right);
	int median_(int left, int right);
	int partition_(int left, int right, const T& pivot);
	void swap_(int index_1, int index_2);

	static int default_comparator_(const T& first, const T& second);
};


		/* DEFINITIONS */
		
		/* SortedArray: public */

template<typename T>
SortedArray<T>::SortedArray() noexcept :
	Array<T>(),
	comparator_()
{
	comparator_.bind(&default_comparator_);
}

template<typename T>
SortedArray<T>::SortedArray(const SortedArray<T>& array) noexcept :
	Array<T>(array),
	comparator_(array.comparator_)
{}

template<typename T>
SortedArray<T>::SortedArray(SortedArray<T>&& array) noexcept :
	Array<T>(std::forward<Array<T>>(array)),
	comparator_(array.comparator_)
{}

template<typename T>
SortedArray<T>::SortedArray(int size) :
	Array<T>(size),
	comparator_()
{
	comparator_.bind(&default_comparator_);
}

template<typename T>
void SortedArray<T>::set_comparator(const std::function<int(const T&, const T&)>& comparator)
{
	comparator_.bind(comparator);
	sort_();
}

template<typename T>
void SortedArray<T>::set_comparator(const Delegate<int, const T&, const T&>& comparator)
{
	comparator_.bind(comparator);
	sort_();
}

template<typename T>
template<typename T_Class>
void SortedArray<T>::set_comparator(T_Class& object, const std::function<int(T_Class&, const T&, const T&)>& comparator)
{
	comparator_.bind(object, comparator);
	sort_();
}

template<typename T>
bool SortedArray<T>::add(const T& element)
{
	return Array<T>::add(element, get_index_to_add_(element));
}

template<typename T>
bool SortedArray<T>::add(T&& element)
{
	return Array<T>::add(std::forward<T>(element), get_index_to_add_(element));
}

template<typename T>
bool SortedArray<T>::add(const T& element, int index)
{
	return add(element);
}

template<typename T>
bool SortedArray<T>::add(T&& element, int index)
{
	return add(std::forward<T>(element));
}

template<typename T>
int SortedArray<T>::add(const Array<T>& array)
{
	int res = 0;
	for (int i = 0; i < array.size(); i++)
	{
		res += static_cast<int>(add(array[i]));
	}
	return res;
}

template<typename T>
int SortedArray<T>::add(Array<T>&& array)
{
	int res = 0;
	for (int i = 0; i < array.size(); i++)
	{
		res += static_cast<int>(add(std::move(array[i])));
	}
	return res;
}

template<typename T>
int SortedArray<T>::remove_all(const T& element)
{
	int found = get_index_to_add_(element);
	int first = found;
	int last = found;
	if (found > 0 && compare((*this)[found - 1], element) == 0)
	{
		while (--first > 0 && compare((*this)[first - 1], element) == 0);
		while (++last < Array<T>::size() && compare((*this)[last], element) == 0);
		return Array<T>::remove(first, last);
	}
	else
	{
		return 0;
	}
}

template<typename T>
int SortedArray<T>::find_any(const T& element) const
{
	int found = get_index_to_add_(element);
	if (found > 0 && compare((*this)[--found], element) == 0)
	{
		return found;
	}
	else
	{
		return -1;
	}
}

template<typename T>
int SortedArray<T>::find_first(const T& element) const
{
	int found = get_index_to_add_(element);
	if (found > 0 && compare((*this)[found - 1], element) == 0)
	{
		while (--found > 0 && compare((*this)[found - 1], element) == 0);
		return found;
	}
	else
	{
		return -1;
	}
}

template<typename T>
int SortedArray<T>::find_last(const T& element) const
{
	int found = get_index_to_add_(element);
	if (found > 0 && compare((*this)[--found], element) == 0)
	{
		while (++found < Array<T>::size() && compare((*this)[found], element) == 0);
		return found - 1;
	}
	else
	{
		return -1;
	}
}

template<typename T>
bool SortedArray<T>::contains(const T& element) const
{
	int index = get_index_to_add_(element);
	return index > 0 && compare((*this)[index - 1], element) == 0;
}

template<typename T>
int SortedArray<T>::count(const T& element) const
{
	int found = get_index_to_add_(element);
	int first = found;
	int last = found;
	if (found > 0 && compare((*this)[found - 1], element) == 0)
	{
		while (--first > 0 && compare((*this)[first - 1], element) == 0);
		while (++last < Array<T>::size() && compare((*this)[last], element) == 0);
		return last - first;
	}
	else
	{
		return 0;
	}
}

template<typename T>
int SortedArray<T>::compare(const T& first, const T& second) const
{
	try
	{
		return comparator_(first, second);
	}
	catch (std::logic_error e)
	{
		comparator_.bind(&default_comparator_);
		return comparator_(first, second);
	}
}

template<typename T>
int SortedArray<T>::compare_by_index(int first, int second) const
{
	return compare((*this)[first], (*this)[second]);
}

template<typename T>
SortedArray<T>& SortedArray<T>::operator=(const Array<T>& array)
{
	Array<T>::operator=(array);
	sort_();
	return *this;
}

template<typename T>
SortedArray<T>& SortedArray<T>::operator=(Array<T>&& array)
{
	Array<T>::operator=(std::forward<Array<T>>(array));
	sort_();
	return *this;
}
		
		/* SortedArray: private */

template<typename T>
int SortedArray<T>::get_index_to_add_(const T& element) const
{
	return Array<T>::is_empty() ? 0 : get_index_to_add_(element, 0, Array<T>::size() - 1);
}

template<typename T>
int SortedArray<T>::get_index_to_add_(const T& element, int from, int to) const
{
	int middle = (from + to) / 2;
	int comp_res = compare((*this)[middle], element);
	if (comp_res == 0)
	{
		return middle + 1;
	}
	else if (comp_res < 0)
	{
		return from < to ? get_index_to_add_(element, middle + 1, to) : middle + 1;
	}
	else
	{
		return from < to ? get_index_to_add_(element, from, middle - 1) : middle;
	}
}

template<typename T>
void SortedArray<T>::sort_()
{
	quick_sort_(0, Array<T>::size() - 1);
}

template<typename T>
void SortedArray<T>::quick_sort_(int left, int right)
{
	if (right - left < 9)
	{
		insertion_sort_(left, right);
	}
	else
	{
		int median = median_(left, right);
		int part = partition_(left, right, (*this)[median]);
		quick_sort_(left, part - 1);
		quick_sort_(part + 1, right);
	}
}

template<typename T>
void SortedArray<T>::insertion_sort_(int left, int right)
{
	for (int i = left + 1; i <= right; i++)
	{
		T tmp = std::move((*this)[i]);
		int j;
		for (j = i; j > left && compare((*this)[j - 1], tmp) >= 0; j--)
		{
			(*this)[j] = std::move((*this)[j - 1]);
		}
		(*this)[j] = std::move(tmp);
	}
}

template<typename T>
int SortedArray<T>::median_(int left, int right)
{
	int centre = (left + right) / 2;

	if (compare_by_index(left, centre) > 0)
	{
		swap_(left, centre);
	}
	if (compare_by_index(left, right) > 0)
	{
		swap_(left, right);
	}
	if (compare_by_index(centre, right) > 0)
	{
		swap_(centre, right);
	}

	swap_(centre, right - 1);
	return right - 1;
}

template<typename T>
int SortedArray<T>::partition_(int left, int right, const T& pivot)
{
	int left_ptr = left;
	int right_ptr = right - 1;
	while (true)
	{
		while (compare((*this)[++left_ptr], pivot) < 0)
			;
		while (compare((*this)[--right_ptr], pivot) > 0)
			;
		if (left_ptr >= right_ptr)
		{
			break;
		}
		else
		{
			swap_(left_ptr, right_ptr);
		}
	}
	swap_(left_ptr, right - 1);
	return left_ptr;
}

template<typename T>
void SortedArray<T>::swap_(int index_1, int index_2)
{
	T tmp = std::move((*this)[index_2]);
	(*this)[index_2] = std::move((*this)[index_1]);
	(*this)[index_1] = std::move(tmp);
}

template<typename T>
int SortedArray<T>::default_comparator_(const T& first, const T& second)
{
	return util::hash_code(first) - util::hash_code(second);
}

template<>
int SortedArray<float>::default_comparator_(const float& first, const float& second)
{
	return math::ceil_abs(first - second);
}

}