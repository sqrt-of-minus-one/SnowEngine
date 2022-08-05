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
	view_.setCenter(transform.get_position().get_x(), transform.get_position().get_y());
	view_.setRotation(transform.get_rotation().get_degrees());
	view_.setSize(Game::config.resolution.get_x(), Game::config.resolution.get_y());
	// Todo: scale

	on_transformed.bind<CameraComponent>(*this, &CameraComponent::update_view_);
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

		/* CameraComponent: private */

void CameraComponent::update_view_(Component& component, const Transform& old_transform, const Transform& new_transform)
{
	view_.setCenter(new_transform.get_position().get_x(), new_transform.get_position().get_y());
	view_.setRotation(new_transform.get_rotation().get_degrees());
	// Todo: scale
}
