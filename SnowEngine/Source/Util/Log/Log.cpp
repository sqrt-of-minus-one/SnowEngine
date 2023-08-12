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

#include <fstream>
#include <iostream>
#include <ctime>
#include <filesystem>

#include "../../Game/Game.h"
#include "../../Game/ConfigManager.h"
#include "../Time/Time.h"
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
