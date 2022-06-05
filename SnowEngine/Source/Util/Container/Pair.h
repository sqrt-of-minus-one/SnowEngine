    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Pair.h                      //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with `Pair` class
 *	
 *	This file contains the definition of the `Pair` class.
 *	
 *	\~russian
 *	\brief Файл с классом `Pair`
 *	
 *	Этот файл содержит определение класса `Pair`.
 */

#include "../../Object.h"

#include "../Util.h"

namespace snow
{

namespace
{

// Do not use this struct directly
template<typename T>
struct Wrap_
{
public:
	Wrap_(const T& v) noexcept;
	Wrap_(T&& v) noexcept;

	T var;
};

template<typename T>
struct Wrap_<std::unique_ptr<T>>
{
public:
	Wrap_(const std::unique_ptr<T>& v) noexcept;
	Wrap_(std::unique_ptr<T>&& v) noexcept;

	std::unique_ptr<T> var;
};

}

/**
 *	\~english
 *	\brief The container to keep two objects
 *	
 *	An object of the `Pair` class can keep two variables. If you need to store objects of some
 *	class, it is highly recommended to store pointers to them. If the type is not primitive,
 *	`to_string` and `hash_code` methods must be defined for it (any `snow::Object` has them). If
 *	the type is not a pointer, it also must have a default constructor, an assignment operator
 *	(`=`) and an equality operator (`==`). The default and copy constructors are assumed not to
 *	throw any exceptions.
 *	\warning If one of the pair variables is `unique_ptr`, methods that copy it (for example, the
 *	copy constructor) must not be called (`std::logic_error` exception can be thrown).
 *	\tparam T_First Type of the first variable in the pair.
 *	\tparam T_Second Type of the second variable in the pair.
 *	
 *	\~russian
 *	\brief Контейнер для хранения двух объектов
 *	
 *	Объект класса `Pair` может хранить две переменные. Если вам нужно хранить объекты некоторого
 *	класса, настоятельно рекомендуется хранить указатели на них. Если тип не примитивный, для него
 *	должны быть определены методы `to_string` и `hash_code` (у любого `snow::Object` они есть).
 *	Если тип не является указателем, у него также должны быть определёны конструктор по умолчанию,
 *	оператор присваивания (`=`) и оператор равенства (`==`). Предполагается, что конструктор по
 *	умолчанию и конструктор копирования не выбрасывают никаких исключений.
 *	\warning Если одна из переменных пары является `unique_ptr`ом, то методы, копирующие её
 *	(например, конструктор копирования) не должны вызываться (может быть выброшено исключение
 *	`std::logic_error`).
 *	\tparam T_First Тип первой переменной пары.
 *	\tparam T_Second Тип второй переменной пары.
 */
template<typename T_First, typename T_Second>
class Pair : public Object
{
public:
		/* CONSTRUCTORS */
	
	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates a new pair. Variables of the pair are initialized using default constructors.
	 *	
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *	
	 *	Создаёт новую пару. Переменные пары инициализируются с использованием конструктора по
	 *	умолчанию.
	 */
	Pair() noexcept;

	/**
	 *	\~english
	 *	\brief The copy constructor
	 *	
	 *	Copies the pair.
	 *	\warning This constructor must not be used if one of the pair variables is `unique_ptr`
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param pair The pair that will be copied.
	 *	
	 *	\~russian
	 *	\brief Конструктор копирования
	 *	
	 *	Копирует пару.
	 *	\warning Этот конструктор не должен быть использован, если одна из переменных пары
	 *	является `unique_ptr`ом (может быть выброшено исключение `std::logic_error`). Вместо этого
	 *	используйте семантику перемещения.
	 *	\param pair Пара, которая будет скопирована.
	 */
	Pair(const Pair<T_First, T_Second>& pair) noexcept;

	/**
	 *	\~english
	 *	\brief The move constructor
	 *	
	 *	Moves variables to a new pair from the passed one.
	 *	\param pair The pair whose variables will be moved.
	 *	
	 *	\~russian
	 *	\brief Конструктор перемещения
	 *	
	 *	Перемещает переменные в новую пару из переданной.
	 *	\param pair Пара, чьи переменные будут перемещены.
	 */
	Pair(Pair<T_First, T_Second>&& pair) noexcept;

	/**
	 *	\~english
	 *	\brief The elementwise copy constructor
	 *	
	 *	Copies the passed values into a new pair.
	 *	\warning This constructor must not be used if one of the pair variables is `unique_ptr`
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param first The value for the first variable.
	 *	\param second The value for the second variable.
	 *	
	 *	\~russian
	 *	\brief Поэлементный конструктор копирования
	 *	
	 *	Копирует переданные значения в новую пару.
	 *	\warning Этот метод не должен быть использован, если одна из переменных пары является
	 *	`unique_ptr`ом (может быть выброшено исключение `std::logic_error`). Вместо этого
	 *	используйте семантику перемещения.
	 *	\param first Значение для первой переменной.
	 *	\param second Значение для второй переменной.
	 */
	Pair(const T_First& first, const T_Second& second);

	/**
	 *	\~english
	 *	\brief The elementwise move constructor
	 *
	 *	Moves the passed values into a new pair.
	 *	\param first The value for the first variable.
	 *	\param second The value for the second variable.
	 *
	 *	\~russian
	 *	\brief Поэлементный конструктор перемещения
	 *
	 *	Перемещает переданные значения в новую пару.
	 *	\param first Значение для первой переменной.
	 *	\param second Значение для второй переменной.
	 */
	Pair(T_First&& first, T_Second&& second);

	/**
	 *	\~english
	 *	\brief The elementwise copy/move constructor
	 *
	 *	Copies the first value and moves the second value into a new pair.
	 *	\warning This constructor must not be used if the first pair variable is `unique_ptr`
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param first The value for the first variable.
	 *	\param second The value for the second variable.
	 *
	 *	\~russian
	 *	\brief Поэлементный конструктор копирования/перемещения
	 *
	 *	Копирует первое значение и перемещает второе значение в новую пару.
	 *	\warning Этот конструктор не должен быть использован, если первая переменная пары является
	 *	`unique_ptr`ом (может быть выброшено исключение `std::logic_error`). Вместо этого
	 *	используйте семантику перемещения.
	 *	\param first Значение для первой переменной.
	 *	\param second Значение для второй переменной.
	 */
	Pair(const T_First& first, T_Second&& second);

	/**
	 *	\~english
	 *	\brief The elementwise move/copy constructor
	 *
	 *	Moves the first value and copies the second value into a new pair.
	 *	\warning This constructor must not be used if the second pair variable is `unique_ptr`
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param first The value for the first variable.
	 *	\param second The value for the second variable.
	 *
	 *	\~russian
	 *	\brief Поэлементный конструктор перемещения/копирования
	 *
	 *	Перемещает первое значение и копирует второе значение в новую пару.
	 *	\warning Этот конструктор не должен быть использован, если вторая переменная пары является
	 *	`unique_ptr`ом (может быть выброшено исключение `std::logic_error`). Вместо этого
	 *	используйте семантику перемещения.
	 *	\param first Значение для первой переменной.
	 *	\param second Значение для второй переменной.
	 */
	Pair(T_First&& first, const T_Second& second);
	
			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the pair to string
	 *
	 *	Creates a string in the format `[<1>: <2>]` where `<1>` represents the first variable and
	 *	`<2>` represents the second one. `util::to_string` is used to convert variables to string.
	 *	\return A result string.
	 *
	 *	\~russian
	 *	\brief Конвертирует пару в строку
	 *
	 *	Создаёт строку в формате `[<1>: <2>]`, где `<1>` представляет первую переменную, а `<2>` —
	 *	вторую. Для конвертации переменных в строку используется `util::to_string`.
	 *	\return Итоговая строка.
	 */
	virtual String to_string() const noexcept override;

	/**
	 *	\~english
	 *	\brief Hash code of the pair
	 *	
	 *	Hash code of a pair is a difference between hash codes of two variables.
	 *	\return Hash code of the pair.
	 *	
	 *	\~russian
	 *	\brief Хеш-код пары
	 *	
	 *	Хеш-код пары — это разность между хеш-кодами двух переменных.
	 *	\return Хеш-код пары
	 */
	virtual int hash_code() const noexcept override;
	
	/**
	 *	\~english
	 *	\brief The first variable
	 *	
	 *	Allows to access the first variable of the pair.
	 *	\return A reference to the first variable of the pair.
	 *
	 *	\~russian
	 *	\brief Первая переменная
	 *	
	 *	Позволяет получить доступ к первой переменной пары.
	 *	\return Ссылка на первую переменную пары.
	 */
	T_First& get_first() noexcept;

	/**
	 *	\~english
	 *	\brief The second variable
	 *
	 *	Allows to access the second variable of the pair.
	 *	\return A reference to the second variable of the pair.
	 *
	 *	\~russian
	 *	\brief Вторая переменная
	 *
	 *	Позволяет получить доступ ко второй переменной пары.
	 *	\return Ссылка на вторую переменную пары.
	 */
	T_Second& get_second() noexcept;

	/**
	 *	\~english
	 *	\brief The first variable
	 *
	 *	Allows to read the first variable of the pair.
	 *	\return A constant reference to the first variable of the pair.
	 *
	 *	\~russian
	 *	\brief Первая переменная
	 *
	 *	Позволяет прочитать первую переменную пары.
	 *	\return Константная ссылка на первую переменную пары.
	 */
	const T_First& get_first() const noexcept;

	/**
	 *	\~english
	 *	\brief The second variable
	 *
	 *	Allows to read the second variable of the pair.
	 *	\return A constant reference to the second variable of the pair.
	 *
	 *	\~russian
	 *	\brief Вторая переменная
	 *
	 *	Позволяет прочитать вторую переменную пары.
	 *	\return Константная ссылка на вторую переменную пары.
	 */
	const T_Second& get_second() const noexcept;

	/**
	 *	\~english
	 *	\brief Sets the first variable
	 *	
	 *	Allows to set the first variable of the pair.
	 *	\warning This method must not be used if the first pair variable is `unique_ptr`
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param first The new value of the first variable.
	 *
	 *	\~russian
	 *	\brief Устанавливает первую переменную
	 *
	 *	Позволяет установить первую переменную пары.
	 *	\warning Этот метод не должен быть использован, если первая переменная пары является
	 *	`unique_ptr`ом (может быть выброшено исключение `std::logic_error`). Вместо этого
	 *	используйте семантику перемещения.
	 *	\param first Новое значение первой переменной.
	 */
	void set_first(const T_First& first);

	/**
	 *	\~english
	 *	\brief Sets the second variable
	 *
	 *	Allows to set the second variable of the pair.
	 *	\warning This method must not be used if the second pair variable is `unique_ptr`
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param second The new value of the second variable.
	 *
	 *	\~russian
	 *	\brief Устанавливает вторую переменную
	 *
	 *	Позволяет установить вторую переменную пары.
	 *	\warning Этот метод не должен быть использован, если вторая переменная пары является
	 *	`unique_ptr`ом (может быть выброшено исключение `std::logic_error`). Вместо этого
	 *	используйте семантику перемещения.
	 *	\param second Новое значение второй переменной.
	 */
	void set_second(const T_Second& second);

	/**
	 *	\~english
	 *	\brief Sets the first variable
	 *
	 *	Allows to set the first variable of the pair.
	 *	\param first The value that will be assigned to the first variable.
	 *
	 *	\~russian
	 *	\brief Устанавливает первую переменную
	 *
	 *	Позволяет установить первую переменную пары.
	 *	\param first Новое значение первой переменной.
	 */
	void set_first(T_First&& first);

	/**
	 *	\~english
	 *	\brief Sets the second variable
	 *
	 *	Allows to set the second variable of the pair.
	 *	\param second The new value of the second variable.
	 *
	 *	\~russian
	 *	\brief Устанавливает вторую переменную
	 *
	 *	Позволяет установить вторую переменную пары.
	 *	\param second Новое значение второй переменной.
	 */
	void set_second(T_Second&& second);

			/* OPERATORS */

	/**
	 *	\~english
	 *	\brief The copy assignment operator
	 *
	 *	Replaces variables of the pair with copies of variables of the passed one.
	 *	\warning This operator must not be used if one of the pair variables is `unique_ptr`
	 *	(`std::logic_error` exception can be thrown). Instead, use move semantics.
	 *	\param pair The pair that will be copied.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Конструктор присваивания копированием
	 *
	 *	Заменяет переменные данной пары на копии переменных переданной.
	 *	\warning Этот оператор не должен быть использован, если одна из переменных пары является
	 *	`unique_ptr`ом (может быть выброшено исключение `std::logic_error`). Вместо этого
	 *	используйте семантику перемещения.
	 *	\param angle Пара, которая будет скопирована.
	 *	\return Ссылка на себя.
	 */
	Pair<T_First, T_Second>& operator=(const Pair<T_First, T_Second>& pair);

	/**
	 *	\~english
	 *	\brief The move assignment operator
	 *
	 *	Moves variables of the passed pair and set them instead of variables of this one.
	 *	\param pair The pair that will be moved.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Конструктор присваивания перемещением
	 *
	 *	Перемещает переменные переданной пары и устанавливает их вместо переменных данной.
	 *	\param angle Пара, которая будет перемещена.
	 *	\return Ссылка на себя.
	 */
	Pair<T_First, T_Second>& operator=(Pair<T_First, T_Second>&& pair);

	/**
	 *	\~english
	 *	\brief Checks whether two pairs are equal
	 *
	 *	Two pairs are equal if their first elements are equal to each other, and second elements
	 *	are equal to each other.
	 *	\param pair The pair to compare.
	 *	\return `true` if two pairs are equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, равны ли две пары
	 *
	 *	Две пары равны, если их первые элементы равны между собой и вторые элементы равны между
	 *	собой.
	 *	\param pair Пара для сравнения.
	 *	\return `true`, если две пары равны, иначе `false`.
	 */
	bool operator==(const Pair<T_First, T_Second>& pair) const;

	/**
	 *	\~english
	 *	\brief Checks whether two pairs are not equal
	 *
	 *	Two pairs are equal if their first elements are equal to each other, and second elements
	 *	are equal to each other.
	 *	\param pair The pair to compare.
	 *	\return `true` if two pairs are not equal, `false` otherwise.
	 *
	 *	\~russian
	 *	\brief Проверяет, различаются ли две пары
	 *
	 *	Две пары равны, если их первые элементы равны между собой и вторые элементы равны между
	 *	собой.
	 *	\param pair Пара для сравнения.
	 *	\return `true`, если две пары не равны, иначе `false`.
	 */
	bool operator!=(const Pair<T_First, T_Second>& pair) const;

private:
	Wrap_<T_First> first_;
	Wrap_<T_Second> second_;
};


		/* DEFINITIONS OF Wrap_ */

template<typename T>
Wrap_<T>::Wrap_(const T& v) noexcept :
	var(v)
{}

template<typename T>
Wrap_<T>::Wrap_(T&& v) noexcept :
	var(std::move(v))
{}

template<typename T>
Wrap_<std::unique_ptr<T>>::Wrap_(const std::unique_ptr<T>& v) noexcept :
	var()
{
	throw std::logic_error("Using of this method is not allowed for containers of unique_ptr's");
}

template<typename T>
Wrap_<std::unique_ptr<T>>::Wrap_(std::unique_ptr<T>&& v) noexcept :
	var(std::move(v))
{}

		/* DEFINITIONS OF Pair */

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>::Pair() noexcept :
	first_(),
	second_()
{}

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>::Pair(const Pair<T_First, T_Second>& pair) noexcept :
	first_(pair.first_.var),
	second_(pair.second_.var)
{}

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>::Pair(Pair<T_First, T_Second>&& pair) noexcept :
	first_(std::move(pair.first_.var)),
	second_(std::move(pair.second_.var))
{}

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>::Pair(const T_First& first, const T_Second& second) :
	first_(first),
	second_(second)
{}

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>::Pair(T_First&& first, T_Second&& second) :
	first_(std::move(first)),
	second_(std::move(second))
{}

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>::Pair(const T_First& first, T_Second&& second) :
	first_(first),
	second_(std::move(second))
{}

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>::Pair(T_First&& first, const T_Second& second) :
	first_(std::move(first)),
	second_(second)
{}

template<typename T_First, typename T_Second>
String Pair<T_First, T_Second>::to_string() const noexcept
{
	return L"["_s + util::to_string(first_.var) + L": "_s + util::to_string(second_.var) + L"]"_s;
}

template<typename T_First, typename T_Second>
int Pair<T_First, T_Second>::hash_code() const noexcept
{
	return util::hash_code(first_.var) - util::hash_code(second_.var);
}

template<typename T_First, typename T_Second>
T_First& Pair<T_First, T_Second>::get_first() noexcept
{
	return first_.var;
}

template<typename T_First, typename T_Second>
T_Second& Pair<T_First, T_Second>::get_second() noexcept
{
	return second_.var;
}

template<typename T_First, typename T_Second>
const T_First& Pair<T_First, T_Second>::get_first() const noexcept
{
	return first_.var;
}

template<typename T_First, typename T_Second>
const T_Second& Pair<T_First, T_Second>::get_second() const noexcept
{
	return second_.var;
}

template<typename T_First, typename T_Second>
void Pair<T_First, T_Second>::set_first(const T_First& first)
{
	assign_(first_.var, first);
}

template<typename T_First, typename T_Second>
void Pair<T_First, T_Second>::set_second(const T_Second& second)
{
	assign_(second_.var, second);
}

template<typename T_First, typename T_Second>
void Pair<T_First, T_Second>::set_first(T_First&& first)
{
	first_.var = std::move(first);
}

template<typename T_First, typename T_Second>
void Pair<T_First, T_Second>::set_second(T_Second&& second)
{
	second_.var = std::move(second);
}

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>& Pair<T_First, T_Second>::operator=(const Pair<T_First, T_Second>& pair)
{
	assign_(first_.var, pair.first_.var);
	assign_(second_.var, pair.second_.var);
	return *this;
}

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>& Pair<T_First, T_Second>::operator=(Pair<T_First, T_Second>&& pair)
{
	first_.var = std::move(pair.first_.var);
	second_.var = std::move(pair.second_.var);
	return *this;
}

template<typename T_First, typename T_Second>
bool Pair<T_First, T_Second>::operator==(const Pair<T_First, T_Second>& pair) const
{
	return first_.var == pair.first_.var && second_.var == pair.second_.var;
}

template<typename T_First, typename T_Second>
bool Pair<T_First, T_Second>::operator!=(const Pair<T_First, T_Second>& pair) const
{
	return !(*this == pair);
}

}
