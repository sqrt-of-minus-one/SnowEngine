    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Config.cpp                  //
////////////////////////////////////////

#include "Config.h"

#include <fstream>
#include <filesystem>

using namespace snow;

#define DEFAULT_CONFIG \
L"[default]\n\
log_path = Logs\n\
lang_path = Localization\n\
default_lang = en_UK\n"

inline void check_and_write_(std::wofstream& file, String& str)
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
		file << '"' << tmp << '"';
	}
	else
	{
		file << tmp;
	}
}

Config::Config() :
	// Default values
	log_path(L"Logs"_s),
	lang_path(L"Localization"_s),
	default_lang(L"en_UK"_s)
{
	if (!std::filesystem::exists(L"config.ini"))
	{
		// Create a config file if it doesn't exist
		std::wofstream file(L"config.ini");

		// Default content
		file << DEFAULT_CONFIG;
		file.close();
	}
	else
	{
		load();
	}

	if (!std::filesystem::exists(lang_path.to_std_string()))
	{
		std::filesystem::create_directories(lang_path.to_std_string());
	}
	if (!std::filesystem::exists((lang_path + L'\\' + default_lang + L".lang").to_std_string()))
	{
		std::wofstream file((lang_path + L'\\' + default_lang + L".lang").to_std_string());
		file << L"lang.name: English (United Kingdom)" << std::endl <<
			L"lang.code: " << default_lang.to_std_string() << std::endl <<
			L"lang.test: Hello World!" << std::endl;
		file.close();
	}
}

String Config::to_string() const noexcept
{
	return
		String(L"[default]") +
		L"\nlog_path = " + log_path +
		L"\nlang_path = " + lang_path +
		L"\ndefault_lang = " + default_lang;
}

int Config::hash_code() const noexcept
{
	return log_path.hash_code() - lang_path.hash_code() + default_lang.hash_code();
}

void Config::save()
{
	std::wofstream file(L"config.ini");
	file << L"[default]" << std::endl << "log_path = ";
	check_and_write_(file, log_path);

	file << std::endl << "lang_path = ";
	check_and_write_(file, lang_path);

	file << std::endl << "default_lang = ";
	check_and_write_(file, default_lang);

	file << std::endl;
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
					else if (field == L"lang_path")
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
				}
			}
		}
	}
	file.close();
}
