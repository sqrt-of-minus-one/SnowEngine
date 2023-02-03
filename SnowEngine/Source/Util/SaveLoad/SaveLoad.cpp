    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: SaveLoad.cpp                //
////////////////////////////////////////

//****__ __*****/===\******\SnowFall/***********||===|********** /| ** /| ***********************//
//**_/  V  \_***||   ***************************||    ********** || ** || ***********************//
//**\__^_^__/***||   ***************************||    ********** || ** || ***********************//
//** *  *  * ***\===\**||==\***/=\***||     ||**||===|***/==| ** || ** || ********/==============//
//**  *  *   ***   ||**||  |**|| ||**||     ||**||    **|| || ** || ** || *******||* SnowEngine *//
//**   *  *  ***   ||**||  |**|| ||**\\ /^\ //**||    **|| || ** || ** || *******||*   saving   *//
//**    *  * ***\===/**||  |***\=/****\V/ \V/***||    ***\==\_**_||_**_||_*******||*   system   *//

#include "SaveLoad.h"

#include "String.h"
#include "../../Game/Config.h"
#include "../../Game/Game.h"

#include <filesystem>
#include <fstream>

using namespace snow;

		/* SaveLoad: public */

std::list<String> SaveLoad::get_saves()
{
	std::list<String> ret;
	for (const auto& i : std::filesystem::recursive_directory_iterator(Game::config.saves_path.to_std_string()))
	{
		String path = i.path().wstring();
		int s = path.size();
		// Only .sav files are considered
		if (path[s - 4] == L'.' && path[s - 3] == L's' && path[s - 2] == L'a' && path[s - 1] == L'v')
		{
			path.remove(s - 4, s);
			path.remove(0, Game::config.saves_path.size() + 1);
			ret.emplace_back(path);
		}
	}
	return ret;
}

bool SaveLoad::remove_save(const String& name, bool do_backup)
{
	std::wstring path = (Game::config.saves_path + L"\\" + name).to_std_string();
	if (std::filesystem::exists(path + L".sav"))
	{
		if (do_backup)
		{
			std::filesystem::rename(path + L".sav", path + L".tmp");
		}
		else
		{
			std::filesystem::remove(path + L".sav");
		}
	}
	else
	{
		return false;
	}
}

bool SaveLoad::exist(const String& name)
{
	return std::filesystem::exists((Game::config.saves_path + L"\\" + name + L".sav").to_std_string());
}

bool SaveLoad::save(const String& save_name, const std::map<String, String>& data, bool do_backup)
{
	std::wstring path = (Game::config.saves_path + L"\\" + save_name).to_std_string();
	if (std::filesystem::exists(path + L".sav") && do_backup)
	{
		std::filesystem::rename(path + L".sav", path + L".tmp");
	}
	std::wofstream file(path + L".sav", std::ios_base::trunc);
	if (file.is_open())
	{
		for (const auto& [key, value] : data)
		{
			String k = key;
			String v = value;
			for (int i = 0; i < k.size(); i++)
			{
				if (k[i] == L'\\' || k[i] == L'"')
				{
					k.add(L'\\', i++);
				}
				else if (k[i] == L'\n')
				{
					k.add(L'\\', i++);
					k[i] = L'n';
				}
			}
			for (int i = 0; i < v.size(); i++)
			{
				if (v[i] == L'\\' || v[i] == L'"')
				{
					v.add(L'\\', i++);
				}
				else if (v[i] == L'\n')
				{
					v.add(L'\\', i++);
					v[i] = L'n';
				}
			}
			file << String::format(L"\"%s\": \"%s\"\n"_s, k, v);
		}
		file.close();
		return true;
	}
	else
	{
		return false;
	}
}

std::map<String, String> SaveLoad::load(const String& save_name)
{
	std::map<String, String> res;
	std::wifstream file((Game::config.saves_path + L"\\" + save_name + L".sav").to_std_string());
	if (file.is_open())
	{
		std::wstring line;
		while (std::getline(file, line))
		{
			String l(line);
			int mid = l.find_first(L"\": \"");
			String a = l.substring(1, mid);
			String b = l.substring(mid + 4, l.size() - 1);
			for (int i = 0; i < a.size() - 1; i++)
			{
				if (a[i] == L'\\')
				{
					if (a[i + 1] == L'\\')
					{
						a.remove(i);
					}
					else if (a[i + 1] == L'"')
					{
						a.remove(i);
					}
					else if (a[i + 1] == L'n')
					{
						a.remove(i);
						a[i] = L'\n';
					}
				}
			}
			for (int i = 0; i < b.size() - 1; i++)
			{
				if (b[i] == L'\\')
				{
					if (b[i + 1] == L'\\')
					{
						b.remove(i);
					}
					else if (b[i + 1] == L'"')
					{
						b.remove(i);
					}
					else if (b[i + 1] == L'n')
					{
						b.remove(i);
						b[i] = L'\n';
					}
				}
			}
			res.insert(std::pair<String, String>(a, b));
		}
		return res;
	}
	else
	{
		throw std::runtime_error("The save file does not exist or cannot be accessed");
	}
}
