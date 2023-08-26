    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: LangManager.cpp             //
////////////////////////////////////////

//   \_____/     ***     SnowFlake            *****  *           *                               //
//   /\___/\    *   *                         *      *           *                               //
//  / /\ /\ \   *      ****    ***   *     *  *      *    ****   *  *   ***                      //
// =====X=====   ***   *   *  *   *  *     *  *****  *   *   *   * *   *   *     **************  //
//  \ \/_\/ /       *  *   *  *   *  *  *  *  *      *   *   *   **    *****    *  SnowEngine  * //
//   \/___\/    *   *  *   *  *   *  * * * *  *      *   *   *   * *   *        * localization * //
//   /     \     ***   *   *   ***    *   *   *       *   *** *  *  *   ****    *    system    * //

#include "LangManager.h"

#include <filesystem>
#include <fstream>

#include "../../Game/Game.h"
#include "../../Game/ConfigManager.h"
#include "../Util.h"
#include "../../Math/Math.h"
#include "../Log/LogManager.h"
#include "../Json/JsonObject.h"
#include "../Json/Value.h"

using namespace snow;

		/* LangManager: public */

LangManager& LangManager::get_instance()
{
	static LangManager lang;
	return lang;
}

const String& LangManager::get_current_lang() noexcept
{
	return current_lang_;
}

void LangManager::set_lang(const String& lang)
{
	if (lang == current_lang_)
	{
		LOG_I(LANG_LOG_, L"Attempt to change the language to "_s + lang + L", which is already active");
		return;
	}

	load_table_(CURRENT_CONFIG.lang_default_table, lang, CURRENT_CONFIG.lang_path);
	
	current_lang_ = lang;
	int errors = reload_(CURRENT_CONFIG.lang_path);
	LOG_I(LANG_LOG_, L"The language has been changed to "_s + lang);
	if (errors > 0)
	{
		LOG_E(LANG_LOG_, L"Couldn't load some localization tables ("_s + errors + L") while changing the language");
	}
}

void LangManager::load_table(const String& table, bool reload)
{
	if (is_table_loaded(table) && !reload)
	{
		LOG_I(LANG_LOG_, L"Attempt to load the localization table \""_s + table + L"\" for " + current_lang_ + L", which has already been loaded");
		return;
	}

	load_table_(table, current_lang_, CURRENT_CONFIG.lang_path);
	LOG_I(LANG_LOG_, L"The localization table \""_s + table + L"\" for " + current_lang_ + L" has been loaded");
}

bool LangManager::unload_table(const String& table)
{
	return table != CURRENT_CONFIG.lang_default_table && static_cast<bool>(strings_.erase(table.to_std_string()));
}

int LangManager::unload_all_tables()
{
	int count = strings_.size() - 1;
	Table_ def_table = std::move(strings_.at(CURRENT_CONFIG.lang_default_table.to_std_string()));
	strings_.clear();
	strings_.insert({ CURRENT_CONFIG.lang_default_table.to_std_string(), std::move(def_table) });
	return count;
}
bool LangManager::is_table_loaded(const String& table)
{
	return strings_.find(table.to_std_string()) != strings_.end();
}

std::set<String> LangManager::get_loaded_tables() const
{
	std::set<String> result;
	for (const auto& [k, v] : strings_)
	{
		result.insert(String(k));
	}
	return result;
}


String LangManager::get_string(const String& key, bool allow_loading)
{
	std::pair<String, String> pair = key_to_table_and_id(key);
	return get_string(pair.first, pair.second, allow_loading);
}

String LangManager::get_string(const String& table, const String& id, bool allow_loading)
{
	if (!is_table_loaded(table) && allow_loading)
	{
		try
		{
			load_table(table);
		}
		catch (...)
		{
			return table + L'.' + id;
		}
	}

	auto table_iter = strings_.find(table.to_std_string());
	if (table_iter == strings_.end())
	{
		return table + L'.' + id;
	}

	auto str_iter = table_iter->second.find(id.to_std_string());
	if (str_iter == table_iter->second.end())
	{
		return table + L'.' + id;
	}
	return str_iter->second;
}

bool LangManager::is_valid(const String& key, bool allow_loading)
{
	std::pair<String, String> pair = key_to_table_and_id(key);
	return is_valid(pair.first, pair.second, allow_loading);
}

bool LangManager::is_valid(const String& table, const String& id, bool allow_loading)
{
	if (!is_table_loaded(table) && allow_loading)
	{
		try
		{
			load_table(table);
		}
		catch (...)
		{
			return false;
		}
	}

	auto table_iter = strings_.find(table.to_std_string());
	if (table_iter == strings_.end())
	{
		return false;
	}
	return table_iter->second.find(id.to_std_string()) != table_iter->second.end();
}

std::pair<String, String> LangManager::key_to_table_and_id(const String& key)
{
	if (!key.is_empty() && key != L'.')
	{
		int dot_pos = key.find_first(L'.');
		if (dot_pos < 0 || dot_pos >= key.size() - 1) // No dot or it's the last character
		{
			return { CURRENT_CONFIG.lang_default_table, key };
		}
		else if (dot_pos == 0) // Dot is the first character
		{
			return { CURRENT_CONFIG.lang_default_table, key.substring(1, key.size() - 1) };
		}
		else // Dot is in the middle of the string
		{
			return { key.substring(0, dot_pos), key.substring(dot_pos + 1, key.size() - 1) };
		}
	}
	else
	{
		return { L""_s, L""_s };
	}
}

		/* LangManager: private */

LangManager::LangManager() :
	current_lang_(),
	strings_()
{
	set_lang(CURRENT_CONFIG.lang_default_lang);
	ConfigManager::get_instance().on_changed_lang_path.bind<LangManager>(*this, &LangManager::change_path_);
	ConfigManager::get_instance().on_changed_lang_default_table.bind<LangManager>(*this, &LangManager::change_default_table_);
}

void LangManager::load_table_(const String& table, const String& lang, const Path& path)
{
	std::shared_ptr<json::JsonObject> json = std::dynamic_pointer_cast<json::JsonObject>(
		json::Element::load(path / lang.to_std_string() / (table + L".json").to_std_string()));
	if (!json)
	{
		throw std::invalid_argument("Couldn't load a localization table: the JSON in the file must be an object");
	}

	Table_ t;
	for (const auto& [k, v] : json->get_content())
	{
		t.insert({ k.to_std_string(), util::json_to_string(v) });
	}
	strings_.erase(table.to_std_string());
	strings_.insert({ table.to_std_string(), std::move(t) });
}

int LangManager::reload_(const Path& path)
{
	int error_counter = 0;
	std::set<String> tables = get_loaded_tables();
	unload_all_tables();
	for (const String& i : tables)
	{
		if (i != CURRENT_CONFIG.lang_default_table)
		{
			try
			{
				load_table_(i, current_lang_, path);
			}
			catch (...)
			{
				error_counter++;
				LOG_D(LANG_LOG_, L"Couldn't load the localization table \""_s + i + L"\" for " + current_lang_);
			}
		}
	}
	return error_counter;
}

void LangManager::change_path_(const Config& new_config)
{
	load_table_(new_config.lang_default_table, current_lang_, new_config.lang_path);

	int errors = reload_(new_config.lang_path);
	LOG_I(LANG_LOG_, L"The path of the localization directory has been changed"_s);
	if (errors > 0)
	{
		LOG_E(LANG_LOG_, L"Couldn't load some localization tables ("_s + errors + L") while changing the path");
	}
}

void LangManager::change_default_table_(const Config& new_config)
{
	if (!is_table_loaded(new_config.lang_default_table))
	{
		load_table_(new_config.lang_default_table, current_lang_, new_config.lang_path);
	}
}

const String LangManager::LANG_LOG_ = L"SnowFlake";
