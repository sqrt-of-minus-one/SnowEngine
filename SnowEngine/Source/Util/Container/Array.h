    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Array.h                     //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `Array` class
 *	
 *	This file contains the definition of the `Array` class.
 *	
 *	\~russian
 *	\brief Файл с классом `Array`
 *	
 *	Этот файл содержит определение класса `Array`.
 */

#include "ArrayIterator.h"
		// + Object
		// + IContainer

#include <list>

#include "../../Math/Math.h"

namespace snow
{

/**
 *	\~english
 *	\brief The class of array
 *	
 *	This class is used as the array. It should be used if you need to have a fast access to its
 *	elements. Increasing the size of the array, inserting or removing elements in its middle or
 *	beginning is slow and should be avoided. If you need to insert or remove elements in the middle
 *	or beginning, the `LinkedList` container may be more suitable for you.
 *	\warning If the array contains `unique_ptr`'s, methods that copy the array elements (for
 *	example, the copy constructor) must not be called (`std::logic_error` exception can be thrown).
 *	\tparam T Type of the array elements. If you need to store objects of some class in the array,
 *	it is highly recommended to store pointers to them. If `T` is not a primitive type, `to_string`
 *	and `hash_code` methods must be defined for it (any `snow::Object` has them). If `T` is not a
 *	pointer, it also must have a default constructor, an assignment operator (`=`) and an equality
 *	operator (`==`). The default and copy constructors are assumed not to throw any exceptions.
 *	
 *	\~russian
 *	\brief Класс массива
 *	
 *	Этот класс используется в качестве массива. Его следует использовать, если необходим быстрый
 *	доступ к его элементам. Увеличение размера массива, вставка или удаление элементов из его
 *	середины или начала происходят медленно, поэтому их следует избегать. Если вам необходимо
 *	вставлять или удалять элементы в середину или начало, класс `LinkedList` может оказаться более
 *	подходящим.
 *	\warning Если массив содержит `unique_ptr`ы, то методы, копирующие элементы массива,
 *	(например, конструктор копирования) не должны вызываться (может быть выброшено исключение
 *	`std::logic_error`).
 *	\tparam T Тип элементов массива. Если вам нужно хранить в массиве объекты некоторого класса,
 *	настоятельно рекомендуется хранить указатели на них. Если `T` не примитивный тип, для него
 *	должны быть определены методы `to_string` и `hash_code` (у любого `snow::Object` они есть).
 *	Если `T` не указатель, у него также должны быть определёны конструктор по умолчанию, оператор
 *	присваивания (`=`) и оператор равенства (`==`). Предполагается, что конструктор по умолчанию и
 *	конструктор копирования не выбрасывают никаких исключений.
 */
template<typename T>
class Array :
	public Object,
	public IContainer<T>
{
	template<typename T_Container, typename T_Element>
	friend class BaseArrayIterator_;

public:
			/* CONSTRUCTORS */
	
	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates an empty array.
	 *	
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *	
	 *	Создаёт пустой массив.
	 */
	Array() noexcept;

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *	
	 *	Copies the array.
	 *	\warning This constructor must not be used if the array contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param array The array that will be copied.
	 *	
	 *	\~russian
	 *	\brief Конструктор копирования
	 *	
	 *	Копирует массив.
	 *	\warning Этот конструктор не должен быть использован, если массив содержит `unique_ptr`ы
	 *	(может быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param array Массив, который будет скопирован.
	 */
	Array(const Array<T>& array) noexcept;

	/**
	 *	\~english
	 *	\brief The move constructor
	 *	
	 *	Moves elements to a new array from the passed one.
	 *	\param array The array whose elements will be moved.
	 *	
	 *	\~russian
	 *	\brief Конструктор перемещения
	 *	
	 *	Перемещает элементы в новый массив из переданного.
	 *	\param array Массив, чьи элементы будут перемещены.
	 */
	Array(Array<T>&& array) noexcept;

	/**
	 *	\~english
	 *	\brief Creates an array of the specified size
	 *	
	 *	Creates an array of the specified size and fills it with default elements. If the array
	 *	stores pointers, `nullptr`s are added. Otherwise inserted elements are created using a
	 *	default constructor.
	 *	\param size The size of the array.
	 *	
	 *	\~russian
	 *	\brief Создаёт массив заданного размера
	 *	
	 *	Создаёт массив заданного размера и заполняет его элементами по умолчанию. Если массив
	 *	хранит указатели, добавляются `nullptr`. Иначе вставляемые элементы будут создаваться с
	 *	использованием конструктора по умолчанию.
	 *	\param size Размер массива.
	 */
	Array(int size);

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
	virtual ~Array() noexcept;

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the array into a string
	 *	
	 *	Creates a string representing the list of the array elements. `util::to_string` is used to
	 *	convert elements to string.
	 *	\return A result string in the format `{ x, x, ..., x }`. `{ }` if the array is empty.
	 *	
	 *	\~russian
	 *	\brief Конвертирует массив в строку
	 *
	 *	Создаёт строку, представляющую из себя список элементов массива. Для конвертации элементов
	 *	в строку используется `util::to_string`.
	 *	\return Итоговая строка в формате `{ x, x, ..., x }`. `{ }`, если массив пуст.
	 */
	virtual String to_string() const noexcept override;

	/**
	 *	\~english
	 *	\brief Hash code of the array
	 *	
	 *	Hash code is calculated using `util::hash_code` function and formula:
	 *	\f[
	 *		\sum^{n}_{i = 0} ((-1)^i \cdot a[i]) = a[0] - a[1] + a[2] - ...
	 *	\f]
	 *	\f$n\f$ is the array size, \f$a[i]\f$ is the hash code of i-th element of the array.
	 *	\return Hash code of the array.
	 *	
	 *	\~russian
	 *	\brief Хеш-код массива
	 *
	 *	Хеш-код вычисляется с использованием `util::hash_code` по формуле:
	 *	\f[
	 *		\sum^{n}_{i = 0} ((-1)^i \cdot (a[i]) = a[0] - a[1] + a[2] - ...
	 *	\f]
	 *	\f$n\f$ — размер массива, \f$a[i]\f$ — хеш-код i-го элемента массива.
	 *	\return Хеш-код массива.
	 */
	virtual int hash_code() const noexcept override;

			/* METHODS FROM IContainer &
				METHODS */

	/**
	 *	\~english
	 *	\brief The size of the array
	 *
	 *	Allows to get the number of elements in the array.
	 *	\return The number of elements in the array.
	 *
	 *	\~russian
	 *	\brief Размер массива
	 *
	 *	Позволяет получить количество элеменов в массиве.
	 *	\return Количество элеменов в массиве.
	 */
	virtual int size() const noexcept override;

	/**
	 *	\~english
	 *	\brief Checks whether the array is empty
	 *
	 *	Checks whether the array is empty.
	 *	\return `true` if the array does not contain any element, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, пуст ли массив
	 *
	 *	Проверяет, пуст ли массив.
	 *	\return `true`, если массив не содержит никаких элементов, иначе `false`.
	 */
	virtual bool is_empty() const noexcept override;

	/**
	 *	\~english
	 *	\brief Clears the array
	 *
	 *	Removes all of the elements in the array and sets all of its iterators to the end.
	 *	
	 *	\~russian
	 *	\brief Очищает массив
	 *
	 *	Удаляет все элементы массива и устанавливает его итераторы в конец.
	 */
	virtual void clear() noexcept override;
	
	/**
	 *	\~english
	 *	\brief Changes the array size
	 *
	 *	Increases or decreases the array size. If the new size is more than the old one, a formed
	 *	space will be filled with default elements (`nullptr`s for pointers, a default constructor
	 *	otherwise). In this case end iterators will be moved in order to continue to be end. If the
	 *	new size is less than the old one, the last elements, that didn't fit in the array, will be
	 *	removed. Iterators pointing to removed elements become end (`is_end` is true).
	 *	\param new_size The new array size.
	 *	\return `true` if the array has been successfully resized, `false` otherwise (i. g. if the
	 *	new size is negative).
	 *	
	 *	\~russian
	 *	\brief Изменяет размер массива
	 *	
	 *	Увеличивает или уменьшает размер массива. Если новый размер больше старого, образовавшееся
	 *	место будет заполнено элементами по умолчанию (`nullptr` для указателей, иначе конструктор
	 *	по умолчанию). В этом случает итераторы, указывающие на конец, будут сдвинуты, чтобы
	 *	продолжать указывать на конец. Если новый размер меньше старого, последние элементы, не
	 *	помещающиеся в массив, будут удалены. Итераторы, указывающие на удалённые элементы, будут
	 *	указывать на конец (`is_end` для них будет возвращать `true`).
	 *	\param new_size Новый размер массива.
	 *	\return `true`, если размер был успешно изменён, иначе `false` (например, если новый размер
	 *	отрицательный).
	 */
	bool resize(int new_size) noexcept;

	/**
	 *	\~english
	 *	\brief Adds a new element
	 *	
	 *	Inserts a new element into the end of the array. If there are iterators that point to the
	 *	end (`is_end` is true), they will continue to be end after executing this method.
	 *	\warning This method must not be used if the array contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param element The element that will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Добавляет новый элемент
	 *	
	 *	Вставляет новый элемент в конец массива. Если есть итераторы, указывающие на конец 
	 *	(`is_end` истинно), после выполнения метода они продолжат указывать на конец.
	 *	\warning Этот метод не должен быть использован, если массив содержит `unique_ptr`ы (может
	 *	быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param element Элемент, который будет добавлен.
	 *	\return `true`, если элемент был успешно добавлен, иначе `false`.
	 */
	virtual bool add(const T& element);

	/**
	 *	\~english
	 *	\brief Adds a new element
	 *
	 *	Inserts a new element into the end of the array. If there are iterators that points to the
	 *	end (`is_end` is true), they will continue to be end after executing this method.
	 *	\param element The element that will be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Добавляет новый элемент
	 *
	 *	Вставляет новый элемент в конец массива. Если есть итераторы, указывающие на конец
	 *	(`is_end` истинно), после выполнения метода они продолжат указывать на конец.
	 *	\param element Элемент, который будет добавлен.
	 *	\return `true`, если элемент был успешно добавлен, иначе `false`.
	 */
	virtual bool add(T&& element);

	/**
	 *	\~english
	 *	\brief Adds a new element with the specified index
	 *	
	 *	Inserts a new element into the array. The new element will have the passed index. Moves the
	 *	subsequent elements towards the end of the array. The iterators will also be moved and
	 *	continue to point to their elements.
	 *	\warning This method must not be used if the array contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param element The element that will be added.
	 *	\param index The index that the new element will have.
	 *	\return `true` if the element has been successfully added, `false` otherwise (i. g. if the
	 *	index is out of the array bounds).
	 *	
	 *	\~russian
	 *	\brief Добавляет новый элемент с заданным индексом
	 *	
	 *	Вставляет новый элемент в массив. Новый элемент будет иметь переданный индекс. Передвигает
	 *	последующие элементы к концу массива. Итераторы также будут передвинуты и продолжат
	 *	указывать на свои элементы.
	 *	\warning Этот метод не должен быть использован, если массив содержит `unique_ptr`ы (может
	 *	быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param element Элемент, который будет добавлен.
	 *	\param index Индекс, который новый элемент будет иметь.
	 *	\return `true`, если элемент был успешно добавлен, иначе `false` (например, если индекс
	 *	выходит за границы массива).
	 */
	virtual bool add(const T& element, int index);

	/**
	 *	\~english
	 *	\brief Adds a new element with the specified index
	 *
	 *	Inserts a new element into the array. The new element will have the passed index. Moves the
	 *	subsequent elements towards the end of the array. The iterators will also be moved and
	 *	continue to point to their elements.
	 *	\param element The element that will be added.
	 *	\param index The index that the new element will have.
	 *	\return `true` if the element has been successfully added, `false` otherwise (i. g. if the
	 *	index is out of the array bounds).
	 *
	 *	\~russian
	 *	\brief Добавляет новый элемент с заданным индексом
	 *
	 *	Вставляет новый элемент в массив. Новый элемент будет иметь переданный индекс. Передвигает
	 *	последующие элементы к концу массива. Итераторы также будут передвинуты и продолжат
	 *	указывать на свои элементы.
	 *	\param element Элемент, который будет добавлен.
	 *	\param index Индекс, который новый элемент будет иметь.
	 *	\return `true`, если элемент был успешно добавлен, иначе `false` (например, если индекс
	 *	выходит за границы массива).
	 */
	virtual bool add(T&& element, int index);

	/**
	 *	\~english
	 *	\brief Adds into the array copies of elements of the passed array
	 *	
	 *	Inserts into the end of the array copies of elements of the passed array. If there are
	 *	iterators that points to the end (`is_end` is true), they will continue to be end after
	 *	executing this method.
	 *	\warning This method must not be used if the array contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param array The array whose elements will be added.
	 *	\return The number of elements that have been successfully added.
	 *	
	 *	\~russian
	 *	\brief Добавляет в массив копии элементов переданного массива
	 *	
	 *	Вставляет в конец массива копии элементов переданного массива. Если есть итераторы,
	 *	указывающие на конец (`is_end` истинно), после выполнения метода они продолжат указывать на
	 *	конец.
	 *	\warning Этот метод не должен быть использован, если массив содержит `unique_ptr`ы (может
	 *	быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param array Массив, чьи элементы будут добавлены.
	 *	\return Количество успешно добавленных элементов.
	 */
	virtual int add(const Array<T>& array);

	/**
	 *	\~english
	 *	\brief Moves into the array elements of the passed array
	 *
	 *	Moves into the end of the array elements of the passed array. If there are iterators that
	 *	points to the end (`is_end` is true), they will continue to be end after executing this
	 *	method.
	 *	\param array The array whose elements will be moved.
	 *	\return The number of elements that have been successfully added.
	 *	
	 *	\~russian
	 *	\brief Перемещает в массив элементы из переданного массива
	 *	
	 *	Перемещает в конец массива элементы из переданного массива. Если есть итераторы,
	 *	указывающие на конец (`is_end` истинно), после выполнения метода они продолжат указывать на
	 *	конец.
	 *	\param array Массив, чьи элементы будут перемещены.
	 *	\return Количество успешно добавленных элементов.
	 */
	virtual int add(Array<T>&& array);

	/**
	 *	\~english
	 *	\brief Removes an element with the specified index
	 *	
	 *	Removes an element that has the specified index. The subsequent elements are moved and fill
	 *	a formed space. All iterators will continue to point to their elements. Iterators that
	 *	pointed to the removed element will point to the next element after executing this method.
	 *	\param index The index of the element that will be removed.
	 *	\return `true` if the element has been successfully removed, `false` otherwise (i. g. if
	 *	the index is out of the array bounds).
	 *	
	 *	\~russian
	 *	\brief Удаляет элемент с заданным индексом
	 *	
	 *	Удаляет элемент, который имеет заданный индекс. Следующие элементы при этом сдвигаются и
	 *	заполняют образованное пространство. Все итераторы продолжат указывать на свои элементы.
	 *	Итераторы, указывавшие на удалённый элемент, после выполнения метода будут указывать на
	 *	следующий.
	 *	\param index Индекс элемента, который будет удалён.
	 *	\return `true`, если элемент был успешно удалён, иначе `false` (например, если индекс
	 *	выходит за границы массива).
	 */
	bool remove(int index);

	/**
	 *	\~english
	 *	\brief Removes an element by iterator
	 *	
	 *	Removes an element that the passed iterator points to. The subsequent elements are moved
	 *	and fill a formed space. All iterators will continue to point to their elements. Iterators
	 *	that pointed to the removed element (including the passed one) will point to the next
	 *	element after executing this method.
	 *	\param element The iterator pointing to the element that will be removed.
	 *	\return `true` if the element has been successfully removed, `false` otherwise (i. g. if
	 *	the iterator points to an element of other array).
	 *	
	 *	\~russian
	 *	\brief Удаляет элемент по итератору
	 *	
	 *	Удаляет элемент, на который указывает переданный итератор. Следующие элементы при этом
	 *	сдвигаются и заполняют образованное пространство. Все итераторы продолжат указывать на свои
	 *	элементы. Итераторы, указывавшие на удалённый элемент (включая переданный), после
	 *	выполнения метода будут указывать на следующий.
	 *	\param element Итератор, указывающий на элемент, который будет удалён.
	 *	\return `true`, если элемент был успешно удалён, иначе `false` (например, если итератор
	 *	указывает на элемент другого массива).
	 */
	bool remove(const ArrayIterator<T>& element);

	/**
	 *	\~english
	 *	\brief Removes an element by iterator
	 *
	 *	Removes an element that the passed iterator points to. The subsequent elements are moved
	 *	and fill a formed space. All iterators will continue to point to their elements. Iterators
	 *	that pointed to the removed element (including the passed one) will point to the next
	 *	element after executing this method.
	 *	\param element The iterator pointing to the element that will be removed.
	 *	\return `true` if the element has been successfully removed, `false` otherwise (i. g. if
	 *	the iterator points to an element of other array).
	 *
	 *	\~russian
	 *	\brief Удаляет элемент по итератору
	 *
	 *	Удаляет элемент, на который указывает переданный итератор. Следующие элементы при этом
	 *	сдвигаются и заполняют образованное пространство. Все итераторы продолжат указывать на свои
	 *	элементы. Итераторы, указывавшие на удалённый элемент (включая переданный), после
	 *	выполнения метода будут указывать на следующий.
	 *	\param element Итератор, указывающий на элемент, который будет удалён.
	 *	\return `true`, если элемент был успешно удалён, иначе `false` (например, если итератор
	 *	указывает на элемент другого массива).
	 */
	bool remove(const ConstArrayIterator<T>& element);

	/**
	 *	\~english
	 *	\brief Removes elements in the specified range
	 *	
	 *	Removes elements that are in the specified range. The subsequent elements are moved and
	 *	fill a formed space. All iterators will continue to point to their elements. Iterators that
	 *	pointed to one of the removed elements will point to the first element after the removed
	 *	range after executing this method.
	 *	\param from The beginning of the range that will be removed.
	 *	\param to The end of the range that will be removed. An element with this index won't be
	 *	removed, but the previous one will.
	 *	\return The number of elements that have been successfully removed.
	 *	
	 *	\~russian
	 *	\brief Удаляет элементы в заданном диапазоне
	 *	
	 *	Удаляет элементы, которых входят в заданный диапазон. Последующие элементы при этом
	 *	сдвигаются и заполняют образованное пространство. Все итераторы продолжат указывать на свои
	 *	элементы. Итераторы, указывавшие на один из удалённых элементов, после выполнения метода
	 *	будут указывать на первый элемент после удалённого диапазона.
	 *	\param from Начало диапазона, который будет удалён.
	 *	\param to Конец диапазона, который будет удалён. Элемент с этим индектом удалён не будет, а
	 *	предыдущий — будет.
	 *	\return Количество успешно удалённых элементов.
	 */
	int remove(int from, int to);

	/**
	 *	\~english
	 *	\brief Removes elements in the specified range
	 *
	 *	Removes elements that are in the specified range. The subsequent elements are moved and
	 *	fill a formed space. All iterators will continue to point to their elements. Iterators that
	 *	pointed to one of the removed elements will point to the first element after the removed
	 *	range after executing this method.
	 *	\param from The iterator pointing to the first element in the range that will be removed.
	 *	\param to The iterator pointing after the last element in the range that will be removed.
	 *	This element won't be removed.
	 *	\return The number of elements that have been successfully removed.
	 *
	 *	\~russian
	 *	\brief Удаляет элементы в заданном диапазоне
	 *
	 *	Удаляет элементы, которых входят в заданный диапазон. Последующие элементы при этом
	 *	сдвигаются и заполняют образованное пространство. Все итераторы продолжат указывать на свои
	 *	элементы. Итераторы, указывавшие на один из удалённых элементов, после выполнения метода
	 *	будут указывать на первый элемент после удалённого диапазона.
	 *	\param from Итератор, указывающий на первый элемент диапазона, который будет удалён.
	 *	\param to Итератор, указывающий после последнего элемента диапазона, который будет удалён.
	 *	Этот элемент не будет удалён.
	 *	\return Количество успешно удалённых элементов.
	 */
	int remove(const ArrayIterator<T>& from, const ArrayIterator<T>& to);

	/**
	 *	\~english
	 *	\brief Removes elements in the specified range
	 *
	 *	Removes elements that are in the specified range. The subsequent elements are moved and
	 *	fill a formed space. All iterators will continue to point to their elements. Iterators that
	 *	pointed to one of the removed elements will point to the first element after the removed
	 *	range after executing this method.
	 *	\param from The iterator pointing to the first element in the range that will be removed.
	 *	\param to The iterator pointing after the last element in the range that will be removed.
	 *	This element won't be removed.
	 *	\return The number of elements that have been successfully removed.
	 *
	 *	\~russian
	 *	\brief Удаляет элементы в заданном диапазоне
	 *
	 *	Удаляет элементы, которых входят в заданный диапазон. Последующие элементы при этом
	 *	сдвигаются и заполняют образованное пространство. Все итераторы продолжат указывать на свои
	 *	элементы. Итераторы, указывавшие на один из удалённых элементов, после выполнения метода
	 *	будут указывать на первый элемент после удалённого диапазона.
	 *	\param from Итератор, указывающий на первый элемент диапазона, который будет удалён.
	 *	\param to Итератор, указывающий после последнего элемента диапазона, который будет удалён.
	 *	Этот элемент не будет удалён.
	 *	\return Количество успешно удалённых элементов.
	 */
	int remove(const ConstArrayIterator<T>& from, const ConstArrayIterator<T>& to);

	/**
	 *	\~english
	 *	\brief Removes any element that is equal to the passed one
	 *
	 *	Compares elements of the array with the passed one and removes one of matches. All
	 *	iterators will continue to point to their elements. Iterators that pointed to the removed
	 *	element will point to the next element after executing this method.
	 *	\param element The object to compare.
	 *	\return `true` if an element has been successfully removed, `false` otherwise (i. g. if the
	 *	array doesn't contain the passed object).
	 *	
	 *	\~russian
	 *	\brief Удаляет любой элемент, который равен переданному
	 *	
	 *	Сравнивает элементы массива с переданным и удаляет одно из совпадений. Все итераторы
	 *	продолжат указывать на свои элементы. Итераторы, указывавшие на удалённый элемент, после
	 *	выполнения метода будут указывать на следующий.
	 *	\param element Объект для сравнения.
	 *	\return `true`, если элемент был успешно удалён, иначе `false` (например, если массив не
	 *	содержит переданный объект).
	 */
	bool remove_any(const T& element);

	/**
	 *	\~english
	 *	\brief Removes the first element that is equal to the passed one
	 *	
	 *	Compares elements of the array with the passed one starting from the beginning and
	 *	removes the first match. All iterators will continue to point to their elements. Iterators
	 *	that pointed to the removed element will point to the next element after executing this
	 *	method.
	 *	\param element The object to compare.
	 *	\return `true` if an element has been successfully removed, `false` otherwise (i. g. if the
	 *	array doesn't contain the passed object).
	 *	
	 *	\~russian
	 *	\brief Удаляет первый элемент, равный переданному
	 *
	 *	Сравнивает элементы массива с переданным, начиная с начала, и удаляет первое совпадение.
	 *	Все итераторы продолжат указывать на свои элементы. Итераторы, указывавшие на удалённый
	 *	элемент, после выполнения метода будут указывать на следующий.
	 *	\param element Объект для сравнения.
	 *	\return `true`, если элемент был успешно удалён, иначе `false` (например, если массив не
	 *	содержит переданный объект).
	 */
	bool remove_first(const T& element);

	/**
	 *	\~english
	 *	\brief Removes the last element that is equal to the passed one
	 *
	 *	Compares elements of the array with the passed one starting from the end and removes the
	 *	first match. All iterators will continue to point to their elements. Iterators that pointed
	 *	to the removed element will point to the next element after executing this method.
	 *	\param element The object to compare.
	 *	\return `true` if an element has been successfully removed, `false` otherwise (i. g. if the
	 *	array doesn't contain the passed object).
	 *
	 *	\~russian
	 *	\brief Удаляет последний элемент, равный переданному
	 *
	 *	Сравнивает элементы массива с переданным, начиная с конца, и удаляет первое совпадение.
	 *	Все итераторы продолжат указывать на свои элементы. Итераторы, указывавшие на удалённый
	 *	элемент, после выполнения метода будут указывать на следующий.
	 *	\param element Объект для сравнения.
	 *	\return `true`, если элемент был успешно удалён, иначе `false` (например, если массив не
	 *	содержит переданный объект).
	 */
	bool remove_last(const T& element);

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

	// This method can be useful in the SortedArray class
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
	virtual int find_any(const T& element) const;

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
	virtual int find_first(const T& element) const;

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
	virtual int find_last(const T& element) const;

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

	/**
	 *	\~english
	 *	\brief Creates an iterator to the first element
	 *	
	 *	Creates an iterator that points to the first element of the array. If the array is empty,
	 *	the created iterator is end (`is_end` is true).
	 *	\return The iterator to the first element of the array.
	 *	
	 *	\~russian
	 *	\brief Создаёт итератор на первый элемент
	 *	
	 *	Создаёт итератор, который указывает на первый элемент массива. Если массив пуст, созданный
	 *	итератор будет указывать на конец (`is_end` истинно).
	 *	\return Итератор на первый элемент массива.
	 */
	ArrayIterator<T> begin() noexcept;

	/**
	 *	\~english
	 *	\brief Creates an iterator to the last element
	 *
	 *	Creates an iterator that points to the last element of the array. If the array is empty,
	 *	the created iterator is end (`is_end` is true).
	 *	\return The iterator to the last element of the array.
	 *
	 *	\~russian
	 *	\brief Создаёт итератор на последний элемент
	 *
	 *	Создаёт итератор, который указывает на последний элемент массива. Если массив пуст,
	 *	созданный итератор будет указывать на конец (`is_end` истинно).
	 *	\return Итератор на последний элемент массива.
	 */
	ArrayIterator<T> last() noexcept;

	/**
	 *	\~english
	 *	\brief Creates an iterator pointing after the last element
	 *
	 *	Creates an iterator that points to a space after the last element of the array (this
	 *	iterator is end: `is_end` is true).
	 *	\return The end iterator.
	 *	
	 *	\~russian
	 *	\brief Создаёт итератор, указывающий после последнего элемента
	 *	
	 *	Создаёт итератор, который указывает на пространство после последнего элемента массива (этот
	 *	итератор указывает в конец: `is_end` истинно).
	 *	\return Итератор на конец.
	 */
	ArrayIterator<T> end() noexcept;

	/**
	 *	\~english
	 *	\brief Creates an iterator pointing to the specified element
	 *	
	 *	Creates an iterator that points to an element with the passed index.
	 *	\param index The index of an element that the iterator will points to.
	 *	\return The iterator pointing to the specified element.
	 *	\throw std::out_of_range The index is out of the array bounds.
	 *	
	 *	\~russian
	 *	\brief Создаёт итератор, указывающий на заданный элемент
	 *	
	 *	Создаёт итератор, который указывает на элемент с переданным индексом.
	 *	\param index Индекс элемента, на который будет указывать итератор.
	 *	\return Итератор, указывающий на заданный элемент.
	 *	\throw std::out_of_range Индекс выходит за границы массива.
	 */
	ArrayIterator<T> create_iterator(int index);

	/**
	 *	\~english
	 *	\brief Creates a constant iterator to the first element
	 *
	 *	Creates a constant iterator that points to the first element of the array. If the array is
	 *	empty the created iterator is end (`is_end` is true).
	 *	\return The constant iterator to the first element of the array.
	 *
	 *	\~russian
	 *	\brief Создаёт константный итератор на первый элемент
	 *
	 *	Создаёт константный итератор, который указывает на первый элемент массива. Если массив
	 *	пуст, созданный итератор будет указывать на конец (`is_end` истинно).
	 *	\return Итератор на первый элемент массива.
	 */
	ConstArrayIterator<T> begin() const noexcept;

	/**
	 *	\~english
	 *	\brief Creates a constant iterator to the last element
	 *
	 *	Creates a constant iterator that points to the last element of the array. If the array is
	 *	empty the created iterator is end (`is_end` is true).
	 *	\return The constant iterator to the last element of the array.
	 *
	 *	\~russian
	 *	\brief Создаёт константный итератор на последний элемент
	 *
	 *	Создаёт константный итератор, который указывает на последний элемент массива. Если массив
	 *	пуст, созданный итератор будет указывать на конец (`is_end` истинно).
	 *	\return Константный итератор на последний элемент массива.
	 */
	ConstArrayIterator<T> last() const noexcept;

	/**
	 *	\~english
	 *	\brief Creates a constant iterator pointing after the last element
	 *
	 *	Creates a constant iterator that points to a space after the last element of the array
	 *	(this iterator is end: `is_end` is true).
	 *	\return The constant end iterator.
	 *
	 *	\~russian
	 *	\brief Создаёт константный итератор, указывающий после последнего элемента
	 *
	 *	Создаёт константный итератор, который указывает на пространство после последнего элемента
	 *	массива (этот итератор указывает в конец: `is_end` истинно).
	 *	\return Константный итератор на конец.
	 */
	ConstArrayIterator<T> end() const noexcept;

	/**
	 *	\~english
	 *	\brief Creates a constant iterator pointing to the specified element
	 *
	 *	Creates a constant iterator that points to an element with the passed index.
	 *	\param index The index of an element that the iterator will points to.
	 *	\return The constnant iterator pointing to the specified element.
	 *	\throw std::out_of_range The index is out of the array bounds.
	 *
	 *	\~russian
	 *	\brief Создаёт константный итератор, указывающий на заданный элемент
	 *
	 *	Создаёт константный итератор, который указывает на элемент с переданным индексом.
	 *	\param index Индекс элемента, на который будет указывать итератор.
	 *	\return Константный итератор, указывающий на заданный элемент.
	 *	\throw std::out_of_range Индекс выходит за границы массива.
	 */
	ConstArrayIterator<T> create_iterator(int index) const;

	/**
	 *	\~english
	 *	\brief Converts `ArrayIterator` to `ConstArrayIterator`
	 *
	 *	Converts the passed array iterator to constant array iterator that points to the same
	 *	element of the same array.
	 *	\param iterator The array iterator that will be converted.
	 *	\return A result constant array iterator.
	 *
	 *	\~russian
	 *	\brief Конвертирует `ArrayIterator` в `ConstArrayIterator`
	 *
	 *	Конвертирует переданный итератор массива в константный итератор массива, указывающий на тот
	 *	же элемент того же массива.
	 *	\param iterator Итератор, который будет сконвертирован.
	 *	\return Полученный константный итератор.
	 */
	static ConstArrayIterator<T> iterator_to_const(const ArrayIterator<T>& iterator) noexcept;

			/* OPERATORS */

	/**
	 *	\~english
	 *	\brief The copy assignment operator
	 *	
	 *	Clears the array and inserts into it copies of elements of the passed array. Invalidates
	 *	all iterators.
	 *	\warning This operator must not be used if the array contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param array The array to assign.
	 *	\return A reference to itself.
	 *	
	 *	\~russian
	 *	\brief Оператор присваивания копированием
	 *	
	 *	Очищает массив и вставляет в него копии элементов переданного массива. Аннулирует все
	 *	итераторы.
	 *	\warning Этот оператор не должен быть использован, если массив содержит `unique_ptr`ы
	 *	(может быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param array Массив для присваивания.
	 *	\return Ссылка на себя.
	 */
	virtual Array<T>& operator=(const Array<T>& array);

	/**
	 *	\~english
	 *	\brief The move assignment operator
	 *
	 *	Clears the array and moves into it elements of the passed array. Invalidates all iterators.
	 *	\param array The array to move.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Оператор присваивания перемещением
	 *
	 *	Очищает массив и перемещает в него элементы переданного массива. Аннулирует все итераторы.
	 *	\param array Массив для перемещения.
	 *	\return Ссылка на себя.
	 */
	virtual Array<T>& operator=(Array<T>&& array);

	/**
	 *	\~english
	 *	\brief Checks whether two arrays are equal
	 *	
	 *	Two arrays are equal if all of their elements are equal and have the same order.
	 *	\param array The array to compare.
	 *	\return `true` if two arrays are equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, равны ли два массива
	 *
	 *	Два массива равны, если их элементы равны и находятся в одинаковом порядке.
	 *	\param array Массив для сравнения.
	 *	\return `true`, если два массива равны, иначе `false`.
	 */
	bool operator==(const Array<T>& array) const;

	/**
	 *	\~english
	 *	\brief Checks whether two arrays are not equal
	 *
	 *	Two arrays are equal if all of their elements are equal and have the same order.
	 *	\param array The array to compare.
	 *	\return `true` if two arrays are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, различаются ли два массива
	 *
	 *	Два массива равны, если их элементы равны и находятся в одинаковом порядке.
	 *	\param array Массив для сравнения.
	 *	\return `true`, если два массива не равны, иначе `false`.
	 */
	bool operator!=(const Array<T>& array) const;

	/**
	 *	\~english
	 *	\brief Returns the specifies element
	 *	
	 *	Allows to access an element with the specified index.
	 *	\param index The index of the element.
	 *	\return A reference to the desired element.
	 *	\throw std::out_of_range The index is out of the array bounds.
	 *
	 *	\~russian
	 *	\brief Возвращает заданный элемент
	 *
	 *	Позволяет получить доступ к элементу с заданным индексом.
	 *	\param index Индекс элемента.
	 *	\return Ссылка на требуемый элемент.
	 *	\throw std::out_of_range Индекс выходит за границы массива.
	 */
	T& operator[](int index);

	/**
	 *	\~english
	 *	\brief Returns the specifies element
	 *
	 *	Allows to read an element with the specified index.
	 *	\param index The index of the element.
	 *	\return A constant reference to the desired element.
	 *	\throw std::out_of_range The index is out of the array bounds.
	 *
	 *	\~russian
	 *	\brief Возвращает заданный элемент
	 *
	 *	Позволяет прочитать элемент с заданным индексом.
	 *	\param index Индекс элемента.
	 *	\return Константная ссылка на требуемый элемент.
	 *	\throw std::out_of_range Индекс выходит за границы массива.
	 */
	const T& operator[](int index) const;

private:
	int real_size_;
	int size_;
	std::unique_ptr<T[]> array_;

	bool add_to_end_(const T& element);
	bool add_to_end_(T&& element);
	void check_real_size_to_add_(int required_size);

	mutable std::list<ArrayIterator<T>*> iterators_;
	mutable std::list<ConstArrayIterator<T>*> const_iterators_;
	void register_iterator_(ArrayIterator<T>* iterator) noexcept;
	void unregister_iterator_(ArrayIterator<T>* iterator) noexcept;
	void register_iterator_(ConstArrayIterator<T>* iterator) const noexcept;
	void unregister_iterator_(ConstArrayIterator<T>* iterator) const noexcept;
	void clear_iterators_() const noexcept;

	static const int DEFAULT_REAL_SIZE_;
};


		/* DEFINITIONS */

#define FOR_ITERATORS_(i, arg) \
	for (auto i : iterators_) arg \
	for (auto i : const_iterators_) arg

		/* Array: public */

template<typename T>
Array<T>::Array() noexcept :
	real_size_(DEFAULT_REAL_SIZE_),
	size_(0),
	array_(new T[real_size_])
{}

template<typename T>
Array<T>::Array(const Array<T>& array) noexcept :
	real_size_(array.real_size_),
	size_(array.size_),
	array_(new T[real_size_])
{
	for (int i = 0; i < size_; i++)
	{
		assign_(array_[i], array.array_[i]);
	}
}

template<typename T>
Array<T>::Array(Array<T>&& array) noexcept :
	real_size_(array.real_size_),
	size_(array.size_),
	array_(std::move(array.array_))
{
	array.clear_iterators_();
}

template<typename T>
Array<T>::Array(int size) :
	real_size_(size),
	size_(size),
	array_(new T[size] { })
{}

template<typename T>
Array<T>::~Array() noexcept
{
	clear_iterators_();
}

template<typename T>
String Array<T>::to_string() const noexcept
{
	if (is_empty())
	{
		return L"{ }"_s;
	}
	else
	{
		String str = L"{ "_s;
		for (int i = 0; i < size_ - 1; i++)
		{
			str += util::to_string(array_[i]) + L", "_s;
		}
		return str + util::to_string(array_[size_ - 1]) + L" }"_s;
	}
}

template<typename T>
int Array<T>::hash_code() const noexcept
{
	int hash = 0;
	for (int i = 0; i < size_; i += 2)
	{
		hash += util::hash_code(array_[i]);
	}
	for (int i = 1; i < size_; i += 2)
	{
		hash -= util::hash_code(array_[i]);
	}
	return hash;
}

template<typename T>
int Array<T>::size() const noexcept
{
	return size_;
}

template<typename T>
bool Array<T>::is_empty() const noexcept
{
	return size_ == 0;
}

template<typename T>
void Array<T>::clear() noexcept
{
	real_size_ = DEFAULT_REAL_SIZE_;
	size_ = 0;
	array_.reset(new T[real_size_]);

	FOR_ITERATORS_(i,
	{
		i->index_ = 0;
	})
}

template<typename T>
bool Array<T>::resize(int new_size) noexcept
{
	if (new_size > 0)
	{
		if (new_size <= size_)
		{
			size_ = new_size;

			FOR_ITERATORS_(i,
			{
				if (i->index_ > new_size)
				{
					i->index_ = new_size;
				}
			})
		}
		else
		{
			int to_reset = math::min(new_size, real_size_);
			for (int i = size_; i < to_reset; i++)
			{
				array_[i] = T();
			}
			check_real_size_to_add_(new_size);

			FOR_ITERATORS_(i,
			{
				if (i->index_ >= size_)
				{
					i->index_ = new_size;
				}
			})

			size_ = new_size;
		}
		return true;
	}
	else if (new_size == 0)
	{
		clear();
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
bool Array<T>::add(const T& element)
{
	check_real_size_to_add_(size_ + 1);
	assign_(array_[size_], element);

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
bool Array<T>::add(T&& element)
{
	check_real_size_to_add_(size_ + 1);
	array_[size_] = std::move(element);

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
bool Array<T>::add(const T& element, int index)
{
	if (index < 0 || index > size_)
	{
		return false;
	}
	else
	{
		if (index == size_)
		{
			return add_to_end_(element);
		}
		else
		{
			check_real_size_to_add_(size_ + 1);
			for (int i = size_++; i > index; i--)
			{
				array_[i] = std::move(array_[i - 1]);
			}

			FOR_ITERATORS_(i,
			{
				if (i->index_ >= index)
				{
					i->index_++;
				}
			})

			assign_(array_[index], element);
			return true;
		}
	}
}

template<typename T>
bool Array<T>::add(T&& element, int index)
{
	if (index < 0 || index > size_)
	{
		return false;
	}
	else
	{
		if (index == size_)
		{
			return add_to_end_(std::forward<T>(element));
		}
		else
		{
			check_real_size_to_add_(size_ + 1);
			for (int i = size_++; i > index; i--)
			{
				array_[i] = std::move(array_[i - 1]);
			}

			FOR_ITERATORS_(i,
			{
				if (i->index_ >= index)
				{
					i->index_++;
				}
			})

			array_[index] = std::move(element);
			return true;
		}
	}
}

template<typename T>
int Array<T>::add(const Array<T>& array)
{
	if (!array.is_empty())
	{
		check_real_size_to_add_(size_ + array.size_);
		int old_size = size_;
		for (int i = 0; i < array.size_; i++)
		{
			assign_(array_[size_++], array.array_[i]);
		}

		FOR_ITERATORS_(i,
		{
			if (i->index_ >= old_size)
			{
				i->index_ += array.size_;
			}
		})
	}
	return array.size_;
}

template<typename T>
int Array<T>::add(Array<T>&& array)
{
	if (!array.is_empty())
	{
		check_real_size_to_add_(size_ + array.size_);
		int old_size = size_;
		for (int i = 0; i < array.size_; i++)
		{
			array_[size_++] = std::move(array.array_[i]);
		}

		FOR_ITERATORS_(i,
		{
			if (i->index_ >= old_size)
			{
				i->index_ += array.size_;
			}
		})
	}
	return array.size_;
}

template<typename T>
bool Array<T>::remove(int index)
{
	return remove(index, index + 1) > 0;
}

template<typename T>
int Array<T>::remove(int from, int to)
{
	if (from < to && from >= 0 && to <= size_)
	{
		int delta = to - from;
		size_ -= delta;
		for (int i = from; i < size_; i++)
		{
			array_[i] = std::move(array_[i + delta]);
		}
		
		FOR_ITERATORS_(i,
		{
			if (i->index_ > from && i->index_ < to)
			{
				i->index_ = from;
			}
			else if (i->index_ >= to)
			{
				i->index_ -= delta;
			}
		})

		return delta;
	}
	else
	{
		return 0;
	}
}

template<typename T>
bool Array<T>::remove(const ArrayIterator<T>& element)
{
	return remove(iterator_to_const(element));
}

template<typename T>
bool Array<T>::remove(const ConstArrayIterator<T>& element)
{
	if (element.is_element_valid() && &element.get_container() == this)
	{
		return remove(element.get_index());
	}
	else
	{
		return false;
	}
}

template<typename T>
int Array<T>::remove(const ArrayIterator<T>& from, const ArrayIterator<T>& to)
{
	return remove(iterator_to_const(from), iterator_to_const(to));
}

template<typename T>
int Array<T>::remove(const ConstArrayIterator<T>& from, const ConstArrayIterator<T>& to)
{
	if (from.is_element_valid() && from.is_valid() && &from.get_container() == this && &to.get_container() == this)
	{
		return remove(from.get_index(), to.get_index());
	}
	else
	{
		return 0;
	}
}

template<typename T>
bool Array<T>::remove_any(const T& element)
{
	return remove(find_any(element));
}

template<typename T>
bool Array<T>::remove_first(const T& element)
{
	return remove(find_first(element));
}

template<typename T>
bool Array<T>::remove_last(const T& element)
{
	return remove(find_last(element));
}

template<typename T>
int Array<T>::remove_all(const T& element)
{
	for (int to = 0, from = -1; to < size_; to++)
	{
		do
		{
			if (++from >= size_)
			{
				size_ -= from - to;
				return from - to;
			}
		} while (array_[from] == element);
		if (from != to)
		{
			array_[to] = std::move(array_[from]);

			FOR_ITERATORS_(i,
			{
				if (i->index_ == from)
				{
					i->index_ = to;
				}
			})
		}
	}
	return 0;
}

template<typename T>
int Array<T>::find_any(const T& element) const
{
	return find_first(element);
}

template<typename T>
int Array<T>::find_first(const T& element) const
{
	for (int i = 0; i < size_; i++)
	{
		if (array_[i] == element)
		{
			return i;
		}
	}
	return -1;
}

template<typename T>
int Array<T>::find_last(const T& element) const
{
	for (int i = size_ - 1; i >= 0; i--)
	{
		if (array_[i] == element)
		{
			return i;
		}
	}
	return -1;
}

template<typename T>
bool Array<T>::contains(const T& element) const
{
	return find_first(element) >= 0;
}

template<typename T>
int Array<T>::count(const T& element) const
{
	int counter = 0;
	for (int i = 0; i < size_; i++)
	{
		if (array_[i] == element)
		{
			counter++;
		}
	}
	return counter;
}

template<typename T>
ArrayIterator<T> Array<T>::begin() noexcept
{
	return ArrayIterator<T>(*this, 0);
}

template<typename T>
ArrayIterator<T> Array<T>::last() noexcept
{
	return ArrayIterator<T>(*this, size_ - 1);
}

template<typename T>
ArrayIterator<T> Array<T>::end() noexcept
{
	return ArrayIterator<T>(*this, size_);
}

template<typename T>
ArrayIterator<T> Array<T>::create_iterator(int index)
{
	if (index >= 0 && index <= size_)
	{
		return ArrayIterator<T>(*this, index);
	}
	else
	{
		throw std::out_of_range("Index is out of array bounds");
	}
}

template<typename T>
ConstArrayIterator<T> Array<T>::begin() const noexcept
{
	return ConstArrayIterator<T>(*this, 0);
}

template<typename T>
ConstArrayIterator<T> Array<T>::last() const noexcept
{
	return ConstArrayIterator<T>(*this, size_ - 1);
}

template<typename T>
ConstArrayIterator<T> Array<T>::end() const noexcept
{
	return ConstArrayIterator<T>(*this, size_);
}

template<typename T>
ConstArrayIterator<T> Array<T>::create_iterator(int index) const
{
	if (index >= 0 && index <= size_)
	{
		return ConstArrayIterator<T>(*this, index);
	}
	else
	{
		throw std::out_of_range("Index is out of array bounds");
	}
}

template<typename T>
ConstArrayIterator<T> Array<T>::iterator_to_const(const ArrayIterator<T>& iterator) noexcept
{
	return ConstArrayIterator<T>(iterator.container_, iterator.index_, iterator.is_valid_);
}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& array)
{
	clear_iterators_();
	real_size_ = array.real_size_;
	size_ = array.size_;
	array_.reset(new T[real_size_]);
	for (int i = 0; i < size_; i++)
	{
		assign_(array_[i], array.array_[i]);
	}
	return *this;
}

template<typename T>
Array<T>& Array<T>::operator=(Array<T>&& array)
{
	clear_iterators_();
	real_size_ = array.real_size_;
	size_ = array.size_;
	array_ = std::move(array.array_);
	return *this;
}

template<typename T>
bool Array<T>::operator==(const Array<T>& array) const
{
	if (size_ == array.size_)
	{
		for (int i = 0; i < size_; i++)
		{
			if (!(array_[i] == array.array_[i]))
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
bool Array<T>::operator!=(const Array<T>& array) const
{
	return !(*this == array);
}

template<typename T>
T& Array<T>::operator[](int index)
{
	if (index >= 0 && index < size_)
	{
		return array_[index];
	}
	else
	{
		throw std::out_of_range("Index is out of array bounds");
	}
}

template<typename T>
const T& Array<T>::operator[](int index) const
{
	if (index >= 0 && index < size_)
	{
		return array_[index];
	}
	else
	{
		throw std::out_of_range("Index is out of array bounds");
	}
}

		/* Array: private */

template<typename T>
bool Array<T>::add_to_end_(const T& element)
{
	return Array<T>::add(element);
}

template<typename T>
bool Array<T>::add_to_end_(T&& element)
{
	return Array<T>::add(std::forward<T>(element));
}

template<typename T>
void Array<T>::check_real_size_to_add_(int required_size)
{
	if (required_size > real_size_)
	{
		int old_size = real_size_;
		if (old_size < 2)
		{
			real_size_ = DEFAULT_REAL_SIZE_;
		}
		else
		{
			real_size_ = math::max(static_cast<int>(real_size_ * 1.5f), required_size);
		}
		std::unique_ptr<T[]> new_ptr(new T[real_size_] { });
		for (int i = 0; i < old_size; i++)
		{
			new_ptr[i] = std::move(array_[i]);
		}
		array_ = std::move(new_ptr);
	}
}

template<typename T>
void Array<T>::register_iterator_(ArrayIterator<T>* iterator) noexcept
{
	iterators_.push_back(iterator);
}

template<typename T>
void Array<T>::unregister_iterator_(ArrayIterator<T>* iterator) noexcept
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
void Array<T>::register_iterator_(ConstArrayIterator<T>* iterator) const noexcept
{
	const_iterators_.push_back(iterator);
}

template<typename T>
void Array<T>::unregister_iterator_(ConstArrayIterator<T>* iterator) const noexcept
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
void Array<T>::clear_iterators_() const noexcept
{
	FOR_ITERATORS_(i,
	{
		i->is_valid_ = false;
	})
	iterators_.clear();
	const_iterators_.clear();
}

template<typename T>
const int Array<T>::DEFAULT_REAL_SIZE_ = 5;

#undef FOR_ITERATORS_

}
