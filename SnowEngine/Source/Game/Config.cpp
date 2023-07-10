    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Config.cpp                  //
////////////////////////////////////////

#include "Config.h"

#include "ConfigManager.h"
#include "../Util/Json/JsonObject.h"
#include "../Util/Json/Array.h"
#include "../Util/Json/Value.h"

using namespace snow;

void format_path_(String& path)
{
	while (path[path.size() - 1] == L'/' || path[path.size() - 1] == L'\\')
	{
		path.remove(path.size() - 1);
	}
}

bool load_section_(std::shared_ptr<json::JsonObject> section, std::shared_ptr<json::JsonObject> json, const String& name)
{
	try
	{
		section = std::dynamic_pointer_cast<json::JsonObject>(json->get_content().at(name));
		if (section)
		{
			return true;
		}
		// Log
	}
	catch (const std::out_of_range& e)
	{
		// Log
	}
	return false;
}

template<typename T>
void load_value_(T& var, std::shared_ptr<json::JsonObject> json, const String& name)
{
	std::shared_ptr<json::snow_::Value_<T>> value;
	try
	{
		value = std::dynamic_pointer_cast<json::snow_::Value_<T>>(json->get_content().at(name));
		if (value)
		{
			var = value->get();
		}
		else
		{
			// Log
		}
	}
	catch (const std::out_of_range& e)
	{
		// Log
	}
}

template<>
void load_value_<Point2>(Point2& var, const std::shared_ptr<json::JsonObject> json, const String& name)
{
	std::shared_ptr<json::Array> value;
	try
	{
		value = std::dynamic_pointer_cast<json::Array>(json->get_content().at(name));

		if (value && value->get_content().size() == 2)
		{
			std::shared_ptr<json::IntValue> x = std::dynamic_pointer_cast<json::IntValue>(value->get_content().at(0));
			std::shared_ptr<json::IntValue> y = std::dynamic_pointer_cast<json::IntValue>(value->get_content().at(1));
			if (x && y)
			{
				var.set_x(x->get());
				var.set_y(y->get());
			}
			else
			{
				// Log
			}
		}
		else
		{
			// Log
		}
	}
	catch (const std::out_of_range& e)
	{
		// Log
	}
}

template<typename T>
void add_(std::shared_ptr<json::JsonObject>& json, const T& var, const String& name)
{
	std::shared_ptr<json::snow_::Value_<T>> value = std::make_shared<json::snow_::Value_<T>>(var);
	json->get_content().insert({ name, value });
}

template<>
void add_<Point2>(std::shared_ptr<json::JsonObject>& json, const Point2& var, const String& name)
{
	std::shared_ptr<json::Array> value = std::make_shared<json::Array>();

	std::shared_ptr<json::IntValue> x = std::make_shared<json::IntValue>(var.get_x());
	std::shared_ptr<json::IntValue> y = std::make_shared<json::IntValue>(var.get_y());
	value->get_content().push_back(x);
	value->get_content().push_back(y);
	json->get_content().insert({ name, value });
}

		/* Config: public */

Config::Config(const Config& config) :
	window_resolution(config.window_resolution),
	window_fullscreen(config.window_fullscreen),
	window_resize(config.window_resize),
	window_titlebar(config.window_titlebar),
	window_titlebar_buttons(config.window_titlebar_buttons),
	window_title(config.window_title),

	res_check_period_sec(config.res_check_period_sec),
	res_textures_path(config.res_textures_path),
	res_fonts_path(config.res_fonts_path),
	res_sounds_path(config.res_sounds_path),
	res_music_path(config.res_music_path),

	chunks_collision_size(config.chunks_collision_size),
	chunks_clickable_size(config.chunks_clickable_size),

	lang_path(config.lang_path),
	lang_default_lang(config.lang_default_lang),
	lang_default_table(config.lang_default_table),

	log_path(config.log_path),
	saves_path(config.saves_path)
{}

Config::Config(Config&& config) :
	window_resolution(config.window_resolution),
	window_fullscreen(config.window_fullscreen),
	window_resize(config.window_resize),
	window_titlebar(config.window_titlebar),
	window_titlebar_buttons(config.window_titlebar_buttons),
	window_title(std::move(config.window_title)),

	res_check_period_sec(config.res_check_period_sec),
	res_textures_path(std::move(config.res_textures_path)),
	res_fonts_path(std::move(config.res_fonts_path)),
	res_sounds_path(std::move(config.res_sounds_path)),
	res_music_path(std::move(config.res_music_path)),

	chunks_collision_size(config.chunks_collision_size),
	chunks_clickable_size(config.chunks_clickable_size),

	lang_path(std::move(config.lang_path)),
	lang_default_lang(std::move(config.lang_default_lang)),
	lang_default_table(std::move(config.lang_default_table)),

	log_path(std::move(config.log_path)),
	saves_path(std::move(config.saves_path))
{}

Config::Config(const String& name) :
	Config(json::Element::load(ConfigManager::get_instance().get_path() + L'\\' + name + L".json")))
{}

Config::Config(std::shared_ptr<const json::Element> json) :
	Config()
{
	std::shared_ptr<json::JsonObject> config_json = std::dynamic_pointer_cast<json::JsonObject>(json));
	if (!config_json)
	{
		// Log
	}
	const std::map<String, std::shared_ptr<json::Element>>& sections = config_json->get_content();

	std::shared_ptr<json::JsonObject> section;

	load_section_(section, config_json, L"window"_s);
	load_value_(window_resolution, section, L"resolution"_s);
	load_value_(window_fullscreen, section, L"fullscreen"_s);
	load_value_(window_resize, section, L"resize"_s);
	load_value_(window_titlebar, section, L"titlebar"_s);
	load_value_(window_titlebar_buttons, section, L"titlebar_buttons"_s);
	load_value_(window_title, section, L"title"_s);

	load_section_(section, config_json, L"res"_s);
	load_value_(res_check_period_sec, section, L"check_period_sec"_s);
	load_value_(res_textures_path, section, L"textures_path"_s);
	load_value_(res_fonts_path, section, L"fonts_path"_s);
	load_value_(res_sounds_path, section, L"sounds_path"_s);
	load_value_(res_music_path, section, L"music_path"_s);

	load_section_(section, config_json, L"chunks"_s);
	load_value_(chunks_collision_size, section, L"collision_size"_s);
	load_value_(chunks_clickable_size, section, L"clickable_size"_s);

	load_section_(section, config_json, L"lang"_s);
	load_value_(lang_path, section, L"path"_s);
	load_value_(lang_default_lang, section, L"default_lang"_s);
	load_value_(lang_default_table, section, L"default_table"_s);

	load_section_(section, config_json, L"log"_s);
	load_value_(log_path, section, L"path"_s);

	load_section_(section, config_json, L"saves"_s);
	load_value_(saves_path, section, L"path"_s);

	format_path_(res_textures_path);
	format_path_(res_fonts_path);
	format_path_(res_sounds_path);
	format_path_(res_music_path);
	format_path_(lang_path);
	format_path_(log_path);
	format_path_(saves_path);
}

String Config::to_string() const
{
	return make_json_()->to_string();
}

std::shared_ptr<json::Element> Config::to_json() const
{
	std::shared_ptr<json::JsonObject> result = std::make_shared<json::JsonObject>();

	std::shared_ptr<json::JsonObject> window = std::make_shared<json::JsonObject>();
	add_(window, window_resolution, L"resolution"_s);
	add_(window, window_fullscreen, L"fullscreen"_s);
	add_(window, window_resize, L"resize"_s);
	add_(window, window_titlebar, L"titlebar"_s);
	add_(window, window_titlebar_buttons, L"titlebar_buttons"_s);
	add_(window, window_title, L"title"_s);
	result->get_content().insert({ L"window"_s, window });

	std::shared_ptr<json::JsonObject> res = std::make_shared<json::JsonObject>();
	add_(res, res_check_period_sec, L"check_period_sec"_s);
	add_(res, res_textures_path, L"textures_path"_s);
	add_(res, res_fonts_path, L"fonts_path"_s);
	add_(res, res_sounds_path, L"sounds_path"_s);
	add_(res, res_music_path, L"music_path"_s);
	result->get_content().insert({ L"res"_s, res });

	std::shared_ptr<json::JsonObject> chunks = std::make_shared<json::JsonObject>();
	add_(res, chunks_collision_size, L"collision_size"_s);
	add_(res, chunks_clickable_size, L"clickable_size"_s);
	result->get_content().insert({ L"chunks"_s, chunks });

	std::shared_ptr<json::JsonObject> lang = std::make_shared<json::JsonObject>();
	add_(res, lang_path, L"path"_s);
	add_(res, lang_default_lang, L"default_lang"_s);
	add_(res, lang_default_table, L"default_table"_s);
	result->get_content().insert({ L"lang"_s, lang });

	std::shared_ptr<json::JsonObject> log = std::make_shared<json::JsonObject>();
	add_(res, log_path, L"path"_s);
	result->get_content().insert({ L"log"_s, log });

	std::shared_ptr<json::JsonObject> saves = std::make_shared<json::JsonObject>();
	add_(res, saves_path, L"path"_s);
	result->get_content().insert({ L"saves"_s, saves });

	return result;
}

void Config::save(const String& name, bool allow_override)
{
	make_json_()->save(ConfigManager::get_instance().get_path() + L"\\" + name + L".json", allow_override);
}

const Config Config::DEFAULT;

		/* Config: private */

Config::Config() :
	window_resolution(800, 600),
	window_fullscreen(false),
	window_resize(true),
	window_titlebar(true),
	window_titlebar_buttons(true),
	window_title(L"The Game (powered by SnowEngine)"),

	res_check_period_sec(300.),
	res_textures_path(L"Resources\\Textures"),
	res_fonts_path(L"Resources\\Fonts"),
	res_sounds_path(L"Resources\\Sounds"),
	res_music_path(L"Resources\\Music"),

	chunks_collision_size(1500, 1500),
	chunks_clickable_size(500, 500),

	lang_path(L"Localization"),
	lang_default_lang(L"en_UK"),
	lang_default_table(L"default"),

	log_path(L"Logs"),
	saves_path(L"Saves")
{}
