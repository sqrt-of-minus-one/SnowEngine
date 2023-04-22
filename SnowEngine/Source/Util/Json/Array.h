    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Array.h                     //
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
 *	\brief The file with `Array` class
 *	
 *	This file contains the definition of the `Array` class of SnowStorm system.
 *	
 *	\~russian
 *	\brief Файл с классом `Array`
 *	
 *	Этот файл содержит определение класса `Array` системы SnowStorm.
 */

#include "Element.h"

#include <vector>

namespace snow
{

namespace json
{

/**
 *	\~english
 *	\brief JSON array
 *	
 *	The values of the JSON array can be any JSON elements (string, integer, double, boolean or null
 *	values, objects, another arrays). You can access these elements via `get_content()` method.
 *	
 *	\~russian
 *	\brief Массив JSON
 *	
 *	Значениями массива JSON могут быть любые элементы JSON (строковые, целочисленные, вещественные,
 *	булевы или нулевые значения, объекты, другие массивы). Вы можете получить доступ к этим
 *	значениям методом `get_content()`.
 */
class Array : public Element
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates an empty array (`[ ]`).
	 *	
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *	
	 *	Создаёт пустой массив (`[ ]`).
	 */
	Array();

	/**
	 *	\~english
	 *	\brief The move constructor
	 *	
	 *	Creates a new array by moving the content of another one.
	 *	
	 *	\~russian
	 *	\brief Конструктор перемещения
	 *	
	 *	Создаёт новый массив путём перемещения содержимого другого.
	 */
	Array(Array&& object);
	
			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Hash code of the array
	 *
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes. Hash code of an empty array is zero.
	 *	\return Hash code of the object.
	 *
	 *	\~russian
	 *	\brief Хеш-код массива
	 *
	 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
	 *	также могут иметь одинаковые хеш-коды. Хеш-код пустого массива — ноль.
	 *	\return Хеш-код объекта.
	 */
	virtual int hash_code() const noexcept override;

			/* METHODS FROM Element */
	
	/**
	 *	\~english
	 *	\brief The type of the element
	 *	
	 *	Allows to get the element type.
	 *	\return `EType::ARRAY`.
	 *	
	 *	\~russian
	 *	\brief Тип элемента
	 *	
	 *	Позволяет получить тип элемента.
	 *	\return `EType::ARRAY`.
	 */
	virtual EType get_type() const override;

	/**
	 *	\~english
	 *	\brief Puts the array to the stream
	 *	
	 *	Converts the array to JSON format and puts it to the stream.
	 *	\param stream The stream where the array will be put.
	 *	\param nesting Only affects nesting objects if there are any.
	 *	
	 *	\~russian
	 *	\brief Помещает массив в поток
	 *	
	 *	Конвертирует массив в формат JSON и помещает его в поток.
	 *	\param stream Поток, куда будет помещён массив.
	 *	\param nesting Влияет только на вложенные объекты, если они имеются.
	 */
	virtual void to_stream(std::wostream& stream, int nesting = 0) const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief The content of the array
	 *	
	 *	Allows to access the elements of the array.
	 *	\return The reference to the vector with the array content.
	 *	
	 *	\~russian
	 *	\brief Содержимое массива
	 *	
	 *	Позволяет получить доступ к элементам массива.
	 *	\return Ссылка на вектор с содержимым массива.
	 */
	std::vector<std::unique_ptr<Element>>& get_content() noexcept;

	/**
	 *	\~english
	 *	\brief The content of the array
	 *	
	 *	Allows to read the elements of the array.
	 *	\return The constant reference to the vector with the array content.
	 *	
	 *	\~russian
	 *	\brief Содержимое массива
	 *	
	 *	Позволяет прочитать к элементам массива.
	 *	\return Константная ссылка на вектор с содержимым массива.
	 */
	const std::vector<std::unique_ptr<Element>>& get_content() const noexcept;
	
private:
	std::vector<std::unique_ptr<Element>> content_;
};

}

}
