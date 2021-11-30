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
	Lang();

	const String& get_current_lang();
	bool set_lang(const String& lang);

	String get_string(const String& key);

private:
	String current_lang_;
	Map<String, String> strings_;
	Log lang_log_;

};

}
