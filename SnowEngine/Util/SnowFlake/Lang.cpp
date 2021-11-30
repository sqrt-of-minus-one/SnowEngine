    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Lang.cpp                    //
////////////////////////////////////////

//   \_____/     ***     SnowFlake            *****  *           *                               //
//   /\___/\    *   *                         *      *           *                               //
//  / /\ /\ \   *      ****    ***   *     *  *      *    ****   *  *   ***                      //
// =====X=====   ***   *   *  *   *  *     *  *****  *   *   *   * *   *   *     **************  //
//  \ \/_\/ /       *  *   *  *   *  *  *  *  *      *   *   *   **    *****    *  SnowEngine  * //
//   \/___\/    *   *  *   *  *   *  * * * *  *      *   *   *   * *   *        * localization * //
//   /     \     ***   *   *   ***    *   *   *       *   *** *  *  *   ****    *    system    * //

#include "Lang.h"

#include "../Config.h"

#include <filesystem>
#include <fstream>

using namespace snow;

const String& Lang::get_current_lang()
{
	return current_lang_;
}

bool Lang::set_lang(const String& lang)
{
	String file_path = Config::get_lang_path() + L'\\' + lang + L".lang";
	std::wifstream file(file_path.to_std_string());
	if (file.is_open())
	{
		strings_.clear();
		std::wstring line;
		while (std::getline(file, line))
		{
			String line_s(line);
			int pos = line_s.find_first(L':');
			if (pos > 0)
			{
				strings_.add(line_s.substring(0, pos), line_s.substring(pos + 2, line_s.size()));
			}
		}

		current_lang_ = lang;
		lang_log_.i(L"The language is changed to "_s + lang);
		return true;
	}
	else
	{
		lang_log_.e(L"Attempt to change the language to "_s + lang + L". Failure: the language file does not exist or cannot be accessed"_s);
		return false;
	}
}

String Lang::get_string(const String& key)
{
	try
	{
		return strings_[key];
	}
	catch (std::invalid_argument e)
	{
		return key;
	}
}

String Lang::current_lang_(L""_s);
Map<String, String> Lang::strings_;
Log Lang::lang_log_(L"SnowFlake"_s);
