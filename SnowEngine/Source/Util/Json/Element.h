    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Element.h                   //
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
 *	\brief The file with `Element` class
 *	
 *	This file containt the definition of the `Element` class of SnowStorm system.
 *	
 *	\~russian
 *	\brief Файл с классом `Element`
 *	
 *	Этот файл содержит определение класса `Element` системы SnowStorm.
 */

#include "../../Object.h"

namespace snow
{

namespace json
{

class JsonObject;
class Array;

/**
 *	\~english
 *	\brief The type of JSON element
 *	
 *	The enumeration with JSON element types.
 *	
 *	\~russian
 *	\brief Тип элемента JSON
 *	
 *	Перечисление с типами элементов JSON.
 */
enum class EType
{
	OBJECT,			/// \~english JSON object/map \~russian Объект/словарь JSON
	ARRAY,			/// \~english JSON array \~russian Массив JSON
	STRING_VALUE,	/// \~english JSON string value \~russian Строковое значение JSON
	INT_VALUE,		/// \~english JSON integer value \~russian Целочисленное значение JSON
	DOUBLE_VALUE,	/// \~english JSON double value \~russian Вещественное значение JSON
	BOOL_VALUE,		/// \~english JSON boolean value \~russian Булево значение JSON
	NULL_VALUE		/// \~english JSON null value \~russian Нулевое значение JSON
};

/**
 *	\~english
 *	\brief The JSON element
 *	
 *	The base class for all JSON elements: objects, arrays and values. You can convert the string to
 *	JSON element using `from_string()` method. You can also load an element from file using
 *	`load()` method.
 *	
 *	\~russian
 *	\brief Элемент JSON
 *	
 *	Базовый класс для всех элементов JSON: объектов, массивов и значений. Вы можете конвертировать
 *	строку в элемент JSON с помощью метода `from_string()`. Вы можете также загрузить элемент из
 *	файла с помощью метода `load()`.
 */
class Element : public Object
{
public:
			/* METHODS FROM Object */

	/**
	 *	\~english
	 *	\brief Converts the element to string
	 *	
	 *	Creates a string in JSON format representing the element.
	 *	\return The JSON string.
	 *	\sa
	 *	- `from_string()`
	 *	
	 *	\~russian
	 *	\brief Конвертирует элемент в строку
	 *	
	 *	Создаёт строку в формате JSON, представляющую элемент.
	 *	\return JSON-строка.
	 *	\sa
	 *	- `from_string()`
	 */
	virtual String to_string() const override;

			/* METHODS */
	
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
	virtual EType get_type() const = 0;
	
	/**
	 *	\~english
	 *	\brief Saves in the file
	 *	
	 *	Saves the element in the file in JSON format.
	 *	\param filename The path to the file where the element will be saved.
	 *	\throw std::runtime_error The file cannot be created or accessed.
	 *	\sa
	 *	- `load()`
	 *	
	 *	\~russian
	 *	\brief Сохраняет в файл
	 *	
	 *	Сохраняет элемент в файл в формате JSON.
	 *	\param filename Путь к файлу, где элемент будет сохранён.
	 *	\throw std::runtime_error Файл не может быть создан или к нему не удаётся получить доступ.
	 *	\sa
	 *	- `load()`
	 */
	void save(const String& filename) const;

	/**
	 *	\~english
	 *	\brief Puts the element to the stream
	 *	
	 *	Converts the element to JSON format and puts it to the stream.
	 *	\param stream The stream where the element will be put.
	 *	\param nesting Number of tabs to the left of the element (only affects objects).
	 *	\sa
	 *	- `from_stream()`
	 *	
	 *	\~russian
	 *	\brief Помещает элемент в поток
	 *	
	 *	Конвертирует элемент в формат JSON и помещает его в поток.
	 *	\param stream Поток, куда будет помещён элемент.
	 *	\param nesting Количество табуляций слева от элемента (влияет только на объекты).
	 *	\sa
	 *	- `from_stream()`
	 */
	virtual void to_stream(std::wostream& stream, int nesting = 0) const = 0;
	
	/**
	 *	\~english
	 *	\brief Creates the element based on the string
	 *	
	 *	Converts the string to the JSON element.
	 *	\param string The string with JSON.
	 *	\return The unique pointer to the created element.
	 *	\throw std::runtime_error The string is not valid JSON.
	 *	\sa
	 *	- `to_string()`
	 *	
	 *	\~russian
	 *	\brief Создаёт элемент на основе строки
	 *	
	 *	Конвертирует строку в элемент JSON.
	 *	\param string Строка с JSON.
	 *	\return Уникальный указатель на созданный элемент.
	 *	\throw std::runtime_error Строка не является корректным JSON.
	 *	\sa
	 *	- `to_string()`
	 */
	static std::unique_ptr<Element> from_string(const String& string);
	
	/**
	 *	\~english
	 *	\brief Creates the element by loading JSON from file
	 *	
	 *	Loads the file content and creates the JSON element based on it.
	 *	\param filename The path to the file with JSON.
	 *	\return The unique pointer to the created element.
	 *	\throw std::runtime_error The file does not exist, cannot be accessed or doesn't contain a
	 *	valid JSON.
	 *	\sa
	 *	- `save()`
	 *	
	 *	\~russian
	 *	\brief Создаёт элемент, загружая JSON из файла
	 *	
	 *	Загружает содержимое файла и создаёт на его основе элемент JSON.
	 *	\param filename Путь к файлу с JSON.
	 *	\return Уникальный указатель на созданный элемент.
	 *	\throw std::runtime_error Файл не существует, к нему не удаётся получить доступ или он не
	 *	содержит корректный JSON.
	 *	\sa
	 *	- `save()`
	 */
	static std::unique_ptr<Element> load(const String& filename);
	
	/**
	 *	\~english
	 *	\brief Creates the element based on the stream
	 *	
	 *	Reads the stream and converts its content to the JSON element.
	 *	\param stream The stream with JSON.
	 *	\return The unique pointer to the created element.
	 *	\throw std::runtime_error The stream doesn't contain a valid JSON.
	 *	\sa
	 *	- `to_stream()`
	 *	
	 *	\~russian
	 *	\brief Создаёт элемент на основе поток
	 *	
	 *	Конвертирует строку в элемент JSON.
	 *	\param stream Поток с JSON.
	 *	\return Уникальный указатель на созданный элемент.
	 *	\throw std::runtime_error Поток не содержит корректный JSON.
	 *	\sa
	 *	- `to_stream()`
	 */
	static std::unique_ptr<Element> from_stream(std::wistream& stream);
	
private:
	static std::unique_ptr<JsonObject> read_object_(std::wistream& stream); // The { character is supposed to be already read
	static std::unique_ptr<Array> read_array_(std::wistream& stream); // The [ character is supposed to be already read
	static String read_string_(std::wistream& stream, wchar_t first); // The " or ' character is supposed to be already read and is passed as argument (first)
	static std::unique_ptr<Element> read_number_(std::wistream& stream, wchar_t first); // The first character is supposed to be already read and is passed as argument (first)
	static bool read_lit_(std::wistream& stream, const String& lit); // The first character is supposed to be already read; returns false if couldn't read a desired literal (lit)
	static void read_comment_(std::wistream& stream); // The / character is supposed to be already read
	static void pass_(std::wistream& stream, wchar_t& c); // Pass the space characters and comments
};

}

}
