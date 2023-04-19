    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Config.cpp                  //
////////////////////////////////////////

#include "Config.h"

#include <fstream>
#include <filesystem>

#include "../Util/Util.h"

using namespace snow;

// Check string: replace " with \"; if string has spaces of tabs, add " to the beginning and the end
inline String check_string_(const String& str)
{
	String tmp = str;
	bool has_sp = false;
	for (int i = 0; i < tmp.size(); i++)
	{
		switch (tmp[i])
		{
		case '"':
		{
			tmp.add(L'\\', i);
			i++;
			break;
		}
		case ' ':
		case '\t':
		{
			has_sp = true;
			break;
		}
		}
	}
	if (has_sp)
	{
		return L"\"" + tmp + L"\"";
	}
	else
	{
		return tmp;
	}
}

Point2 string_to_point_(const String& string, const Point2& default_value)
{
	Point2 ret;
	std::vector<String> parts = string.split(L'x', 2, false);
	try
	{
		if (parts.size() < 2)
		{
			return default_value;
		}
		else
		{
			ret.set_x(parts[0].to_int());
			ret.set_y(parts[1].to_int());
			if (ret.get_x() <= 0 || ret.get_y() <= 0)
			{
				return default_value;
			}
			return ret;
		}
	}
	catch (std::invalid_argument e)
	{
		return default_value;
	}
}

		/* Config: public */

String Config::to_string() const
{
	return
		L"[default]"_s +
		L"\nlog_path = " + check_string_(log_path) +
		L"\nsaves_path = " + check_string_(saves_path) +
		L"\n" +
		L"\n[window]" +
		L"\nresolution = " + util::to_string(resolution.get_x()) + L"x" + util::to_string(resolution.get_y()) +
		L"\nfullscreen = " + (fullscreen ? L"true" : L"false") +
		L"\nresize = " + (resize ? L"true" : L"false") +
		L"\ntitlebar = " + (titlebar ? L"true" : L"false") +
		L"\ntitlebar_buttons = " + (titlebar_buttons ? L"true" : L"false") +
		L"\ntitle = " + check_string_(title) +
		L"\n" +
		L"\n[resources]" +
		L"\nres_check_period_sec = " + util::to_string(res_check_period_sec) +
		L"\nres_textures_path = " + check_string_(res_textures_path) +
		L"\nres_fonts_path = " + check_string_(res_fonts_path) +
		L"\nres_sounds_path = " + check_string_(res_sounds_path) +
		L"\nres_music_path = " + check_string_(res_music_path) +
		L"\n" +
		L"\n[chunks]" +
		L"\ncollision_chunk_size = " + util::to_string(collision_chunk_size.get_x()) + L"x" + util::to_string(collision_chunk_size.get_y()) +
		L"\nclickable_chunk_size = " + util::to_string(clickable_chunk_size.get_x()) + L"x" + util::to_string(clickable_chunk_size.get_y()) +
		L"\n" +
		L"\n[localization]" +
		L"\nlang_path = " + check_string_(lang_path) +
		L"\ndefault_lang = " + check_string_(default_lang) +
		L"\ndefault_table = " + check_string_(default_table);
}

int Config::hash_code() const noexcept
{
	return log_path.hash_code() - saves_path.hash_code() + lang_path.hash_code() - default_lang.hash_code() + resolution.hash_code() -
		static_cast<int>(fullscreen) + static_cast<int>(resize) - static_cast<int>(titlebar) + static_cast<int>(titlebar_buttons) -
		title.hash_code();
}

void Config::save()
{
	std::wofstream file(L"config.ini");
	file << L"[default]"_s <<
		L"\nlog_path = " << check_string_(log_path) <<
		L"\nsaves_path = " << check_string_(saves_path) <<
		L"\n" <<
		L"\n[window]" <<
		L"\nresolution = " << util::to_string(resolution.get_x()) << L"x" << util::to_string(resolution.get_y()) <<
		L"\nfullscreen = " << (fullscreen ? L"true" : L"false") <<
		L"\nresize = " << (resize ? L"true" : L"false") <<
		L"\ntitlebar = " << (titlebar ? L"true" : L"false") <<
		L"\ntitlebar_buttons = " << (titlebar_buttons ? L"true" : L"false") <<
		L"\ntitle = " << check_string_(title) <<
		L"\n" <<
		L"\n[resources]" <<
		L"\nres_check_period_sec = " << util::to_string(res_check_period_sec) <<
		L"\nres_textures_path = " << check_string_(res_textures_path) <<
		L"\nres_fonts_path = " << check_string_(res_fonts_path) <<
		L"\nres_sounds_path = " << check_string_(res_sounds_path) <<
		L"\nres_music_path = " << check_string_(res_music_path) <<
		L"\n" <<
		L"\n[chunks]" <<
		L"\ncollision_chunk_size = " << util::to_string(collision_chunk_size.get_x()) << L"x" << util::to_string(collision_chunk_size.get_y()) <<
		L"\nclickable_chunk_size = " << util::to_string(clickable_chunk_size.get_x()) << L"x" << util::to_string(clickable_chunk_size.get_y()) <<
		L"\n" <<
		L"\n[localization]" <<
		L"\nlang_path = " << check_string_(lang_path) <<
		L"\ndefault_lang = " << check_string_(default_lang) <<
		L"\ndefault_table = " << check_string_(default_table) <<
		std::endl;
	file.close();
}

void Config::load()
{
	std::wifstream file(L"config.ini");
	std::wstring category;
	std::wstring str;
	int line = 0; // Line number
	while (std::getline(file, str))
	{
		line++;
		std::wstring field, value;
		bool is_now_value = false; // True if we are reading value now
		bool inside_quot = false; // True if what we are reading now is inside ""
		unsigned int i;
		for (i = 0; i < str.length(); i++)
		{
			switch (str[i])
			{
			case L';':
			case L'#':
			{
				if (!inside_quot)
				{
					// If we're not inside "", it's a comment. Skip it
					goto end_loop; // Yes, goto is bad, but...
				}
				break;
			}
			case L'=':
			{
				if (!is_now_value)
				{
					// After = a value begins
					is_now_value = true;
					continue;
				}
				break;
			}
			case L'"':
			{
				if (is_now_value)
				{
					inside_quot = !inside_quot;
					continue;
				}
				break;
			}
			case L'\\':
			{
				if (is_now_value && i + 1 < str.length() - 1 && str[i + 1] == L'"')
				{
					// Characters \" can be used to write " inside value
					i++;
				}
				break;
			}
			case L' ':
			case L'\t':
			{
				if (!inside_quot)
				{
					// Ignore spaces outside ""
					continue;
				}
				break;
			}
			}
			if (is_now_value)
			{
				value.push_back(str[i]);
			}
			else
			{
				field.push_back(str[i]);
			}
		}
end_loop:;
		if (!field.empty())
		{
			if (field.front() == L'[' && field.back() == L']')
			{
				// The category name is inside []
				category = field;
			}
			else if (!value.empty())
			{
				if (category == L"[default]")
				{
					if (field == L"log_path")
					{
						while (value.back() == L'\\' || value.back() == L'/')
						{
							value.pop_back();
						}
						log_path = value;
					}
					else if (field == L"saves_path")
					{
						while (value.back() == L'\\' || value.back() == L'/')
						{
							value.pop_back();
						}
						saves_path = value;
					}
				}
				else if (category == L"[window]")
				{
					if (field == L"resolution")
					{
						resolution = string_to_point_(value, Point2(800, 600));
					}
					else if (field == L"fullscreen")
					{
						fullscreen = (value == L"true" || value == L"1");
					}
					else if (field == L"resize")
					{
						resize = (value == L"true" || value == L"1");
					}
					else if (field == L"titlebar")
					{
						titlebar = (value == L"true" || value == L"1");
					}
					else if (field == L"titlebar_buttons")
					{
						titlebar_buttons = (value == L"true" || value == L"1");
					}
					else if (field == L"title")
					{
						title = value;
					}
				}
				else if (category == L"[resources]")
				{
					if (field == L"res_check_period_sec")
					{
						try
						{
							res_check_period_sec = String(value).to_double();
						}
						catch (std::invalid_argument e)
						{
							res_check_period_sec = 300.;
						}
					}
					if (field == L"res_textures_path")
					{
						while (value.back() == L'\\' || value.back() == L'/')
						{
							value.pop_back();
						}
						res_textures_path = value;
					}
					else if (field == L"res_fonts_path")
					{
						while (value.back() == L'\\' || value.back() == L'/')
						{
							value.pop_back();
						}
						res_fonts_path = value;
					}
					else if (field == L"res_sounds_path")
					{
						while (value.back() == L'\\' || value.back() == L'/')
						{
							value.pop_back();
						}
						res_sounds_path = value;
					}
					else if (field == L"res_music_path")
					{
						while (value.back() == L'\\' || value.back() == L'/')
						{
							value.pop_back();
						}
						res_music_path = value;
					}
				}
				else if (category == L"[chunks]")
				{
					if (field == L"collision_chunk_size")
					{
						collision_chunk_size = string_to_point_(value, Point2(1500, 1500));
					}
					if (field == L"clickable_chunk_size")
					{
						clickable_chunk_size = string_to_point_(value, Point2(1500, 1500));
					}
				}
				else if (category == L"[localization]")
				{
					if (field == L"lang_path")
					{
						while (value.back() == L'\\' || value.back() == L'/')
						{
							value.pop_back();
						}
						lang_path = value;
					}
					else if (field == L"default_lang")
					{
						default_lang = value;
					}
					else if (field == L"default_table")
					{
						default_table = value;
					}
				}
			}
		}
	}
	file.close();
}

		/* Config: private */

Config::Config() :
		// default
	log_path(L"Logs"_s),
	saves_path(L"Saves"_s),
		// window
	resolution(800, 600),
	fullscreen(false),
	resize(true),
	titlebar(true),
	titlebar_buttons(true),
	title(L"The Game (powered by SnowEngine)"),
		// resources
	res_check_period_sec(300.),
	res_textures_path(L"Resources\\Textures"),
	res_fonts_path(L"Resources\\Fonts"),
	res_sounds_path(L"Resources\\Sounds"),
	res_music_path(L"Resources\\Music"),
		// chunks
	collision_chunk_size(1500, 1500),
	clickable_chunk_size(500, 500),
		// localization
	lang_path(L"Localization"_s),
	default_lang(L"en_UK"_s),
	default_table(L"default"_s)
{
	if (!std::filesystem::exists(L"config.ini"))
	{
		save();
	}
	else
	{
		load();
	}

	if (!std::filesystem::exists(saves_path.to_std_string()))
	{
		std::filesystem::create_directories(saves_path.to_std_string());
	}

	String default_lang_path = lang_path + L'\\' + default_lang;
	if (!std::filesystem::exists(default_lang_path.to_std_string()))
	{
		std::filesystem::create_directories(default_lang_path.to_std_string());
	}
	if (!std::filesystem::exists((default_lang_path + L'\\' + default_table + L".lang").to_std_string()))
	{
		std::wofstream file((default_lang_path + L'\\' + default_table + L".lang").to_std_string());
		file << (default_lang == L"en_UK" ? L"lang.name: English (United Kingdom)" : L"lang.name: Unnamed language") << std::endl <<
			L"lang.code: " << default_lang.to_std_string() << std::endl <<
			L"lang.test: Hello World!" << std::endl;
		file.close();
	}
}
