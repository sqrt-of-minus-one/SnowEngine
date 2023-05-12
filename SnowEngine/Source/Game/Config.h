    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Config.h                    //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include "../Math/Vector/Point2.h"
#include "../Util/Types/String.h"

namespace snow
{

namespace json
{
class JsonObject;
}

class Config : public Object
{
public:
			/* CONSTRUCTORS */

	Config(const Config& config);
	Config(Config&& config);
	
			/* METHODS FROM Object */

	virtual String to_string() const override;
	virtual int hash_code() const noexcept override;

			/* METHODS */
	
	void save(const String& name, bool allow_override = false);
	static Config load(const String& name);

			/* FIELDS
				SECTION: default */
	
	String path_log;
	String path_saves;

			/* FIELDS
				SECTION: window */
	
	Point2 window_resolution;
	bool window_fullscreen;
	bool window_resize;
	bool window_titlebar;
	bool window_titlebar_buttons;
	String window_title;

			/* FIELDS
				SECTION: resources */

	double resources_check_period_sec;
	String resources_textures_path;
	String resources_fonts_path;
	String resources_sounds_path;
	String resources_music_path;

			/* FIELDS
				SECTION: chunks */
	
	Point2 chunks_collision_size;
	Point2 chunks_clickable_size;

			/* FIELDS
				SECTION: localization */
	
	String localization_path;
	String localization_default_lang;
	String localization_default_table;

			/* FIELDS
				SECTION: log */
	
	String log_path;

			/* FIELDS
				SECTION: saves */

	String saves_path;

			/* CONSTANTS */

	static const Config DEFAULT;

private:
	Config();

	std::shared_ptr<json::JsonObject> make_json_() const;
}

}
