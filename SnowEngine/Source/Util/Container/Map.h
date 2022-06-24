    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Map.h                       //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `Map` class
 *	
 *	This file contains the definition of the `Map` class.
 *	
 *	\~russian
 *	\brief Файл с классом `Map`
 *	
 *	Этот файл содержит определение класса `Map`.
 */

#include "MapIterator.h"
		// + Object
		// + IContainer

#include <list>

#include "Array.h"
#include "Pair.h"
#include "LinkedList.h"

namespace snow
{

/**
 *	\~english
 *	\brief The class of map
 *	
 *	This class is used as the map. Each element of the map is associated with a key and each key
 *	corresponds to a single element. Any element can be accessed using its key. A map provides a
 *	fast access to an arbitrary element, fast inserting and removing. When you initialise a map,
 *	you can specify its internal size. The more elements there are, the slower operations with the
 *	map works. For maximum speed, it is recommended that the number of elements doesn't exceed
 *	half of the internal size or two-thirds as a last resort (though theoretically number of
 *	elements is not limited). To organise the elements, the map uses hash cods of their keys. If
 *	the key is not a pointer, it's important that its hash code is calculated fast.
 *	\warning If the map contains `unique_ptr`'s, methods that copy the map elements (for example,
 *	the copy constructor) must not be called (`std::logic_error` exception can be thrown).
 *	\tparam T_Key Type of the map keys. If you want the keys to be objects of some class, it is
 *	highly recommended to use pointers, but you cannot use `unique_ptr`'s as keys. If `T_key` is
 *	not a primitive type, `to_string` and `hash_code` methods must be defined for it (any
 *	`snow::Object` has them). If `T_Key` is not a pointer, it also must have a default constructor,
 *	an assignment operator (`=`) and an equality operator (`==`). The default and copy constructors
 *	are assumed not to throw any exceptions.
 *	\tparam T_Value Type of the map elements. If you need to store objects of some class in the
 *	map, it is highly recommended to store pointers to them. If `T_Value` is not a primitive type,
 *	`to_string` and `hash_code` methods must be defined for it (any `snow::Object` has them). If
 *	`T_Value` is not a pointer, it also must have a default constructor, an assignment operator
 *	(`=`) and an equality operator (`==`). The default and copy constructors are assumed not to
 *	throw any exceptions.
 *	
 *	\~russian
 *	Этот класс используется в качестве словаря. Каждый элемент словаря ассоциирован с ключом, а
 *	каждый ключ соответствует единственному элементу. К любому элементу можно получить доступ с
 *	помощью его ключа. Словарь обеспечивает быстрый доступ к произвольному элементу, быструю
 *	вставку и удаление. Когда вы инициализируете словарь, вы можете определить его внутренний
 *	размер. Чем больше элементов, тем медленнее работают операции со словарём. Для максимальной
 *	скорости рекомендуется, чтобы число элементов не превышало половины или, в крайнем случае,
 *	двух третей внутреннего размера (хотя теоретически ограничения на число элементов нет). Для
 *	упорядочивания элементов словарь использует хеш-коды их ключей. Если ключ не является
 *	указателем, важно, чтобы его хеш-код вычислялся быстро.
 *	\warning Если связный список содержит `unique_ptr`ы, то методы, копирующие элементы связного,
 *	списка (например, конструктор копирования) не должны вызываться (может быть выброшено
 *	исключение `std::logic_error`).
 *	\tparam T_Key Тип ключей словаря. Если вы хотите, чтобы ключи были объектами некоторого класса,
 *	настоятельно рекомендуется использовать указатели на них, но вы не можете использовать в
 *	качестве ключей `unique_ptr`ы. Если `T_Key` не примитивный тип, для него должны быть определены
 *	методы `to_string` и `hash_code` (у любого `snow::Object` они есть). Если `T_Key` не указатель,
 *	у него также должны быть определёны конструктор по умолчанию, оператор присваивания (`=`) и
 *	оператор равенства (`==`). Предполагается, что конструктор по умолчанию и конструктор
 *	копирования не выбрасывают никаких исключений.
 *	\tparam T_Value Тип элементов словаря. Если вам нужно хранить в словаре объекты некоторого
 *	класса, настоятельно рекомендуется хранить указатели на них. Если `T_Value` не примитивный тип,
 *	для него должны быть определены методы `to_string` и `hash_code` (у любого `snow::Object` они
 *	есть). Если `T_Value` не указатель, у него также должны быть определёны конструктор по
 *	умолчанию, оператор присваивания (`=`) и оператор равенства (`==`). Предполагается, что
 *	конструктор по умолчанию и конструктор копирования не выбрасывают никаких исключений.
 */
template<typename T_Key, typename T_Value>
class Map :
	public Object,
	public IContainer<T_Value>
{
	template<typename T_Container, typename T_Key, typename T_Value>
	friend class BaseMapIterator_;

public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The default constructor
	 *
	 *	Creates an empty map with default internal size (you can get it using `internal_size`
	 *	method).
	 *
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *
	 *	Создаёт пустой словарь с внутренним размером по умолчанию (вы можете получить его,
	 *	используя метод `internal_size`).
	 */
	Map() noexcept;

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *
	 *	Copies the map.
	 *	\warning This constructor must not be used if the map contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param map The map that will be copied.
	 *
	 *	\~russian
	 *	\brief Конструктор копирования
	 *
	 *	Копирует массив.
	 *	\warning Этот конструктор не должен быть использован, если словарь содержит `unique_ptr`ы
	 *	(может быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param map Словарь, который будет скопирован.
	 */
	Map(const Map<T_Key, T_Value>& map) noexcept;

	/**
	 *	\~english
	 *	\brief The move constructor
	 *
	 *	Moves elements to a new map from the passed one.
	 *	\param map The map whose elements will be moved.
	 *
	 *	\~russian
	 *	\brief Конструктор перемещения
	 *
	 *	Перемещает элементы в новый словарь из переданного.
	 *	\param map Словарь, чьи элементы будут перемещены.
	 */
	Map(Map<T_Key, T_Value>&& map) noexcept;

	/**
	 *	\~english
	 *	\brief Creates a map with the specified internal size
	 *
	 *	Creates a map with the specified internal size. It is recommended that the number of
	 *	elements doesn't exceed half of the internal size or two-thirds as a last resort.
	 *	\param size The internal size of the map.
	 *	
	 *	\~russian
	 *	\brief Создаёт словарь с заданным внутренним размером
	 *	
	 *	Создаёт словарь с заданным внутренним размером. Рекомендуется, чтобы число элементов не
	 *	превышало половины или, в крайнем случае, двух третей внутреннего размера.
	 *	\param size Размер словаря.
	 */
	Map(int size);

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
	virtual ~Map() noexcept;

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the map into a string
	 *
	 *	Creates a string representing the list of the map elements. `util::to_string` is used to
	 *	convert elements to string.
	 *	\return A result string in the format `{ [k: v], [k: v], ..., [k: v] }` (`k` is key, `v`
	 *	is value). `{ }` if the map is empty.
	 *
	 *	\~russian
	 *	\brief Конвертирует словарь в строку
	 *
	 *	Создаёт строку, представляющую из себя список элементов словаря. Для конвертации элементов
	 *	в строку используется `util::to_string`.
	 *	\return Итоговая строка в формате `{ [к: з], [к: з], ..., [к: з] }` (`к` — ключ, `з` —
	 *	значение). `{ }`, если словарь пуст.
	 */
	virtual String to_string() const noexcept override;

	/**
	 *	\~english
	 *	\brief Hash code of the map
	 *
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes. Hash code of an empty map is zero.
	 *	\return Hash code of the object.
	 *
	 *	\~russian
	 *	\brief Хеш-код словаря
	 *
	 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
	 *	также могут иметь одинаковые хеш-коды. Хеш-код пустого словаря — ноль.
	 *	\return Хеш-код объекта.
	 */
	virtual int hash_code() const noexcept override;

			/* METHODS FROM IContainer &
				METHODS */

	/**
	 *	\~english
	 *	\brief The size of the map
	 *
	 *	Allows to get the number of elements in the map. Do not confuse this method with
	 *	`internal_size`.
	 *	\return The number of elements in the map.
	 *
	 *	\~russian
	 *	\brief Размер словаря
	 *
	 *	Позволяет получить количество элеменов в словаре. Не путайте этот метод с `internal_size`.
	 *	\return Количество элеменов в словаре.
	 */
	virtual int size() const noexcept override;

	/**
	 *	\~english
	 *	\brief The internal size of the map
	 *
	 *	Allows to get the internal size of the map. It is recommended that the number of elements
	 *	doesn't exceed half of the internal size or two-thirds as a last resort.
	 *	\return The internal size of the map.
	 *
	 *	\~russian
	 *	\brief Внутренний размер словаря
	 *
	 *	Позволяет получить внутренний размер словаря. Рекомендуется, чтобы число элементов не
	 *	превышало половины или, в крайнем случае, двух третей внутреннего размера.
	 *	\return Размер словаря.
	 */
	int internal_size() const noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether the map is empty
	 *
	 *	Checks whether the map is empty.
	 *	\return `true` if the map does not contain any element, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, пуст ли словарь
	 *
	 *	Проверяет, пуст ли словарь.
	 *	\return `true`, если словарь не содержит никаких элементов, иначе `false`.
	 */
	virtual bool is_empty() const noexcept override;

	/**
	 *	\~english
	 *	\brief Clears the map
	 *
	 *	Removes all of the elements in the map and sets all of its iterators to the end.
	 *	
	 *	\~russian
	 *	\brief Очищает словарь
	 *
	 *	Удаляет все элементы словаря и устанавливает его итераторы в конец.
	 */
	virtual void clear() noexcept override;
	
	/**
	 *	\~english
	 *	\brief Changes the the internal size of the map
	 *
	 *	Changes the internal size without changing number of elements. After executing this method
	 *	all iterators will continue to point to their elements but the map traversal order will be
	 *	changed. This method completely restructurizes the whole map, that's why it can work very
	 *	slowly.
	 *	\param new_size The new internal size.
	 *	\return `true` if the map has been successfully resized, `false` otherwise (e. g. if the
	 *	new size is negative).
	 *	
	 *	\~russian
	 *	\brief Изменяет внутренний размер словаря
	 *	
	 *	Изменяет внутренний размер без изменения количества элементов. После выполнения этого
	 *	все итераторы продолжат указывать на свои элементы, но порядок обхода словаря изменится.
	 *	Этот метод полностью перестраивает весь словарь и поэтому может работать очень медленно.
	 *	\param new_size Новый внутренний размер.
	 *	\return `true`, если размер был успешно изменён, иначе `false` (например, если новый размер
	 *	отрицательный).
	 */
	bool resize(int new_size);

	/**
	 *	\~english
	 *	\brief Adds a new element
	 *	
	 *	Inserts a new element with the specified key. The iterators won't be changed, but the new
	 *	element can be added in the middle of their order.
	 *	\warning This method must not be used if the map contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param key The key of a new element.
	 *	\param value The element that will be added.
	 *	\param allow_override Determines what the method should do if the map already contains an
	 *	element with the passed key. If `true`, the element will be overridden; if `false`, the
	 *	element won't be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise (i. g. if
	 *	there is already an element with this key and override is not allowed).
	 *	
	 *	\~russian
	 *	\brief Добавляет новый элемент
	 *	
	 *	Вставляет новый элемент c указанным ключом. Итераторы не будут изменены, но новый элемент
	 *	может быть добавлен в середину их порядка обхода.
	 *	\warning Этот метод не должен быть использован, если словарь содержит `unique_ptr`ы (может
	 *	быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param key Ключ нового элемента.
	 *	\param value Элемент, который будет добавлен.
	 *	\param allow_override Определяет, что должен сделать метод, если словарь уже содержит
	 *	элемент с переданным ключом. Если `true`, элемент будет перезаписан; если `false`, элемент
	 *	не будет добавлен.
	 *	\return `true`, если элемент был успешно добавлен, иначе `false` (например, если уже есть
	 *	элемент с таким ключом и перезапись не разрешена).
	 */
	bool add(const T_Key& key, const T_Value& value, bool allow_override = false);

	/**
	 *	\~english
	 *	\brief Adds a new element
	 *
	 *	Inserts a new element with the specified key. The iterators won't be changed, but the new
	 *	element can be added in the middle of their order.
	 *	\param key The key of a new element.
	 *	\param value The element that will be added.
	 *	\param allow_override Determines what the method should do if the map already contains an
	 *	element with the passed key. If `true`, the element will be overridden; if `false`, the
	 *	element won't be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise (i. g. if
	 *	there is already an element with this key and override is not allowed).
	 *
	 *	\~russian
	 *	\brief Добавляет новый элемент
	 *
	 *	Вставляет новый элемент c указанным ключом. Итераторы не будут изменены, но новый элемент
	 *	может быть добавлен в середину их порядка обхода.
	 *	\param key Ключ нового элемента.
	 *	\param value Элемент, который будет добавлен.
	 *	\param allow_override Определяет, что должен сделать метод, если словарь уже содержит
	 *	элемент с переданным ключом. Если `true`, элемент будет перезаписан; если `false`, элемент
	 *	не будет добавлен.
	 *	\return `true`, если элемент был успешно добавлен, иначе `false` (например, если уже есть
	 *	элемент с таким ключом и перезапись не разрешена).
	 */
	bool add(const T_Key& key, T_Value&& value, bool allow_override = false);

	/**
	 *	\~english
	 *	\brief Adds a new pair
	 *	
	 *	Inserts a new element with the specified key. The iterators won't be changed, but the new
	 *	element can be added in the middle of their order.
	 *	\warning This method must not be used if the map contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param pair The pair that contains key and value that will be added.
	 *	\param allow_override Determines what the method should do if the map already contains an
	 *	element with the passed key. If `true`, the element will be overridden; if `false`, the
	 *	element won't be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise (i. g. if
	 *	there is already an element with this key and override is not allowed).
	 *	
	 *	\~russian
	 *	\brief Добавляет новую пару
	 *	
	 *	Вставляет новый элемент c указанным ключом. Итераторы не будут изменены, но новый элемент
	 *	может быть добавлен в середину их порядка обхода.
	 *	\warning Этот метод не должен быть использован, если словарь содержит `unique_ptr`ы (может
	 *	быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param pair Пара, содержащая ключ и элемент, который будет добавлен.
	 *	\param allow_override Определяет, что должен сделать метод, если словарь уже содержит
	 *	элемент с переданным ключом. Если `true`, элемент будет перезаписан; если `false`, элемент
	 *	не будет добавлен.
	 *	\return `true`, если элемент был успешно добавлен, иначе `false` (например, если уже есть
	 *	элемент с таким ключом и перезапись не разрешена).
	 */
	bool add(const Pair<T_Key, T_Value>& pair, bool allow_override = false);

	/**
	 *	\~english
	 *	\brief Adds a new pair
	 *
	 *	Inserts a new element with the specified key. The iterators won't be changed, but the new
	 *	element can be added in the middle of their order.
	 *	\param pair The pair that contains key and value that will be added.
	 *	\param allow_override Determines what the method should do if the map already contains an
	 *	element with the passed key. If `true`, the element will be overridden; if `false`, the
	 *	element won't be added.
	 *	\return `true` if the element has been successfully added, `false` otherwise (i. g. if
	 *	there is already an element with this key and override is not allowed).
	 *
	 *	\~russian
	 *	\brief Добавляет новую пару
	 *
	 *	Вставляет новый элемент c указанным ключом. Итераторы не будут изменены, но новый элемент
	 *	может быть добавлен в середину их порядка обхода.
	 *	\param pair Пара, содержащая ключ и элемент, который будет добавлен.
	 *	\param allow_override Определяет, что должен сделать метод, если словарь уже содержит
	 *	элемент с переданным ключом. Если `true`, элемент будет перезаписан; если `false`, элемент
	 *	не будет добавлен.
	 *	\return `true`, если элемент был успешно добавлен, иначе `false` (например, если уже есть
	 *	элемент с таким ключом и перезапись не разрешена).
	 */
	bool add(Pair<T_Key, T_Value>&& pair, bool allow_override = false);

	/**
	 *	\~english
	 *	\brief Adds into the map copies of elements of the passed map
	 *
	 *	Inserts into the map copies of elements of the passed map. The iterators won't be changed,
	 *	but the new elements can be added in the middle of their order.
	 *	\warning This method must not be used if the map contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param map The map whose elements will be added.
	 *	\param allow_override Determines what the method should do if in the passed map there is an
	 *	element with the key that is already contained in the map. If `true`, the element will be
	 *	overridden; if `false`, the element won't be added.
	 *	\return The number of elements that have been successfully added.
	 *
	 *	\~russian
	 *	\brief Добавляет в словарь копии элементов переданного словаря
	 *
	 *	Вставляет в словарь копии элементов переданного словаря. Итераторы не будут изменены, но
	 *	новые элементы могут быть добавлен в середину их порядка обхода.
	 *	\warning Этот метод не должен быть использован, если словарь содержит `unique_ptr`ы (может
	 *	быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param map Словарь, чьи элементы будут добавлены.
	 *	\param allow_override Определяет, что должен сделать метод, если в переданном словаре есть
	 *	элемент с ключом, который уже содержится в данном словаре. Если `true`, элемент будет
	 *	перезаписан; если `false`, элемент не будет добавлен.
	 *	\return Количество успешно добавленных элементов.
	 */
	int add(const Map<T_Key, T_Value>& map, bool allow_override = false);

	/**
	 *	\~english
	 *	\brief Adds into the map copies of elements of the passed map
	 *
	 *	Inserts into the map copies of elements of the passed map. The iterators won't be changed,
	 *	but the new elements can be added in the middle of their order.
	 *	\param map The map whose elements will be added.
	 *	\param allow_override Determines what the method should do if in the passed map there is an
	 *	element with the key that is already contained in the map. If `true`, the element will be
	 *	overridden; if `false`, the element won't be added.
	 *	\return The number of elements that have been successfully added.
	 *
	 *	\~russian
	 *	\brief Добавляет в словарь копии элементов переданного словаря
	 *
	 *	Вставляет в словарь копии элементов переданного словаря. Итераторы не будут изменены, но
	 *	новые элементы могут быть добавлен в середину их порядка обхода.
	 *	\param map Словарь, чьи элементы будут добавлены.
	 *	\param allow_override Определяет, что должен сделать метод, если в переданном словаре есть
	 *	элемент с ключом, который уже содержится в данном словаре. Если `true`, элемент будет
	 *	перезаписан; если `false`, элемент не будет добавлен.
	 *	\return Количество успешно добавленных элементов.
	 */
	int add(Map<T_Key, T_Value>&& map, bool allow_override = false);
	
	/**
	 *	\~english
	 *	\brief Removes an element with the specified key
	 *	
	 *	Removes an element that has the specified key. Iterators that pointed to the removed
	 *	element (including the passed one) will point to the next element after executing this
	 *	method.
	 *	\param key The key of the element that will be removed.
	 *	\return `true` if the element has been successfully removed, `false` otherwise (e. g. if
	 *	the map doesn't contain the element with the passed key).
	 *	
	 *	\~russian
	 *	\brief Удаляет элемент с заданным ключом
	 *	
	 *	Удаляет элемент, который имеет заданный ключ.
	 *	\param key Ключ элемента, который будет удалён.
	 *	\return `true`, если элемент был успешно удалён, иначе `false` (например, если словарь не
	 *	содержит элемента с переданным ключом).
	 */
	bool remove(const T_Key& key);

	/**
	 *	\~english
	 *	\brief Removes an element by iterator
	 *	
	 *	Removes an element that the passed iterator points to. Iterators that pointed to the
	 *	removed element (including the passed one) will point to the next element after executing
	 *	this method.
	 *	\param element The iterator pointing to the element that will be removed.
	 *	\return `true` if the element has been successfully removed, `false` otherwise (e. g. if
	 *	the iterator points to an element of other map).
	 *	
	 *	\~russian
	 *	\brief Удаляет элемент по итератору
	 *	
	 *	Удаляет элемент, на который указывает переданный итератор. Итераторы, указывавшие на
	 *	удалённый элемент (включая переданный), после выполнения метода будут указывать на
	 *	следующий.
	 *	\param element Итератор, указывающий на элемент, который будет удалён.
	 *	\return `true`, если элемент был успешно удалён, иначе `false` (например, если итератор
	 *	указывает на элемент другого словаря).
	 */
	bool remove(const MapIterator<T_Key, T_Value>& element);

	/**
	 *	\~english
	 *	\brief Removes an element by iterator
	 *
	 *	Removes an element that the passed iterator points to. Iterators that pointed to the
	 *	removed element (including the passed one) will point to the next element after executing
	 *	this method.
	 *	\param element The iterator pointing to the element that will be removed.
	 *	\return `true` if the element has been successfully removed, `false` otherwise (e. g. if
	 *	the iterator points to an element of other map).
	 *
	 *	\~russian
	 *	\brief Удаляет элемент по итератору
	 *
	 *	Удаляет элемент, на который указывает переданный итератор. Итераторы, указывавшие на
	 *	удалённый элемент (включая переданный), после выполнения метода будут указывать на
	 *	следующий.
	 *	\param element Итератор, указывающий на элемент, который будет удалён.
	 *	\return `true`, если элемент был успешно удалён, иначе `false` (например, если итератор
	 *	указывает на элемент другого словаря).
	 */
	bool remove(const ConstMapIterator<T_Key, T_Value>& element);

	/**
	 *	\~english
	 *	\brief Removes any element that is equal to the passed one
	 *
	 *	Compares elements of the map with the passed one and removes one of matches. Iterators that
	 *	pointed to the removed element will point to the next element after executing this method.
	 *	\param element The object to compare.
	 *	\return `true` if an element has been successfully removed, `false` otherwise (e. g. if the
	 *	map doesn't contain the passed object).
	 *	
	 *	\~russian
	 *	\brief Удаляет любой элемент, который равен переданному
	 *	
	 *	Сравнивает элементы словаря с переданным и удаляет одно из совпадений. Итераторы,
	 *	указывавшие на удалённый элемент, после выполнения метода будут указывать на следующий.
	 *	\param element Объект для сравнения.
	 *	\return `true`, если элемент был успешно удалён, иначе `false` (например, если словарь не
	 *	содержит переданный объект).
	 */
	bool remove_any(const T_Value& element);

	/**
	 *	\~english
	 *	\brief Removes all elements that are equal to the passed one
	 *	
	 *	Compares every element of the map with the passed one and removes all matches. Iterators
	 *	that pointed to one of the removed elements will point to the next element after executing
	 *	this method.
	 *	\param element The object to compare.
	 *	\return Number of elements that have been successfully removed.
	 *
	 *	\~russian
	 *	\brief Удаляет все элементы, равные переданному
	 *
	 *	Сравнивает каждый элемент словаря с переданным и удаляет все совпадения. Итераторы,
	 *	указывавшие на один из удалённых элементов, после выполнения метода будут указывать на
	 *	следующий.
	 *	\param element Объект для сравнения.
	 *	\return Количество успешно удалённых элементов.
	 */
	virtual int remove_all(const T_Value& element) override;

	/**
	 *	\~english
	 *	\brief Finds any element that is equal to the passed one
	 *
	 *	Compares elements of the map with the passed one. If a match is found, returns its key.
	 *	\warning If the match isn't found, this method still returns a default object. This can
	 *	lead to mistakes, so it's recommended to use another method overload with boolean parameter.
	 *	\param element The desired element.
	 *	\return A key of a first match. If no match has been found, creates an object using a
	 *	default constructor.
	 *
	 *	\~russian
	 *	\brief Находит любой элемент, который равен переданному
	 *
	 *	Сравнивает элементы словаря с переданным. Если совпадение найдено, возвращает его ключ.
	 *	\warning Если совпадение не найдено, этот метод всё равно возвращает объект по умолчанию.
	 *	Это может привести к ошибкам, поэтому рекомендуется использовать другую перегрузку метода,
	 *	имеющую булевый параметр.
	 *	\param element Искомый элемент.
	 *	\return Ключ совпадения. Если совпадения не было найдено, создаёт объект с использованием
	 *	конструктора по умолчанию.
	 */
	T_Key find(const T_Value& element) const;

	/**
	 *	\~english
	 *	\brief Finds any element that is equal to the passed one
	 *	
	 *	Compares elements of the map with the passed one. If a match is found, returns its key.
	 *	\param[in] element The desired element.
	 *	\param[out] out_success `true` if a match has been found, `false` otherwise.
	 *	\return A key of a first match. If no match has been found, creates an object using a
	 *	default constructor.
	 *	
	 *	\~russian
	 *	\brief Находит любой элемент, который равен переданному
	 *	
	 *	Сравнивает элементы словаря с переданным. Если совпадение найдено, возвращает его ключ.
	 *	\param[in] element Искомый элемент.
	 *	\param[out] out_success `true`, если совпадение найдено, иначе `false`.
	 *	\return Ключ совпадения. Если совпадения не было найдено, создаёт объект с использованием
	 *	конструктора по умолчанию.
	 */
	T_Key find(const T_Value& element, bool& out_success) const;
	
	/**
	 *	\~english
	 *	\brief Checks whether the map contains an element with the passed key
	 *
	 *	Checks whether the map has an element whose key is equal to the passed one.
	 *	\param key The desired key.
	 *	\return `true` if the map contains the element with the passed key, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, содержит ли словарь элемент с переданным ключом
	 *	
	 *	Проверяет, содержит ли словарь элемент, чей ключ равен переданному.
	 *	\param key Искомый ключ.
	 *	\return `true`, если словарь содержит элемент с переданным ключом, иначе `false`.
	 */
	bool contains_key(const T_Key& key) const;

	/**
	 *	\~english
	 *	\brief Checks whether the map contains the passed element
	 *
	 *	Checks whether the map has an element that is equal to the passed one.
	 *	\param element The desired element.
	 *	\return `true` if the map contains the passed element, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, содержит ли словарь переданный элемент
	 *
	 *	Проверяет, содержит ли словарь элемент, равный переданному.
	 *	\param element Искомый элемент.
	 *	\return `true`, если словарь содержит переданный элемент, иначе `false`.
	 */
	virtual bool contains(const T_Value& element) const override;

	/**
	 *	\~english
	 *	\brief How many elements of the map are equal to the passed one
	 *
	 *	Counts elements that are equal to the passed one.
	 *	\param element The desired element.
	 *	\return Number of matches.
	 *
	 *	\~russian
	 *	\brief Сколько элементов словаря равны переданному
	 *
	 *	Подсчитывает элементы, равные переданному.
	 *	\param element Требуемый элемент.
	 *	\return Количество совпадений.
	 */
	virtual int count(const T_Value& element) const override;
	
	/**
	 *	\~english
	 *	\brief All keys of the map
	 *	
	 *	Allows to get all keys contained in the map.
	 *	\return An array with all keys of the map.
	 *	
	 *	\~russian
	 *	\brief Все ключи словаря
	 *	
	 *	Позволяет получить все ключи, содержащиеся в словаре.
	 *	\return Массив со всеми ключами словаря.
	 */
	Array<T_Key> get_keys() const;

	/**
	 *	\~english
	 *	\brief All values of the map
	 *
	 *	Allows to get all elements contained in the map.
	 *	\return An array with all elements of the map.
	 *
	 *	\~russian
	 *	\brief Все значения словаря
	 *
	 *	Позволяет получить все элементы, содержащиеся в словаре.
	 *	\return Массив со всеми элементами словаря.
	 */
	Array<T_Value> get_values() const;

	/**
	 *	\~english
	 *	\brief All key-value pairs of the map
	 *	
	 *	Allows to get all key-value pairs contained in the map.
	 *	\return An array with all pairs of the map.
	 *	
	 *	\~russian
	 *	\brief Все пары ключ-значение словаря
	 *	
	 *	Позволяет получить все пары ключ-значение, содержащиеся в словаре.
	 *	\return Массив со всеми парами словаря.
	 */
	Array<Pair<T_Key, T_Value>> get_pairs() const;

	/**
	 *	\~english
	 *	\brief Creates an iterator to the first element
	 *	
	 *	Creates an iterator that points to the first element of the mar. If the map is empty, the
	 *	created iterator is end (`is_end` is true).
	 *	\return The iterator to the first element of the map.
	 *	
	 *	\~russian
	 *	\brief Создаёт итератор на первый элемент
	 *	
	 *	Создаёт итератор, который указывает на первый элемент словаря. Если словарь пуст, созданный
	 *	итератор будет указывать на конец (`is_end` истинно).
	 *	\return Итератор на первый элемент словаря.
	 */
	MapIterator<T_Key, T_Value> begin() noexcept;

	/**
	 *	\~english
	 *	\brief Creates an iterator to the last element
	 *
	 *	Creates an iterator that points to the last element of the map. If the map is empty, the
	 *	created iterator is end (`is_end` is true).
	 *	\return The iterator to the last element of the map.
	 *
	 *	\~russian
	 *	\brief Создаёт итератор на последний элемент
	 *
	 *	Создаёт итератор, который указывает на последний элемент словаря. Если словарь пуст,
	 *	созданный итератор будет указывать на конец (`is_end` истинно).
	 *	\return Итератор на последний элемент словаря.
	 */
	MapIterator<T_Key, T_Value> last() noexcept;

	/**
	 *	\~english
	 *	\brief Creates an iterator pointing after the last element
	 *
	 *	Creates an iterator that points to a space after the last element of the map (this iterator
	 *	is end: `is_end` is true).
	 *	\return The end iterator.
	 *
	 *	\~russian
	 *	\brief Создаёт итератор, указывающий после последнего элемента
	 *
	 *	Создаёт итератор, который указывает на пространство после последнего элемента словаря (этот
	 *	итератор указывает в конец: `is_end` истинно).
	 *	\return Итератор на конец.
	 */
	MapIterator<T_Key, T_Value> end() noexcept;

	/**
	 *	\~english
	 *	\brief Creates an iterator pointing to the specified element
	 *	
	 *	Creates an iterator that points to an element with the passed key.
	 *	\param key The key of an element that the iterator will points to.
	 *	\return The iterator pointing to the specified element.
	 *	\throw std::invalid_argument The map doesn't contain the passed key.
	 *	
	 *	\~russian
	 *	\brief Создаёт итератор, указывающий на заданный элемент
	 *	
	 *	Создаёт итератор, который указывает на элемент с переданным ключом.
	 *	\param key Ключ элемента, на который будет указывать итератор.
	 *	\return Итератор, указывающий на заданный элемент.
	 *	\throw std::invalid_argument Словарь не содержит переданного ключа.
	 */
	MapIterator<T_Key, T_Value> create_iterator(const T_Key& key);

	/**
	 *	\~english
	 *	\brief Creates a constant iterator to the first element
	 *
	 *	Creates a constant iterator that points to the first element of the mar. If the map is
	 *	empty, the created iterator is end (`is_end` is true).
	 *	\return The constant iterator to the first element of the map.
	 *
	 *	\~russian
	 *	\brief Создаёт константный итератор на первый элемент
	 *
	 *	Создаёт константный итератор, который указывает на первый элемент словаря. Если словарь
	 *	пуст, созданный итератор будет указывать на конец (`is_end` истинно).
	 *	\return Константный итератор на первый элемент словаря.
	 */
	ConstMapIterator<T_Key, T_Value> begin() const noexcept;

	/**
	 *	\~english
	 *	\brief Creates a constant iterator to the last element
	 *
	 *	Creates a constant iterator that points to the last element of the map. If the map is
	 *	empty, the created iterator is end (`is_end` is true).
	 *	\return The constant iterator to the last element of the map.
	 *
	 *	\~russian
	 *	\brief Создаёт константный итератор на последний элемент
	 *
	 *	Создаёт константный итератор, который указывает на последний элемент словаря. Если словарь
	 *	пуст, созданный итератор будет указывать на конец (`is_end` истинно).
	 *	\return Константный итератор на последний элемент словаря.
	 */
	ConstMapIterator<T_Key, T_Value> last() const noexcept;

	/**
	 *	\~english
	 *	\brief Creates a constant iterator pointing after the last element
	 *
	 *	Creates a constant iterator that points to a space after the last element of the map (this
	 *	iterator is end: `is_end` is true).
	 *	\return The constant end iterator.
	 *
	 *	\~russian
	 *	\brief Создаёт константный итератор, указывающий после последнего элемента
	 *
	 *	Создаёт константный итератор, который указывает на пространство после последнего элемента
	 *	словаря (этот итератор указывает в конец: `is_end` истинно).
	 *	\return Константный итератор на конец.
	 */
	ConstMapIterator<T_Key, T_Value> end() const noexcept;

	/**
	 *	\~english
	 *	\brief Creates a constant iterator pointing to the specified element
	 *
	 *	Creates a constant iterator that points to an element with the passed key.
	 *	\param key The key of an element that the iterator will points to.
	 *	\return The constant iterator pointing to the specified element.
	 *	\throw std::invalid_argument The map doesn't contain the passed key.
	 *
	 *	\~russian
	 *	\brief Создаёт константный итератор, указывающий на заданный элемент
	 *
	 *	Создаёт константный итератор, который указывает на элемент с переданным ключом.
	 *	\param key Ключ элемента, на который будет указывать итератор.
	 *	\return Константный итератор, указывающий на заданный элемент.
	 *	\throw std::invalid_argument Словарь не содержит переданного ключа.
	 */
	ConstMapIterator<T_Key, T_Value> create_iterator(const T_Key& key) const;

	/**
	 *	\~english
	 *	\brief Converts `MapIterator` to `ConstMapIterator`
	 *
	 *	Converts the passed map iterator to constant map iterator that points to the same element
	 *	of the same map.
	 *	\param iterator The map iterator that will be converted.
	 *	\return A result constant map iterator.
	 *
	 *	\~russian
	 *	\brief Конвертирует `MapIterator` в `ConstMapIterator`
	 *
	 *	Конвертирует переданный итератор словаря в константный итератор словаря, указывающий на тот
	 *	же элемент того же словаря.
	 *	\param iterator Итератор, который будет сконвертирован.
	 *	\return Полученный константный итератор.
	 */
	static ConstMapIterator<T_Key, T_Value> iterator_to_const(const MapIterator<T_Key, T_Value>& iterator) noexcept;

			/* OPERATORS */

	/**
	 *	\~english
	 *	\brief The copy assignment operator
	 *	
	 *	Clears the map and inserts into it copies of elements of the passed map. Invalidates all
	 *	iterators.
	 *	\warning This operator must not be used if the map contains `unique_ptr`'s
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param map The map to assign.
	 *	\return A reference to itself.
	 *	
	 *	\~russian
	 *	\brief Оператор присваивания копированием
	 *	
	 *	Очищает словарь и вставляет в него копии элементов переданного словаря. Аннулирует все
	 *	итераторы.
	 *	\warning Этот оператор не должен быть использован, если словарь содержит `unique_ptr`ы
	 *	(может быть выброшено исключение `std::logic_error`). Вместо этого используйте семантику
	 *	перемещения.
	 *	\param map Словарь для присваивания.
	 *	\return Ссылка на себя.
	 */
	Map<T_Key, T_Value>& operator=(const Map<T_Key, T_Value>& map);

	/**
	 *	\~english
	 *	\brief The move assignment operator
	 *
	 *	Clears the map and moves into it elements of the passed map. Invalidates all iterators.
	 *	\param map The map to move.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Оператор присваивания перемещением
	 *
	 *	Очищает словарь и перемещает в него элементы переданного словаря. Аннулирует все итераторы.
	 *	\param map Словарь для перемещения.
	 *	\return Ссылка на себя.
	 */
	Map<T_Key, T_Value>& operator=(Map<T_Key, T_Value>&& map);

	/**
	 *	\~english
	 *	\brief Checks whether two maps are equal
	 *	
	 *	Two maps are equal if all of their elements and keys are equal.
	 *	\param map The map to compare.
	 *	\return `true` if two maps are equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, равны ли два словаря
	 *
	 *	Два словаря равны, если равны их элементы и ключи.
	 *	\param map Словарь для сравнения.
	 *	\return `true`, если два словаря равны, иначе `false`.
	 */
	bool operator==(const Map<T_Key, T_Value>& map) const;

	/**
	 *	\~english
	 *	\brief Checks whether two maps are not equal
	 *
	 *	Two maps are equal if all of their elements and keys are equal.
	 *	\param map The map to compare.
	 *	\return `true` if two maps are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, различаются ли два словаря
	 *
	 *	Два словаря равны, если равны их элементы и ключи.
	 *	\param map Словарь для сравнения.
	 *	\return `true`, если два словаря не равны, иначе `false`.
	 */
	bool operator!=(const Map<T_Key, T_Value>& map) const;

	/**
	 *	\~english
	 *	\brief Returns the specifies element
	 *	
	 *	Allows to access an element with the specified key.
	 *	\param key The key of the element.
	 *	\return A reference to the desired element.
	 *	\throw std::invalid_argument The map doesn't contain the passed key.
	 *
	 *	\~russian
	 *	\brief Возвращает заданный элемент
	 *
	 *	Позволяет получить доступ к элементу с заданным ключом.
	 *	\param key Ключ элемента.
	 *	\return Ссылка на требуемый элемент.
	 *	\throw std::invalid_argument Словарь не содержит переданного ключа.
	 */
	T_Value& operator[](const T_Key& key);

	/**
	 *	\~english
	 *	\brief Returns the specifies element
	 *
	 *	Allows to read an element with the specified key.
	 *	\param key The key of the element.
	 *	\return A constant reference to the desired element.
	 *	\throw std::invalid_argument The map doesn't contain the passed key.
	 *
	 *	\~russian
	 *	\brief Возвращает заданный элемент
	 *
	 *	Позволяет прочитать элемент с заданным ключом.
	 *	\param key Ключ элемента.
	 *	\return Константная ссылка на требуемый элемент.
	 *	\throw std::invalid_argument Словарь не содержит переданного ключа.
	 */
	const T_Value& operator[](const T_Key& key) const;

private:
	Array<LinkedList<Pair<T_Key, T_Value>>> map_;
	int size_;
	int internal_size_;
	
	int first_filled_;
	int last_filled_;

	mutable std::list<MapIterator<T_Key, T_Value>*> iterators_;
	mutable std::list<ConstMapIterator<T_Key, T_Value>*> const_iterators_;
	void register_iterator_(MapIterator<T_Key, T_Value>* iterator) noexcept;
	void unregister_iterator_(MapIterator<T_Key, T_Value>* iterator) noexcept;
	void register_iterator_(ConstMapIterator<T_Key, T_Value>* iterator) const noexcept;
	void unregister_iterator_(ConstMapIterator<T_Key, T_Value>* iterator) const noexcept;
	void clear_iterators_() const noexcept;

	static const int DEFAULT_SIZE_;
};


		/* DEFINITIONS */

#define FOR_ITERATORS_(i, arg) \
	for (auto i : iterators_) arg \
	for (auto i : const_iterators_) arg

		/* Map: public */

template<typename T_Key, typename T_Value>
Map<T_Key, T_Value>::Map() noexcept :
	map_(DEFAULT_SIZE_),
	size_(0),
	internal_size_(DEFAULT_SIZE_),
	first_filled_(-1),
	last_filled_(-1)
{}

template<typename T_Key, typename T_Value>
Map<T_Key, T_Value>::Map(const Map<T_Key, T_Value>& map) noexcept :
	map_(map.map_),
	size_(map.size_),
	internal_size_(map.internal_size_),
	first_filled_(map.first_filled_),
	last_filled_(map.last_filled_)
{}

template<typename T_Key, typename T_Value>
Map<T_Key, T_Value>::Map(Map<T_Key, T_Value>&& map) noexcept :
	map_(std::move(map.map_)),
	size_(map.size_),
	internal_size_(map.internal_size_),
	first_filled_(map.first_filled_),
	last_filled_(map.last_filled_)
{}

template<typename T_Key, typename T_Value>
Map<T_Key, T_Value>::Map(int size) :
	map_(size),
	size_(0),
	internal_size_(size),
	first_filled_(-1),
	last_filled_(-1)
{}

template<typename T_Key, typename T_Value>
Map<T_Key, T_Value>::~Map() noexcept
{
	clear_iterators_();
}

template<typename T_Key, typename T_Value>
String Map<T_Key, T_Value>::to_string() const noexcept
{
	if (size_ <= 0)
	{
		return L"{ }"_s;
	}
	else
	{
		String ret = L"{ "_s;
		for (const auto& i : map_)
		{
			for (const auto& j : i)
			{
				ret += j.to_string() + L", "_s;
			}
		}
		ret[ret.size() - 2] = L' ';
		ret[ret.size() - 1] = L'}';
		return ret;
	}
}
			

template<typename T_Key, typename T_Value>
int Map<T_Key, T_Value>::hash_code() const noexcept
{
	int ret = 0;
	for (const auto& i : map_)
	{
		for (const auto& j : i)
		{
			ret += j.hash_code();
		}
	}
	return ret;
}

template<typename T_Key, typename T_Value>
int Map<T_Key, T_Value>::size() const noexcept
{
	return size_;
}

template<typename T_Key, typename T_Value>
int Map<T_Key, T_Value>::internal_size() const noexcept
{
	return internal_size_;
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::is_empty() const noexcept
{
	return size_ == 0;
}

template<typename T_Key, typename T_Value>
void Map<T_Key, T_Value>::clear() noexcept
{
	map_.clear();
	map_.resize(internal_size_);
	size_ = 0;

	FOR_ITERATORS_(i,
	{
		i->is_end_ = true;
	})
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::resize(int new_size)
{
	if (internal_size_ != new_size)
	{
		if (internal_size > 0)
		{
			Array<Pair<T_Key, T_Value>> pairs(size_);
			for (auto& i : map_)
			{
				for (auto& j : i)
				{
					pairs.add(std::move(j));
				}
			}
			internal_size_ = new_size;
			map_.clear();
			map_.resize(new_size);
			for (const auto& i : pairs)
			{
				add(std::move(i));
			}
			return true;
		}
		else
		{
			return false;
		}
	}
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::add(const T_Key& key, const T_Value& value, bool allow_override)
{
	return add(Pair<T_Key, T_Value>(key, value), allow_override);
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::add(const T_Key& key, T_Value&& value, bool allow_override)
{
	return add(Pair<T_Key, T_Value>(key, std::forward<T_Value>(value)), allow_override);
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::add(const Pair<T_Key, T_Value>& pair, bool allow_override)
{
	int hash = math::abs(util::hash_code(pair.get_first()) % internal_size_);
	auto& list = map_[hash];
	for (auto& i : list)
	{
		if (i.get_first() == pair.get_first())
		{
			if (allow_override)
			{
				i = pair;
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	if (size_ == 0 || list.is_empty() && hash < first_filled_)
	{
		first_filled_ = hash;
	}
	if (size_ == 0 || list.is_empty() && hash > last_filled_)
	{
		last_filled_ = hash;
	}
	list.add(pair);
	size_++;
	return true;
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::add(Pair<T_Key, T_Value>&& pair, bool allow_override)
{
	int hash = math::abs(util::hash_code(pair.get_first()) % internal_size_);
	auto& list = map_[hash];
	for (auto& i : list)
	{
		if (i.get_first() == pair.get_first())
		{
			if (allow_override)
			{
				i = std::forward<Pair<T_Key, T_Value>>(pair);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	if (size_ == 0 || list.is_empty() && hash < first_filled_)
	{
		first_filled_ = hash;
	}
	if (size_ == 0 || list.is_empty() && hash > last_filled_)
	{
		last_filled_ = hash;
	}
	list.add(std::forward<Pair<T_Key, T_Value>>(pair));
	size_++;
	return true;
}

template<typename T_Key, typename T_Value>
int Map<T_Key, T_Value>::add(const Map<T_Key, T_Value>& map, bool allow_override)
{
	int ret = 0;
	Array<Pair<T_Key, T_Value>> pairs = map.get_pairs();
	for (auto& i : pairs)
	{
		ret += static_cast<int>(add(std::move(i), allow_override));
	}
	return ret;
}

template<typename T_Key, typename T_Value>
int Map<T_Key, T_Value>::add(Map<T_Key, T_Value>&& map, bool allow_override)
{
	int ret = 0;
	Array<Pair<T_Key, T_Value>> pairs(map.size_);
	for (auto& i : map.map_)
	{
		for (auto& j : i)
		{
			pairs.add(std::move(j));
		}
	}
	for (auto& i : pairs)
	{
		ret += static_cast<int>(add(std::move(i), allow_override));
	}
	return ret;
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::remove(const T_Key& key)
{
	int hash = math::abs(util::hash_code(key) % internal_size_);
	auto& list = map_[hash];
	for (auto i = list.begin(); !i.is_end(); i.next())
	{
		if (i->get_first() == key)
		{
			FOR_ITERATORS_(j,
			{
				if (j->get_key() == key)
				{
					j->next();
				}
			})
			list.remove(i);
			size_--;
			if (size_ == 0)
			{
				first_filled_ = -1;
				last_filled_ = -1;
			}
			else
			{
				if (list.is_empty() && first_filled_ == hash)
				{
					int index = hash;
					while (map_[++index].is_empty());
					first_filled_ = index;
				}
				if (list.is_empty() && last_filled_ == hash)
				{
					int index = hash;
					while (map_[--index].is_empty());
					last_filled_ = index;
				}
			}
			return true;
		}
	}
	return false;
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::remove(const MapIterator<T_Key, T_Value>& element)
{
	return remove(iterator_to_const(element));
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::remove(const ConstMapIterator<T_Key, T_Value>& element)
{
	return remove(element.get_key());
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::remove_any(const T_Value& element)
{
	for (auto i = begin(); !i.is_end(); i.next())
	{
		if (i.get() == element)
		{
			return remove(i.get_key());
		}
	}
	return false;
}

template<typename T_Key, typename T_Value>
int Map<T_Key, T_Value>::remove_all(const T_Value& element)
{
	int ret = 0;
	while (size_ > 0 && begin().get() == element)
	{
		ret += static_cast<int>(remove(begin()));
	}
	auto i = begin();
	while(i.next())
	{
		if (i.get() == element)
		{
			ret += static_cast<int>(remove(i--));
		}
	}
	return ret;
}

template<typename T_Key, typename T_Value>
T_Key Map<T_Key, T_Value>::find(const T_Value& element) const
{
	bool success;
	return find(element, success);
}

template<typename T_Key, typename T_Value>
T_Key Map<T_Key, T_Value>::find(const T_Value& element, bool& out_success) const
{
	for (auto i = begin(); !i.is_end(); i.next())
	{
		if (i.get() == element)
		{
			out_success = true;
			return i.get_key();
		}
	}
	out_success = false;
	return T_Key();
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::contains_key(const T_Key& key) const
{
	for (auto i = begin(); !i.is_end(); i.next())
	{
		if (i.get_key() == key)
		{
			return true;
		}
	}
	return false;
}	

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::contains(const T_Value& element) const
{
	for (auto i = begin(); !i.is_end(); i.next())
	{
		if (i.get() == element)
		{
			return true;
		}
	}
	return false;
}	

template<typename T_Key, typename T_Value>
int Map<T_Key, T_Value>::count(const T_Value& element) const
{
	int ret = 0;
	for (auto i = begin(); !i.is_end(); i.next())
	{
		if (i.get() == element)
		{
			ret++;
		}
	}
	return ret;
}

template<typename T_Key, typename T_Value>
Array<T_Key> Map<T_Key, T_Value>::get_keys() const
{
	Array<T_Key> ret(size_);
	int index = 0;
	for (auto i = begin(); !i.is_end(); i.next())
	{
		ret[index++] = i.get_key();
	}
	return ret;
}

template<typename T_Key, typename T_Value>
Array<T_Value> Map<T_Key, T_Value>::get_values() const
{
	Array<T_Value> ret(size_);
	int index = 0;
	for (const auto& i : *this)
	{
		ret[index++] = i;
	}
	return ret;
}

template<typename T_Key, typename T_Value>
Array<Pair<T_Key, T_Value>> Map<T_Key, T_Value>::get_pairs() const
{
	Array<Pair<T_Key, T_Value>> ret(size_);
	int index = 0;
	for (auto& i : map_)
	{
		for (auto j = i.begin(); !j.is_end(); j.next())
		{
			ret[index++] = j.get();
		}
	}
	return ret;
}

template<typename T_Key, typename T_Value>
MapIterator<T_Key, T_Value> Map<T_Key, T_Value>::begin() noexcept
{
	if (size_ > 0)
	{
		return MapIterator<T_Key, T_Value>(*this, map_[first_filled_].get_begin().get_first(), false);
	}
	else
	{
		return MapIterator<T_Key, T_Value>(*this, T_Key(), true);
	}
}

template<typename T_Key, typename T_Value>
MapIterator<T_Key, T_Value> Map<T_Key, T_Value>::last() noexcept
{
	if (size_ > 0)
	{
		return MapIterator<T_Key, T_Value>(*this, map_[last_filled_].get_last().get_first(), false);
	}
	else
	{
		return MapIterator<T_Key, T_Value>(*this, T_Key(), true);
	}
}

template<typename T_Key, typename T_Value>
MapIterator<T_Key, T_Value> Map<T_Key, T_Value>::end() noexcept
{
	return MapIterator<T_Key, T_Value>(*this, T_Key(), true);
}

template<typename T_Key, typename T_Value>
MapIterator<T_Key, T_Value> Map<T_Key, T_Value>::create_iterator(const T_Key& key)
{
	if (contains_key(key))
	{
		return MapIterator<T_Key, T_Value>(*this, key, false);
	}
	else
	{
		throw std::invalid_argument("A map doesn't contain the passed key");
	}
}

template<typename T_Key, typename T_Value>
ConstMapIterator<T_Key, T_Value> Map<T_Key, T_Value>::begin() const noexcept
{
	if (size_ > 0)
	{
		return ConstMapIterator<T_Key, T_Value>(*this, map_[first_filled_].get_begin().get_first(), false);
	}
	else
	{
		return ConstMapIterator<T_Key, T_Value>(*this, T_Key(), true);
	}
}

template<typename T_Key, typename T_Value>
ConstMapIterator<T_Key, T_Value> Map<T_Key, T_Value>::last() const noexcept
{
	if (size_ > 0)
	{
		return ConstMapIterator<T_Key, T_Value>(*this, map_[last_filled_].get_last().get_first(), false);
	}
	else
	{
		return ConstMapIterator<T_Key, T_Value>(*this, T_Key(), true);
	}
}

template<typename T_Key, typename T_Value>
ConstMapIterator<T_Key, T_Value> Map<T_Key, T_Value>::end() const noexcept
{
	return ConstMapIterator<T_Key, T_Value>(*this, T_Key(), true);
}


template<typename T_Key, typename T_Value>
ConstMapIterator<T_Key, T_Value> Map<T_Key, T_Value>::create_iterator(const T_Key& key) const
{
	if (contains_key(key))
	{
		return ConstMapIterator<T_Key, T_Value>(*this, key, false);
	}
	else
	{
		throw std::invalid_argument("A map doesn't contain the passed key");
	}
}

template<typename T_Key, typename T_Value>
ConstMapIterator<T_Key, T_Value> Map<T_Key, T_Value>::iterator_to_const(const MapIterator<T_Key, T_Value>& iterator) noexcept
{
	return ConstMapIterator<T_Key, T_Value>(iterator.container_, iterator.key_, iterator.is_end_, iterator.is_valid_);
}

template<typename T_Key, typename T_Value>
Map<T_Key, T_Value>& Map<T_Key, T_Value>::operator=(const Map<T_Key, T_Value>& map)
{
	clear_iterators_();
	map_ = map.map_;
	size_ = map.size_;
	internal_size_ = map.internal_size_;
	first_filled_ = map.first_filled_;
	last_filled_ = map.last_filled_;
}

template<typename T_Key, typename T_Value>
Map<T_Key, T_Value>& Map<T_Key, T_Value>::operator=(Map<T_Key, T_Value>&& map)
{
	clear_iterators_();
	map_ = std::move(map.map_);
	size_ = map.size_;
	internal_size_ = map.internal_size_;
	first_filled_ = map.first_filled_;
	last_filled_ = map.last_filled_;
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::operator==(const Map<T_Key, T_Value>& map) const
{
	if (size_ == map.size_)
	{
		Map<T_Key, T_Value> copy = map;
		copy.resize(internal_size_);
		return get_pairs() == copy.get_pairs();
	}
	else
	{
		return false;
	}
}

template<typename T_Key, typename T_Value>
bool Map<T_Key, T_Value>::operator!=(const Map<T_Key, T_Value>& map) const
{
	return !(*this == map);
}

template<typename T_Key, typename T_Value>
T_Value& Map<T_Key, T_Value>::operator[](const T_Key& key)
{
	int hash = math::abs(util::hash_code(key) % internal_size_);
	auto& list = map_[hash];
	for (auto i = list.begin(); !i.is_end(); i.next())
	{
		if (i->get_first() == key)
		{
			return i->get_second();
		}
	}
	throw std::invalid_argument("A map doesn't contain the passed key");
}

template<typename T_Key, typename T_Value>
const T_Value& Map<T_Key, T_Value>::operator[](const T_Key& key) const
{
	int hash = math::abs(util::hash_code(key) % internal_size_);
	auto& list = map_[hash];
	for (auto i = list.begin(); !i.is_end(); i.next())
	{
		if (i->get_first() == key)
		{
			return i->get_second();
		}
	}
	throw std::invalid_argument("A map doesn't contain the passed key");
}
		
		/* Map: private */

template<typename T_Key, typename T_Value>
void Map<T_Key, T_Value>::register_iterator_(MapIterator<T_Key, T_Value>* iterator) noexcept
{
	iterators_.push_back(iterator);
}

template<typename T_Key, typename T_Value>
void Map<T_Key, T_Value>::unregister_iterator_(MapIterator<T_Key, T_Value>* iterator) noexcept
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

template<typename T_Key, typename T_Value>
void Map<T_Key, T_Value>::register_iterator_(ConstMapIterator<T_Key, T_Value>* iterator) const noexcept
{
	const_iterators_.push_back(iterator);
}

template<typename T_Key, typename T_Value>
void Map<T_Key, T_Value>::unregister_iterator_(ConstMapIterator<T_Key, T_Value>* iterator) const noexcept
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

template<typename T_Key, typename T_Value>
void Map<T_Key, T_Value>::clear_iterators_() const noexcept
{
	FOR_ITERATORS_(i,
	{
		i->is_valid_ = false;
	})
	iterators_.clear();
	const_iterators_.clear();
}

template<typename T_Key, typename T_Value>
const int Map<T_Key, T_Value>::DEFAULT_SIZE_ = 51;

#undef FOR_ITERATORS_

}
