    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Lang.h                      //
////////////////////////////////////////

//   \_____/     ***     SnowFlake            *****  *           *                               //
//   /\___/\    *   *                         *      *           *                               //
//  / /\ /\ \   *      ****    ***   *     *  *      *    ****   *  *   ***                      //
// =====X=====   ***   *   *  *   *  *     *  *****  *   *   *   * *   *   *    /**************\ //
//  \ \/_\/ /       *  *   *  *   *  *  *  *  *      *   *   *   **    *****   |*  SnowEngine  *|//
//   \/___\/    *   *  *   *  *   *  * * * *  *      *   *   *   * *   *       |* localization *|//
//   /     \     ***   *   *   ***    *   *   *       *   *** *  *  *   ****   |*    system    *|//

#pragma once

#include "../SnowCat/Log.h"
#include "../Container/Map.h"

namespace snow
{

class Lang
{
public:
	Lang() = delete;

	static const String& get_current_lang();
	static bool set_lang(const String& lang);

	static String get_string(const String& key);

private:
	static String current_lang_;
	static Map<String, String> strings_;
	static Log lang_log_;

};

}
