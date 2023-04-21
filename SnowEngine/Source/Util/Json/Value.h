    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Value.h                     //
////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//*+ *+ *+ *+ *** ____************************* ____***|*******SnowStorm*************************//
//**+ *+ *+ *+ **|*****************************|*******|*****************************************//
//*+ *+ *+ *+ ***____ ** ___ ** ___ **|*****|**____ **_|_** ___ ** ___ ** __ __ *****************//
//**+ *+ *+ *+ ******|**|***|**|***|**|**|**|******|***|***|***|**|***_**|**|**|*** SnowEngine **//
//*+ *+ *+ *+ ***_____**_***_**_____***__|__***_____***__**_____**_******_**_**_** JSON  system *//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\~english
 *	\brief The file with JSON value classes
 *	
 *	This file contains the definition of the value classes of SnowStorm system.
 *	
 *	\~russian
 *	\brief Файл с классами значений JSON
 *	
 *	Этот файл содержит определение классов значений системы SnowStorm.
 */

#include "Element.h"

#include <type_traits>

#include "../Util.h"

namespace snow
{

namespace json
{

namespace snow_
{

/**
 *	\~english
 *	\brief JSON value
 *	
 *	Represents the value. You can access it via `get()` and `set()` methods.
 *	\tparam T The type of the value. Can only be `String`, `int`, `double`, `bool` and
 *	`std::nullptr_t`.
 *	\warning Do not use this class directly. Use `StringValue`, `IntValue`, `DoubleValue`,
 *	`BoolValue`, and `NullValue` instead.
 *	
 *	\~russian
 *	\brief Массив JSON
 *	
 *	Значениями массива JSON могут быть любые элементы JSON (строковые, целочисленные, вещественные,
 *	булевы или нулевые значения, объекты, другие массивы). Вы можете получить доступ к этим
 *	значениям методом `get_content()`.
 *	\warning Не используйте этот класс напрямую. Вместо этого используйте классы `StringValue`,
 *	`IntValue`, `DoubleValue`, `BoolValue` и `NullValue`.
 */
template<typename T>
class Value_ : public Element
{
	static_assert(std::is_same<T, String>::value || std::is_same<T, int>::value ||
				  std::is_same<T, double>::value || std::is_same<T, bool>::value.
				  "Only String, int, double, bool, and nullptr_t are allowed to be the template parameter of the Value_ class");

public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates a default value using the default constructor of `T`.
	 *	
	 *	\~russian
	 *	\brief Констуктор по умолчанию
	 *	
	 *	Создаёт значение по умолчанию с помощью конструктора по умолчанию `T`.
	 */
	Value_();
	
	/**
	 *	\~english
	 *	\brief The copy constructor
	 *	
	 *	Creates a copy of the value.
	 *	
	 *	\~russian
	 *	\brief Констуктор копирования
	 *	
	 *	Создаёт копию значения.
	 */
	Value_(const Value_<T>& object);

	/**
	 *	\~english
	 *	\brief The move constructor
	 *	
	 *	Creates a new value by moving another one.
	 *	
	 *	\~russian
	 *	\brief Конструктор перемещения
	 *	
	 *	Создаёт новое значение путём перемещения другого.
	 */
	Value_(Value_<T>&& object);
	
	/**
	 *	\~english
	 *	\brief The copy constructor
	 *	
	 *	Creates a copy of the value.
	 *	
	 *	\~russian
	 *	\brief Констуктор копирования
	 *	
	 *	Создаёт копию значения.
	 */
	Value_(const T& value);

	/**
	 *	\~english
	 *	\brief The move constructor
	 *	
	 *	Creates a new value by moving another one.
	 *	
	 *	\~russian
	 *	\brief Конструктор перемещения
	 *	
	 *	Создаёт новое значение путём перемещения другого.
	 */
	Value_(T&& value);
	
			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Hash code of the value
	 *
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes.
	 *	\return Hash code of the value.
	 *
	 *	\~russian
	 *	\brief Хеш-код значения
	 *
	 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
	 *	также могут иметь одинаковые хеш-коды.
	 *	\return Хеш-код значения.
	 */
	virtual int hash_code() const noexcept override;

			/* METHODS FROM Element */
	
	/**
	 *	\~english
	 *	\brief The type of the element
	 *	
	 *	Allows to get the element type.
	 *	\return The type of the element.
	 *	
	 *	\~russian
	 *	\brief Тип элемента
	 *	
	 *	Позволяет получить тип элемента.
	 *	\return Тип элемента.
	 */
	virtual EType get_type() const override;
	
	/**
	 *	\~english
	 *	\brief Puts the value to the stream
	 *	
	 *	Puts the value to the stream. If the value is string, puts it in `"` and uses escape
	 *	sequences.
	 *	\param stream The stream where the value will be put.
	 *	\param nesting Does not affect anything.
	 *	
	 *	\~russian
	 *	\brief Помещает значение в поток
	 *	
	 *	Помещает значение в поток. Если значение является строковым, оборачивает его в `"` и
	 *	использует управляющие последовательности.
	 *	\param stream Поток, куда будет помещено значение.
	 *	\param nesting Ни на что не влияет.
	 */
	virtual void to_stream(std::wostream& stream, int nesting = 0) const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief The value
	 *	
	 *	Allows to access the value.
	 *	\return The reference to the value.
	 *	
	 *	\~russian
	 *	\brief Значение
	 *	
	 *	Позволяет получить доступ к значению.
	 *	\return Ссылка на значение.
	 */
	T& get() noexcept;

	/**
	 *	\~english
	 *	\brief The value
	 *	
	 *	Allows to read the value.
	 *	\return The constant reference to the value.
	 *	
	 *	\~russian
	 *	\brief Значение
	 *	
	 *	Позволяет прочитать к значению.
	 *	\return Константная ссылка на значение.
	 */
	const T& get() const noexcept;

	/**
	 *	\~english
	 *	\brief Sets the value
	 *	
	 *	Allows to set the value.
	 *	\param value The value to set.
	 *	
	 *	\~russian
	 *	\brief Устанавливает значение
	 *	
	 *	Позволяет установить значение.
	 *	\param value Значение для установки.
	 */
	void set(const T& value) noexcept(noexcept(std::declval<T>() = std::declval<T>()));
	
private:
	T value_;
};

/**
 *	\~english
 *	\brief The `NullValue` implementation
 *	
 *	This class implements the JSON null value.
 *	\warning Do not use this class directly. Use `NullValue` instead.
 *	
 *	\~russian
 *	\brief Реализация `NullValue`
 *	
 *	Этот класс реализует нулевое значение JSON.
 *	\warning Не используйте этот класс напрямую. Вместо этого используйте `NullValue`.
 */
template<>
class Value_<std::nullptr_t> : public Element
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates a null value.
	 *	
	 *	\~russian
	 *	\brief Констуктор по умолчанию
	 *	
	 *	Создаёт нулевое значение.
	 */
	Value_();
	
			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Hash code of the value
	 *
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes. Hash code of a null value is always zero.
	 *	\return Hash code of the value.
	 *
	 *	\~russian
	 *	\brief Хеш-код значения
	 *
	 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
	 *	также могут иметь одинаковые хеш-коды. Хеш-код нулевого значения — всегда ноль.
	 *	\return Хеш-код значения.
	 */
	virtual int hash_code() const noexcept override;

			/* METHODS FROM Element */
	
	/**
	 *	\~english
	 *	\brief The type of the element
	 *	
	 *	Allows to get the element type.
	 *	\return `EType::NULL_VALUE`.
	 *	
	 *	\~russian
	 *	\brief Тип элемента
	 *	
	 *	Позволяет получить тип элемента.
	 *	\return `EType::NULL_VALUE`.
	 */
	virtual EType get_type() const override;

	/**
	 *	\~english
	 *	\brief Puts the value to the stream
	 *	
	 *	Puts `null` to the stream.
	 *	\param stream The stream where the value will be put.
	 *	\param nesting Does not affect anything.
	 *	
	 *	\~russian
	 *	\brief Помещает значение в поток
	 *	
	 *	Помещает в поток `null`.
	 *	\param stream Поток, куда будет помещено значение.
	 *	\param nesting Ни на что не влияет.
	 */
	virtual void to_stream(std::wostream& stream, int nesting = 0) const override;
};

template<typename T>
extern EType type_() noexcept = delete;

template<>
extern EType type_<String>() noexcept;

template<>
extern EType type_<int>() noexcept;

template<>
extern EType type_<double>() noexcept;

template<>
extern EType type_<bool>() noexcept;

template<>
extern EType type_<std::nullptr_t>() noexcept;

}

using StringValue = snow_::Value_<String>;			/// \~english The string value \~russian Строковое значение
using IntValue = snow_::Value_<int>;				/// \~english The integer value \~russian Целочисленное значение
using DoubleValue = snow_::Value_<double>;			/// \~english The double value \~russian Вещественное значение
using BoolValue = snow_::Value_<bool>;				/// \~english The boolean value \~russian Булево значение
using NullValue = snow_::Value_<std::nullptr_t>;	/// \~english The null value \~russian Нулевое значение

}


		/* DEFINITIONS */

		/* Value_: public */

template<typename T>
json::snow_::Value_<T>::Value_() :
	value_()
{}

template<typename T>
json::snow_::Value_<T>::Value_(const Value_<T>& object) :
	value_(object.value_)
{}

template<typename T>
json::snow_::Value_<T>::Value_(Value_<T>&& object) :
	value_(std::move(object.value_))
{}

template<typename T>
json::snow_::Value_<T>::Value_(const T& value) :
	value_(value)
{}

template<typename T>
json::snow_::Value_<T>::Value_(T&& value) :
	value_(std::move(value))
{}

template<typename T>
int json::snow_::Value_<T>::hash_code() const noexcept
{
	return util::hash_code(value_);
}

template<typename T>
json::EType json::snow_::Value_<T>::get_type() const
{
	return snow_::type_<T>();
}

template<typename T>
T& json::snow_::Value_<T>::get() noexcept
{
	return value_;
}

template<typename T>
const T& json::snow_::Value_<T>::get() const noexcept
{
	return value_;
}

template<typename T>
void json::snow_::Value_<T>::set(const T& value) noexcept(noexcept(std::declval<T>() = std::declval<T>()))
{
	value_ = value;
}

template<typename T>
void json::snow_::Value_<T>::to_stream(std::wostream& stream, int nesting) const
{
	if (std::is_same<T, String>::value)
	{
		stream << L'"' << util::to_string(value_).escape() << L'"';
	}
	else
	{
		stream << util::to_string(value_);
	}
}

}
