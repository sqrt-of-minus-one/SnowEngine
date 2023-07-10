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
 *	SnowCat is a simple tool allowing to keep a log. See the documentation of the `Log` class for
 *	more details.
 *	
 *	\~english
 *	\brief SnowCat, система ведения лога SnowEngine
 *	
 *	SnowCat — это простой инструмент, позволяющий вести лог. Более подробную информацию см. в
 *	документации класса `Log`.
 */

/**
 *	\addtogroup SnowCat
 *	\{
 */

/**
 *	\~english
 *	\brief The class of the SnowCat logger
 *	
 *	The main class of the SnowCat system. Is used to log. When you create a `Log` object, you
 *	should specify its log category. To write something in log use one of these methods:
 *	Method | Meaning
 *	-------|---------
 *	`i()`  | Information.
 *	`w()`  | Warning.
 *	`e()`  | Error.
 *	`d()`  | Debug message (is ignored unless debug mode is active).
 *	The debug mode is disabled by default unless project configuration is Debug. You can switch the
 *	debug mode manually using `enable_debug_mode()` and `disable_debug_mode()` methods. The log is
 *	output to the console and saved in the file. The directory where log files are saved is
 *	specified by `config.ini`.
 *	
 *	\~russian
 *	\brief Класс лога SnowCat
 *	
 *	Главный класс системы SnowCat. Используется для ведения лога. При создании объекта `Log` вам
 *	следует определить категорию лога. Чтобы записать что-нибудь в лог, используйте один из
 *	следующих методов:
 *	Метод  | Значение
 *	-------|----------
 *	`i()`  | Информация.
 *	`w()`  | Предупреждение.
 *	`e()`  | Ошибка.
 *	`d()`  | Сообщение для отладки (игнорируется, если режим отладки выключён).
 *	Режим отладки по умолчанию активирован, если проект собирается в конфигурации Degub. Вы можете
 *	переключать режим отладки вручную с помощью методов `enable_debug_mode()` и
 *	`disable_debug_mode()`. Лог выводится в консоль и сохраняется в файле. Директория, где
 *	сохраняются файлы лога, определяется в `config.ini`.
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
	Log(const String& category_name);

	/**
	 *	\~english
	 *	\brief The constructor of the logger
	 *	
	 *	Creates a new logger. The log category is defined by the passed JSON. It must be a JSON
	 *	string with the category name.
	 *	\param json The JSON string defining the log category.
	 *	\throw std::invalid_argument The passed JSON is not correct.
	 *	
	 *	\~russian
	 *	\brief Конструктор объекта логгера
	 *	
	 *	Создаёт новый логгер. Категория лога определяется переданным JSON. Это должна быть строка
	 *	JSON с названием категории.
	 *	\param json Строка JSON, определяющая категорию лога.
	 *	\throw std::invalid_argument Переданный JSON неправильный.
	 */
	Log(const std::shared_ptr<json::Element> json);

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
	virtual ~Log();

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

			/* METHODS */

	/**
	 *	\~english
	 *	\brief Enables debug mode
	 *	
	 *	Enables debug mode. If debug mode is enabled, debug messages (`d()` method) are logged.
	 *	
	 *	\~russian
	 *	\brief Активирует режим отладки
	 *	
	 *	Активирует режим отладки. Если режим отладки активирован, отладочные сообщения (метод
	 *	`d()`) сохраняются.
	 */
	static void enable_debug_mode() noexcept;

	/**
	 *	\~english
	 *	\brief Disables debug mode
	 *
	 *	Disables debug mode. If debug mode is disabled, debug messages (`d()` method) are ignored.
	 *
	 *	\~russian
	 *	\brief Деактивирует режим отладки
	 *
	 *	Деактивирует режим отладки. Если режим отладки деактивирован, отладочные сообщения (метод
	 *	`d()`) игнорируются.
	 */
	static void disable_debug_mode() noexcept;

	/**
	 *	\~english
	 *	\brief Checks whether debug mode is enabled
	 *	
	 *	Checks whether debug mode is enabled. If it is, debug messages (`d()` method) are logged.
	 *	\return `true` if debug mode is enabled, `false` otherwise.
	 *	
	 *	\~russian
	 *	\brief Проверяет, активирован ли режим отладки. Если да, отладочные сообщения (метод
	 *	`d()`), сохраняются.
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
	void d(const String& message);

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
	void i(const String& message);

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
	void w(const String& message);

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
	void e(const String& message);
private:
	String name_;
	
	/* lazy */ static bool& debug_mode_() noexcept;
	/* lazy */ static std::mutex& log_file_mtx_() noexcept;
	/* lazy */ static std::wofstream& log_file_();

	void log_(const String& type, const String& message);
	void open_();

	static int object_counter_;
};

/**
 *	\}
 */

}