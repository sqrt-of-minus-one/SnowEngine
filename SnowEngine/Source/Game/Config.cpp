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

		/* Config: public */

String Config::to_string() const
{
	return
		L"[default]"_s +
		L"\nlog_path = " + check_string_(log_path) +
		L"\n" +
		L"\n[window]" +
		L"\nresolution = " + util::to_string(resolution.get_x()) + L"x" + util::to_string(resolution.get_y()) +
		L"\nfullscreen = " + (fullscreen ? L"true" : L"false") +
		L"\nresize = " + (resize ? L"true" : L"false") +
		L"\ntitlebar = " + (titlebar ? L"true" : L"false") +
		L"\ntitlebar_buttons = " + (titlebar_buttons ? L"true" : L"false") +
		L"\ntitle = " + check_string_(title) +
		L"\n" +
		L"\n[localization]" +
		L"\nlang_path = " + check_string_(lang_path) +
		L"\ndefault_lang = " + check_string_(default_lang) +
		L"\ndefault_table = " + check_string_(default_table);
}

int Config::hash_code() const noexcept
{
	return log_path.hash_code() - lang_path.hash_code() + default_lang.hash_code() - resolution.hash_code() +
		static_cast<int>(fullscreen) - static_cast<int>(resize) + static_cast<int>(titlebar) - static_cast<int>(titlebar_buttons) +
		title.hash_code();
}

void Config::save()
{
	std::wofstream file(L"config.ini");
	file << to_string();
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
				}
				else if (category == L"[window]")
				{
					if (field == L"resolution")
					{
						String val = value;
						int x_pos = val.find_first(L'x');
						try
						{
							resolution.set_x(val.substring(0, x_pos).to_int());
							resolution.set_y(val.substring(x_pos + 1, val.size()).to_int());
							if (resolution.get_x() <= 0 || resolution.get_y() <= 0)
							{
								resolution.set_x(800);
								resolution.set_y(600);
							}
						}
						catch (std::invalid_argument e)
						{
							resolution.set_x(800);
							resolution.set_y(600);
						}
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
				else if (category == L"[localization")
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
		// window
	resolution(800, 600),
	fullscreen(false),
	resize(true),
	titlebar(true),
	titlebar_buttons(true),
	title(L"The Game (powered by SnowEngine)"),
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
