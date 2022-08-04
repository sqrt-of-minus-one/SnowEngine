    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: CameraComponent.h           //
////////////////////////////////////////

#pragma once

#include "../Component.h"

#include <SFML/Graphics/View.hpp>

namespace sf
{
class RenderWindow;
}

namespace snow
{

class Actor;

class CameraComponent : public Component
{
public:
	CameraComponent(Actor& actor, std::weak_ptr<Component> parent, const Transform& transform);

protected:
	virtual void tick(float delta_sec) override;

private:
	sf::View view_;
	sf::RenderWindow& window_;

	void update_view_(Component& component, const Transform& old_transform, const Transform& new_transform);
};

}
