    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SaveManager.cpp             //
////////////////////////////////////////

//****__ __****   /===\     \SnowFall/           ||===|           /|    /|                      //
//**_/  V  \_**   ||                             ||               ||    ||                      //
//**\__^_^__/**   ||                             ||               ||    ||                      //
//** *  *  * **   \===\ ||==\   /=\   ||     ||  ||===|   /==|    ||    ||       /==============//
//**  *  *   **      || ||  |  || ||  ||     ||  ||      || ||    ||    ||      ||* SnowEngine *//
//**   *  *  **      || ||  |  || ||  \\ /^\ //  ||      || ||    ||    ||      ||*   saving   *//
//**    *  * **   \===/ ||  |   \=/    \V/ \V/   ||       \==\_  _||_  _||_     ||*   system   *//

#include "SaveManager.h"

#include "String.h"
#include "../../Game/ConfigManager.h"
#include "../Log/LogManager.h"
#include "../../Game/Game.h"

#include <fstream>

using namespace snow;

		/* SaveManager: public */

SaveManager& SaveManager::get_instance()
{
	static SaveManager save_load;
	return save_load;
}

String SaveManager::to_string() const
{
	return L"SaveManager, path: "_s + CURRENT_CONFIG.saves_path.wstring();
}

std::shared_ptr<json::Element> SaveManager::to_json() const
{
	std::shared_ptr<json::JsonObject> result = std::make_shared<json::JsonObject>();
	result->get_content().insert({ L"path"_s, util::to_json(CURRENT_CONFIG.saves_path) });
	std::shared_ptr<json::Array> array = std::make_shared<json::Array>();
	std::set<String> saves = get_saves();
	for (const String& i : saves)
	{
		array->get_content().push_back(i.to_json());
	}
	result->get_content().insert({ L"saves"_s, array });
	return result;
}

std::set<String> SaveManager::get_saves() const
{
	const Path& path = CURRENT_CONFIG.saves_path;
	String path_string = path.wstring();
	std::set<String> result;
	for (const auto& i : std::filesystem::recursive_directory_iterator(path))
	{
		String file_path = i.path().wstring();
		int s = file_path.size();
		// Only .json files are considered
		if (file_path.substring(s - 5, s).to_lower() == L".json")
		{
			result.insert(file_path.substring(path_string.size() + 1, s - 5));
		}
	}
	return result;
}

bool SaveManager::remove_save(const String& name, bool do_backup)
{
	Path path = CURRENT_CONFIG.saves_path;
	if (!std::filesystem::exists(path / (name + L".json").to_std_string()))
	{
		LOG_I(SAVE_LOG, L"Attempt to remove the \""_s + name + L"\" save, which does not exist");
		return false;
	}

	if (do_backup)
	{
		std::filesystem::rename(
			path / (name + L".json").to_std_string(),
			path / (L'~' + name + L".json").to_std_string());
		LOG_I(SAVE_LOG, L"The \""_s + name + L"\" save has been removed (a backup has been created)");
	}
	else
	{
		std::filesystem::remove(path / (name + L".json").to_std_string());
		LOG_I(SAVE_LOG, L"The \""_s + name + L"\" save has been removed");
	}
	return true;
}

bool SaveManager::exists(const String& name) const
{
	return std::filesystem::exists(CURRENT_CONFIG.saves_path / (name + L".json").to_std_string());
}

bool SaveManager::save(const String& name, std::shared_ptr<const json::Element> data, bool do_backup)
{
	if (name.get_first() == L'~' && !data)
	{
		return false;
	}

	Path path = CURRENT_CONFIG.saves_path;
	if (std::filesystem::exists(path / (name + L".json").to_std_string()) && do_backup)
	{
		std::filesystem::rename(
			path / (name + L".json").to_std_string(),
			path / (L'~' + name + L".json").to_std_string());
		LOG_I(SAVE_LOG, L"The \""_s + name + L"\" save is going to be created. The old save with the save name has been backed up");
	}
	data->save(path / (name + L".json").to_std_string(), true);
	LOG_I(SAVE_LOG, L"The \""_s + name + L"\" save has been created");
	return true;
}

std::shared_ptr<json::Element> SaveManager::load(const String& name)
{
	LOG_D(SAVE_LOG, L"The \""_s + name + L"\" save is going to be loaded");
	return json::Element::load(CURRENT_CONFIG.saves_path / (name + L".json").to_std_string());
}

const String SaveManager::SAVE_LOG = L"SnowFall";
