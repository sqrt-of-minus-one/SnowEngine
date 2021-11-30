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

#include "../Game.h"

#include <filesystem>
#include <fstream>

using namespace snow;

Lang::Lang() :
	current_lang_(L""_s),
	strings_(),
	lang_log_(L"SnowFlake"_s)
{
	set_lang(Game::config.get_default_lang());
}

const String& Lang::get_current_lang()
{
	return current_lang_;
}

bool Lang::set_lang(const String& lang)
{
	if (lang != current_lang_)
	{
		String file_path = Game::config.get_lang_path() + L'\\' + lang + L".lang";
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
	else
	{
		lang_log_.i(L"Attempt to change the language to "_s + lang + L". The language hasn't been changed because the target language is already active"_s);
		return true;
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
