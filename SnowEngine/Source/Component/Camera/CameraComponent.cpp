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

DoubleRect CameraComponent::get_viewport() const
{
	sf::FloatRect viewport = view_.getViewport();
	return DoubleRect(Vector2(viewport.left, viewport.top), Vector2(viewport.width, viewport.height));
}

void CameraComponent::set_viewport(const DoubleRect& rect)
{
	view_.setViewport(sf::FloatRect(rect.get_position().get_x(), rect.get_position().get_y(),
									rect.get_size().get_x(), rect.get_size().get_y()));
}

const std::map<const Level*, std::list<CameraComponent*>>& CameraComponent::get_camera_components()
{
	return camera_components_;
}

EventBinder<sf::RenderWindow& /*window*/>& CameraComponent::on_draw(const Level& level, int layer)
{
	std::map<int, EventBinder<sf::RenderWindow&>>& map = on_draw_binder_[&level];
	auto binder_iter = map.find(layer);
	if (binder_iter != map.end())
	{
		return *bindre_iter;
	}

	on_draw_[&level].insert({ layer, Event<sf::RenderWindow>() });
	map.insert({ layer, EventBinder<sf::RenderWindow>(on_draw_[&level][layer]) });
	return map[layer];
}

		/* CameraComponent: protected */

void CameraComponent::tick(double delta_sec)
{
	Component::tick(delta_sec);

	std::shared_ptr<sf::RenderWindow> window = Game::get_window().lock();
	auto map_iter = on_draw_.find(&get_level());
	if (window && map_iter != on_draw_.end())
	{
		window->setView(view_);
		for (auto& [k, v] : map_iter->second)
		{
			v.execute(*window);
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

std::map<const Level*, std::map<int /*layer*/, Event<>>> CameraComponent::on_draw_;
std::map<const Level*, std::map<int /*layer*/, EventBinder<>>> CameraComponent::on_draw_binder_;
std::map<const Level*, std::list<CameraComponent*>> CameraComponent::camera_components_;
