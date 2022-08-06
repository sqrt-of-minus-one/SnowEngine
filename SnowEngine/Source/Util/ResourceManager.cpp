    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: ResourceManager.cpp         //
////////////////////////////////////////

#include "ResourceManager.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>

#include "Types/String.h"
#include "../Game/Game.h"
#include "../Game/Config.h"
#include "Time/TimerManager.h"
#include "Function/Delegate.h"

using namespace snow;

		/* ResourceManager: public */

ResourceManager& ResourceManager::get_instance()
{
	static ResourceManager resource_manager;
	return resource_manager;
}

String ResourceManager::to_string() const
{
	return String::format(L"{ textures: %d }"_s, textures_.size());
}

int ResourceManager::hash_code() const noexcept
{
	int ret = 0;
	int sign = 1;
	for (const auto& i : textures_)
	{
		ret += sign * reinterpret_cast<int>(i.second.lock().get());
		sign = -sign;
	}
	return ret;
}

std::shared_ptr<sf::Texture> ResourceManager::get_texture(String name)
{
	auto iter = textures_.find(name.to_std_string());
	if (iter != textures_.end())
	{
		auto ret = iter->second.lock();
		if (ret)
		{
			return ret;
		}
		else
		{
			textures_.erase(iter);
		}
	}
	std::shared_ptr<sf::Texture> res = std::make_shared<sf::Texture>();
	if (res->loadFromFile(sf::String((Game::config.res_textures_path + L'\\' + name).to_std_string()).toAnsiString()))
	{
		textures_.insert(std::make_pair(name.to_std_string(), res));
		return res;
	}
	else
	{
		return nullptr;
	}
}

		/* ResourceManager: private */

ResourceManager::ResourceManager()
{
	Delegate<void> check_delegate;
	check_delegate.bind<ResourceManager>(*this, &ResourceManager::check_resources_);
	TimerManager::get_instance().create_timer(check_delegate, 300.f, 300.f);
}

void ResourceManager::check_resources_()
{
	for (auto i = textures_.begin(); i != textures_.end(); )
	{
		if (!i->second.lock())
		{
			textures_.erase(i);
		}
		else
		{
			i++;
		}
	}
}
