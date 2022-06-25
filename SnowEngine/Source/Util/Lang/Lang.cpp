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

#include <filesystem>
#include <fstream>

#include "../Game.h"
#include "../Config.h"

using namespace snow;

		/* Lang: public */

String Lang::to_string() const noexcept
{
	return current_lang_;
}

int Lang::hash_code() const noexcept
{
	return current_lang_.hash_code();
}

const String& Lang::get_current_lang()
{
	return current_lang_;
}

bool Lang::set_lang(const String& lang)
{
	if (lang != current_lang_)
	{
		if (load_table_(Game::config.default_table, lang))
		{
			current_lang_ = lang;
			int error_counter = 0;
			Array<String> tables = strings_.get_keys();
			for (String& i : tables)
			{
				if (i != Game::config.default_table)
				{
					strings_.remove(i);
					if (!load_table_(i, current_lang_))
					{
						error_counter++;
						lang_log_.d(L"Couldn't load the localization table "_s + i + L" while changing the language");
					}
				}
			}
			lang_log_.i(L"The language has been changed to "_s + lang + L". Localization tables that couldn't be loaded: " + util::to_string(error_counter));
			return true;
		}
		else
		{
			lang_log_.e(L"Attempt to change the language to "_s + lang + L". The language hasn't been changed because the file of its default localization table does not exist or cannot be accessed");
			return false;
		}
	}
	else
	{
		lang_log_.i(L"Attempt to change the language to "_s + lang + L", which has already been active");
		return true;
	}
}

bool Lang::load_table(const String& table)
{
	if (!strings_.contains_key(table))
	{
		if (load_table_(table, current_lang_))
		{
			lang_log_.i(L"The localization table "_s + table + L" has been loaded");
			return true;
		}
		else
		{
			lang_log_.e(L"Couldn't load the localization table "_s + table + L" because its file does not exist or cannot be accessed");
			return false;
		}
	}
	else
	{
		lang_log_.i(L"Attempt to load the localization table "_s + table + L", which has already been loaded");
		return true;
	}
}

bool Lang::unload_table(const String& table)
{
	return table != Game::config.default_table && strings_.remove(table);
}

bool Lang::is_table_loaded(const String& table)
{
	return strings_.contains_key(table);
}

String Lang::get_string(const String& key)
{
	int sep_pos = key.find_first(L'.');
	Pair<String, String> pair = split_to_table_key_(key);
	try
	{
		std::unique_ptr<String>& string = strings_[pair.get_first()][pair.get_second()];
		return Object::is_valid(string.get()) ? *string : key;
	}
	catch (std::invalid_argument e)
	{
		return key;
	}
}

bool Lang::is_valid(const String& key)
{
	Pair<String, String> pair = split_to_table_key_(key);
	return strings_.contains_key(pair.get_first()) && strings_[pair.get_first()].contains_key(pair.get_second());
}

		/* Lang: private */

Lang::Lang() :
	current_lang_(L""_s),
	strings_(),
	lang_log_(L"SnowFlake"_s)
{
	set_lang(Game::config.default_lang);
}

bool Lang::load_table_(const String& table, const String& lang)
{
	String file_path = Game::config.lang_path + L'\\' + lang + L'\\' + table + L".lang";
	std::wifstream file(file_path.to_std_string());
	if (file.is_open())
	{
		Table_ t;
		std::wstring line;
		while (std::getline(file, line))
		{
			String line_s(line);
			int pos = line_s.find_first(L':');
			if (pos > 0)
			{
				Pair<String, std::unique_ptr<String>> pair(line_s.substring(0, pos), nullptr);
				pair.set_second(std::make_unique<String>(line_s.substring(pos + 2, line_s.size())));
				t.add(std::move(pair));
			}
		}

		strings_.add(table, std::move(t), true);
		return true;
	}
	else
	{
		return false;
	}
}

Pair<String, String> Lang::split_to_table_key_(const String& key)
{
	int sep_pos = key.find_first(L'.');
	return Pair<String, String>(
		sep_pos <= 0 ? Game::config.default_table : key.substring(0, sep_pos),
		key.substring(math::max(sep_pos + 1, 0), key.size()));
}
