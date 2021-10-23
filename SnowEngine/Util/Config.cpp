    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Config.cpp                  //
////////////////////////////////////////

#include "Config.h"

#include <fstream>

using namespace snow;

void Config::init()
{
	if (!was_init_)
	{
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
							while (value.back() == L'\\' || value.back() == L'/')
							{
								value.pop_back();
							}
							default_lang_ = value;
						}
					}
				}
			}
		}
		file.close();

		was_init_ = true;
	}
}

const String& Config::get_log_path()
{
	return log_path_;
}

const String& Config::get_lang_path()
{
	return lang_path_;
}

const String& Config::get_default_lang()
{
	return default_lang_;
}

bool Config::was_init_(false);

String Config::log_path_(L"Logs");
String Config::lang_path_(L"Localization");
String Config::default_lang_(L"en_UK");
