﻿    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Log.h                       //
////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////SnowCat//////////////////
////// \// \////////     ///   ///  ///    //  ///   ///  ///    //   //         ////////////////
/////       ///////  //////    //  //  //  //  //    //  //  /////    /////  //////////////////////
////  o   o  //////    ///  /  /  //  //  ///  /  /  /  //  /////  =  ////  /////////////////////
////    0    ////////  //  //    //  //  ////    //    //  /////      ///  ////   SnowEngine   ////
/////  / \  ////     ///  ///   ///    //////   ///   ///    //  ///  //  //// logging system ///
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../../Object.h"

#include <mutex>

#include "../Types/String.h"

namespace snow
{

/**
 *	\defgroup SnowCat SnowCat
 *	\~english
 *	\brief SnowCat, the SnowEngine logging system
 *	
 *	SnowCat is a simple tool allowing to keep a log.
 *	
 *	\~english
 *	\brief SnowCat, система ведения лога SnowEngine
 *	
 *	SnowCat — это простой инструмент, позволяющий вести лог.
 */

/**
 *	\addtogroup SnowCat
 *	\{
 */

/**
 *	\~english
 *	\brief The log category 
 *	
 *	In order to log something, you need to create a log category using this method. Then use
 *	methods of the `LogManager` class.
 *	
 *	\~russian
 *	\brief Категория лога
 *	
 *	Чтобы записать что-нибудь в лог, вам нужно создать категорию лога, используя данный класс.
 *	Далее используйте методы класса `LogManager`.
 */
class Log : public Object
{
public:
			/* CONSTRUCTORS */
	
	/**
	 *	\~english
	 *	\brief The constructor of the log category
	 *	
	 *	Creates a new log category.
	 *	\param category_name Log category name.
	 *	
	 *	\~russian
	 *	\brief Конструктор категории лога
	 *	
	 *	Создаёт новую категрию лога.
	 *	\param category_name Название категории лога.
	 */
	Log(const String& category_name);

	/**
	 *	\~english
	 *	\brief The constructor of the log category
	 *	
	 *	Creates a new log category. Its name is defined by the passed JSON. It must be a JSON
	 *	string.
	 *	\param json The JSON string defining the name of the log category.
	 *	\throw std::invalid_argument The passed JSON is not correct.
	 *	
	 *	\~russian
	 *	\brief Конструктор категории лога
	 *	
	 *	Создаёт новую категорию лога. Её название определяется переданным JSON. Это должна быть
	 *	строка JSON.
	 *	\param json Строка JSON, определяющая название категории лога.
	 *	\throw std::invalid_argument Переданный JSON неправильный.
	 */
	Log(const std::shared_ptr<json::Element> json);

			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the logger to string
	 *	
	 *	Returns a log category name.
	 *	\return The log category name.
	 *	
	 *	\~russian
	 *	\brief Конвертирует логгер в строку
	 *	
	 *	Возвращает название категории лога.
	 *	\return Название категории лога.
	 */
	virtual String to_string() const override;

	/**
	 *	\~english
	 *	\brief Converts the logger into a JSON element
	 *
	 *	Creates a JSON string with the log category name.
	 *	\return The JSON string with the category name.
	 *
	 *	\~russian
	 *	\brief Конвертирует логгер в элемент JSON
	 *
	 *	Создаёт строку JSON с названием категории лога.
	 *	\return Строка JSON с названием категории.
	 */
	virtual std::shared_ptr<json::Element> to_json() const override;

private:
	String name_;
};

/**
 *	\}
 */

}