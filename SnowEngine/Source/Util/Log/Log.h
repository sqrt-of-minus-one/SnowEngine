    ////////////////////////////////////////
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

/**
 *	\file
 *	\~english
 *	\brief The file with `Log` class
 *
 *	This file contains the definition of the `Log` class of the SnowCat system.
 *
 *	\~russian
 *	\brief Файл с классом `Log`
 *
 *	Этот файл содержит определение класса `Log` системы SnowCat.
 */

#include "../../Object.h"

#include <mutex>

#include "../Types/String.h"

namespace snow
{

/**
 *	\~english
 *	\brief The class of the SnowCat logger
 *	
 *	The main class of the SnowCat system. Is used to log. When you create a `Log` object, you
 *	should specify its log category. To write something in log use one of these methods:
 *	Method | Meaning
 *	-------|---------
 *	`i`    | Information.
 *	`w`    | Warning.
 *	`e`    | Error.
 *	`d`    | Debug message (is ignored unless debug mode is active).
 *	The debug mode is enabled by default if project configuration is Debug. The log is output to
 *	the console and saved in the file. The directory where log files are saved is specified by
 *	`config.ini`.
 *	
 *	\~russian
 *	\brief Класс лога SnowCat
 *	
 *	Главный класс системы SnowCat. Используется для ведения лога. При создании объекта `Log` вам
 *	следует определить категорию лога. Чтобы записать что-нибудь в лог, используйте один из
 *	следующих методов:
 *	Метод  | Значение
 *	-------|----------
 *	`i`    | Информация.
 *	`w`    | Предупреждение.
 *	`e`    | Ошибка.
 *	`d`    | Сообщение для отладки (игнорируется, если режим отладки выключён).
 *	Режим отладки по умолчанию активирован, если проект собирается в конфигурации Degub. Лог
 *	выводится в консоль и сохраняется в файле. Директория, где сохраняются файлы лога, определяется
 *	в `config.ini`.
 */
class Log : public Object
{
public:
			/* CONSTRUCTORS */
	
	/**
	 *	\~english
	 *	\brief The constructor of the logger
	 *	
	 *	Creates a new logger that is associated with the passed log category.
	 *	\param category_name Log category name.
	 *	
	 *	\~russian
	 *	\brief Конструктор объекта логгера
	 *	
	 *	Создаёт новый логгер, связанный с переданной категорией лога.
	 *	\param category_name Название категории лога.
	 */
	Log(const String& category_name) noexcept;

	/**
	 *	\~english
	 *	\brief The destructor of the logger
	 *	
	 *	If necessary, closes the log file.
	 *	
	 *	\~russian
	 *	\brief Деструктор логгера
	 *	
	 *	При необходимости закрывает файл лога.
	 */
	virtual ~Log() noexcept;

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
	virtual String to_string() const noexcept override;

	/**
	 *	\~english
	 *	\brief Hash code of the looger
	 *
	 *	Hash code is an integer number. Hash codes of two equal object are equal, but two different
	 *	objects can also have the same hash codes.
	 *	\return Hash code of the object.
	 *
	 *	\~russian
	 *	\brief Хеш-код логгера
	 *
	 *	Хеш-код — это целое число. Хеш-коды двух равных объектов равны, но два различных объекта
	 *	также могут иметь одинаковые хеш-коды.
	 *	\return Хеш-код объекта.
	 */
	virtual int hash_code() const noexcept override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Enables debug mode
	 *	
	 *	Enables debug mode. If debug mode is enabled, debug messages (`d` method) are logged.
	 *	
	 *	\~russian
	 *	\brief Активирует режим отладки
	 *	
	 *	Активирует режим отладки. Если режим отладки активирован, отладочные сообщения (метод `d`)
	 *	сохраняются.
	 */
	static void enable_debug_mode() noexcept;

	/**
	 *	\~english
	 *	\brief Disables debug mode
	 *
	 *	Disables debug mode. If debug mode is disabled, debug messages (`d` method) are ignored.
	 *
	 *	\~russian
	 *	\brief Деактивирует режим отладки
	 *
	 *	Деактивирует режим отладки. Если режим отладки деактивирован, отладочные сообщения (метод
	 *	`d`) игнорируются.
	 */
	static void disable_debug_mode() noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether debug mode is enabled
	 *	
	 *	Checks whether debug mode is enabled. If it is, debug messages (`d` method) are logged.
	 *	\return `true` if debug mode is enabled, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, активирован ли режим отладки. Если да, отладочные сообщения (метод `d`),
	 *	сохраняются.
	 *	\return `true`, если режим отладки активирован, иначе `false`.
	 */
	static bool is_debug_mode_enabled() noexcept;

	/**
	 *	\~english
	 *	\brief Debug message
	 *	
	 *	Creates a debug log entry. It will be ignored unless debug mode is enabled.
	 *	\param message The log message.
	 *	
	 *	\~russian
	 *	\brief Отладочное сообщение
	 *	
	 *	Создаёт запись лога с отладочным сообщением. Оно будет проигнорировано, если отладчоный
	 *	режим отключен.
	 *	\param message Сообщение лога.
	 */
	void d(const String& message) noexcept;

	/**
	 *	\~english
	 *	\brief Info message
	 *
	 *	Creates an info log entry.
	 *	\param message The log message.
	 *
	 *	\~russian
	 *	\brief Информационное сообщение
	 *
	 *	Создаёт запись лога с информационным сообщением.
	 *	\param message Сообщение лога.
	 */
	void i(const String& message) noexcept;

	/**
	 *	\~english
	 *	\brief Warning message
	 *
	 *	Creates a warning log entry.
	 *	\param message The log message.
	 *
	 *	\~russian
	 *	\brief Сообщение с предупреждением
	 *
	 *	Создаёт запись лога с предупреждением.
	 *	\param message Сообщение лога.
	 */
	void w(const String& message) noexcept;

	/**
	 *	\~english
	 *	\brief Error message
	 *
	 *	Creates an error log entry.
	 *	\param message The log message.
	 *
	 *	\~russian
	 *	\brief Сообщение об ошибке
	 *
	 *	Создаёт запись лога об ошибке.
	 *	\param message Сообщение лога.
	 */
	void e(const String& message) noexcept;
private:
	const String name_;
	static int object_counter_;
	
	
	/* lazy */ static bool& debug_mode_();
	/* lazy */ static std::mutex& log_file_mtx_();
	/* lazy */ static std::wofstream& log_file_();

	void log_(const String& type, const String& message) noexcept;
};

}