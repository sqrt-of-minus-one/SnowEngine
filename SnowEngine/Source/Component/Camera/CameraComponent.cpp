    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: CameraComponent.h           //
////////////////////////////////////////

#include "CameraComponent.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "../../Level/Level.h"
#include "../../Actor/Actor.h"
#include "../Visible/VisibleComponent.h"
#include "../../Game/Game.h"
#include "../../Game/Config.h"

using namespace snow;

		/* CameraComponent: public */

CameraComponent::CameraComponent(Actor& actor, Component* parent, const Transform& transform) :
	Component(actor, parent, transform),
	view_()
{
	camera_components_[&get_level()].push_back(this);

	view_.setCenter(transform.get_position().get_x(), transform.get_position().get_y());
	view_.setRotation(transform.get_rotation().get_degrees());
	view_.setSize(Game::config.resolution.get_x(), Game::config.resolution.get_y());
	// Todo: scale
}

CameraComponent::~CameraComponent()
{
	auto& list = camera_components_[&get_level()];
	for (auto i = list.begin(); i != list.end(); i++)
	{
		if (*i == this)
		{
			list.erase(i);
			break;
		}
	}
	if (list.empty())
	{
		camera_components_.erase(&get_level());
	}
}

FloatRect CameraComponent::get_viewport() const
{
	sf::FloatRect viewport = view_.getViewport();
	return FloatRect(Vector2(viewport.left, viewport.top), Vector2(viewport.width, viewport.height));
}

void CameraComponent::set_viewport(const FloatRect& rect)
{
	view_.setViewport(sf::FloatRect(rect.get_position().get_x(), rect.get_position().get_y(),
									rect.get_size().get_x(), rect.get_size().get_y()));
}

const std::map<const Level*, std::list<CameraComponent*>>& CameraComponent::get_camera_components()
{
	return camera_components_;
}

		/* CameraComponent: protected */

void CameraComponent::tick(float delta_sec)
{
	Component::tick(delta_sec);

	std::shared_ptr<sf::RenderWindow> window = Game::get_window().lock();
	const auto& all_visible_components = VisibleComponent::get_visible_components();
	if (window && all_visible_components.find(&get_level()) != all_visible_components.end())
	{
		window->setView(view_);
		const auto& visible_components = all_visible_components.at(&get_level());
		for (auto& i : visible_components)
		{
			if (Object::is_valid(i))
			{
				i->draw(*window);
			}
		}
	}
}

void CameraComponent::when_transformed(const Transform& new_level_transform)
{
	Component::when_transformed(new_level_transform);

	view_.setCenter(new_level_transform.get_position().get_x(), new_level_transform.get_position().get_y());
	view_.setRotation(new_level_transform.get_rotation().get_degrees());
	// Todo: scale
}

std::map<const Level*, std::list<CameraComponent*>> CameraComponent::camera_components_;
