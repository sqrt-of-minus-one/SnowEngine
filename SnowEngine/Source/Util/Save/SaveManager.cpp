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
	return L"SaveManager, path: " + CURRENT_CONFIG.saves_path.wstring();
}

std::shared_ptr<json::Element> SaveManager::to_json() const
{
	std::shared_ptr<json::JsonObject> result = std::make_shared<json::JsonObject>();
	result->get_content().insert({ L"path", util::to_json(CURRENT_CONFIG.saves_path) });
	std::shared_ptr<json::Array> array = std::make_shared<json::Array>();
	std::set<String> saves = get_saves();
	for (const String& i : saves)
	{
		array->get_content().push_back(util::to_json(i));
	}
	result->get_content().insert({ L"saves", array });
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
		int s = file_path.length();
		// Only .json files are considered
		if (string::to_lower(file_path.substr(s - 5, 5)) == L".json")
		{
			result.insert(file_path.substr(path_string.length() + 1, s - path_string.length() - 6));
		}
	}
	return result;
}

bool SaveManager::remove_save(const String& name, bool do_backup)
{
	Path path = CURRENT_CONFIG.saves_path;
	if (!std::filesystem::exists(path / (name + L".json")))
	{
		LOG_I(SAVE_LOG, L"Attempt to remove the \"" + name + L"\" save, which does not exist");
		return false;
	}

	if (do_backup)
	{
		std::filesystem::rename(
			path / (name + L".json"),
			path / (L'~' + name + L".json"));
		LOG_I(SAVE_LOG, L"The \"" + name + L"\" save has been removed (a backup has been created)");
	}
	else
	{
		std::filesystem::remove(path / (name + L".json"));
		LOG_I(SAVE_LOG, L"The \"" + name + L"\" save has been removed");
	}
	return true;
}

bool SaveManager::exists(const String& name) const
{
	return std::filesystem::exists(CURRENT_CONFIG.saves_path / (name + L".json"));
}

bool SaveManager::save(const String& name, std::shared_ptr<const json::Element> data, bool do_backup)
{
	if (name.front() == L'~' && !data)
	{
		return false;
	}

	Path path = CURRENT_CONFIG.saves_path;
	if (std::filesystem::exists(path / (name + L".json")) && do_backup)
	{
		std::filesystem::rename(
			path / (name + L".json"),
			path / (L'~' + name + L".json"));
		LOG_I(SAVE_LOG, L"The \"" + name + L"\" save is going to be created. The old save with the save name has been backed up");
	}
	data->save(path / (name + L".json"), true);
	LOG_I(SAVE_LOG, L"The \"" + name + L"\" save has been created");
	return true;
}

std::shared_ptr<json::Element> SaveManager::load(const String& name)
{
	LOG_D(SAVE_LOG, L"The \"" + name + L"\" save is going to be loaded");
	return json::Element::load(CURRENT_CONFIG.saves_path / (name + L".json"));
}

const String SaveManager::SAVE_LOG = L"SnowFall";
