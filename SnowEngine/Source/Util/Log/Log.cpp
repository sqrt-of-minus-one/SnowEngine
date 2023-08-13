    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Log.cpp                     //
////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////SnowCat//////////////////
////// \// \////////     ///   ///  ///    //  ///   ///  ///    //   //         ////////////////
/////       ///////  //////    //  //  //  //  //    //  //  /////    /////  //////////////////////
////  o   o  //////    ///  /  /  //  //  ///  /  /  /  //  /////  =  ////  /////////////////////
////    0    ////////  //  //    //  //  ////    //    //  /////      ///  ////   SnowEngine   ////
/////  / \  ////     ///  ///   ///    //////   ///   ///    //  ///  //  //// logging system ///
///////////////////////////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS

#include "Log.h"

#include "LogManager.h"
#include "../Json/Value.h"

using namespace snow;

		/* Log: public */

Log::Log(const String& category_name) :
	name_(category_name)
{}

Log::Log(const std::shared_ptr<json::Element> json) :
	name_(util::json_to_string(json))
{}

String Log::to_string() const
{
	return name_;
}

std::shared_ptr<json::Element> Log::to_json() const
{
	return name_.to_json();
}

void Log::d(const String& message)
{
	LogManager::get_instance().d(*this, message);
}

void Log::i(const String& message)
{
	LogManager::get_instance().i(*this, message);
}

void Log::w(const String& message)
{
	LogManager::get_instance().w(*this, message);
}

void Log::e(const String& message)
{
	LogManager::get_instance().e(*this, message);
}
