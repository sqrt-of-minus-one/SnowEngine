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
 *	\brief The file of the SnowCat logger
 *	
 *	This file contains the definition of the Log class.
 */

#include "../../Object.h"

#include <mutex>

#include "../Types/String.h"

namespace snow
{

/**
 *	\brief The class of the logger
 *	
 *	Every Log object is associated with a log category. Use `config.ini` file to set log directory.
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
	Log(const String& category_name) noexcept;

	/**
	 *	\brief Destructor of the logger
	 *	
	 *	If necessary, closes the log file.
	 */
	virtual ~Log() noexcept;

	/**
	 *	\brief Convert to string
	 *	
	 *	Returns a log category name
	 *	\return A name.
	 */
	virtual String to_string() const noexcept override;

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
	void d(const String& message) noexcept;

	/**
	 *	\brief Log info message
	 *
	 *	Creates an info log entry.
	 *	\param message The log message.
	 */
	void i(const String& message) noexcept;

	/**
	 *	\brief Log warning message
	 *
	 *	Creates a warning log entry.
	 *	\param message The log message.
	 */
	void w(const String& message) noexcept;

	/**
	 *	\brief Log error message
	 *
	 *	Creates an error log entry.
	 *	\param message The log message.
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