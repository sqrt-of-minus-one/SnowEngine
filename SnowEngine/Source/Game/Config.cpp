    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Config.cpp                  //
////////////////////////////////////////

#include "Config.h"

#include "../Util/Json/JsonObject.h"

using namespace snow;

		/* Config: public */

Config::Config(const Config& config) :
	window_resolution(config.window_resolution),
	window_fullscreen(config.window_fullscreen),
	window_resize(config.window_resize),
	window_titlebar(config.window_titlebar),
	window_titlebar_buttons(config.window_titlebar_buttons),
	window_title(config.window_title),

	resources_check_period_sec(config.resources_check_period_sec),
	resources_textures_path(config.resources_textures_path),
	resources_fonts_path(config.resources_fonts_path),
	resources_sounds_path(config.resources_sounds_path),
	resources_music_path(config.resources_music_path),

	chunks_collision_size(config.chunks_collision_size),
	chunks_clickable_size(config.chunks_clickable_size),

	localization_path(config.localization_path),
	localization_default_lang(config.localization_default_lang),
	localization_default_table(config.localization_default_table),

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

	resources_check_period_sec(config.resources_check_period_sec),
	resources_textures_path(std::move(config.resources_textures_path)),
	resources_fonts_path(std::move(config.resources_fonts_path)),
	resources_sounds_path(std::move(config.resources_sounds_path)),
	resources_music_path(std::move(config.resources_music_path)),

	chunks_collision_size(config.chunks_collision_size),
	chunks_clickable_size(config.chunks_clickable_size),

	localization_path(std::move(config.localization_path)),
	localization_default_lang(std::move(config.localization_default_lang)),
	localization_default_table(std::move(config.localization_default_table)),

	log_path(std::move(config.log_path)),
	saves_path(std::move(config.saves_path))
{}

String Config::to_string() const
{
	return make_json_()->to_string();
}

int Config::hash_code() const noexcept
{
	return make_json_()->hash_code();
}

void Config::save(const String& name, bool allow_override)
{
	make_json_()->save(name + L".json", allow_override);
}

Config Config::load(const String& name)
{
	std::shared_ptr<json::JsonObject> config_json = std::dynamic_pointer_cast<json::JsonObject>(json::Element::load(name + L".json"));
	if (!config_json)
	{
		throw std::runtime_error("Error while reading the config file");
	}

	std::shared_ptr<json::JsonObject> section = std::dynamic_point_cast<json::JsonObject>(config_json)
}
