    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Config.cpp                  //
////////////////////////////////////////

#include "Config.h"

#include <fstream>
#include <filesystem>

using namespace snow;

void Config::init()
{
	if (!was_init_)
	{
		if (!std::filesystem::exists(L"config.ini"))
		{
			std::wofstream file(L"config.ini");
			file <<
L"[default]\n\
log_path = Logs\n\
lang_path = Localization\n\
default_lang = en_UK\n";
			file.close();
		}

		std::wifstream file(L"config.ini");
		std::wstring category;
		std::wstring str;
		int line = 0;
		while (std::getline(file, str))
		{
			line++;
			std::wstring field, value;
			bool is_now_value = false;
			bool inside_quot = false;
			int i;
			for (i = 0; i < str.length(); i++)
			{
				switch (str[i])
				{
				case L';':
				case L'#':
				{
					if (!inside_quot)
					{
						goto end_loop;
					}
					break;
				}
				case L'=':
				{
					if (!is_now_value)
					{
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
						i++;
					}
					break;
				}
				case L' ':
				case L'\t':
				{
					if (!inside_quot)
					{
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
							log_path_ = value;
						}
						else if (field == L"lang_path")
						{
							while (value.back() == L'\\' || value.back() == L'/')
							{
								value.pop_back();
							}
							lang_path_ = value;
						}
						else if (field == L"default_lang")
						{
							default_lang_ = value;
						}
					}
				}
			}
		}
		file.close();

		was_init_ = true;
		if (!std::filesystem::exists(lang_path_.to_std_string()))
		{
			std::filesystem::create_directories(lang_path_.to_std_string());
		}
		if (!std::filesystem::exists((lang_path_ + L'\\' + default_lang_ + L".lang").to_std_string()))
		{
			std::wofstream file((lang_path_ + L'\\' + default_lang_ + L".lang").to_std_string());
			file << L"lang.name: English (United Kingdom)" << std::endl <<
				L"lang.code: " << default_lang_.to_std_string() << std::endl <<
				L"lang.test: Hello World!" << std::endl;
			file.close();
		}
	}
}

const String& Config::get_log_path()
{
	init();
	return log_path_;
}

const String& Config::get_lang_path()
{
	init();
	return lang_path_;
}

const String& Config::get_default_lang()
{
	init();
	return default_lang_;
}

bool Config::was_init_(false);

String Config::log_path_(L"Logs"_s);
String Config::lang_path_(L"Localization"_s);
String Config::default_lang_(L"en_UK"_s);
