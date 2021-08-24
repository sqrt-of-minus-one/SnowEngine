    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Log.h                       //
////////////////////////////////////////

#pragma once

/**
 *	\file
 *	\brief The file of the logger
 *	
 *	This file contains the definition of the Log class.
 */

#include "../Object.h"

namespace snow
{

/**
 *	\brief The class of the logger
 *	
 *	Every Log object is associated with a log category.
 */
class Log : public Object
{
public:
	
	/**
	 *	\brief Constructor of the log category
	 *	
	 *	Creates a new Log class that is associated with the passed log category.
	 *	\param category_name Log category name.	
	 */
	Log(const std::string& category_name);

	/**
	 *	\brief Destructor of the logger
	 *	
	 *	If necessary, closes the log file.
	 */
	~Log();

	/**
	 *	\brief Convert to string
	 *	
	 *	Returns a log category name
	 *	\return A name.
	 */
	virtual std::string to_string() const noexcept override;

	/**
	 *	\brief Allows to get hash code of the object
	 *
	 *	Returns hash code of the logger.
	 *	\return Hash code of the logger.
	 */
	virtual int hash_code() const noexcept override;

	/**
	 *	\brief Enable debug mode
	 *	
	 *	Enables debug mode. If debug mode is enabled, debug messages (`d()` method) are logged.
	 */
	static void enable_debug_mode() noexcept;

	/**
	 *	\brief Disable debug mode
	 *
	 *	Enables debug mode. If debug mode is disabled, debug messages (`d()` method) are not
	 *	logged.
	 */
	static void disable_debug_mode() noexcept;

	/**
	 *	\brief Whether debug mode is enabled
	 *	
	 *	Checks whether debug mode is enabled. If it is, debug messages (`d()` method) are logged.
	 *	\return `true` if debug mode is enabled, `false` otherwise. Debug mode should be enabled by
	 *	default if project configuration is Debug.
	 */
	static bool is_debug_mode_enabled() noexcept;

	/**
	 *	\brief Log debug message
	 *	
	 *	Creates a debug log entry. It won't be logged if debug mode is disabled.
	 *	\param message The log message.
	 */
	void d(const std::string& message);

	/**
	 *	\brief Log info message
	 *
	 *	Creates an info log entry.
	 *	\param message The log message.
	 */
	void i(const std::string& message);

	/**
	 *	\brief Log warning message
	 *
	 *	Creates a warning log entry.
	 *	\param message The log message.
	 */
	void w(const std::string& message);

	/**
	 *	\brief Log error message
	 *
	 *	Creates an error log entry.
	 *	\param message The log message.
	 */
	void e(const std::string& message);
private:
	std::string name_;
	static bool debug_mode_;
	static int object_counter_;
	static std::ofstream file_;

	static std::string get_time_string_();
	void log_(const std::string& type, const std::string& message);
};

}