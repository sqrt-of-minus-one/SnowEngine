    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Config.cpp                  //
////////////////////////////////////////

#include "Config.h"

#include "ConfigManager.h"
#include "../Util/Log/LogManager.h"
#include "../Util/Json/JsonObject.h"
#include "../Util/Json/Array.h"
#include "../Util/Json/Value.h"

using namespace snow;

#define LOAD_VALUE_(var, from_json, section_name, name)																									\
	try																																					\
	{																																					\
		(var) = (from_json)(section->get_content().at(name));																							\
	}																																					\
	catch (const std::out_of_range& e)																													\
	{																																					\
		config_log_().e(L"The \"" + (section_name) + L"\" section does not contain the \"" + (name) + L"\" field. The default value will be used");	\
	}																																					\
	catch (const std::invalid_argument& e)																												\
	{																																					\
		config_log_().e(L"The \"" + (section_name) + L"\" section contains invalid \"" + (name) + L"\" value. The default value will be used");		\
	}

bool load_section_(Log& log, std::shared_ptr<json::JsonObject> section, std::shared_ptr<json::JsonObject> json, const String& name)
{
	try
	{
		section = std::dynamic_pointer_cast<json::JsonObject>(json->get_content().at(name));
		if (!section)
		{
			throw std::out_of_range("Catch me please, the catch block!");
		}
		return true;
	}
	catch (const std::out_of_range& e)
	{
		log.e(L"Couldn't load the \"" + name + L"\" section of the configuration profile. The default values will be used");
	}
	return false;
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
	saves_path(config.saves_path),

	config_mtx_()
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
	Config(json::Element::load(ConfigManager::get_instance().get_path() / (name + L".json")))
{}

Config::Config(std::shared_ptr<const json::Element> json) :
	Config()
{
	std::shared_ptr<json::JsonObject> config_json = std::dynamic_pointer_cast<json::JsonObject>(json);
	if (!config_json)
	{
		config_log_().e(L"Couldn't create a configuration profile using the provided JSON");
		throw std::invalid_argument("Couldn't create a configuration profile: the passed JSON is not an object");
	}
	const std::map<String, std::shared_ptr<json::Element>>& sections = config_json->get_content();

	std::shared_ptr<json::JsonObject> section;

	if (load_section_(config_log_(), section, config_json, L"window"))
	{
		LOAD_VALUE_(window_resolution,			IntVector2,					L"window",	L"resolution");
		LOAD_VALUE_(window_fullscreen,			util::json_to_bool,		L"window",	L"fullscreen");
		LOAD_VALUE_(window_resize,				util::json_to_bool,		L"window",	L"resize");
		LOAD_VALUE_(window_titlebar,			util::json_to_bool,		L"window",	L"titlebar");
		LOAD_VALUE_(window_titlebar_buttons,	util::json_to_bool,		L"window",	L"titlebar_buttons");
		LOAD_VALUE_(window_title,				util::json_to_string,	L"window",	L"title");
	}
	if(load_section_(config_log_(), section, config_json, L"res"))
	{
		LOAD_VALUE_(res_check_period_sec,		util::json_to_double,	L"res",		L"check_period_sec");
		LOAD_VALUE_(res_textures_path,			util::json_to_path,		L"res",		L"textures_path");
		LOAD_VALUE_(res_fonts_path,				util::json_to_path,		L"res",		L"fonts_path");
		LOAD_VALUE_(res_sounds_path,			util::json_to_path,		L"res",		L"sounds_path");
		LOAD_VALUE_(res_music_path,				util::json_to_path,		L"res",		L"music_path");
	}
	if(load_section_(config_log_(), section, config_json, L"chunks"))
	{
		LOAD_VALUE_(chunks_collision_size,		IntVector2,					L"chunks",	L"collision_size");
		LOAD_VALUE_(chunks_clickable_size,		IntVector2,					L"chunks",	L"clickable_size");
	}
	if(load_section_(config_log_(), section, config_json, L"lang"))
	{
		LOAD_VALUE_(lang_path,					util::json_to_path,		L"lang",		L"path");
		LOAD_VALUE_(lang_default_lang,			util::json_to_string,	L"lang",		L"default_lang");
		LOAD_VALUE_(lang_default_table,			util::json_to_string,	L"lang",		L"default_table");
	}
	if(load_section_(config_log_(), section, config_json, L"log"))
	{
		LOAD_VALUE_(log_path,					util::json_to_path,		L"log",		L"path");
	}
	if(load_section_(config_log_(), section, config_json, L"saves"))
	{
		LOAD_VALUE_(saves_path,					util::json_to_path,		L"saves",		L"path");
	}
}

String Config::to_string() const
{
	return to_json()->to_string();
}

std::shared_ptr<json::Element> Config::to_json() const
{
	std::shared_ptr<json::JsonObject> result = std::make_shared<json::JsonObject>();

	std::shared_ptr<json::JsonObject> window = std::make_shared<json::JsonObject>();
	window->get_content().insert({ L"resolution", util::to_json(window_resolution) });
	window->get_content().insert({ L"fullscreen", util::to_json(window_fullscreen) });
	window->get_content().insert({ L"resize", util::to_json(window_resize) });
	window->get_content().insert({ L"titlebar", util::to_json(window_titlebar) });
	window->get_content().insert({ L"titlebar_buttons", util::to_json(window_titlebar_buttons) });
	window->get_content().insert({ L"title", util::to_json(window_title) });
	result->get_content().insert({ L"window", window });

	std::shared_ptr<json::JsonObject> res = std::make_shared<json::JsonObject>();
	res->get_content().insert({ L"check_period_sec", util::to_json(res_check_period_sec) });
	res->get_content().insert({ L"textures_path", util::to_json(res_textures_path) });
	res->get_content().insert({ L"fonts_path", util::to_json(res_fonts_path) });
	res->get_content().insert({ L"sounds_path", util::to_json(res_sounds_path) });
	res->get_content().insert({ L"music_path", util::to_json(res_music_path) });
	result->get_content().insert({ L"res", res });
	
	std::shared_ptr<json::JsonObject> chunks = std::make_shared<json::JsonObject>();
	chunks->get_content().insert({ L"collision_size", util::to_json(chunks_collision_size) });
	chunks->get_content().insert({ L"clickable_size", util::to_json(chunks_clickable_size) });
	result->get_content().insert({ L"chunks", chunks });

	std::shared_ptr<json::JsonObject> lang = std::make_shared<json::JsonObject>();
	lang->get_content().insert({ L"path", util::to_json(lang_path) });
	lang->get_content().insert({ L"default_lang", util::to_json(lang_default_lang) });
	lang->get_content().insert({ L"default_table", util::to_json(lang_default_table) });
	result->get_content().insert({ L"lang", lang });
	
	std::shared_ptr<json::JsonObject> log = std::make_shared<json::JsonObject>();
	log->get_content().insert({ L"path", util::to_json(log_path) });
	result->get_content().insert({ L"log", log });
	
	std::shared_ptr<json::JsonObject> saves = std::make_shared<json::JsonObject>();
	saves->get_content().insert({ L"path", util::to_json(saves_path) });
	result->get_content().insert({ L"saves", saves });

	return result;
}

void Config::save(const String& name, bool allow_override) const
{
	to_json()->save(ConfigManager::get_instance().get_path() / (name + L".json"), allow_override);
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
	res_textures_path(L"Resources/Textures"),
	res_fonts_path(L"Resources/Fonts"),
	res_sounds_path(L"Resources/Sounds"),
	res_music_path(L"Resources/Music"),

	chunks_collision_size(1500, 1500),
	chunks_clickable_size(500, 500),

	lang_path(L"Localization"),
	lang_default_lang(L"en_UK"),
	lang_default_table(L"default"),

	log_path(L"Logs"),
	saves_path(L"Saves")
{}

		/* Config: private */

const String Config::CONFIG_LOG_ = L"Config";
