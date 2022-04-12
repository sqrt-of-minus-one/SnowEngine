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
	 *	\param pair The pair that will be copied.
	 *	
	 *	\~russian
	 *	\brief Конструктор копирования
	 *	
	 *	Копирует пару.
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
	 *	\param first The value for the first variable.
	 *	\param second The value for the second variable.
	 *	
	 *	\~russian
	 *	\brief Поэлементный конструктор копирования
	 *	
	 *	Копирует переданные значения в новую пару.
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
	 *	\param first The new value of the first variable.
	 *
	 *	\~russian
	 *	\brief Устанавливает первую переменную
	 *
	 *	Позволяет установить первую переменную пары.
	 *	\param first Новое значение первой переменной.
	 */
	void set_first(const T_First& first);

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
	 *	\param pair The pair that will be copied.
	 *	\return A reference to itself.
	 *
	 *	\~russian
	 *	\brief Конструктор присваивания копированием
	 *
	 *	Заменяет переменные данной пары на копии переменных переданной.
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
	T_First first_;
	T_Second second_;
};


		/* DEFINITIONS */

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>::Pair() noexcept :
	first_(),
	second_()
{}

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>::Pair(const Pair<T_First, T_Second>& pair) noexcept :
	first_(pair.first_),
	second_(pair.second_)
{}

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>::Pair(Pair<T_First, T_Second>&& pair) noexcept :
	first_(std::move(pair.first_)),
	second_(std::move(pair.second_))
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
String Pair<T_First, T_Second>::to_string() const noexcept
{
	return L"["_s + util::to_string(first_) + L": "_s + util::to_string(second_) + L"]"_s;
}

template<typename T_First, typename T_Second>
int Pair<T_First, T_Second>::hash_code() const noexcept
{
	return util::hash_code(first_) - util::hash_code(second_);
}

template<typename T_First, typename T_Second>
T_First& Pair<T_First, T_Second>::get_first() noexcept
{
	return first_;
}

template<typename T_First, typename T_Second>
T_Second& Pair<T_First, T_Second>::get_second() noexcept
{
	return second_;
}

template<typename T_First, typename T_Second>
const T_First& Pair<T_First, T_Second>::get_first() const noexcept
{
	return first_;
}

template<typename T_First, typename T_Second>
const T_Second& Pair<T_First, T_Second>::get_second() const noexcept
{
	return second_;
}

template<typename T_First, typename T_Second>
void Pair<T_First, T_Second>::set_first(const T_First& first)
{
	first_ = first;
}

template<typename T_First, typename T_Second>
void Pair<T_First, T_Second>::set_second(const T_Second& second)
{
	second_ = second;
}

template<typename T_First, typename T_Second>
void Pair<T_First, T_Second>::set_first(T_First&& first)
{
	first_ = std::move(first);
}

template<typename T_First, typename T_Second>
void Pair<T_First, T_Second>::set_second(T_Second&& second)
{
	second_ = std::move(second);
}

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>& Pair<T_First, T_Second>::operator=(const Pair<T_First, T_Second>& pair)
{
	first_ = pair.first_;
	second_ = pair.second_;
	return *this;
}

template<typename T_First, typename T_Second>
Pair<T_First, T_Second>& Pair<T_First, T_Second>::operator=(Pair<T_First, T_Second>&& pair)
{
	first_ = std::move(pair.first_);
	second_ = std::move(pair.second_);
	return *this;
}

template<typename T_First, typename T_Second>
bool Pair<T_First, T_Second>::operator==(const Pair<T_First, T_Second>& pair) const
{
	return first_ == pair.first_ && second_ == pair.second_;
}

template<typename T_First, typename T_Second>
bool Pair<T_First, T_Second>::operator!=(const Pair<T_First, T_Second>& pair) const
{
	return !(*this == pair);
}

}
