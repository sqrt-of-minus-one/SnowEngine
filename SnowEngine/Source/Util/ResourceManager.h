    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ResourceManager.h           //
////////////////////////////////////////

#pragma once

#include "../Object.h"

#include <unordered_map>

namespace sf
{
class Texture;
}

namespace snow
{

class ResourceManager : public Object
{
public:
			/* SINGLETON */

	static ResourceManager& get_instance();

			/* METHODS FROM Object */

	virtual String to_string() const override;

	virtual int hash_code() const noexcept override;

			/* METHODS */

	std::shared_ptr<sf::Texture> get_texture(String name);

private:
	ResourceManager();

	void check_resources_();

	std::unordered_map<std::wstring, std::weak_ptr<sf::Texture>> textures_;
};

}
